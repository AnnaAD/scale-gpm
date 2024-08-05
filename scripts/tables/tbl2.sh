## NS Online

./sansa/bin/ns_final inputs/livej/graph 10000 3 triangle 0.1 3 1 0
./sansa/bin/ns_final inputs/livej/graph 10000 4 4clique 0.1 3 1 0
./sansa/bin/ns_final inputs/livej/graph 10000 6 6clique 0.1 3 1 0

./sansa/bin/ns_final inputs/friendster/graph 10000 3 triangle 0.1 3 1 0
./sansa/bin/ns_final inputs/friendster/graph 10000 4 4clique 0.1 3 1 0
./sansa/bin/ns_final inputs/friendster/graph 10000 6 6clique 0.1 3 1 0

./sansa/bin/ns_final inputs/twitter40/graph 10000 3 triangle 0.1 3 1 0
./sansa/bin/ns_final inputs/twitter40/graph 10000 4 4clique 0.1 3 1 0
./sansa/bin/ns_final inputs/twitter40/graph 10000 6 6clique 0.1 3 1 0

## Arya - ELP

./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/triangle inputs/livej/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/4_motif/4_clique inputs/livej/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/6_clique inputs/livej/graph 1 48 10 0.1

./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/friendster/graph arya_asap/graph_counting/patterns/triangle inputs/friendster/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/friendster/graph arya_asap/graph_counting/patterns/4_motif/4_clique inputs/friendster/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/friendster/graph arya_asap/graph_counting/patterns/6_clique inputs/friendster/graph 1 48 10 0.1

./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/triangle inputs/twitter40/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/4_motif/4_clique inputs/twitter40/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/6_clique inputs/twitter40/graph 1 48 10 0.1

# Arya - Run

./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/triangle 19163 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/4_motif/4_clique 334771887 48

./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/triangle 15367 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/4_motif/4_clique 259818186 48

./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/friendster/graph arya_asap/graph_counting/patterns/triangle 10678 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/friendster/graph arya_asap/graph_counting/patterns/4_motif/4_clique 2178913700 48

## Exact

./sansa/bin/sansa_omp_base inputs/livej/graph triangle 1 1 1
./sansa/bin/sansa_omp_base inputs/livej/graph 4clique 1 1 1
./sansa/bin/sansa_omp_base inputs/livej/graph 6clique 1 1 1

./sansa/bin/sansa_omp_base inputs/twitter40/graph triangle 1 1 1
./sansa/bin/sansa_omp_base inputs/twitter40/graph 4clique 1 1 1
./sansa/bin/sansa_omp_base inputs/twitter40/graph 6clique 1 1 1

./sansa/bin/sansa_omp_base inputs/friendster/graph triangle 1 1 1
./sansa/bin/sansa_omp_base inputs/friendster/graph 4clique 1 1 1
./sansa/bin/sansa_omp_base inputs/friendster/graph 6clique 1 1 1