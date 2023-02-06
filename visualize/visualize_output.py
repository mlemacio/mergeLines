from matplotlib import collections as mc
import matplotlib.pyplot as plt
import numpy as np
import json

EXPECTED_OUTPUT_FILE = '../test/assets/1-reference.json'
ACTUAL_OUTPUT_FILE = '../test/assets/1-output.json'

fig, ax = plt.subplots(1, 2)
ax[0].set_title("EXPECTED")
ax[1].set_title("ACTUAL")

for idx, file_name in enumerate([EXPECTED_OUTPUT_FILE, ACTUAL_OUTPUT_FILE]):
    ax_to_use = ax[idx]

    file = open(file_name)
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

    for line in lines:
        lc = mc.LineCollection(line, linewidths=1, color='black')
        ax_to_use.add_collection(lc)

    ax_to_use.autoscale()
    ax_to_use.margins(0.1)
    ax_to_use.plot(x, y, 'o', color='red')

plt.tight_layout()
plt.show()
