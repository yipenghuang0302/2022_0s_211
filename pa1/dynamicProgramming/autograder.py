#!/usr/bin/python3

import os
import datetime
import random
import subprocess
import numpy

def cost ( matDims ):
    # matDims are an array of tuples; first element of tuple is row count, second element of tuple is col count
    if len(matDims)==1:
        return 0
    else:
        costs = []
        for split in range( 0, len(matDims)-1 ):
            splitCost = cost( matDims[:split+1] ) + matDims[0][0]*matDims[split][1]*matDims[-1][1] + cost( matDims[split+1:] )
            costs.append ( splitCost )
    return min(costs)

def generate_test ( filenum, matCount=2, maxDim=4, path="./" ):

    matDims = []
    matDims.append( (random.randrange(1,maxDim), random.randrange(1,maxDim)) )
    for matIndex in range(1, matCount):
        matDims.append( (matDims[matIndex-1][1], random.randrange(1,maxDim)) )
    # print("matDims=")
    # print(matDims)

    with open("{}tests/test{}.txt".format(path,filenum), "w") as infile:
        infile.write("{}\n".format(matCount))
        for matIndex in range(matCount):
            infile.write("{} {}\n".format(matDims[matIndex][0], matDims[matIndex][1]))

    with open("{}answers/answer{}.txt".format(path,filenum), "w") as outfile:

        outfile.write( "{}\n".format( cost(matDims) ) )

def generate_test_suite():

    os.makedirs("tests", exist_ok=True)
    os.makedirs("answers", exist_ok=True)

    generate_test ( 0, matCount=2, maxDim=4, path="./" )
    generate_test ( 1, matCount=3, maxDim=4, path="./" )
    generate_test ( 2, matCount=4, maxDim=4, path="./" )
    generate_test ( 3, matCount=4, maxDim=8, path="./" )
    generate_test ( 4, matCount=8, maxDim=8, path="./" )
    generate_test ( 5, matCount=8, maxDim=16, path="./" )

def test_dynamicProgramming ( filenum, path="./", verbose=False ):

    try:
        with open("{}answers/answer{}.txt".format(path,filenum), "r") as outfile:
            lines = outfile.read().split('\n')
            answerMulCount = int(lines[0])

    except EnvironmentError: # parent of IOError, OSError
        print ("answers/answer{}.txt missing".format(filenum))

    try:
        result = subprocess.run(
            ["./dynamicProgramming", "tests/test{}.txt".format(filenum)],
            cwd=path,
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            encoding="ASCII",
            timeout=datetime.timedelta(seconds=2).total_seconds(),
        )

        lines = result.stdout.split('\n')
        resultMulCount = int(lines[0])

        if verbose:
            print (' '.join(result.args))
            print ("answerMulCount")
            print (answerMulCount)
            print ("resultMulCount")
            print (resultMulCount)
        assert resultMulCount == answerMulCount, "The optimal number of multiplications you used doesn't match answers/answer{}.txt.".format(filenum)
        return True
    except subprocess.CalledProcessError as e:
        print (e.output)
        print ("Calling ./dynamicProgramming returned an error.")
    except ValueError as e:
        print (' '.join(result.args))
        print (result.stdout)
        print ("Please check your output formatting.")
    except AssertionError as e:
        print (result.stdout)
        print (e.args[0])

    return False

def grade_dynamicProgramming( path="./", verbose=False ):

    score = 0

    try:
        subprocess.run( ["make", "clean"], cwd=path, check=True, )
        subprocess.run( ["make", "-B"], cwd=path, check=True, )
    except subprocess.CalledProcessError as e:
        print ("Couldn't compile dynamicProgramming.c.")
        return score

    if test_dynamicProgramming(0,path,verbose):
        score += 3
        if test_dynamicProgramming(1,path,verbose):
            score += 3
            if test_dynamicProgramming(2,path,verbose):
                score += 3
                if test_dynamicProgramming(3,path,verbose):
                    score+= 3
                    if test_dynamicProgramming(4,path,verbose):
                        score+= 3
                        if test_dynamicProgramming(5,path,verbose):
                            score+= 3
                            allPass = True
                            for filenum in range(6,16):
                                generate_test ( filenum, matCount=8, maxDim=16, path=path )
                                allPass &= test_dynamicProgramming(filenum,path,verbose)
                            if allPass:
                                score+=2

    print ("Score on dynamicProgramming: {} out of 20.".format(score))
    return score

if __name__ == '__main__':
    # generate_test_suite()
    grade_dynamicProgramming(verbose=True)
    exit()
