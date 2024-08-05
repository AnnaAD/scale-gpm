# NS-Online

./sansa/bin/ns_final inputs/livej/graph 10000 5 path 0.1 3 0 0
./sansa/bin/ns_final inputs/livej/graph 10000 5 house 0.1 3 0 0
./sansa/bin/ns_final inputs/livej/graph 10000 6 dumbbell 0.1 3 0 0

./sansa/bin/ns_final inputs/friendster/graph 10000 5 path 0.1 3 0 0
./sansa/bin/ns_final inputs/friendster/graph 10000 5 house 0.1 3 0 0
./sansa/bin/ns_final inputs/friendster/graph 10000 6 dumbbell 0.1 3 0 0

./sansa/bin/ns_final inputs/twitter40/graph 10000 5 path 0.1 3 0 0
./sansa/bin/ns_final inputs/twitter40/graph 10000 5 house 0.1 3 0 0
./sansa/bin/ns_final inputs/twitter40/graph 10000 6 dumbbell 0.1 3 0 0

## Arya - ELP

./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/5_path inputs/livej/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/triangle_triangle inputs/livej/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/5_house inputs/livej/graph 1 48 10 0.1

./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/friendster/graph arya_asap/graph_counting/patterns/5_path inputs/friendster/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/friendster/graph arya_asap/graph_counting/patterns/triangle_triangle inputs/friendster/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/friendster/graph arya_asap/graph_counting/patterns/5_house inputs/friendster/graph 1 48 10 0.1

./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/5_path inputs/twitter40/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/triangle_triangle inputs/twitter40/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/5_house inputs/twitter40/graph 1 48 10 0.1

## Arya - Run

./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/5_house 1565584467 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/5_path 10138699 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/livej/graph arya_asap/graph_counting/patterns/triangle_triangle 1057943054 48

./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/5_house 67728191 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/5_path 293915 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/twitter40/graph arya_asap/graph_counting/patterns/triangle_triangle 217891370 48

./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out inputs/friendster/graph arya_asap/graph_counting/patterns/5_path 143690346 48

## Exact

./sansa/bin/sansa_omp_base inputs/livej/graph 5path 1 1 0
./sansa/bin/sansa_omp_base inputs/livej/graph house 1 1 0
./sansa/bin/sansa_omp_base inputs/livej/graph dumbbell 1 1 0

./sansa/bin/sansa_omp_base inputs/friendster/graph 5path 1 1 0
./sansa/bin/sansa_omp_base inputs/friendster/graph house 1 1 0
./sansa/bin/sansa_omp_base inputs/friendster/graph dumbbell 1 1 0

./sansa/bin/sansa_omp_base inputs/twitter40/graph 5path 1 1 0
./sansa/bin/sansa_omp_base inputs/twitter40/graph house 1 1 0
./sansa/bin/sansa_omp_base inputs/twitter40/graph dumbbell 1 1 0

