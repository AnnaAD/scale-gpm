# Sansa

To run the ScaleGPM system, first build the program in `sansa/src/approx/NS` and `sansa/src/approx/GS` with `make`.

Then, run either mode as follows:

- GS:
`./sansa/bin/sansa_omp_base /data/xhchen/friendster/graph 8clique 2 1024 1`

- NS-Online:

`./sansa/bin/ns_final /data/xhchen/livej/graph 10000 3 triangle 0.1 3 1 0`

# arya_asap

Our modifications nessecary to run arya_asap with binary format graphs are contained here.

# performance model

A python implementation of the thresholding decision and performance model calculations.

