import math

def get_ns(C, g, pattern, e, TC):
    k = pattern.k
    print(pattern.type,"k", k, "error", e, "TC", TC, "|E|", g.e, "∆", g.max_degree, "scalar", C)
    k2, c = C
    #assert k2 == k
    print("RES NS:", g.name, pattern.type + str(k), c * (g.e) * pow(g.max_degree,k-1) / ( (e**2) * TC * 0.01 ))
    return c * (g.e) * pow(g.max_degree,k-1) / ( (e**2) * TC * 0.01 )

def get_c(C, g, pattern, e, TC):
    k = pattern.k
    print(pattern)
    print(pattern.k)
    if k == 3:
        return 100
    if k == 5 or k == 4:
        return 50
    if k == 6:
        return 20
    
    return 10

def get_elp_gs(C, g, k, c):
    return 0

# ns = c * (g.e) * pow(g.max_degree,k-1) / ( (e**2) * TC * 0.01 )
# e = sqrt(c * (g.e) * pow(g.max_degree,k-1) / (ns * TC * 0.01))
def get_elp_asap(C, g, pattern, ns, TC):
    k = pattern.k
    k2, c = C
    #assert k2 == k
    out = math.sqrt(c*(g.e)*pow(g.max_degree,k-1)/(ns*TC*0.01))*100
    print(pattern.type,"k", k, "ns", ns, "TC", TC, "|E|", g.e, "∆", g.max_degree, "scalar", c, " = ", out)
    return (ns, out)

from data import Pattern, graphs
#livej 3path
print(get_ns((3,0.001720),graphs["livej"], Pattern("3path",3),0.1,1144004100000000))
print(get_ns((3,0.000697),graphs["twitter40"], Pattern("3path",3),0.1,240565888600000000))
print(get_ns((3,0.002101),graphs["twitter40"], Pattern("3path",3),0.1,119738800300000000))

