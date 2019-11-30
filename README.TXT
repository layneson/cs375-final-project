Run 'make' to build the 'sort' program.

The 'sort' program takes the following mandatory arguments, in order:
  - seed: The seed to use for RNG.
  - gen mode: The method used to fill arrays to be sorted. Must be one of:
    - 'random': Randomly selects numbers from a uniform distribution.
    - 'sorted': Inserts consecutive numbers from a random starting number.
    - 'reverse_sorted': Same as 'sorted' but in decreasing order.
  - max array size: The maximum size of the sorted array.
  - array size step: The amount to increase the array size by each sorting round.
  - repetitions: The number of times each array is sorted.
  - rep mode: The method to use when repeating an array size. Must be one of:
    - 'same': Uses the same array each repetition.
    - 'new': Generates a new array each repetition.
  - max num: The maximum value of any number sorted (all numbers are non-negative).
  - max radix: The maximum base to test with radix sort.

The 'sort' program will create three output CSV files in the 'output' folder.

Running 'python3 plotsorts.py' will run 'sort' to create graphs based
on the current code within the script. It requires pandas, numpy, and
matplotlib as dependencies. The graphs are displayed in a GUI and
saved to the 'output' directory.
