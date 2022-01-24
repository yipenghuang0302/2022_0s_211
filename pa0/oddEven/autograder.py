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

        if integer%2:
            outfile.write("odd")
        else:
            outfile.write("even")

def generate_test_suite():

    os.makedirs("tests", exist_ok=True)
    os.makedirs("answers", exist_ok=True)

    generate_test ( 0, max=4, path="./" )
    generate_test ( 1, max=16, path="./" )
    generate_test ( 2, max=256, path="./" )
    generate_test ( 3, max=1024, path="./" )

def test_oddEven ( filenum, path="./", verbose=False ):

    try:
        with open("{}answers/answer{}.txt".format(path,filenum), "r") as outfile:
            answerString = outfile.read().split('\n')[0]

    except EnvironmentError: # parent of IOError, OSError
        print ("answers/answer{}.txt missing".format(filenum))

    try:
        with open("{}tests/test{}.txt".format(path,filenum), "r") as infile:
            number = infile.read().split('\n')[0]

            result = subprocess.run(
                ["./oddEven", number],
                cwd=path,
                check=True,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                encoding="ASCII",
                timeout=datetime.timedelta(seconds=2).total_seconds(),
            )

            resultString = result.stdout.split()[0]

            if verbose:
                print (' '.join(result.args))
                # print ("answerString")
                # print (answerString)
                # print ("resultString")
                # print (resultString)
            assert resultString == answerString, "The oddEven result doesn't match answers/answer{}.txt.".format(filenum)
            return True
    except subprocess.CalledProcessError as e:
        print (e.output)
        print ("Calling ./oddEven returned an error.")
    except ValueError as e:
        print (' '.join(result.args))
        print (result.stdout)
        print ("Please check your output formatting.")
    except AssertionError as e:
        print (result.stdout)
        print (e.args[0])

    return False

def grade_oddEven( path="./", verbose=False ):

    score = 0

    try:
        subprocess.run( ["make", "clean"], cwd=path, check=True, )
        subprocess.run( ["make", "-B"], cwd=path, check=True, )
    except subprocess.CalledProcessError as e:
        print ("Couldn't compile oddEven.c.")
        return score

    if test_oddEven(0,path,verbose):
        score += 2
        if test_oddEven(1,path,verbose):
            score += 2
            if test_oddEven(2,path,verbose):
                score += 2
                if test_oddEven(3,path,verbose):
                    score+= 2
                    allPass = True
                    for filenum in range(8,16):
                        generate_test ( filenum, max=65536, path=path )
                        allPass &= test_oddEven(filenum,path,verbose)
                    if allPass:
                        score+=2

    print ("Score on oddEven: {} out of 10.".format(score))
    return score

if __name__ == '__main__':
    # generate_test_suite()
    grade_oddEven(verbose=True)
    exit()
