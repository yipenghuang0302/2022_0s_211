#!/usr/bin/python3

from collatz import autograder as collatz_autograder

total = 0

total += collatz_autograder.grade_collatz ( path="collatz/", verbose=True )

print ("Score on assignment: {} out of 20.".format(total))
