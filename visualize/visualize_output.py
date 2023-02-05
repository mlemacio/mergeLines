from matplotlib import collections as mc
import pylab as pl
import numpy as np
import json

f = open('../test/assets/1-reference.json')
data = json.load(f)

coords = []

x = []
y = []
for i in range(0, len(data["lines"])):
    first = data["lines"][i]

    first_coord = [(first['start'][0], first['start'][1]),
                   (first['end'][0], first['end'][1])]

    coords.append([first_coord])
    x.append(first['start'][0])
    y.append(first['start'][1])

    x.append(first['end'][0])
    y.append(first['end'][1])


subset = coords[0:10]

c = np.array([(1, 0, 0, 1), (0, 1, 0, 1), (0, 0, 1, 1), (0, 1, 1, 0)])


fig, ax = pl.subplots()

for i in subset:
    lc = mc.LineCollection(i, colors=c, linewidths=2, color='black')
    ax.add_collection(lc)

ax.autoscale()
ax.margins(0.1)
pl.plot(x[0:20], y[0:20], 'o', color='red')



pl.show()
