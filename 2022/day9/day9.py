fileName = "day9/input.txt"

def moveTail(headPos, tailPos, positions):
    [x,y] = tailPos

    while headPos[0] > x+1 or headPos[0] < x-1 or headPos[1] < y-1 or headPos[1] > y+1:
        # print('x',x,'y',y, headPos)
        # print(positions)
        if (headPos[0] < x-1 and headPos[1] < y) or(headPos[0] < x and headPos[1] < y-1):
            x-=1
            y-=1
            positions = addTailPosition([x,y], positions)
            continue
        elif (headPos[0] < x-1 and headPos[1] > y) or (headPos[0] < x and headPos[1] > y+1):
            x-=1
            y+=1
            positions = addTailPosition([x,y], positions)
            continue
        elif (headPos[0] > x+1 and headPos[1] > y) or (headPos[0] > x and headPos[1] > y+1):
            x+=1
            y+=1
            positions = addTailPosition([x,y], positions)
            continue
        elif (headPos[0] > x+1 and headPos[1] < y) or (headPos[0] > x and headPos[1] < y-1):
            x+=1
            y-=1
            positions = addTailPosition([x,y], positions)
            continue
        # Left
        if headPos[0] < x-1:
            x-=1

        # Right
        if headPos[0] > x+1:
            x+=1

        # Up
        if headPos[1] < y-1:
            y-=1

        # Down
        if headPos[1] > y+1:
            y+=1
        positions = addTailPosition([x,y], positions)
    tailPos = [x,y]
    return [tailPos, positions]

def addTailPosition(currentPos, tailPositions):
    if ",".join(map(str, currentPos)) not in tailPositions:
                tailPositions.append(",".join(map(str, currentPos)))
    return tailPositions

def solveFirst(file):
    file = open(file, 'r')
    lines = file.readlines()
    headPos = [0,0]
    tailPositions = ["0,0"]
    tailPos = [0,0]
    for line in lines:
        [dir, steps] = line.split(" ")
        if dir == 'U':
            headPos[0]-=int(steps)
            [tailPos, tailPositions] = moveTail(headPos, tailPos, tailPositions)
        if dir == 'D':
            headPos[0]+=int(steps)
            [tailPos, tailPositions] = moveTail(headPos, tailPos, tailPositions)
        if dir == 'L':
            headPos[1]-=int(steps)
            [tailPos, tailPositions] = moveTail(headPos, tailPos, tailPositions)
        if dir == 'R':
            headPos[1]+=int(steps)
            [tailPos, tailPositions] = moveTail(headPos, tailPos, tailPositions)


    print('The solution is:', len(tailPositions))

def solveSecond(file):
    file = open(file, 'r')
    lines = file.readlines()

    print('The solution is:', )

solveFirst(fileName)
# solveSecond(fileName)