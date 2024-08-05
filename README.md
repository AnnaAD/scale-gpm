# Sansa

To run the ScaleGPM system, first build the program in `sansa/src/approx/NS` and `sansa/src/approx/GS` with `make`.


See `expermients.md` for more details on reproducing experiment results.

# /arya_asap

Our modifications nessecary to run arya_asap with binary format graphs are contained here.

# /performance_model

A python implementation of the thresholding decision and performance model calculations.


# /sansa
Contains all the code for ScaleGPM system.

## sansa/approx/GS
A C++, OpenMP implementation of the GS, color-sparsification, engine.

## sansa/approx/NS

A C++, OpenMP implementation of the NS-Online engine.

## sansa/approx/fast-profiler
A C++, OpenMP implementation of the fast profiler, for determining inputs to the python performance model.
