COMPUTE_FACTOR_NS = ((2.45*10**-9) / (128/3) ) / 50
COMPUTE_FACTOR_GS = (2.45*10**-9)


class Graph:
    def __init__(self, name, v, e, tri_cnt, max_degree, mem_look_up_time):
        self.name = name
        self.v = v
        self.e = e
        self.tri_cnt = tri_cnt
        self.max_degree = max_degree
        self.mem_look_up_time = mem_look_up_time

class Pattern:
    def __init__(self, in_type, k):
        self.type = in_type
        self.k = k


def get_elp_constant(g_ns, graph, pattern):

    patterngraph = f"{pattern}-{graph}"
    k_c_dict = {
        '4clique-friendster': (4,1.17967e-08),
        '6clique-friendster': (6,1.18772e-07),
        'house-friendster': (5,0.000069),
        'triangle-friendster': (3,0.000018),
        '5path-friendster': (5,7.93688e-06),
        '9clique-youtube': (9,0),
        '4clique-youtube':  (4,0.000897),
        '6clique-youtube':  (6,0.000288),
        'house-youtube':  (5,0.002245),
        '5path-youtube': (5,0.000072),
        'triangle-youtube': (3,0.012723),
        '4clique-mico': (4,0.003217),
        '6clique-mico': (6,0.000174),
        'house-mico': (5,0.001154),
        'triangle-mico': (3,0.001866),
        '5path-mico': (5,0.000317),
        '4clique-livej': (4, 9.148e-05),
        '6clique-livej': (6,1.84704e-06),
        'house-livej': (5,1.11536e-06),
        'triangle-livej': (3,0.000089),
        '5path-livej': (5,5.66833e-06),
        'triangle-gsh2015': (3,0.000128),
        '4clique-gsh2015': (4,5.64951e-06),
        '6clique-gsh2015':(6,3.08256e-07),
        'house-gsh2015':(5,1.725214),
        '5path-gsh2015':(5,3.74597e-06),
        'triangle-clueweb12':(3,2.44593e-05),
        '4clique-clueweb12':(4,3.33035e-05),
        '6clique-clueweb12':(6,3.59486e-08),
        'house-clueweb12':(5,32.063),
        '5path-clueweb12':(5, 0.000161448),
        'triangle-twitter40':(3,0.001041),
        '4clique-twitter40':(4, 0.000112),
        '6clique-twitter40':(6,4.92465e-05),
        'house-twitter40':(5,21.580112),
        '5path-twitter40':(5,0.000044),
        'dumbell-twitter40':(6,0.000260),
        'dumbell-livej': (6,3.2115e-07),
        'dumbell-friendster': (6, 2.05343e-05),
    }

    k_c_dict2 = {
        '4clique-friendster': (4,1.17967e-08),
        '6clique-friendster': (6,1.18772e-07),
        'house-friendster': (5,0),
        'triangle-friendster': (3,0.000018),
        '5path-friendster': (5,0),
        '9clique-youtube': (9,0),
        '4clique-youtube':  (4,0.000020),
        '6clique-youtube':  (6,0.000724),
        'house-youtube':  (5,0),
        '5path-youtube': (5,0),
        'triangle-youtube': (3,0.000022),
        '4clique-mico': (4,0.003217),
        '6clique-mico': (6,0.000174),
        'house-mico': (5,0),
        'triangle-mico': (3,0.002927),
        '5path-mico': (5,0),
        '4clique-livej': (4, 0.000202),
        '6clique-livej': (6,6.78641e-07),
        'house-livej': (5,0),
        'triangle-livej': (3,0.002675),
        '5path-livej': (5,0),
    }

    if(g_ns == "NS"):
        return k_c_dict[patterngraph]
    
    if(g_ns == "GS"):
        return k_c_dict2[patterngraph]

