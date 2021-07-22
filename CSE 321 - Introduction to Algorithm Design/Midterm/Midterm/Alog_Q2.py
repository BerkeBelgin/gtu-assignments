def findMissing(bitArray, arraySize, bitSize):
    resultInt = []
    for bitIndex in range(bitSize - 1, -1, -1):
        evenCount = 0
        evenArray = []
        
        oddCount = 0
        oddArray = []
        
        for arrayIndex in range(arraySize):
            if bitArray[arrayIndex * bitSize + bitIndex] == 0:
                evenCount += 1
                for bit in range(bitSize):
                    evenArray.append(bitArray[arrayIndex * bitSize + bit]) 
            elif bitArray[arrayIndex * bitSize + bitIndex] == 1:
                oddCount += 1
                for bit in range(bitSize):
                    oddArray.append(bitArray[arrayIndex * bitSize + bit])     
            else:
                return [-1]

        if evenCount <= oddCount:
            bitArray = evenArray
            arraySize = evenCount
            resultInt.insert(0, 0)
        else:
            bitArray = oddArray
            arraySize = oddCount
            resultInt.insert(0, 1)
    return resultInt

array = [
    0, 0, 0, 0,
    0, 0, 0, 1,
    0, 0, 1, 0,
    0, 0, 1, 1,
    0, 1, 0, 0,
    0, 1, 0, 1,
    0, 1, 1, 0,
    0, 1, 1, 1,
    1, 0, 0, 0,
    1, 0, 0, 1,
    1, 0, 1, 0,
    1, 0, 1, 1,
    1, 1, 0, 0,
    1, 1, 0, 1,
    1, 1, 1, 0,
    #1, 1, 1, 1,
]
arraySize = 15
bitSize = 4

print(findMissing(array, arraySize, bitSize))
