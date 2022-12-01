fileName = 'day1/input.txt'

def firstPart(file):
    file = open(file, 'r')
    Lines = file.readlines()
    currMax = 0
    max = 0
    iters=0
    for line in Lines:
        iters+=1
        if(line == "\n"):
            if(currMax>max):
                max = currMax
            currMax = 0
            continue
        currMax+= int(line)
        if(iters == len(Lines) and currMax > max):
            max = currMax
            continue

    print(max)

def secondPart(file):
    file = open(file, 'r')
    Lines = file.readlines()
    index=0
    currMax = 0
    maxes = [0]*len(Lines)
    iters = 0
    for line in Lines:
        iters+=1
        if(line == "\n"):
            if(currMax>maxes[index]):
                maxes[index] = currMax
            index+=1
            currMax = 0
            continue
        currMax+= int(line)
        if(iters == len(Lines)):
            maxes[index] = int(line)
            continue

    maxes.sort(reverse=True)
    result = 0
    for i in range(3):
        result += maxes[i]
    print(result)

firstPart(fileName)
secondPart(fileName)