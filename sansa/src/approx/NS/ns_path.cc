#include "graph.h"
#include "sample.hh"
//#include "asap.hh"

void sample_3path(Graph &g, eidType num_samples, uint64_t &total);
void sample_3path_vertex_induced(Graph &g, eidType num_samples, uint64_t &total);
void sample_odd_path(Graph &g, int k, eidType num_samples, uint64_t &total);
void sample_path_sb(Graph &g, int k, eidType num_samples, uint64_t &total); // with symmetry breaking
void sample_path(Graph &g, int k, eidType num_samples, uint64_t &total);
void sample_path_ASAP(Graph &g, int k, eidType num_samples, uint64_t &total);

int main(int argc, char* argv[]) {
  if (argc < 4) {
    std::cout << "Usage: " << argv[0] << " <graph> <path_nodes> <num_samples>\n";
    std::cout << "Example: " << argv[0] << " ../../inputs/mico/graph 3 1000\n";
    exit(1);
  }
  Graph g(argv[1]);
  g.print_meta_data();

  int k = atoi(argv[2]); // number of vertices in the path
  assert(k > 2);
  std::cout << "Finding " << k << "-path\n";
  eidType num_samples = atoi(argv[3]);
  std::cout << "num_samples: " << num_samples << "\n";

  Timer t;
  t.Start();
  uint64_t total = 0;
  //sample_3path_vertex_induced(g, num_samples, total);
  sample_path_sb(g, k, num_samples, total);
  //sample_path(g, k, num_samples, total);
  //sample_path_ASAP(g, k, num_samples, total);
  t.Stop();
  std::cout << "runtime = " << t.Seconds() << " sec\n";
  std::cout << "Estimated count " << FormatWithCommas(total) << "\n";
}

void sample_path_ASAP(Graph &g, int k, eidType num_samples, uint64_t &total) {
  auto m = g.init_edgelist();
  double global_counter = 0.0;
  int num_threads = 1;
  #pragma omp parallel
  {
    num_threads = omp_get_num_threads();
  }
  std::cout << "Using " << num_threads << " threads\n";
  //assert(num_samples%num_threads == 0);
  auto num_samples_per_thread = num_samples / num_threads;
  std::uniform_int_distribution <eidType> edge_dist(0, m-1);
  #pragma omp parallel reduction(+:global_counter)
  {
    random_device sd;
    default_random_engine my_rng(sd());
    double counter = 0.;
    for (int i = 0; i < num_samples_per_thread; i++) {
      auto eid = edge_dist(my_rng);
      std::vector<vidType> path_vertex_set;
      counter += path_sampler(g, k, eid, my_rng, path_vertex_set);
    }
    global_counter += counter;
  }
  total = global_counter * m / num_samples / (1 << (k-1)); // symmetry breaking
}

void sample_path(Graph &g, int k, eidType num_samples, uint64_t &total) {
  auto m = g.init_edgelist();
  double counter = 0;
  int num_threads = 1;
  #pragma omp parallel
  {
    num_threads = omp_get_num_threads();
  }
  std::cout << "OpenMP (" << num_threads << " threads)\n";
  //assert(num_samples%num_threads == 0);
  auto num_samples_per_thread = num_samples / num_threads;
  std::uniform_int_distribution<eidType> edge_dist(0, m-1);
  #pragma omp parallel reduction(+ : counter)
  {
    std::random_device rd;
    rd_engine gen(rd());
    for (eidType i = 0; i < num_samples_per_thread; i++) {
      auto eid = edge_dist(gen);
      double scale = m;
      vidType extender[2];
      extender[0] = g.get_src(eid);
      extender[1] = g.get_dst(eid);
      VertexSet vs;
      vs.add(extender[0]);
      vs.add(extender[1]);
      sort_vertexset(vs);
      for (int j = 2; j < k; j++) {
        if (extender[0] > extender[1]) std::swap(extender[0], extender[1]);
        vidType c = 0;
        if (j == k-1) {
          auto c0 = difference_num(g.N(extender[0]), vs);
          assert(c0 >= 0);
          auto c1 = difference_num(g.N(extender[1]), vs);
          assert(c1 >= 0);
          c = c0 + c1;
        } else {
          VertexSet candidate_set0;
          VertexSet candidate_set1;
          difference_set(candidate_set0, g.N(extender[0]), vs);
          assert(candidate_set0.size() >= 0);
          difference_set(candidate_set1, g.N(extender[1]), vs);
          assert(candidate_set1.size() >= 0);
          c = candidate_set0.size() + candidate_set1.size();
          if (c == 0) { scale = 0; break; }
          auto id = random_select_single(0, c-1, gen);
          vidType v = 0;
          if (id < candidate_set0.size()) {
            v = candidate_set0[id];
            extender[0] = v;
          } else {
            v = candidate_set1[id-candidate_set0.size()];
            extender[1] = v;
          }
          vs.add(v);
          sort_vertexset(vs);
        }
        if (c == 0) { scale = 0; break; }
        scale *= c;
      }
      counter += scale;
    }
  }
  total = counter / num_samples / (1 << (k-1));
}

