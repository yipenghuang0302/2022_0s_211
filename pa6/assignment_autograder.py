#!/usr/bin/python3

from comparator import autograder as comparator_autograder
from sevenSegmentDisplayE import autograder as sevenSegmentDisplayE_autograder
from sevenSegmentDisplayC import autograder as sevenSegmentDisplayC_autograder
from sevenSegmentDisplay import autograder as sevenSegmentDisplay_autograder
from fullyAssociative import autograder as fullyAssociative_autograder
from setAssociative import autograder as setAssociative_autograder
from binSub import autograder as binSub_autograder

total = 0

total += comparator_autograder.grade_comparator ( path="comparator/", verbose=False )
total += sevenSegmentDisplayE_autograder.grade_sevenSegmentDisplayE ( path="sevenSegmentDisplayE/", verbose=False )
total += sevenSegmentDisplayC_autograder.grade_sevenSegmentDisplayC ( path="sevenSegmentDisplayC/", verbose=False )
total += sevenSegmentDisplay_autograder.grade_sevenSegmentDisplay ( path="sevenSegmentDisplay/", verbose=False )
total += fullyAssociative_autograder.grade_fullyAssociative ( path="fullyAssociative/", verbose=False )
total += setAssociative_autograder.grade_setAssociative ( path="setAssociative/", verbose=False )
total += binSub_autograder.grade_binSub ( path="binSub/", verbose=False )

print ("Score on assignment: {} out of 150.".format(total))
