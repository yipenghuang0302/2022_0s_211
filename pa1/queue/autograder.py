#!/usr/bin/python3

import os
import random
import subprocess

def generate_test ( filenum, length, prefix=None ):

    queue = []

    # print (string)
    with open("{}tests/test{}.txt".format(prefix if prefix else "",filenum), "w") as infile:
        for _ in range(length):
            enqueue = bool(random.getrandbits(1))
            if enqueue:
                num = random.randrange(256)
                queue.append(num)
                infile.write("ENQUEUE {}\n".format(num))
            elif queue:
                infile.write("DEQUEUE\n".format(num))
                queue.pop(0)

    with open("{}answers/answer{}.txt".format(prefix if prefix else "",filenum), "w") as outfile:
        for num in queue:
            outfile.write("{} ".format(num))

def generate_test_suite():

    if not os.path.exists("tests"):
        os.mkdir("tests")
    if not os.path.exists("answers"):
        os.mkdir("answers")

    generate_test ( 0, 4 )
    generate_test ( 1, 16 )
    generate_test ( 2, 256 )
    generate_test ( 3, 65536 )

def test_queue( filenum, prefix=None, verbose=False ):

    command = prefix if prefix else "."
    command += "/queue {}tests/test{}.txt".format(prefix if prefix else "",filenum)
    if verbose:
        print (command)

    try:
        with open("{}answers/answer{}.txt".format(prefix if prefix else "",filenum), "r") as outfile:
            answerlist = [ int(num) for num in outfile.read().split() ]
    except EnvironmentError: # parent of IOError, OSError
        print ("answers/answer{}.txt missing".format(filenum))

    try:
        result = subprocess.check_output(command, shell=True).decode('ascii')
        resultlist = [int(string) for string in result.split()]
        assert resultlist == answerlist, "Your answer doesn't match answers/answer{}.txt.".format(filenum)
        return True
    except subprocess.CalledProcessError as e:
        # print (e.output)
        print ("Calling ./queue returned non-zero exit status.")
    except AssertionError as e:
        print (result)
        print (e.args[0])

    return False

def grade_queue( prefix=None, verbose=False ):

    score = 0

    command = "make"
    if prefix:
        command += " --directory=" + prefix
    if verbose:
        print (command)
    try:
        subprocess.check_output(command, shell=True)
        score += 5
    except subprocess.CalledProcessError as e:
        print ("Couldn't compile queue.")
        return score

    if test_queue(0,prefix,verbose):
        score += 3
        if test_queue(1,prefix,verbose):
            score += 3
            if test_queue(2,prefix,verbose):
                score += 3
                if test_queue(3,prefix,verbose):
                    score += 3

                    allpass = True
                    for filenum in range(4,12):
                        generate_test ( filenum, 65536, prefix )
                        allpass &= test_queue(filenum,prefix,verbose)
                    if allpass:
                        score += 5

    print ("Score on queue: {} out of 22.".format(score))
    return score

if __name__ == '__main__':
    # generate_test_suite()
    grade_queue(verbose=True)
    exit()
