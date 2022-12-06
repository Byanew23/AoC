fileName = "day6/sample.txt"

def solveFirst(file):
    file = open(file, 'r')
    line = file.readline()
    diffLet = ""
    index = 0

    for char in line:
        if char not in diffLet:
            diffLet += char

solveFirst(fileName)