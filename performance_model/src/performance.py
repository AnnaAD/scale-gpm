from data import neighbor_size,intersection_size,manual_overhead

def get_work_ns(g, pattern, ns, CF):
    random_gen_time = 0

    if(pattern.type == "clique"):
        k = pattern.k
        total_work = (random_gen_time + g.mem_look_up_time*(1+neighbor_size(g))*1,random_gen_time +  g.mem_look_up_time*(1+neighbor_size(g))*k)
       

    if(pattern.type == "path"):
        k = pattern.k
        total_work = (random_gen_time + g.mem_look_up_time*(1+neighbor_size(g))*1,random_gen_time +  g.mem_look_up_time*(1+neighbor_size(g))*k*k)
    
    # house: O(V * N * N/2 * N * N * I-2)
    if(pattern.type == "house"):
        k = 5
        total_work = (random_gen_time + g.mem_look_up_time*(1+neighbor_size(g))*k,random_gen_time + g.mem_look_up_time*(1+neighbor_size(g))*k*k)

    print(pattern.type)
    if(pattern.type == "dumbell"):
        k = 5
        total_work = (random_gen_time + g.mem_look_up_time*(1+neighbor_size(g))*1,random_gen_time + g.mem_look_up_time*(neighbor_size(g))*(k-2))

    return tuple([ns  * CF * i for i in total_work])

def get_work_gs(g, pattern, c, CF):
    
    #triangle: O(V*N*N) 
    #4clique: O(V*N*N*I-2*I-2)
    #5clique: O(V*N*N*I-2*I-2*I-3*I-3)
    #6clique: O(V*N*N*I-2*I-2*I-3*I-3*I-4*I-4)
    if(pattern.type == "clique"):
        k = pattern.k
        total_work = g.v * (1+neighbor_size(g,c))**2
        for i in range(2, k-1):
            total_work *= (1+intersection_size(i,g,c))**2

    # 5path: O(V*N*N*N)
    if(pattern.type == "path"):
        k = pattern.k
        total_work = g.v * (1+neighbor_size(g,c))**(k-2)
    
    # house: O(V * N * N/2 * N * N * I-2)
    if(pattern.type == "house"):
        k = pattern.k
        print(g.name,neighbor_size(g,c),intersection_size(2,g,c))
        scale_factor = {"friendster":1, "livej":1.5}
        total_work = g.v * 1/2* (1+neighbor_size(g,c))**(scale_factor[g.name]*k-1)*(1+intersection_size(2,g,c))

    if(pattern.type == "dumbell"):
        k = pattern.k
        total_work = g.v * (1+neighbor_size(g,c))**2
        for i in range(2, k-1):
            total_work *= (1+neighbor_size(g,c))

    print("overhead:", get_overhead_gs(g,c, CF))
    return get_overhead_gs(g,c, CF) + total_work*CF

def get_overhead_gs(g, c, CF):
    if(g.name in manual_overhead):
        return manual_overhead[g.name]
    return (2 * g.e * (1 + 1/c)*g.mem_look_up_time/10)*CF

