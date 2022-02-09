#!/usr/bin/python3

from balanced import autograder as balanced_autograder
from bstLevelOrder import autograder as bstLevelOrder_autograder
from edgelist import autograder as edgelist_autograder
from isTree import autograder as isTree_autograder
from mst import autograder as mst_autograder
from findCycle import autograder as findCycle_autograder

total = 0

total += balanced_autograder.grade_balanced ( path="balanced/", verbose=True )
total += bstLevelOrder_autograder.grade_bstLevelOrder ( path="bstLevelOrder/", verbose=True )
total += edgelist_autograder.grade_edgelist ( path="edgelist/", verbose=True )
total += isTree_autograder.grade_isTree ( path="isTree/", verbose=True )
total += mst_autograder.grade_mst ( path="mst/", verbose=True )
total += findCycle_autograder.grade_findCycle ( path="findCycle/", verbose=True )

print ("Score on assignment: {} out of 150.".format(total))
