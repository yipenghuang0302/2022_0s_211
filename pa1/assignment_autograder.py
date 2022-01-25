#!/usr/bin/python3

from greedyScheduling import autograder as greedyScheduling_autograder
from matChainMul import autograder as matChainMul_autograder

total = 0

total += greedyScheduling_autograder.grade_greedyScheduling ( path="greedyScheduling/", verbose=True )
total += matChainMul_autograder.grade_matChainMul ( path="matChainMul/", verbose=True )

print ("Score on assignment: {} out of 40.".format(total))
