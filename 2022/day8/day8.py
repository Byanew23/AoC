fileName = "day8/input.txt"


def makeForestMap(lines):
    forestMap = []
    for line in lines:
        forestMap.append([*line.strip()])
    return forestMap

def checkIfVisible(x,y,forestMap):
    current = int(forestMap[y][x])
    vals = {'top': True, 'bot': True, 'left': True, 'right': True }
    # Check left:
    index = 0
    while index < x:
        if int(forestMap[y][index]) >= current:
            vals['left'] = False
            break
        index+=1

    # Check right:
    index = x+1
    while index < len(forestMap[y]):
        if int(forestMap[y][index]) >= current:
            vals['right'] = False
            break
        index+=1

    # Check top:
    index = 0
    while index < y:
        if int(forestMap[index][x]) >= current:
            vals['top'] = False
            break
        index+=1

    # Check bottom:
    index = y+1
    while index < len(forestMap):
        if int(forestMap[index][x]) >= current:
            vals['bot'] = False
            break
        index+=1

    return any(vals.values())

def checkTreeScore(x,y,forestMap):
    if y == 0 or x == 0 or y == len(forestMap)-1 or x == len(forestMap[y])-1:
        return 0
    scores = []
    current = int(forestMap[y][x])
    currScore = 0

    # Check top:
    index = y-1
    while index >= 0:
        currScore += 1
        if int(forestMap[index][x]) >= current or index == 0:
            scores.append(currScore)
            currScore = 0
            break
        index-=1

    # Check left:
    index = x-1

    while index >= 0:
        currScore +=1
        if int(forestMap[y][index]) >= current or index == 0:
            scores.append(currScore)
            currScore = 0
            break
        index-=1

    # Check bottom:
    index = y+1
    while index < len(forestMap):
        currScore+=1
        if int(forestMap[index][x]) >= current or index == len(forestMap)-1:
            scores.append(currScore)
            currScore = 0
            break
        index+=1

    # Check right:
    index = x+1
    while index < len(forestMap[y]):
        currScore += 1
        if int(forestMap[y][index]) >= current or index == len(forestMap[y])-1:
            scores.append(currScore)
            currScore = 0
            break
        index+=1

    prod = 1
    for val in scores:
        prod = prod*val

    return prod

def solveFirst(file):
    file = open(file, 'r')
    lines = file.readlines()
    visibleCount = 0
    forestMap = makeForestMap(lines)

    for y in range(len(forestMap)):
        for x in range(len(forestMap[y])):
            if y == 0 or x == 0 or y == len(forestMap)-1 or x == len(forestMap[y])-1:
                visibleCount+=1
            else:
                isTreeVisible = checkIfVisible(x,y,forestMap)
                if isTreeVisible:
                    visibleCount += 1
    print('The solution is:', visibleCount)

def solveSecond(file):
    file = open(file, 'r')
    lines = file.readlines()
    forestMap = makeForestMap(lines)
    treeScores = []
    for y in range(len(forestMap)):
        for x in range(len(forestMap[y])):
            treeScores.append(checkTreeScore(x,y,forestMap))

    treeScores.sort()
    res = treeScores[-1]
    print('The solution is:', res)

solveFirst(fileName)
solveSecond(fileName)