def parse_data(filename):
    result = []
    with open(filename, 'r') as file:
        for line in file:
            # Remove leading and trailing whitespace and split by spaces
            parts = line.strip().split()
            
            # Convert the parts to floats and create a tuple
            data_tuple = tuple(float(part) for part in parts)
            result.append(data_tuple)
    return result

def intersection_size(num_intersecting_neighbor_sets,graph,c = 1):
    e = graph.e/c
    tri_cnt = graph.tri_cnt / (c**2)

    p1 = e/(graph.v**2)
    p2 = (tri_cnt * graph.v) / ((e)**2)

    return graph.v*p1*p2**(num_intersecting_neighbor_sets-1)

def neighbor_size(graph,c=1):
    print(c)
    print(graph.e)
    e = graph.e/c
    return e/graph.v

manual_overhead = {
    "friendster": 15,
    "youtube": .13,
    "mico": 0.003529,
    "livej": 0.05,
    "gsh2015": 11.5,
}

friendster = Graph("friendster", 65608366, 1806067135, 4173724142, 868, 10)
youtube = Graph("youtube",7066392,57095242,103017122, 4017, 10)
mico = Graph("mico", 100000,1080156, 12534960, 219, 1)
twitter40 = Graph("twitter40",41652230,1202513046,34824916864, 4102, 10)
livej = Graph("livej",4847571,42851237,285730264, 686, 10)
clueweb12 = Graph("clueweb12", 978407686, 37372179311, 1995295290765, 4244, 10)
gsh2015 = Graph("gsh2015", 988490691, 25690705118, 910140734636, 9911, 10)

graphs = {
    "friendster": friendster,
    "livej": livej,
    "mico": mico,
    "youtube": youtube,
    "twitter40": twitter40,
    "clueweb12": clueweb12,
    "gsh2015": gsh2015
}

patterns = {
    "triangle": Pattern("clique",3),
    "4clique": Pattern("clique", 4),
    "5clique": Pattern("clique", 5),
    "6clique": Pattern("clique", 6),
    "9clique": Pattern("clique", 9),
    "5path": Pattern("path", 5),
    "house": Pattern("house", 5),
    "dumbell": Pattern("dumbell", 6),
}

true_counts = {
    '4clique-friendster': 8963503263,
    '6clique-friendster': 59926510355,
    'house-friendster': 54693897472726,
    'triangle-friendster': 4173724142,
    '5path-friendster': 233944034540139092,
    '9clique-youtube': 1174963754,
    '4clique-youtube': 176614367,
    '6clique-youtube': 478531519,
    'house-youtube': 71503929498,
    '5path-youtube': 4159011830775,
    'triangle-youtube': 103017122,
    '4clique-mico': 514864225,
    '6clique-mico': 631568259280,
    'house-mico': 1655449692098,
    'triangle-mico': 12534960,
    '5path-mico': 5625508932611,
    '4clique-livej': 9933532019,
    '6clique-livej': 20703476954640,
    'house-livej': 53552979463652,
    'triangle-livej': 285730264,
    '5path-livej': 580860878971917,
    'triangle-gsh2015':910140734636,
    '4clique-gsh2015': 205010080145349,
    '6clique-gsh2015':11066230269502145152, #estimate
    'house-gsh2015':90878180740000, #estimate
    '5path-gsh2015':109797480451160000, #estimate
    'triangle-clueweb12':1995295290765, 
    '4clique-clueweb12':296844893108000, #estimate
    '6clique-clueweb12':18384797910862448384, #estimate
    'house-clueweb12':200060849470000, #estimate
    '5path-clueweb12':94244987429770000, #estimate
    'triangle-twitter40':34824916864,
    '4clique-twitter40':6622234180319,
    '6clique-twitter40':561147181080000000,#estimate
    'house-twitter40':3472955140000, #estimate
    '5path-twitter40':1959100399770000, #estimate
    'dumbell-twitter40':10719333043009000000, #estimate
    'dumbell-livej':5802569871045348,
    'dumbell-friendster': 86698723700000, #estimate
}