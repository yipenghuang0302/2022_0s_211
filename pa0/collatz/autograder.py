#!/usr/bin/python3

import os
import datetime
import random
import subprocess

def generate_test ( filenum, max=256, path="./" ):

    integer = random.randrange(1,max)

    with open("{}tests/test{}.txt".format(path,filenum), "w") as infile:

        infile.write(str(integer))
        infile.write("\n")

    with open("{}answers/answer{}.txt".format(path,filenum), "w") as outfile:

        while integer != 1:
            outfile.write("{}\n".format(integer))
            if integer%2:
                integer = 3*integer+1
            else:
                integer = integer>>1

        outfile.write("{}\n".format(integer))

def generate_test_suite():

    os.makedirs("tests", exist_ok=True)
    os.makedirs("answers", exist_ok=True)

    generate_test ( 0, max=4, path="./" )
    generate_test ( 1, max=16, path="./" )
    generate_test ( 2, max=256, path="./" )
    generate_test ( 3, max=1024, path="./" )

def test_collatz ( filenum, path="./", verbose=False ):

    try:
        with open("{}answers/answer{}.txt".format(path,filenum), "r") as outfile:
            answerList = []
            for line in outfile.read().split('\n'):
                if line:
                    answerList.append(int(line))
    except EnvironmentError: # parent of IOError, OSError
        print ("answers/answer{}.txt missing".format(filenum))

    try:
        result = subprocess.run(
            ["./collatz", "tests/test{}.txt".format(filenum)],
            cwd=path,
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            encoding="ASCII",
            timeout=datetime.timedelta(seconds=2).total_seconds(),
        )

        resultList = []
        for line in result.stdout.split():
            resultList.append(int(line))

        if verbose:
            print (' '.join(result.args))
            # print ("answer")
            # print (answerList)
            # print ("result")
            # print (result.stdout)
        assert resultList == answerList, "The Collatz sequence result doesn't match answers/answer{}.txt.".format(filenum)
        return True
    except subprocess.CalledProcessError as e:
        print (e.output)
        print ("Calling ./collatz returned an error.")
    except ValueError as e:
        print (' '.join(result.args))
        print (result.stdout)
        print ("Please check your output formatting.")
    except AssertionError as e:
        print (result.stdout)
        print (e.args[0])

    return False

def grade_collatz( path="./", verbose=False ):

    score = 0

    try:
        subprocess.run( ["make", "clean"], cwd=path, check=True, )
        subprocess.run( ["make", "-B"], cwd=path, check=True, )
    except subprocess.CalledProcessError as e:
        print ("Couldn't compile collatz.c.")
        return score

    if test_collatz(0,path,verbose):
        score += 4
        if test_collatz(1,path,verbose):
            score += 4
            if test_collatz(2,path,verbose):
                score += 4
                if test_collatz(3,path,verbose):
                    score+= 4
                    allPass = True
                    for filenum in range(8,16):
                        generate_test ( filenum, max=65536, path=path )
                        allPass &= test_collatz(filenum,path,verbose)
                    if allPass:
                        score+=4

    print ("Score on collatz: {} out of 20.".format(score))
    return score

if __name__ == '__main__':
    # generate_test_suite()
    grade_collatz(verbose=True)
    exit()
