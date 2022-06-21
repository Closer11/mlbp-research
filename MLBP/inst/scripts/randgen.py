#! /usr/bin/python3
# Writes a problem instance to stdout 

import sys
import random
import argparse
import math
import itertools

# returns a flat list of a list of lists t
def flatten(t):
    return [item for sublist in t for item in sublist]


def first_fit(items, s, capacities):
    random.shuffle(items)  # insert items in random order
    bins = [(0, c, 0) for c in capacities]
    for item in items:
        inserted = False
        for pos, b in enumerate(bins):
            if b[0] + s[item] <= b[1]:
                bins[pos] = (b[0] + s[item], b[1], b[2] + 1)
                inserted = True
                break
        if inserted == False:
            # item could not be inserted -> create new bin with a capacity between s[item] ... s[item] * 1.9
            bins.append((s[item], s[item] + random.randint(0, int(math.ceil(s[item] * 0.9))), 1))
    return bins


def print_mlbp(m, N, S, W, C):
    print(m)
    print(*N, sep=' ')
    for i in range(m+1):
        print(*S[i], sep=' ')
    for i in range(1, m+1):
        print(*W[i], sep=' ')
    for i in range(1, m+1):
        print(*C[i], sep=' ')


# Read input parameters
parser = argparse.ArgumentParser()
parser.add_argument("m", help="number of levels", type=int)
parser.add_argument("n", help="number of items", type=int)
parser.add_argument("x", help="number of times first fit algorithm is repeated to create bins", type=int)
parser.add_argument("--s", help="sample range of item sizes", type=int, nargs=2)
parser.add_argument("--type", help="problem type", choices=['MLBP','MLBPFC'], type=str, default='MLBP')
parser.add_argument("--p", help="penalty factor", type=int, default=0)
parser.add_argument("--q", help="maximum number of different groups", type=int, default=100)
args = parser.parse_args()

s_min = 1
s_max = 100
if args.s != None:
        s_min = args.s[0]
        s_max = args.s[1]

N = [0]*(args.m+1)                 # number of items/bins
S = [[] for _ in range(args.m+1)]  # item/bins sizes
W = [[] for _ in range(args.m+1)]  # bin capacities
C = [[] for _ in range(args.m+1)]  # bin cost

# sample item sizes
N[0] = args.n
S[0] = [random.randint(s_min, s_max+1) for _ in range(args.n)]

# sample bins
for j in range(args.x):
    for i in range(args.m):
        bins = first_fit(list(range(N[i])), S[i], W[i+1])
        S[i+1] = [b[1] + random.randint(0, int(b[1] * 0.5)) for b in bins]
        W[i+1] = [b[1] for b in bins]
        N[i+1] = len(S[i+1])
        C[i+1] = [int(100*math.sqrt(s)) for s in S[i+1]]

print_mlbp(args.m, N, S, W, C)

if args.type == 'MLBPFC':
    # sample groups
    r = int(args.n * args.q / 100.0)
    G = [random.randint(1, r) for _ in range(args.n)]

    print(args.p, args.q)
    print(*G, sep=' ')
