fileName = 'day4/input.txt'

def solveFirst(file):
    file = open(file, 'r')
    lines = file.readlines()
    result = 0
    for line in lines:
        [firstRange, secondRange] = line.split(',')
        [firstStart, firstEnd] = firstRange.split('-')
        [secondStart, secondEnd] = secondRange.split('-')

        if int(firstStart.strip()) <= int(secondStart.strip()) and int(firstEnd.strip()) >= int(secondEnd.strip()):
            result+=1
        elif int(secondStart.strip()) <= int(firstStart.strip()) and int(secondEnd.strip()) >= int(firstEnd.strip()):
            result+=1

    print('First result is:', result)

def solveSecond(file):
    file = open(file, 'r')
    lines = file.readlines()
    result = 0
    for line in lines:
        [firstRange, secondRange] = line.split(',')
        [firstStart, firstEnd] = firstRange.split('-')
        [secondStart, secondEnd] = secondRange.split('-')

        firstStart = int(firstStart.strip())
        secondStart = int(secondStart.strip())
        firstEnd = int(firstEnd.strip())
        secondEnd = int(secondEnd.strip())

        if firstStart >= secondStart and firstStart <= secondEnd:
            result+=1
        elif firstEnd >= secondStart and firstEnd <= secondEnd:
            result+=1
        elif secondStart >= firstStart and secondStart <= firstEnd:
            result+=1
        elif secondEnd >= firstStart and secondEnd <= firstEnd:
            result+=1



    print('Second result is:', result)

solveFirst(fileName)
solveSecond(fileName)