void sample_path_sb(Graph &g, int k, eidType num_samples, uint64_t &total) {
  g.init_simple_edgelist();
  eidType m = g.E();
  __int128_t counter = 0;
  int num_threads = 1;
  #pragma omp parallel
  {
    num_threads = omp_get_num_threads();
  }
  std::cout << "OpenMP (" << num_threads << " threads)\n";
  //assert(num_samples%num_threads == 0);
  auto num_samples_per_thread = num_samples / num_threads;

  std::random_device rd;
  rd_engine gens[num_threads];

  for(int t = 0; t < num_threads; t++) {
    gens[t] = rd_engine(rd());
  }

  #pragma omp parallel reduction(+ : counter) 
  {
  std::uniform_int_distribution<eidType> edge_dist(0, m-1);

  // std::random_device rd;
  // rd_engine gen(rd());
  for (eidType i = 0; i < num_samples_per_thread; i++) {
    auto eid = edge_dist(gens[omp_get_thread_num()]);
    uint64_t scale = m;
    auto v0 = g.get_src(eid);
    auto v1 = g.get_dst(eid);
    VertexSet vs;
    vs.add(v0);
    vs.add(v1);
    sort_vertexset(vs);
    vidType v = v1;
    for (int j = 2; j < k; j++) {
      vidType c = 0;
      if (j == k-1) {
        c = difference_num(g.N(v), vs, v0); // v0 is used for symmetry breaking
      } else {
        VertexSet candidate_set;
        difference_set(candidate_set, g.N(v), vs);
        c = candidate_set.size();
        if (c == 0) { scale = 0; break; }
        auto id = random_select_single(0, c-1, gens[omp_get_thread_num()]);
        v = candidate_set[id];
        vs.add(v);
        sort_vertexset(vs);
      }
      if (c == 0) { scale = 0; break; }
      scale *= c;
    }
    counter += scale;
  }
  }
  total = counter / num_samples; // scale down by number of samples
}

void sample_3path(Graph &g, eidType num_samples, uint64_t &total) {
  auto m = g.init_edgelist(true);
  __int128_t counter = 0;
  int num_threads = 1;
  #pragma omp parallel
  {
    num_threads = omp_get_num_threads();
  }
  std::cout << "OpenMP (" << num_threads << " threads)\n";
  std::uniform_int_distribution<eidType> edge_dist(0, m-1);
  #pragma omp parallel
  {
    std::random_device rd;
    rd_engine gen(rd());
    #pragma omp for reduction(+ : counter) //schedule(dynamic, 1)
    for (eidType i = 0; i < num_samples; i++) {
      auto eid = edge_dist(gen);
      auto v0 = g.get_src(eid);
      auto v1 = g.get_dst(eid);
      auto d0 = g.get_degree(v0);
      auto d1 = g.get_degree(v1);
      if (d0 < 1 || d1 < 1) continue;
      VertexSet vs;
      vs.add(v0);
      vs.add(v1);
      sort_vertexset(vs);
      VertexSet candidate_set;
      difference_set(candidate_set, g.N(v0), vs);
      auto c0 = candidate_set.size();
      if (c0 == 0) continue;
      auto idx0 = random_select_single(0, c0-1, gen);
      auto v2 = candidate_set[idx0];
      vs.add(v2);
      sort_vertexset(vs);
      auto c1 = difference_num(g.N(v1), vs);
      if (c1 == 0) continue;
      counter += m * c0 * c1;
    }
  }
  total = counter / num_samples; // scale down by number of samples
}

