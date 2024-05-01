from igraph import *

graph_name = "/mnt/md0/hb_inputs/lg-graphs/patent_citations.ctxt"

g = Graph.Read_Ncol(graph_name,names=True, directed=False)
print(g.get_edgelist())
