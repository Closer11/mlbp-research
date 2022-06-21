#! /usr/bin/python3
# Creates instance files 

import sys
import os
import argparse

# instance classes
ms = [1, 2, 3, 4, 5]
ns = [10, 15, 20, 25, 30, 35, 40, 45, 50, 100]

x = 2 # number of times first fit is repeated

ninst = 10 # number of instances per class


parser = argparse.ArgumentParser(description="Create benchmark instances")
parser.add_argument("-destination", nargs=1, type=str, default='.', help="Destination folder of created instances")
parser.add_argument("-n", type=int, default=10, help="Number of instances per instance class")
parser.add_argument("-v", "--verbose", help="Let the world know about progress", action="store_true")
args = parser.parse_args()

outfolder = args.destination[0]
ninst = args.n;

for m in ms:
    for n in ns:
        for i in range(ninst):
            cmd = 'py ./randgen.py {} {} {} --s 1 20 --type MLBP > {}\\m{:02d}_n{:04d}__{:03d}.inst'.format(m, n, x, outfolder, m, n, i)
            os.system(cmd)
            if args.verbose:
                print(cmd)
