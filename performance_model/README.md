## /src

Install python3.11 and packages in requirements.txt.

To run the performance model:

python main.py:

```
usage: main.py [-h] [--graph GRAPH] [--pattern PATTERN] [--error ERROR]
               [--NS NS] [--C C]
               {ELP,perf,threshold}

Argument parser for different modes

positional arguments:
  {ELP,perf,threshold}  Select mode: ELP, perf, or threshold

options:
  -h, --help            show this help message and exit
  --graph GRAPH         Specify the graph string
  --pattern PATTERN     Specify the pattern string
  --error ERROR         Acceptable Error Bound (0.0 - 1.0)
  --NS NS               Specify NS (optional)
  --C C                 Specify C for graph sparsification (optional)
```

Specify the graph, pattern, and error target.
