def clearColumn(x, assignments, sizeY, columnSizes, resultAssignment):
    foundY = 0
    columnSizes[x] = 0
    for i in range(sizeY):
        if assignments[i][x] != -1:
            print(assignments[i][x])
            foundY = i
            resultAssignment[x] = assignments[i][x]
            assignments[i][x] = -1
    return foundY

def clearRow(y, assignments, sizeX, rowSizes, resultAssignment):
    foundX = 0
    rowSizes[y] = 0
    for i in range(sizeX):
        if assignments[y][i] != -1:
            print(assignments[y][i])
            foundX = i
            resultAssignment[i] = assignments[y][i]
            assignments[y][i] = -1
    return foundX

def removeElement(y, x, assignments, sizeY, sizeX, rowSizes, columnSizes, resultAssignment):
    assignments[y][x] = -1
    rowSizes[y] -= 1
    columnSizes[x] -= 1

    if columnSizes[x] == 1:
        foundY = clearColumn(x, assignments, sizeY, columnSizes, resultAssignment)
    
    if rowSizes[y] == 1:
        foundX = clearRow(y, assignments, sizeX, rowSizes, resultAssignment)
        
def getResult(sizeY, sizeX, assignments):
    resultLocalMaxAssignment = float('inf')
    
    resultAssignment = []
    rowSizes = []
    columnSizes = []
    
    for i in range(sizeX):
        resultAssignment.append(-1)
    for i in range(sizeY):
        rowSizes.append(sizeX)
    for i in range(sizeX):
        columnSizes.append(sizeY)

    maxValue = -1
    while maxValue != 0:
        for i in range(sizeY):
            print(assignments[i])
        print('')

        
        maxValue = 0
        for y in range(sizeY):
            for x in range(sizeX):
                if assignments[y][x] > maxValue:
                    maxValue = assignments[y][x]
        for y in range(sizeY):
            for x in range(sizeX):
                if assignments[y][x] == maxValue:
                    removeElement(y, x, assignments,sizeY, sizeX, rowSizes, columnSizes, resultAssignment)
    return resultAssignment

assignments = [
    [6, 2, 3, 2, 8],
    [7, 4, 1, 9, 33],
    [11, 32, 24, 12, 5],
    [7, 14, 7, 3, 1],
]

sizeY = len(assignments) #jobSize
sizeX = len(assignments[0]) #peopleSize

print(getResult(sizeY, sizeX, assignments))
