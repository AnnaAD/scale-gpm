# Motif


# NS Online 4 Motif
./sansa/bin/ns_final /data/xhchen/livej/graph 10000 4 4motif 0.1 3 0 0
./sansa/bin/ns_final /data/xhchen/friendster/graph 10000 4 4motif 0.1 3 0 0
./sansa/bin/ns_final /data/xhchen/twitter40/graph 10000 4 4motif 0.1 3 0 0


# 4 Motif Arya
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/livej/graph arya_asap/graph_counting/patterns/4_motif/3_star 121894 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/livej/graph arya_asap/graph_counting/patterns/4_motif/4_chain  19670085 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/livej/graph arya_asap/graph_counting/patterns/4_motif/4_cycle 74205783 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/livej/graph arya_asap/graph_counting/patterns/4_motif/4_motif_4 69630037 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/livej/graph arya_asap/graph_counting/patterns/4_motif/4_motif_5 313827246 48

./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/twitter40/graph arya_asap/graph_counting/patterns/4_motif/3_star 36724 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/twitter40/graph arya_asap/graph_counting/patterns/4_motif/4_chain  237088 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/twitter40/graph arya_asap/graph_counting/patterns/4_motif/4_cycle 11498096 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/twitter40/graph arya_asap/graph_counting/patterns/4_motif/4_motif_4 7498530 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/twitter40/graph arya_asap/graph_counting/patterns/4_motif/4_motif_5 81280118 48

./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/friendster/graph arya_asap/graph_counting/patterns/4_motif/3_star 9093 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/friendster/graph arya_asap/graph_counting/patterns/4_motif/4_chain  75473403 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/friendster/graph arya_asap/graph_counting/patterns/4_motif/4_cycle 1149809600 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/friendster/graph arya_asap/graph_counting/patterns/4_motif/4_motif_4 749853000 48
./arya_asap/graph_counting/src/multi_thread_single_machine/GraphCounting.out /data/xhchen/friendster/graph arya_asap/graph_counting/patterns/4_motif/4_motif_5 8128011800 48


# EXACT

./sansa/bin/sansa_omp_base /data/xhchen/livej/graph 3motif 0 1 0
./sansa/bin/sansa_omp_base /data/xhchen/friendster/graph 3motif 0 1 0
./sansa/bin/sansa_omp_base /data/xhchen/twitter40/graph 3motif 0 1 0

./sansa/bin/sansa_omp_base /data/xhchen/livej/graph 4motif 0 1 0
./sansa/bin/sansa_omp_base /data/xhchen/friendster/graph 4motif 0 1 0 
./sansa/bin/sansa_omp_base /data/xhchen/twitter40/graph 4motif 0 1 0
