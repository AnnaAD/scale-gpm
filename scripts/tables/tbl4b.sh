# Large Graphs


# Arya - ELP

./arya_asap/graph_counting/src/ELP/GraphCounting.out /data/xhchen/uk2007/graph arya_asap/graph_counting/patterns/triangle /data/xhchen/uk2007/graph 1 48 10 0.1
#./arya_asap/graph_counting/src/ELP/GraphCounting.out /data/xhchen/gsh-2015/graph arya_asap/graph_counting/patterns/triangle /data/xhchen/gsh-2015/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out /data/xhchen/clueweb12/graph arya_asap/graph_counting/patterns/triangle /data/xhchen/clueweb12/graph 1 48 10 0.1

./arya_asap/graph_counting/src/ELP/GraphCounting.out /data/xhchen/uk2007/graph arya_asap/graph_counting/patterns/4_motif/4_clique /data/xhchen/uk2007/graph 1 48 10 0.1
#./arya_asap/graph_counting/src/ELP/GraphCounting.out /data/xhchen/gsh-2015/graph arya_asap/graph_counting/patterns/4_motif/4_clique /data/xhchen/gsh-2015/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out /data/xhchen/clueweb12/graph arya_asap/graph_counting/patterns/4_motif/4_clique /data/xhchen/clueweb12/graph 1 48 10 0.1


./arya_asap/graph_counting/src/ELP/GraphCounting.out /data/xhchen/uk2007/graph arya_asap/graph_counting/patterns/5_path /data/xhchen/uk2007/graph 1 48 10 0.1
#./arya_asap/graph_counting/src/ELP/GraphCounting.out /data/xhchen/gsh-2015/graph arya_asap/graph_counting/patterns/5_path /data/xhchen/gsh-2015/graph 1 48 10 0.1
./arya_asap/graph_counting/src/ELP/GraphCounting.out /data/xhchen/clueweb12/graph arya_asap/graph_counting/patterns/5_path /data/xhchen/clueweb12/graph 1 48 10 0.1


# Arya - count

./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/uk2007/graph arya_asap/graph_counting/patterns/triangle 19567 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/gsh-2015/graph arya_asap/graph_counting/patterns/triangle 5500 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/clueweb12/graph arya_asap/graph_counting/patterns/triangle 16000 48



# NS-Online 
./sansa/bin/ns_final /data/xhchen/uk2007/graph 10000 3 triangle 0.1 3 1 0
./sansa/bin/ns_final /data/xhchen/uk2007/graph 10000 4 4clique 0.1 3 1 0
./sansa/bin/ns_final /data/xhchen/uk2007/graph 10000 5 path 0.1 3 0 0

./sansa/bin/ns_final /data/xhchen/clueweb12/graph 10000 3 triangle 0.1 3 1 0
./sansa/bin/ns_final /data/xhchen/clueweb12/graph 10000 4 4clique 0.1 3 1 0
./sansa/bin/ns_final /data/xhchen/clueweb12/graph 100000 5 house 0.1 1 0 0

./sansa/bin/ns_final /data/xhchen/gsh-2015/graph 10000 3 triangle 0.1 3 1 0
./sansa/bin/ns_final /data/xhchen/gsh-2015/graph 10000 4 4clique 0.1 3 1 0
./sansa/bin/ns_final /data/xhchen/gsh-2015/graph 100000 5 path 0.1 3 0 0
