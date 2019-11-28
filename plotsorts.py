import pandas as pd
import numpy as np
from numpy.polynomial.polynomial import polyfit
import matplotlib.pyplot as plt
plt.style.use('dark_background')
# fig, ax = plt.subplots()
plt.figure(figsize=(12,8))

# reading in files. The log files are just CSVs of each algorithm's O(1) time * nlgn for even values 0 through 1500
data_m  = pd.read_csv("output/merge.csv")
data_q  = pd.read_csv("output/quick.csv")
data_r  = pd.read_csv("output/radix.csv")

# only grab one radix for now.
RADIX = 16
data_r = data_r.loc[data_r['r'] == RADIX]

# data_log_m  = pd.read_csv("outputlogmerge.txt")
# data_square_q  = pd.read_csv("outputsquarequick.txt")

# files broken into their x and y components for plotting
arrsize_m = data_m['n']
runtime_m = data_m['t']
arrsize_q = data_q['n']
runtime_q = data_q['t']
arrsize_r = data_r['n']
runtime_r = data_r['t']

# x = data_log_m['x']
# xlgx = data_log_m['y']
# x_short = data_square_q['x']
# xx = data_square_q['y']

# creating scatter plots for arraysize versus runtime
plt.scatter(arrsize_q, runtime_q, s=5, c='r', alpha = 0.6, label='quicksort')
plt.scatter(arrsize_m, runtime_m, s=5, c='b', alpha = 0.6, label='mergesort')
plt.scatter(arrsize_r, runtime_r, s=5, c='g', alpha = 0.6, label='radixsort (radix = {})'.format(RADIX))

# plotting lines of best fit on the subgraph
# ax.plot(np.unique(arrsize_m), np.poly1d(np.polyfit(arrsize_m, runtime_m, 1))(np.unique(arrsize_m)), c='b')
# ax.plot(np.unique(arrsize_q), np.poly1d(np.polyfit(arrsize_q, runtime_q, 1))(np.unique(arrsize_q)), c='r')
# plt.plot(x,xlgx, c='b' ,label="150*(nlgn) : mergesort's upper bound")
# plt.plot(x_short,xx, c ='r', label="150*(n^2) : quicksort's upper bound")

#labeling & display
plt.legend()
plt.xlabel('Array Size')
plt.ylabel('Runtime (microseconds)')
plt.title('Runtime vs Array Size of Comparison and Non-Comparison Sorting Algorithms')
plt.show()

