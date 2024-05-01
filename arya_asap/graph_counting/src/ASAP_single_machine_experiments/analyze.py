import pandas as pd
import matplotlib.pyplot as plt
import math

df = pd.read_csv("coeff.csv")
df['Pattern-Param'] = df['pattern'] + '-' + df['graph_name']

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

df['V'] = df['graph_name'].map(num_V)
df['E'] = df['graph_name'].map(num_E)
df['maxD'] = df['graph_name'].map(max_deg)
df['logmaxD'] = df['maxD'].map(math.log)
df['logE/logV'] = df['E'].map(math.log)/df['V'].map(math.log)
df['E/V'] = df['E'] / df['V']
df["E/V/D"] = df["E/V"]/df["maxD"]
df['logK'] = df['GM'].map(math.log)

xaxis = "E/V/D"
plt.figure()
plt.xlabel(xaxis)
plt.ylabel('logK')
plt.scatter(df[xaxis],df["logK"])
for a,b,c in zip(df["Pattern-Param"],df[xaxis],df['logK']):
    plt.annotate(a,(b,c))
plt.show()