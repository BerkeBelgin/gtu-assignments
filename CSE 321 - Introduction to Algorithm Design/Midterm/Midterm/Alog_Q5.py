from array import *

def removeElement(yIndex, xIndex, assignments, jobSize, peopleSize, rowSizes, columnSizes, resultAssignment):
    assignments[y][x] = -1
    rowSizes[y] -= 1
    columnSizes[x] -= 1

    if rowSizes[y] == 1 or columnSizes[x] == 1:
        rowSizes[y] = 0
        columnSizes[x] = 0
        for i in range(peopleSize):
            assignments[i][x]
        for i in range(jobSize):
            assignments[y][i]
        resultAssignment[]

def getResult(jobSize, peopleSize, assignments):
    resultLocalMaxAssignment = float('inf')
    resultAssignment = []
    for i in range(peopleSize):
        resultAssignment[i] = -1
    columnSizes = []
    for i in range(peopleSize):
        columnSizes.append(jobSize)
    rowSizes = []
    for i in range(jobSize):
        rowSizes.append(peopleSize)

    maxValue = -1
    while != 0:
        maxValue = 0
        for y in range(jobSize):
            for x in range(peopleSize):
                if assignments[y][x] > maxValue:
                    maxValue = assignments[y][x]
        
        for y in range(jobSize):
            localMaxAssignment = 0
            for x in range(peopleSize):
                if assignments[y][x] == maxValue:
                    removeElement(y, x, assignments,jobSize, peopleSize, rowSizes, columnSizes)
    return resultAssignment

jobSize = 0
while jobSize <= 0:
    jobSize = int(input('Enter the amount of jobs: '))

peopleSize = 0
while peopleSize <= 0:
    peopleSize = int(input('Enter the amount of people: '))


assignments = []
for y in range(jobSize):
    inputArr = input('Job ' + str(y) + ': ').split()
    tempArr = []
    for temp in inputArr:
        tempArr.append(int(temp))
    assignments.append(tempArr)




print(getResult(jobSize, peopleSize, assignments))
