"""Softmax."""

scores = [3.0, 1.0, 0.2]

import numpy as np

def softmax(x):
    """Compute softmax values for each sets of scores in x."""
    sum=0
    for i in range(0,len(x)-1):
        print i
        sum = sum + np.exp(x[i])
        print("sum of exp(x) %lf.  %s  " % (sum, "Done."))
        return softmax

print(softmax(scores))