void sample_3path_vertex_induced(Graph &g, eidType num_samples, uint64_t &total) {
  auto m = g.init_edgelist(true);
  std::cout << "sample space: " << m << "\n";
  double counter = 0;
  int num_threads = 1;
  #pragma omp parallel
  {
    num_threads = omp_get_num_threads();
  }
  std::cout << "OpenMP (" << num_threads << " threads)\n";
  std::uniform_int_distribution<eidType> edge_dist(0, m-1);

  std::random_device rd;
  rd_engine gens[num_threads];

  for(int t = 0; t < num_threads; t++) {
    gens[t] = rd_engine(rd());
  }

  #pragma omp parallel
  {
    #pragma omp for reduction(+ : counter) //schedule(dynamic, 1)
    for (eidType i = 0; i < num_samples; i++) {
      auto &gen = gens[omp_get_thread_num()];
      auto eid = edge_dist(gen);
      auto v0 = g.get_src(eid);
      auto v1 = g.get_dst(eid);
      auto d0 = g.get_degree(v0);
      auto d1 = g.get_degree(v1);
      if (d0 < 2 || d1 < 2) continue;
      VertexSet vs;
      vs.add(v1);

      auto y0 = difference_set(g.N(v0), vs);
      auto y0n1 = difference_set(y0, g.N(v1));
      auto c0 = y0n1.size();
      if (c0 == 0) continue;
      auto idx0 = random_select_single(0, c0-1, gen);
      auto v2 = y0n1[idx0];

      vs.add(v0);
      vs.add(v2);
      sort_vertexset(vs);
      auto y1 = difference_set(g.N(v1), vs);
      auto y1n0 = difference_set(y1, g.N(v0));
      auto c1 = difference_num(y1n0, g.N(v2));
      if (c1 == 0) continue;
      counter += c0 * c1;
    }
  }
  total = counter * m / num_samples; // scale down by number of samples
}

void sample_odd_path(Graph &g, int k, eidType num_samples, uint64_t &total) {
  assert(k>2 && k%2 == 0);
  int steps = k / 2;
  auto m = g.init_edgelist(true);
  double counter = 0;
  int num_threads = 1;
  #pragma omp parallel
  {
    num_threads = omp_get_num_threads();
  }
  std::cout << "OpenMP (" << num_threads << " threads)\n";
  std::uniform_int_distribution<eidType> edge_dist(0, m-1);
  #pragma omp parallel
  {
    std::random_device rd;
    rd_engine gen(rd());
    #pragma omp for reduction(+ : counter) //schedule(dynamic, 1)
    for (eidType i = 0; i < num_samples; i++) {
      auto eid = edge_dist(gen);
      auto v0 = g.get_src(eid);
      auto v1 = g.get_dst(eid);
      auto d0 = g.get_degree(v0);
      auto d1 = g.get_degree(v1);
      if (d0 < 1 || d1 < 1) continue;
      VertexSet vs;
      vs.add(v0);
      vs.add(v1);
      double scale = m;
      vidType w0 = v0;
      vidType w1 = v1;
      // each step we extend two edges
      for (int s = 0; s < steps; s++) {
        sort_vertexset(vs);
        VertexSet candidate_set0;
        difference_set(candidate_set0, g.N(w0), vs);
        auto c0 = candidate_set0.size();
        if (c0 == 0) { scale = 0; break; }
        auto idx0 = random_select_single(0, c0-1, gen);
        w0 = candidate_set0[idx0];
        vs.add(w0);
        sort_vertexset(vs);
        VertexSet candidate_set1;
        difference_set(candidate_set1, g.N(w1), vs);
        auto c1 = candidate_set1.size();
        if (c1 == 0) { scale = 0; break; }
        if (s != steps-1) {
          auto idx1 = random_select_single(0, c1-1, gen);
          w1 = candidate_set1[idx1];
          vs.add(w1);
        }
        scale *= c0 * c1;
      }
      counter += scale;
    }
  }
  total = counter / num_samples; // scale down by number of samples
}

