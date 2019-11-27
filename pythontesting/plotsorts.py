import pandas as pd
import numpy as np
from numpy.polynomial.polynomial import polyfit
import matplotlib.pyplot as plt
plt.style.use('dark_background')
# fig, ax = plt.subplots()
plt.figure(figsize=(12,8))

# reading in files. The log files are just CSVs of each algorithm's O(1) time * nlgn for even values 0 through 1500
data_m  = pd.read_csv("outputmerge.txt")
data_q  = pd.read_csv("outputquick.txt")
# data_log_m  = pd.read_csv("outputlogmerge.txt")
# data_square_q  = pd.read_csv("outputsquarequick.txt")

# files broken into their x and y components for plotting
arrsize_m = data_m['x']
runtime_m = data_m['y']
arrsize_q = data_q['x']
runtime_q = data_q['y']
# x = data_log_m['x']
# xlgx = data_log_m['y']
# x_short = data_square_q['x']
# xx = data_square_q['y']

# creating scatter plots for arraysize versus runtime
plt.scatter(arrsize_q, runtime_q, s=5 , c='r', alpha = 0.6, label='quicksort')
plt.scatter(arrsize_m, runtime_m , s=5, c='b', alpha = 0.6, label='mergesort')

# plotting lines of best fit on the subgraph
# ax.plot(np.unique(arrsize_m), np.poly1d(np.polyfit(arrsize_m, runtime_m, 1))(np.unique(arrsize_m)), c='b')
# ax.plot(np.unique(arrsize_q), np.poly1d(np.polyfit(arrsize_q, runtime_q, 1))(np.unique(arrsize_q)), c='r')
# plt.plot(x,xlgx, c='b' ,label="150*(nlgn) : mergesort's upper bound")
# plt.plot(x_short,xx, c ='r', label="150*(n^2) : quicksort's upper bound")

#labeling & display
plt.legend()
plt.xlabel('Array Size')
plt.ylabel('Runtime (nanoseconds)')
plt.title('Runtime vs Array Size of Comparison Sorting Algorithms')
plt.show()

