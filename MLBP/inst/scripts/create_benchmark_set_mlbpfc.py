#! /usr/bin/python3
# Creates instance files 

import sys
import os
import argparse
import math

# instance classes
ms = [1, 2, 3]
ns = [5, 10, 15, 20]
ps = [40, 120]
qs = [20, 40, 60]  # total = 720 instances

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
        for p in ps:
            for q in qs:
                for i in range(ninst):
                    cmd = 'py ./randgen.py {} {} {} --s 1 20 --type MLBPFC --p {} --q {} > {}\\m{:02d}_n{:03d}_p{:03d}_q{:03d}__{:03d}.inst'.format(m, n, x, p, q, outfolder, m, n, p, q, i)
                    os.system(cmd)
                    if args.verbose:
                        print(cmd)
