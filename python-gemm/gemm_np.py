#!/usr/bin/python
import sys
import getopt
import numpy as np


def main(argv):
    width = 0
    try:
        opts, args = getopt.getopt(argv, "hw:", ["width="])
    except getopt.GetoptError:
        print 'gemm.py -w <width>'
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print 'gemm.py -w <width>'
            sys.exit()
        elif opt in ("-w", "--width"):
            width = int(arg)

    if width == 0:
        print 'gemm.py -w <width>'
        exit(0)
    else:
        print('Width of square matrix is %d' % (width))
        a = np.random.rand(width, width)
        b = np.random.rand(width, width)
        c = np.dot(a, b)
        # print(c)
        print("Done.")


if __name__ == "__main__":
    main(sys.argv[1:])
