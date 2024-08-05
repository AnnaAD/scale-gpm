## Input Graphs

To begin with, download the [datasets](https://www.dropbox.com/sh/i1jq1uwtkcd2qo0/AADJck_u3kx7FeSR5BvdrkqYa?dl=0) and clone this repository.
The first 3 graphs (`Mico`, `Patent_citations`, `Youtube`) are vertex-labeled graphs which are used for FSM.
Put the datasets in the `inputs` directory.

# Pre-Requisites

- gcc compiler
- OpenMP, `sudo apt install libomp-dev`


## Quick Experiments

Because the complete experiment suite for the tables in the paper, takes up to 100 hours to complete, and certain runs may timeout at 10 hours, a light suite of experiments of the faster online mode can be run with:

`source scripts/sansa.src`

which runs ScaleGPM NS online mode for cliques, and larger patterns on livej, friendster, and twitter40.

This should complete in under 1 hour, on a 48 core machine.


## Reproducing Tables

Run the following scripts for a complete collection of table results:

- `source tbl2.sh` : produces clique counts seen in table 2. Also runs the ELP for Arya. Each run may take up to ten hours.

- `source tbl3.sh` : produces larger pattern counts seen in table 3. Also runs the ELP for Arya. Each run may take up to ten hours.

- `source tbl3.sh` : produces larger pattern counts seen in table 3. Also runs the ELP for Arya. Each run may take up to ten hours.

- `source tbl4a.sh` : produces motif counts seen in table 4a. Also runs the ELP for Arya. Each run may take up to ten hours.

- `source tbl4b.sh` : produces larger graph counts seen in table 4b. Also runs the ELP for Arya. Each run may take up to ten hours. Needs 1TB of memory.


### Running Arya ELP:

- `cd /arya_asap/graph_counting/src/ELP/`
- `make`
  - this should automatically include the `tbb` library included in the repository.
- `USAGE: ./arya_asap/graph_counting/src/ELP/GraphCounting.out <graph file_in_binary_format> <pattern_file> <graph file_in_binary_format> 1 <threads> <number of paritions for sparsification> <error margin>`

Example:
`./arya_asap/graph_counting/src/ELP/GraphCounting.out /livej/graph arya_asap/graph_counting/patterns/triangle_triangle /data/xhchen/livej/graph 1 48 10 0.1`


### Running Sansa Fast Profiler
- `cd sansa/src/approx/fast-profiler`
- `make`

- `USAGE: ./sansa/bin/ns_fast_profiler /data/xhchen/livej/graph <base window = 10000> <k pattern size> <pattern_name> <base error = 0.5> <(delta) std_devs = 3> <DAG?> <0>`

Example:
`./sansa/bin/ns_fast_profiler /data/xhchen/livej/graph 10000 8 clique 0.5 3 1 0`

#### Running Performance Model

After running the fast profiler, input the results into the performance model as follows:

`cd performance_model`
`pip install requirements.txt`
`cd src`
`USAGE: python main.py {ELP,perf,threshold} --graph GRAPH --pattern PATTERN --error ERROR --NS NS --C C`

Example:
`python main.py threshold --graph livej --pattern triangle --error .1 --NS 10000 --C 20`

Result:
`{'GS': 0.06406906397691069, 'NS': (7.098001249396004e-06, 2.1294003748188015e-05)}`

Which indicates the bounds of `NS` and the predicted `GS` time.

### Running Arya
- `cd /arya_asap/graph_counting/src/multi_thread_single_machine`
- `make`
- `USAGE: ./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out <graph_in_binary_format> <pattern_file> <NS> <threads>`

Example:
`./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out uk2007/graph arya_asap/graph_counting/patterns/triangle 19567 48`

### Running NS-Online
- `cd sansa/src/approx/neighbor_sampling`
- `make`
- `USAGE: ./sansa/bin/ns_fast_profiler /data/xhchen/livej/graph <base window = 10000> <k pattern size> <pattern_name> <base error = 0.5> <(delta) std_devs = 3> <DAG?> <0>`

Example:
`./sansa/bin/ns_final friendster/graph 10000 5 clique 0.1 3 1 0` 

### Running GS
- `cd sansa/src/approx/sansa`
- `make`
- `USAGE: ./sansa/bin/sansa_omp_base livej/graph triangle <num_colors> <chunk_size_parallel> <DAG?>`

Example:
`./sansa/bin/sansa_omp_base livej/graph triangle 20 1 1` 

### Running Exact

The exact count method is embedded in the GS engine. To test, run with number of colors = 1.
- `cd sansa/src/approx/sansa`
- `make`
- `USAGE: ./sansa/bin/sansa_omp_base livej/graph triangle 1 <chunk_size_parallel> <DAG?>`

Example:
`./sansa/bin/sansa_omp_base livej/graph triangle 1 1 1` 



