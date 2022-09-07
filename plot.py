import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


fig = plt.figure()
ax = fig.add_subplot(111)

data = pd.read_csv("indicators.csv", header=None)

adjClose, bdown, bup, vwap = data.values.T.tolist()

x = range(len(adjClose))

ax.plot(x, adjClose, color='green')
ax.plot(x, bdown, color='red')
ax.plot(x, bup, color='red')
ax.plot(x, vwap, color='orange')


plt.show()