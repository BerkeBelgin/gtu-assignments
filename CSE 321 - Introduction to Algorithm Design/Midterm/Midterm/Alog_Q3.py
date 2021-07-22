def insertionSort(array, low, high): 
    for index in range(low + 1, high + 1): 
        element = array[index] 
        shiftIndex = index
        while shiftIndex > low and array[shiftIndex - 1] > element: 
            array[shiftIndex] = array[shiftIndex - 1] 
            shiftIndex -= 1
        array[shiftIndex] = element 

def partition(array, low, high): 
    pivot = array[high] 

    j = low
    for i in range(low, high): 
        if array[i]<pivot:
            temp = array[i]
            array[i] = array[j]
            array[j] = temp
            j += 1

    temp = array[j]
    array[j] = array[high]
    array[high] = temp
    
    return j

def hybridQuickSort(array, low, high): 
    while low < high: 
        if high - low + 1 < 10: 
            insertionSort(array, low, high) 
            break
        else: 
            pivot = partition(array, low, high) 
            if pivot - low < high - pivot: 
                hybridQuickSort(array, low, pivot - 1) 
                low = pivot + 1
            else: 
                hybridQuickSort(array, pivot + 1, high) 
                high = pivot-1
  
array = [
    58, 72, 50,  4, 92,
    42, 15,  3, 54, 95,
    37, 40, 46, 19, 42,
    32, 89, 72, 68, 80
]
arrayLength = 20

hybridQuickSort(array, 0, arrayLength - 1)
print(array) 
