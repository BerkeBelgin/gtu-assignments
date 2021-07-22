def heapify(arr, n, i): 
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2
    
    if l < n and arr[i] < arr[l]: 
        largest = l 

    if r < n and arr[largest] < arr[r]: 
        largest = r

    if largest != i: 
        arr[i],arr[largest] = arr[largest],arr[i]
        heapify(arr, n, largest) 
   
def heapSort(arr): 
    n = len(arr) 

    for i in range(n // 2 - 1, -1, -1): 
        heapify(arr, n, i) 

    for i in range(n-1, 0, -1): 
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)

def findMultipliers(arr, num):
    indxStart = 0
    indxEnd = len(arr) - 1

    while indxStart != indxEnd:
        if arr[indxStart] * arr[indxEnd] == num:
            print(arr[indxStart],arr[indxEnd])
            indxStart += 1
        elif num % arr[indxStart] == 0:
            indxEnd -= 1
        else:
            indxStart += 1

arr = [1,2,3,6,5,4]
heapSort(arr)
findMultipliers(arr, 6)
