fileName = "day10/input.txt"

def checkCycle(x, xReg, signals):
    if x == 20 or (x-20)%40==0:
        signals.append(xReg*x)

def drawCRT(cycle, xReg, crt, rowNumber):
    pos = cycle-1
    # print(cycle, xReg, pos, crt)
    if(cycle >= 40):
        pos = cycle - (40 * (rowNumber))-1
    if cycle%40 == 0:
        # add last pixel
        if xReg-1 <= pos <= xReg+1:
            crt[rowNumber].append("#")
        else:
            crt[rowNumber].append(".")
        crt.append([])
        rowNumber+=1
        return rowNumber

    if xReg-1 <= pos <= xReg+1:
        crt[rowNumber].append("#")
    else:
        crt[rowNumber].append(".")
    return rowNumber

def solveFirst(file):
    file = open(file, 'r')
    lines = file.readlines()
    cycle = 0
    xReg = 1
    signalStrenghts = []
    for line in lines:
        command = line.strip().split(" ")
        # noop
        if len(command) == 1:
            cycle += 1
            checkCycle(cycle, xReg, signalStrenghts)
            continue
        else:
            for i in range(2):
                cycle+=1
                checkCycle(cycle, xReg, signalStrenghts)
            val = int(command[1])
            xReg += val

    res=0
    for num in signalStrenghts:
        res+=num
    print('The solution is:', res)

def solveSecond(file):
    file = open(file, 'r')
    lines = file.readlines()
    cycle = 0
    xReg = 1
    rowNumber = 0
    pixelRows = [[]]
    for line in lines:
        command = line.strip().split(" ")
        # noop
        if len(command) == 1:
            cycle += 1
            rowNumber = drawCRT(cycle, xReg, pixelRows, rowNumber)
            continue
        else:
            for i in range(2):
                cycle+=1
                rowNumber = drawCRT(cycle, xReg, pixelRows, rowNumber)
            val = int(command[1])
            xReg += val

    res=0
    for pixels in pixelRows:
        print(*pixels)
    print('The solution is:', res)

# solveFirst(fileName)
solveSecond(fileName)