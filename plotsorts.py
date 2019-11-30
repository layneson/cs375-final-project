import pandas as pd
import numpy as np
from numpy.polynomial.polynomial import polyfit
import matplotlib.pyplot as plt
import sys
import subprocess

def read_csvs():
    data_m  = pd.read_csv("output/merge.csv")
    data_q  = pd.read_csv("output/quick.csv")
    data_r  = pd.read_csv("output/radix.csv")

    return (data_m, data_q, data_r)


def display_graph(plot, x1, y1, x2, y2, x3, y3, label1, label2, label3, xlabel, ylabel, title):
    plot.scatter(x1, y1, s=5, c='r', alpha = 0.6, label=label1)
    plot.scatter(x2, y2, s=5, c='b', alpha = 0.6, label=label2)
    plot.scatter(x3, y3, s=5, c='g', alpha = 0.6, label=label3)
    
    plot.set(xlabel=xlabel, ylabel=ylabel)
    plot.set_title(title)

"""
plt.style.use('dark_background')
fig, plots = plt.subplots(2, 2, figsize=(24, 16), sharex=True, sharey=True)

subprocess.run(["./sort", "0", "random", "15000", "100", "5", "same", "1000", "16"])

data_m, data_q, data_r = read_csvs()
data_r16 = data_r.loc[data_r['r'] == 16]
data_r2 = data_r.loc[data_r['r'] == 2]

display_graph(plots[0, 0], data_q['n'], data_q['t'], data_m['n'], data_m['t'], data_r2['n'], data_r2['t'], "Quicksort", "Mergesort", "Radix Sort", "Array Size",
    "Running Time (microseconds)", "Running Time vs Array Size with Max = 1000 and Radix Bits = 2")
display_graph(plots[0, 1], data_q['n'], data_q['t'], data_m['n'], data_m['t'], data_r16['n'], data_r16['t'], "Quicksort", "Mergesort", "Radix Sort", "Array Size",
    "Running Time (microseconds)", "Running Time vs Array Size with Max = 1000 and Radix Bits = 16")

subprocess.run(["./sort", "0", "random", "15000", "100", "5", "new", "1000000000", "16"])

data_m, data_q, data_r = read_csvs()
data_r16 = data_r.loc[data_r['r'] == 16]
data_r2 = data_r.loc[data_r['r'] == 2]

display_graph(plots[1, 0], data_q['n'], data_q['t'], data_m['n'], data_m['t'], data_r16['n'], data_r2['t'], "Quicksort", "Mergesort", "Radix Sort", "Array Size",
    "Running Time (microseconds)", "Running Time vs Array Size with Max = 1000000000 and Radix Bits = 2")
display_graph(plots[1, 1], data_q['n'], data_q['t'], data_m['n'], data_m['t'], data_r16['n'], data_r16['t'], "Quicksort", "Mergesort", "Radix Sort", "Array Size",
    "Running Time (microseconds)", "Running Time vs Array Size with Max = 1000000000 and Radix Bits = 16")

plt.legend()
plt.savefig("output/plot.png")
plt.show()
"""
########################################
"""
plt.style.use('dark_background')
fig, plots = plt.subplots(1, 1, figsize=(12, 8), sharex=True, sharey=True)

subprocess.run(["./sort", "0", "sorted", "15000", "100", "5", "new", "1000000000", "16"])

data_m, data_q, data_r = read_csvs()
data_r16 = data_r.loc[data_r['r'] == 16]

display_graph(plots, data_q['n'], data_q['t'], data_m['n'], data_m['t'], data_r16['n'], data_r16['t'], "Quicksort", "Mergesort", "Radix Sort", "Array Size",
    "Running Time (microseconds)", "Running Time vs Array Size with Max = 1000000000, Radix Bits = 16, Presorted")

plt.legend()
plt.savefig("output/plot.png")
plt.show()
"""
#########################################
plt.style.use('dark_background')
fig, plots = plt.subplots(2, 2, figsize=(24, 16), sharex=True, sharey=True)

subprocess.run(["./sort", "0", "random", "15000", "100", "5", "new", "1000", "16"])

data_m, data_q, data_r = read_csvs()
data_r16 = data_r.loc[data_r['r'] == 16]
data_r2 = data_r.loc[data_r['r'] == 2]

display_graph(plots[0, 0], data_q['n'], data_q['m'], data_m['n'], data_m['m'], data_r2['n'], data_r2['m'], "Quicksort", "Mergesort", "Radix Sort", "Array Size",
    "Memory Usage (bytes)", "Memory Usage vs Array Size with Max = 1000, Radix Bits = 2")
display_graph(plots[0, 1], data_q['n'], data_q['m'], data_m['n'], data_m['m'], data_r16['n'], data_r16['m'], "Quicksort", "Mergesort", "Radix Sort", "Array Size",
    "Memory Usage (bytes)", "Memory Usage vs Array Size with Max = 1000, Radix Bits = 16")

subprocess.run(["./sort", "0", "random", "15000", "100", "5", "new", "1000000000", "16"])

data_m, data_q, data_r = read_csvs()
data_r16 = data_r.loc[data_r['r'] == 16]
data_r2 = data_r.loc[data_r['r'] == 2]

display_graph(plots[1, 0], data_q['n'], data_q['m'], data_m['n'], data_m['m'], data_r2['n'], data_r2['m'], "Quicksort", "Mergesort", "Radix Sort", "Array Size",
    "Memory Usage (bytes)", "Memory Usage vs Array Size with Max = 1000000000, Radix Bits = 2")
display_graph(plots[1, 1], data_q['n'], data_q['m'], data_m['n'], data_m['m'], data_r16['n'], data_r16['m'], "Quicksort", "Mergesort", "Radix Sort", "Array Size",
    "Memory Usage (bytes)", "Memory Usage vs Array Size with Max = 1000000000, Radix Bits = 16")

plt.legend()
plt.savefig("output/plot.png")
plt.show()
