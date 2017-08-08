#!/usr/bin/python
import sys
import getopt
import numpy as np
import tensorflow as tf


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
        #m1 = [[1,2,3],[4,5,6],[7,8,9]]
        #m2 = [[1,1,1],[1,0,1],[0,1,0]]
        #m3 = np.dot(m1,m2)
        # print(m3)
        a = np.random.rand(width, width)
        b = np.random.rand(width, width)
        A = tf.constant(a, dtype=tf.float64)
        B = tf.constant(b, dtype=tf.float64)
        with tf.Session() as sess:
            C = tf.matmul(A, B).eval()
            #M1 = tf.constant(m1, dtype=tf.float64)
            #M2 = tf.constant(m2, dtype=tf.float64)
            #M3 = tf.matmul(M1,M2).eval()
            # print(M3)
        print("Done.")


if __name__ == "__main__":
    main(sys.argv[1:])
