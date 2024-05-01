#include <iostream>
#include <string.h>
#include <chrono>
#include <atomic>
#include <thread>
#include <pthread.h>
#include <mutex>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include "graph.h"
#include "estimating.h"

using namespace std;

double used_c = 0;
double max_c = 0;
double avg_c = 0;
double median_c = 0;
long double scaled_h = 0;

/* Application 5: Multi-threaded counting arbitrary pattern
* sampling times, #threads
* note: sampling times now is #sampling trees, may be larger than sampled profiles
*/
tuple<double, double, uint64_t> multi_thread_pattern_counting(Graph &large_graph, Pattern &graph_pattern, uint64_t sampling_times,
                                   uint32_t num_threads) {
    uint32_t lost_edge_cases[100];
    // overall stats
    atomic<uint64_t> global_sampled_times(0);                        // global finished sampling times
    double global_prob_inverse = 0.0;                          // global prob inverse
    long double global_sum_sq = 0.0;

    uint32_t sampling_step = sampling_times / num_threads; 
    vector<uint32_t> worker_sampling_times(num_threads, sampling_step);
    for (uint32_t t = 0; t < sampling_times % num_threads; t++)
        worker_sampling_times[t] += 1;

    // multi-thread variables
    vector <unique_ptr<thread>> workers(num_threads);      // thread pool
    std::mutex iomutex;                                    // to cleanly print something
    atomic<bool> running_flag(true);                    // signal to stop threads

    for (uint32_t t = 0; t < num_threads; t++) { // Spawn threads
        workers[t] = make_unique<thread>([&, t]() {
            random_device sd;
            default_random_engine this_rand_generator(sd());
            uint32_t thread_id = t;

            {
                std::lock_guard <std::mutex> iolock(iomutex);
                /*
                cout << "=== this is thread " << thread_id << " starting to count" << endl;
                */
            }

            // sampling small step by step, until global_sampled_times == sampling_times
            double this_prob_inverse, thread_prob_inverse;
            uint64_t thread_sampled_times, this_sampling_times;
            thread_prob_inverse = 0.0;
            thread_sampled_times = 0;
            long double this_sum_sq, thread_sum_sq;
            //this_sum_sq = 0.0;
            thread_sum_sq = 0.0;

        
            //tie(this_prob_inverse, this_sampling_times) = estimate_pattern(large_graph, graph_pattern, worker_sampling_times[t],lost_edge_cases/*, this_rand_generator*/);
            vector<double> datapoints = ASAP_estimate_4_clique_all(large_graph,worker_sampling_times[t],this_rand_generator);
            this_prob_inverse = 0.0;
            this_sum_sq = 0.0;
            int num0 = 0;
            double maximum = 0;
            double minimum = 1e99;
            for (double sample: datapoints) {
                this_prob_inverse += sample;
                this_sum_sq += (long double) sample*sample;
                num0 += (sample == 0);
                maximum = max(maximum,sample);
                if (sample > 0) minimum = min(minimum,sample);
            }
            cout << num0 << " zeros out of " << datapoints.size() << endl;
            cout << "maximum is " << maximum << endl;
            cout << "minimum is " << minimum << endl;

            // only change sampled times not prob_inverse, since there is no support of atomic double
            global_sampled_times += worker_sampling_times[t];

            thread_sampled_times += worker_sampling_times[t];
            thread_prob_inverse += this_prob_inverse;
            thread_sum_sq += this_sum_sq;

            // cout << global_sampled_times << " " << sampling_times << endl;

            {
                std::lock_guard <std::mutex> iolock(iomutex);
                /*
                 cout << "=== thread " << thread_id << " is to stop, finished " << thread_sampled_times
                     << " sampling, prob_inverse: " << thread_prob_inverse << endl;
                */
                global_prob_inverse += thread_prob_inverse;
                global_sum_sq += thread_sum_sq;
            }

            return;
        });
    }



    //  main thread: test stop and merge results
    auto start = chrono::high_resolution_clock::now();
    for (auto &worker : workers) {
        worker->join();
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    // cout << "***** main: all threads finished " << endl;

    // cout << "raw results after merge threads (total_prob_inverse, total_sampled_times): " << global_prob_inverse << " "
    //      << global_sampled_times << endl;
    double estimated_pattern_count = global_prob_inverse / global_sampled_times;
    // cout << "pattern_nums time_consumed(us) sampling_times sampling/second\n" << estimated_pattern_count << " " << duration.count()
    //      << " " << global_sampled_times << " " << global_sampled_times * 1.0 / duration.count() * 1000000 << endl;
    long double estimated_variance = global_sum_sq / global_sampled_times - estimated_pattern_count*estimated_pattern_count;
    double estimated_standard_deviation = sqrt(estimated_variance);
    return make_tuple(estimated_pattern_count, estimated_standard_deviation, duration.count());
}

tuple<vector<double>, vector<double> > infer_constant(Graph &sampled_subgraph, Pattern &pattern, uint32_t num_threads, long double &ground_truth)
{
    // uint64_t right_num_estimators = 1000000000;
    uint64_t left_num_estimators = 10000; // starting from 1e8
    uint64_t this_time_consumed = 0;
    // double this_estimated_pattern_count[10] = {0,0,0,0,0,0,0, 0, 0, 0};
    double this_estimated_pattern_count[3] = {0, 0, 0}; // reduce to 3 points per #estimators
    double this_estimated_standard_deviation[3] = {0, 0, 0}; // reduce to 3 points per #estimators

    vector<vector<double> > total_estimated_pattern_count;
    vector<double> estimated_error;
    vector<double> estimated_ground_truth;

    while (1)
    {
        double avg_estimated_error = 0;
        double avg_estimated_ground_truth = 0;
        vector<double> tmp;
        cout << "left_num_estimators = " << left_num_estimators << endl;
        for (int i = 0; i < 3; i++)
        {
            tie(this_estimated_pattern_count[i], this_estimated_standard_deviation[i], this_time_consumed) = multi_thread_pattern_counting(sampled_subgraph, pattern, left_num_estimators, num_threads);
            // avg_estimated_error += abs(this_estimated_pattern_count[i] - ground_truth) / ground_truth;
            avg_estimated_ground_truth += this_estimated_pattern_count[i];
            tmp.push_back(this_estimated_pattern_count[i]);
            cout << "this_estimated_pattern_count[i] = " << this_estimated_pattern_count[i] << endl;
            cout << "this_estimated_standard_deviation[i] = " << this_estimated_standard_deviation[i] << endl;
        }
        // avg_estimated_error /= 10.0;
        avg_estimated_ground_truth /= 3.0;
        
        // estimated_error.push_back(avg_estimated_error);
        estimated_ground_truth.push_back(avg_estimated_ground_truth);
        total_estimated_pattern_count.push_back(tmp);
        
        if (estimated_ground_truth.size() > 1)
        {
            double tmp1 = estimated_ground_truth.back();
            double tmp2 = estimated_ground_truth[estimated_ground_truth.size() - 2];
            double min1 = tmp1, max1 = tmp1, min2 = tmp2, max2 = tmp2;
            for (int i = 0; i < 3; i++)
            {
                min1 = min(min1, total_estimated_pattern_count.back()[i]);
                min2 = min(min2, total_estimated_pattern_count[total_estimated_pattern_count.size() - 2][i]);
                max1 = max(max1, total_estimated_pattern_count.back()[i]);
                max2 = max(max2, total_estimated_pattern_count[total_estimated_pattern_count.size() - 2][i]);
            }
            if ((tmp1 != 0 && tmp2 != 0) && abs(tmp1 - tmp2) / tmp1 < 0.05)
            {
                cout << tmp1 << " " << tmp2 << endl;
                cout << (max2 - min2) / tmp2 << " " <<  (max1 - min1) / tmp1 << endl;
                if ((max2 - min2) / tmp2 < 0.1 && (max1 - min1) / tmp1 < 0.1)
                    break;
            }
        }

        left_num_estimators *= 10;
    }
    
    uint64_t left_1 = 10000; // 1e8
    ground_truth = estimated_ground_truth.back();
    cout << "estimated_ground_truth = " << ground_truth << endl;
    for (int j = 0; j < total_estimated_pattern_count.size(); j++)
    {
        double avg_estimated_error = 0;
        for (int i = 0; i < 3; i++)
        {
            avg_estimated_error += abs(total_estimated_pattern_count[j][i] - ground_truth) / ground_truth;   
        }
        avg_estimated_error /= 3.0;
        cout << "avg_estimated_error = " << avg_estimated_error << endl;
        
        estimated_error.push_back(avg_estimated_error);

        left_num_estimators *= 10;
    }

    return make_tuple(estimated_error, estimated_ground_truth);
}

/*
tuple<uint64_t, uint64_t> error_profile(Graph &graph, Pattern &pattern, Graph &sampled_subgraph, double expected_err, double delta, uint32_t num_threads, uint32_t sampling_ratio, double ground_truth)
{
    uint64_t m_sub = sampled_subgraph.total_edges_;
    uint64_t m_large = graph.total_edges_;
    long double rho_H = pattern.fractional_cover_value;
    uint64_t num_estimators = 0;
    long double h = 0.0;
    
    auto start = chrono::high_resolution_clock::now();

    // h will get from a sampled subgraph, and calculate constant c from the equation
    h = ground_truth;

    // scale h to large graph by sampling ratio
    // cout << "edge = " << pattern.edge_count << endl;
    // cout << 1 / pow((long double)sampling_ratio / 100.0, pattern.edge_count) << endl;
    scaled_h = h / pow((long double)sampling_ratio / 100.0, pattern.edge_count);
    cout << "scaled_h = " << scaled_h << endl;

    // calculate large graph's count 
    num_estimators = ceil(used_c * 1.0 / delta * (long double)pow(m_large, rho_H) / scaled_h * (long double)expected_err * (long double)expected_err);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    // cout << "num_estimators = " << num_estimators << endl;
    // cout << "duration.count() = " << duration.count() << endl;

    return make_tuple(num_estimators, duration.count());
}
*/
int main(int argc, char *argv[]) {
    // Parse running parameters
    if (argc < 8) {
        cout << "Counting #subgraphs in a large graph \n"
             << "Usage: GraphCounting graph_file pattern_file subgraph_file sampling_times_vector #threads sampling_ratio(%) delta"
             << endl;
        return 1;
    }

    string graph_file_path = argv[1];
    string pattern_file_path = argv[2];
    string subgraph_file_path = argv[3];
    uint32_t num_threads = stoi(argv[5]);
    uint32_t sampling_ratio = stoi(argv[6]);
    double delta = stod(argv[7]); // 1 - confidence level
    // uint64_t ground_truth = stol(argv[8]);
    //uint32_t sampling_times = stoi(argv[4]);
    stringstream ss(argv[4]);


    vector <uint32_t> sampling_times_vector;
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        sampling_times_vector.push_back(stoi(substr));
    }

    /* Load Graphs and Pattern */
    // Create, load graph
    Graph large_graph(graph_file_path);
    large_graph.load_binary();

    // Application: counting arbitrary pattern in the graph
    Pattern graph_pattern(pattern_file_path);
    graph_pattern.load();

    Graph sampled_subgraph(subgraph_file_path);
    sampled_subgraph.load_binary();

    random_device sd;
    default_random_engine this_rand_generator(sd());
    ofstream outfile("errors5.csv",ios::app);
    for (int run = 1; run <= 3; run++) {
        cout << "sampling..." << endl;
        vector<double> datapoints = ASAP_estimate_4_clique_all(large_graph,1e7,this_rand_generator);
        double sum = 0,sumsq = 0,sumcb = 0;
        for (int i = 1; i <= datapoints.size(); i++) {
            sum += datapoints[i-1];
            sumsq += datapoints[i-1]*datapoints[i-1];
            sumcb += datapoints[i-1]*datapoints[i-1]*datapoints[i-1];
            double stdev = sqrt(((sumsq/i)-(sum/i)*(sum/i))/i);
            if ((i % 100) == 0) {
                outfile << graph_file_path << "," << pattern_file_path << "," << run << ",";
                outfile << i << "," << sum/i << "," << ((sum == 0) ? 0:(stdev/(sum/i))) << ",";
                outfile << ((stdev == 0) ? 0:((sumcb/i+2*pow(sum/i,3)-3*(sum/i)*(sumsq/i))/pow(i,2)/pow(stdev,3))) << endl;
            }
        }
    }
    return 0;
/*
    random_device sd;
    default_random_engine this_rand_generator(sd());
    cout << "sampling..." << endl;
    vector<double> datapoints = ASAP_estimate_4_clique_all(large_graph,1e7,this_rand_generator);
    double sum = 0;
    for (int i = 1; i <= datapoints.size(); i++) {
        sum += datapoints[i-1];
        if ((i % 100000) == 0) cout << i << ": " << sum/i << endl;
    }
    int times = 1000;
    ofstream outfile("errors.txt");
    while (times--) {
        double sum2 = 0;
        for (int i = 0; i < 1e6; i++) sum2 += datapoints[this_rand_generator() % datapoints.size()];
        outfile << (sum2/1e6-sum/datapoints.size())/(sum/datapoints.size()) << endl;
    }
    return 0;
*/
    /* Error Profile */
    // for draw the ELP lines:
    vector<double> expected_err = {5, 6, 10, 20, 40, 50, 60, 80, 100}; // 1 / error_rate
    // for estimating sampling times of running time comparison
    // vector<double> expected_err = {20}; // 1 / error_rate
    vector<double> estimated_pattern_count_vector;
    vector<uint64_t> num_estimators_vector;
    vector<uint64_t> error_profile_time;
    uint64_t this_time_consumed = 0;
    uint64_t this_num_estimators = 0;
    double this_estimated_pattern_count = 0.0;

    long double estimated_ground_truth = 0.0;
    uint64_t right_num_estimators = 1000000000; // large enough?
    // Step 1: estimate ground truth of sampled subgraph
    /*
    tie(estimated_ground_truth, this_time_consumed) = multi_thread_pattern_counting(sampled_subgraph, graph_pattern, right_num_estimators, num_threads);
    cout << "estimated_ground_truth = " << estimated_ground_truth << endl;

    if (estimated_ground_truth == 0) 
        return 0;
    */

    // Step 2: build error profile
    uint64_t m_sub = sampled_subgraph.total_edges_;
    uint64_t m_large = large_graph.total_edges_;
    //long double rho_H = graph_pattern.fractional_cover_value;
    double c = 0;
    vector<double> estimated_error;
    vector<double> C_estimated_ground_truth;
    tie(estimated_error, C_estimated_ground_truth) = infer_constant(sampled_subgraph, graph_pattern, num_threads, estimated_ground_truth);

    cout << "*************************************" << endl;
    cout << "estimated_error:" << endl;
    for (auto error: estimated_error) cout << error << " ";
    cout << endl;
    cout << "C_estimated_ground_truth:" << endl;
    for (auto truth: C_estimated_ground_truth) cout << truth << " ";
    cout << endl;

    uint32_t max_deg = 0;
    for (auto [x,y]: large_graph.v_table_) max_deg = max(max_deg,large_graph.degree(x));
    cout << "max_deg = " << max_deg << endl;
    uint64_t N = sampled_subgraph.total_vertex_;
    uint64_t M = sampled_subgraph.total_edges_;
    uint64_t Ne = 10000;
    for (int i = 0; i < C_estimated_ground_truth.size()-1; i++) Ne *= 10;
    double ground_truth = C_estimated_ground_truth.back();
    double eps = estimated_error.back();

    double K = Ne*pow(eps,2)*ground_truth/((double) M*pow((double) max_deg,graph_pattern.vertex_count-2));
    cout << "K = " << K << endl;

    double h = C_estimated_ground_truth.back();
    uint64_t left_num_estimators = 10000; // 1e8
    vector<double> constant;
    uint32_t num_c = 0;
    long double large_graph_estimated_ground_truth = 0;
    for (uint32_t i = 0; i < estimated_error.size(); i++)
    {
        c = left_num_estimators * h * estimated_error[i] * estimated_error[i] / pow(m_sub, 1.5/*FOR TRIANGLES ONLY*/);
        cout << "Arya c = " << c << endl;
        c = left_num_estimators * h * estimated_error[i] * estimated_error[i] / ((double) M*pow((double) max_deg,graph_pattern.vertex_count-2));
        cout << "number_estimators = " << left_num_estimators << " K(z) = " << c << " estimated_error = " << estimated_error[i] << endl;
        if (estimated_error[i] <= 0.05)
        {
            avg_c += c;
            max_c = max(max_c, c);
            num_c ++;
            constant.push_back(c);
        }
        left_num_estimators *= 10;
    }

    if (num_c != 0)
        avg_c = avg_c / num_c;

        
    
    sort(constant.begin(), constant.end());
    if (constant.size() != 0) 
    {
        if (constant.size() % 2 == 0)
        {
            median_c = constant[constant.size() / 2] + constant[constant.size() / 2 - 1];
        }
        else median_c = constant[constant.size() / 2];
    }

    cout << "max_c = " << max_c << endl;
    cout << "avg_c = " << avg_c << endl;
    cout<< "median_c = " << median_c << endl;

    used_c = max_c;
    //ofstream outfile("data.txt",std::ios_base::app);
    //outfile << graph_file_path << " " << pattern_file_path << ": K = " << max_c << endl;

    return 0;
/*

    // estimated_ground_truth = C_estimated_ground_truth.back();
    for (uint32_t i = 0; i < expected_err.size(); i++)
    {
        tie(this_num_estimators, this_time_consumed) = error_profile(large_graph, graph_pattern, sampled_subgraph, expected_err[i], delta, num_threads, sampling_ratio, estimated_ground_truth);
        num_estimators_vector.push_back(this_num_estimators);
        error_profile_time.push_back(this_time_consumed);
    }


    cout << "Curve constant = " << setprecision(16) << used_c * (long double)pow(m_large, rho_H) * 1 / delta / scaled_h << endl;
*/
/*
    // Step 3: get real error and error bar with 10 times run
    vector<double> last_pattern_count;
    for (uint32_t i = 0; i < expected_err.size(); i++)
    {
        // get real error and error bar for 10 times run
        // TODO: get more points on the right side: e.g. left_number_estimators *= 2;
        for (uint32_t j = 0; j < 10; j++)
        {
            tie(this_estimated_pattern_count, this_time_consumed) = multi_thread_pattern_counting(large_graph, graph_pattern, num_estimators_vector[i], num_threads);
            estimated_pattern_count_vector.push_back(this_estimated_pattern_count);
            cout << "#estimators = " << num_estimators_vector[i] << " " << "#pattern = " << this_estimated_pattern_count << " " << "runtime(us) = " << this_time_consumed << endl;
            if (i == expected_err.size() - 1)
            {
                last_pattern_count.push_back(this_estimated_pattern_count);
            }
        }
    }
    sort(last_pattern_count.begin(), last_pattern_count.end());
    large_graph_estimated_ground_truth = (last_pattern_count[4] + last_pattern_count[5]) / 2;
   

    // print points for drawing profiled worst-case error line
    for (uint32_t i = 0; i < num_estimators_vector.size(); i++)
        cout << num_estimators_vector[i] << ' ';
    cout << endl;

    
    for (uint32_t i = 0; i < error_profile_time.size(); i++)
        cout << error_profile_time[i] << ' ';
    cout << endl;
    */
/*

    // print points for drawing median real error and error bar
    for (uint32_t i = 0; i < estimated_pattern_count_vector.size(); i++)
        cout << setprecision(16) << estimated_pattern_count_vector[i] << ' ';
    cout << endl;

    cout << used_c << endl;
    cout << large_graph_estimated_ground_truth << endl;
    cout << (long double)pow(m_large, rho_H) * 1 / delta << endl;
*/

    return 0;
}
