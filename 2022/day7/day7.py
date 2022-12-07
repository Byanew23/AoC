fileName = "day7/input.txt"

def solveFirst(file, showRes):
    file = open(file, 'r')
    lines = file.readlines()
    currentDir = []
    sizes = {}
    res = 0
    totalSpace = 0
    for line in lines:
        command = line.strip().split(' ')
        # If the command is `cd`
        if len(command) == 3:
            arg = command[-1]

            # Add the size of the current folder to its parent
            if arg == '..':
                # If directory is less than 100 000 add it to the total
                if 0 < sizes[currentDir[-1]] <= 100000 :
                    res += sizes[currentDir[-1]]
                prev = currentDir.pop()
                sizes[currentDir[-1]] += sizes[prev]
            else:
                currentDir.append(arg)
                sizes[arg] = 0

        # If the command is ls
        else:
            [size, _] = line.strip().split(' ')

            if size not in ['dir', '$']:
                sizes[currentDir[-1]] += int(size)
                totalSpace += int(size)
    # Account for last directories after end of commands
    while len(currentDir) >= 1:
        print(currentDir, sizes['/'], sizes[currentDir[-1]])
        prev = currentDir.pop()
        if len(currentDir) == 1:
            sizes['/'] += sizes[prev]
            print('last loop?', sizes['/'])
            break
        else:
            sizes[currentDir[-1]] += sizes[prev]
        if(sizes[prev] <= 100000):
            res += sizes[prev]

    if showRes:
        print('The solution is:', res)

    return [sizes, totalSpace]

def solveSecond(file):
    totalSpace = 70000000
    updateSpace = 30000000
    [sizes, usedSpace] = solveFirst(file, False)
    freeSpace = totalSpace-usedSpace
    neededSpace = updateSpace - freeSpace
    res = totalSpace

    print(usedSpace)

    if freeSpace >= usedSpace:
        print('There is already enough space!')
        return

    for key in sizes.keys():
        if neededSpace <= sizes[key] <= res:
            res = sizes[key]

    print(freeSpace, neededSpace, sizes['/'])
    print('The solution is:', res)

solveFirst(fileName, True)
solveSecond(fileName)