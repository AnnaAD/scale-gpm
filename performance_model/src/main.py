import argparse
import elp
import performance
import data

def perf_run(graph, pattern, ns, c):
    time_gs, time_ns = -1, -1

    if(c):
        time_gs = performance.get_work_gs( data.graphs[graph], data.patterns[pattern], c, data.COMPUTE_FACTOR_GS)
    
    if(ns):
        time_ns = performance.get_work_ns( data.graphs[graph], data.patterns[pattern], ns, data.COMPUTE_FACTOR_NS)

    return {"GS": time_gs, "NS": time_ns}

def elp_run(graph, pattern,error):
    c = elp.get_c(0,0,data.patterns[pattern],0,0)#data.get_elp_constant("GS",graph,pattern), data.graphs[graph], data.patterns[pattern], error, data.true_counts[f"{pattern}-{graph}"])
    ns = elp.get_ns(data.get_elp_constant("NS",graph,pattern), data.graphs[graph], data.patterns[pattern], error, data.true_counts[f"{pattern}-{graph}"])

    return {"c": c, "ns": ns}

def threshold(graph, pattern, error):
    elp_res = elp_run(graph, pattern, error)
    c = elp_res["c"]
    ns = elp_res["ns"]

    print("c:", c, "ns:", ns)

    return perf_run(graph, pattern, ns, c)

def main(mode, graph, pattern, error, ns, c):
    print(f"{mode} graph: {graph} pattern: {pattern} error: {error} NS: {ns} c: {c}")

    if mode == 'ELP':
        print(elp_run(graph, pattern, error))
    elif mode == 'perf':
        print(perf_run(graph, pattern, ns, c))
    elif mode == 'threshold':
        print(threshold(graph, pattern, error))
    else:
        print("Invalid mode selected. Please choose between ELP, performance, or compare.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Argument parser for different modes")
    parser.add_argument('mode', choices=['ELP', 'perf', 'threshold'], help="Select mode: ELP, perf, or threshold")
    parser.add_argument('--graph', type=str, help="Specify the graph string")
    parser.add_argument('--pattern', type=str, help="Specify the pattern string")
    parser.add_argument('--error', type=float, help="Acceptable Error Bound (0.0 - 1.0)")
    parser.add_argument('--NS', type=int, help="Specify NS (optional)")
    parser.add_argument('--C', type=float, help="Specify C for graph sparsification (optional)")

    args = parser.parse_args()
    main(args.mode, args.graph, args.pattern, args.error,args.NS, args.C)