from matplotlib import collections as mc
import pylab as pl
import numpy as np
import json

f = open('./test/assets/1-split.json')
data = json.load(f)

coords = []
num_pairs = int(len(data["lines"]) / 2)

x = []
y = []

a = []
b = []

for i in range(0, num_pairs):
    idx = i * 2
    first = data["lines"][idx]
    second = data["lines"][idx + 1]

    first_coord = [(first['start'][0], first['start'][1]),
                   (first['end'][0], first['end'][1])]
    second_coord = [(second['start'][0], second['start'][1]),
                    (second['end'][0], second['end'][1])]

    coords.append([first_coord, second_coord])
    x.append(first['start'][0])
    y.append(first['start'][1])

    x.append(first['end'][0])
    y.append(first['end'][1])

    a.append(second['start'][0])
    b.append(second['start'][1])

    a.append(second['end'][0])
    b.append(second['end'][1])

subset = coords[0:10]
for i in subset:
    print(i)


c = np.array([(1, 0, 0, 1), (0, 1, 0, 1), (0, 0, 1, 1), (0, 1, 1, 0)])


fig, ax = pl.subplots()

for i in subset:
    lc = mc.LineCollection(i, colors=c, linewidths=2)
    ax.add_collection(lc)

ax.autoscale()
ax.margins(0.1)

pl.plot(x[0:20], y[0:20], 'o', color='blue')

pl.plot(a[0:20], b[0:20], 'o', color='green')

pl.show()
