fileName = 'day3/input.txt'

def solveFirst(file):
    file = open(file, 'r')
    lines = file.readlines()
    result = 0
    for line in lines:
        halfPoint = int(len(line.strip())/2)
        found=[]
        firstValues = [0]*halfPoint
        iter = -1
        # go through first half
        for char in line.strip():
            iter+=1
            # Get charactar value
            charVal = ord(char)-96
            if charVal <1:
                charVal = ord(char)-38

            if iter < halfPoint:
                firstValues[iter] = charVal
            else:
                for val in firstValues:
                    if val == charVal:
                        if val in found:
                            break
                        else:
                            result += val
                            found.append(val)
                            break
    print('First result is:',result)

def solveSecond(file):
    file = open(file, 'r')
    lines = file.readlines()
    iter=-1
    first = ''
    secondPass = []
    result = 0
    for line in lines:
        iter+=1
        if iter == 0:
            first = line.strip()

        elif iter == 1:
            # Second Pass
            for char in line.strip():
                if char in first:
                    secondPass.append(char)
        else:
            for char in line.strip():
                if char in secondPass:
                    charVal = ord(char)-96
                    if charVal <1:
                        charVal = ord(char)-38
                    result+=charVal
                    iter = -1
                    first=''
                    secondPass=[]
    print('Second result is:',result)

solveFirst(fileName)
solveSecond(fileName)
