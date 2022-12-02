points = {'R': 1, 'P':2, 'S':3}
finalPoints = {'W': 6, 'D':3, 'L':0}
map = {'A': 'R', 'B': 'P', 'C':'S', 'X': 'R', 'Y': 'P', 'Z':'S'}

fileName = 'day2/input.txt'

def solveFirst(file):
    f = open(file, 'r')
    lines = f.readlines()

    res = 0
    for line in lines:
        played = line.split(' ')
        played[0] = played[0].strip()
        played[1] = played[1].strip()

        # Add points of what you've chosen
        res += points[map[played[1]]]

        # Draw
        if map[played[0]] == map[played[1]]:
            res += finalPoints['D']

        # Win
        elif((map[played[0]] == 'R' and map[played[1]] == 'P') or (map[played[0]] == 'P' and map[played[1]] == 'S') or (map[played[0]] == 'S' and map[played[1]] == 'R')):
            res += finalPoints['W']
    print('The first score is:',res)

def solveSecond(file):
    f = open(file, 'r')
    lines = f.readlines()
    outcomes = {'X': 'L', 'Y': 'D', 'Z':'W'}
    scenarios = {'W': {'P': 'S', 'S': 'R', 'R': 'P'}, 'L': {'P': 'R', 'S': 'P', 'R': 'S'}, 'D': {'P': 'P', 'S':'S','R':'R'}}
    res = 0
    for line in lines:
        played = line.split(' ')
        played[0] = played[0].strip()
        played[1] = played[1].strip()
        res += finalPoints[outcomes[played[1]]]
        res += points[scenarios[outcomes[played[1]]][map[played[0]]]]
    print('The second score is:',res)


solveFirst(fileName)
solveSecond(fileName)