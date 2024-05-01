import os
import re
import statistics

graph_name = "patent_citations.undigraph"
pattern = "6_clique"
program = "ASAP_single_machine/GraphCounting.out"

#files = ["tc_sample_omp_base", "tc_sample_edge_stream_args"]

arg_vals = ["500000", "1000000", "5000000", "10000000","50000000"]#,"100000000","1000000000"]
depth = 1

def gen_args(depth):
    if(depth == 0):
        return [[]]
    
    output = []
    for i in gen_args(depth-1):
        for j in arg_vals:
            new_item = i[:]
            new_item.append(j)
            output.append(new_item)
    
    return output

#files = ["4cc_sample_omp_base", "4cc_sample_color_sparse", "4cc_sample_edge_sparse", "4cc_sample_edge_stream_v0"]
#files = ["clique_sample_omp_base", "clique_sample_color_sparse", "clique_sample_edge_sparse"]


# print('./../GraphMiner/bin/'+files[0]+' ../GraphMiner/inputs/' + graph_name + '/graph')
# var = os.popen('./../GraphMiner/bin/'+files[0]+' ../GraphMiner/inputs/' + graph_name + '/graph').read()
# m = re.search('total_num_pattern = ([0-9]+)', var)
# count = m.group(1)
# m = re.search('runtime \[\w+\] = ([0-9.]+) sec', var)
# time = m.group(1)
# base = float(count)
# base_time = float(time)

base = 3132860
base_time = 145.491
print("base count: "+ str(base)+ "\nbase time: "+ str(base_time))

print(gen_args(depth))

results = {}
for i in gen_args(depth):
    print(f"mpirun -n 4 ./graph_counting/src/{program} {graph_name} graph_counting/patterns/{pattern} {i[0]} 40 4")
    var = os.popen(f"mpirun -n 4 ./graph_counting/src/{program} {graph_name} graph_counting/patterns/{pattern} {i[0]} 40 4").read() 
    m = re.findall('([0-9.]+) ([0-9.]+) ([0-9.]+) ([0-9.]+)', var)
    results[" ".join(i)] = [[float(time) / 1000000 for count,time,i,j in m], [abs(base - float(count)) / base for count,time,i,j in m]]

print(results)


output = []
for k in results:
    output.append({"args": k, "error": statistics.mean(results[k][1]), "time": statistics.mean(results[k][0])})

output = sorted(output, key=lambda d: float(d['args'])) 

import json
print(json.dumps(output))




