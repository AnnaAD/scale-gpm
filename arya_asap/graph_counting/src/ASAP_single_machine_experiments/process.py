import numpy as np
import csv

data = {}
with open("data.txt","r") as f:
    for l in f:
        a = l.strip().split(' ')
        label = (a[0],a[1])
        if label not in data:
            data[label] = np.array([])
        data[label] = np.append(data[label],[float(a[-1])])

with open("coeff.csv","w") as f:
    writer = csv.writer(f)
    writer.writerow(["graph_name","pattern","AM","GM"])
    for x,y in data.items():
        writer.writerow([x[0].split("\\")[2],x[1].split(".")[0],str(np.sum(y)/y.shape[0]),str(np.prod(y)**(1/y.shape[0]))])