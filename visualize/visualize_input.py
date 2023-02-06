from matplotlib import collections as mc
import matplotlib.pyplot as plt
import numpy as np
import json

SPLIT_LINES_FILE = "../test/assets/1-split.json"
JOINED_LINES_FILE = "../test/assets/1-reference.json"

fig, ax = plt.subplots(1, 2)
ax[0].set_title("SPLIT LINES")
ax[1].set_title("JOINED LINES")

for idx, file_name in enumerate([SPLIT_LINES_FILE]):
    ax_to_use = ax[idx]

    file = open(file_name)
    data = json.load(file)

    coords = []
    num_pairs = int(len(data["lines"]) / 2)

    x = []
    y = []

    a = []
    b = []

    for i in range(0, num_pairs):
        i = i * 2
        first = data["lines"][i]
        second = data["lines"][i + 1]

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

    num_lines = 10
    num_dots = (num_lines * 2)

    subset = coords[0:num_lines]

    for i in subset:
        lc = mc.LineCollection(i, linewidths=2)
        ax_to_use.add_collection(lc)

    ax_to_use.autoscale()
    ax_to_use.margins(0.1)
    ax_to_use.plot(x[0:num_dots], y[0:num_dots], 'o', color='blue')
    ax_to_use.plot(a[0:num_dots], b[0:num_dots], 'o', color='green')

ax_to_use = ax[1]

file = open(JOINED_LINES_FILE)
data = json.load(file)

lines = []
x = []
y = []

for i in range(0, len(data["lines"])):
    curr_line_json = data["lines"][i]

    curr_line = [(curr_line_json['start'][0], curr_line_json['start'][1]),
                    (curr_line_json['end'][0], curr_line_json['end'][1])]

    lines.append([curr_line])
    x.append(curr_line_json['start'][0])
    y.append(curr_line_json['start'][1])

    x.append(curr_line_json['end'][0])
    y.append(curr_line_json['end'][1])

for line in lines[0:10]:
    lc = mc.LineCollection(line, linewidths=1, color='black')
    ax_to_use.add_collection(lc)

ax_to_use.autoscale()
ax_to_use.margins(0.1)
ax_to_use.plot(x[0:20], y[0:20], 'o', color='blue')

plt.tight_layout()
plt.show()
