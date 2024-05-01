import pandas as pd
import matplotlib.pyplot as plt
import math

df = pd.read_csv("errors5.csv")
df['Pattern-Param'] = df['pattern'].map(lambda x:x.split('.')[0]) \
    + '-' + df['graph_name'].map(lambda x:x.split('/')[-2])

num_V = {
    "citeseer": 3312,
    "mico": 100000,
    "patent_citations":	2745761,
    "youtube":	7066392,
    "cit-patents":	3774768,
    "livej":	4847571,
    "orkut":	3072441,
    "twitter20": 21297772,
}
num_E = {
    "citeseer": 9072,
    "mico": 2160312,
    "patent_citations":	27930818,
    "youtube":	114190484,
    "cit-patents":	33037894,
    "livej":	85702474,
    "orkut":	234370166,
    "twitter20": 530051090,
}
max_deg = {
    "citeseer": 99,
    "mico": 1359,
    "patent_citations":	789,
    "youtube":	4017,
    "cit-patents":	793,
    "livej":	20333,
    "orkut":	33313,
    "twitter20": 698112,
}

true_counts = {
    '4clique-friendster': 8963503263*144,
    '4clique-twitter40': 6622234180319*144,
    '4clique-uk2007': 123046503809139*144
}

for pattern_param, group in df.groupby('Pattern-Param'):
    plt.figure(figsize=(8, 6))
    plt.title(f'Predicted Count Plot for {pattern_param}')
    plt.xlabel('NS')
    plt.ylabel('Total_Num')

    for run,c in zip([1,2,3],["red","blue","green"]):
        deltas = group[group['run'] == run]['ns']
        errors = group[group['run'] == run]['Total_Num']
        
        plt.plot(deltas, errors, linestyle='-', color = c)
    plt.grid(True)
    plt.savefig(f'plots/{pattern_param}_estimated_count_plot.png')

    plt.figure(figsize=(8, 6))
    plt.title(f'Predicted Error Plot for {pattern_param}')
    plt.xlabel('NS')
    plt.ylabel('Estimated_Error')

    for run,c in zip([1,2,3],["red","blue","green"]):
        deltas = group[group['run'] == run]['ns']
        errors = group[group['run'] == run]['Estimated_Error']
        
        plt.plot(deltas, errors, linestyle='-', color = c)
    plt.grid(True)
    plt.savefig(f'plots/{pattern_param}_estimated_error_plot.png')

    for run,c in zip([1,2,3],["red","blue","green"]):
        plt.figure(figsize=(8, 6))
        plt.title(f'Predicted Error Plot for {pattern_param} run {run}')
        plt.xlabel('NS')
        plt.ylabel('Error')
        
        deltas = group[group['run'] == run]['ns']
        errors = abs(1-group[group['run'] == run]['Total_Num']/true_counts[pattern_param])
        if pattern_param == "4clique-twitter40" or pattern_param == "4clique-uk2007":
            deltas = deltas[100:]
            errors = errors[100:]
        plt.plot(deltas, errors, linestyle='dotted', color = c)

        deltas = group[group['run'] == run]['ns']
        errors = group[group['run'] == run]['Estimated_Error']
        if pattern_param == "4clique-twitter40" or pattern_param == "4clique-uk2007":
            deltas = deltas[100:]
            errors = errors[100:]
        plt.plot(deltas, errors, linestyle='-', color = "black")

        plt.grid(True)
        plt.savefig(f'plots/{pattern_param}_actual_error_plot_{run}.png')

    plt.figure(figsize=(8, 6))
    plt.title(f'Predicted Skewness Plot for {pattern_param}')
    plt.xlabel('NS')
    plt.ylabel('Estimated_Skewness')

    for run,c in zip([1,2,3],["red","blue","green"]):
        deltas = group[group['run'] == run]['ns']
        errors = group[group['run'] == run]['Estimated_Skewness']
        
        plt.plot(deltas, errors, linestyle='-', color = c)
    plt.grid(True)
    plt.savefig(f'plots/{pattern_param}_estimated_skewness_plot.png')