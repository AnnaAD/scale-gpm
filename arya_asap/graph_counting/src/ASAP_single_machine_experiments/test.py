import math
import matplotlib.pyplot as plt

data = {}
with open("errors.txt","r") as f:
    for l in f:
        a = l.strip().split(' ')
        eps = float(a[0])
        x = round(eps/1e-3)
        if x not in data:
            data[x] = 0
        data[x] += 1
plt.figure()
plt.xlabel("eps/1e-3")
plt.ylabel('num')
plt.scatter(*list(zip(*data.items())))
print(sorted(data.items()))
plt.show()