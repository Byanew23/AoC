fileName = "day6/input.txt"

def findUniqueSequence(file, length):
    file = open(file, 'r')
    line = file.readline()
    diffLet = line[0:length:]
    res = 0
    for i in range(length, len(line)):
        pairs = []
        for x in range(len(diffLet)):
            if diffLet[x] not in pairs:
                if(x == length-1):
                    res = i
                    break
                pairs.append(diffLet[x])
                continue
            else:
                diffLet = line[i-(length-1):i+1:]
                break
        if res >0:
            break


    print('The solution is:', res)

findUniqueSequence(fileName, 4)
findUniqueSequence(fileName, 14)