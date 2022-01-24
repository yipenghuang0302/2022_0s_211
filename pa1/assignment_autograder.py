#!/usr/bin/python3

from greedyScheduling import autograder as greedyScheduling_autograder
from balanced import autograder as balanced_autograder

total = 0

total += greedyScheduling_autograder.grade_greedyScheduling ( path="greedyScheduling/", verbose=True )
total += balanced_autograder.grade_balanced ( path="balanced/", verbose=True )

print ("Score on assignment: {} out of 80.".format(total))
