fileName = 'day5/input.txt'

def solveFirst(file):
    file = open(file, 'r')
    lines = file.readlines()
    stacks = {}
    stacking = True
    # initialize the stacks
    for line in lines:
        if line.strip().split(' ')[0] == '1':
            for x in range(int((len(line)+2)/4)):
                stacks[x+1] = []
            break

    # Populate the stacks
    for line in lines:
        if line == '\n' or line.strip().split(' ')[0] == '1':
            stacking = False
            continue
        prev = 1
        if stacking:
            for stack in stacks.keys():
                if len(line) > prev and line[prev] != ' ':
                    stacks[stack].insert(0, line[prev])
                prev += 4

        # Move the crates around
        else:
            [_, count, _, start, _, end] = line.split(' ')
            for i in range(int(count)):
                stacks[int(end)].append(stacks[int(start)].pop())

    # Extract the last crate from each stack
    res = ''
    for key in stacks.keys():
        res += stacks[key].pop()
    print('First result is:', res)

def solveSecond(file):
    file = open(file, 'r')
    lines = file.readlines()
    stacks = {}
    stacking = True
    # initialize the stacks
    for line in lines:
        if line.strip().split(' ')[0] == '1':
            for x in range(int((len(line)+2)/4)):
                stacks[x+1] = []
            break

    # Populate the stacks
    for line in lines:
        if line == '\n' or line.strip().split(' ')[0] == '1':
            stacking = False
            continue
        prev = 1
        if stacking:
            for stack in stacks.keys():
                if len(line) > prev and line[prev] != ' ':
                    stacks[stack].insert(0, line[prev])
                prev += 4

        # Move the crates around
        else:
            [_, count, _, start, _, end] = line.split(' ')
            for i in stacks[int(start)][-int(count)::]:
                stacks[int(end)].append(i)
            stacks[int(start)][-int(count)::] = []

    # Extract the last crate from each stack
    res = ''
    for key in stacks.keys():
        res += stacks[key].pop()
    print('Second result is:', res)

solveFirst(fileName)
solveSecond(fileName)
