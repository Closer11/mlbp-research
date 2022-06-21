#! /usr/bin/python3
# Creates instance files 

import sys
import os
import argparse
import math

# instance classes
ns = [10, 20, 30, 40, 50, 100, 150, 200]
ms = [1, 2, 3, 4, 5]
qs = [2, 3]

ninst = 10 # number of instances per class


parser = argparse.ArgumentParser(description="Create benchmark instances")
parser.add_argument("destination", nargs=1, type=str, help="Destination folder of created instances")
parser.add_argument("-n", type=int, default=30, help="Number of instances per instance class")
parser.add_argument("-v", "--verbose", help="Let the world know about progress", action="store_true")
args = parser.parse_args()

outfolder = args.destination[0]
ninst = args.n;

for m in ms:
    for n in ns:
        for q in qs:
            for i in range(ninst):
                cmd = './randgen.py {} {} {} --s 1 20 > {}m{:02d}_n{:04d}_q{:01d}__{:03d}.inst'.format(m, n, q, outfolder, m, n, q, i)
                os.system(cmd)
                if args.verbose:
                    print(cmd)
