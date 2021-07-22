def sumArrayElements(array):
    sum = 0
    for i in range(len(array)):
        sum += array[i]
    return sum

def subSets(arr_in, arr_out):
    if len(arr_in) == 0:
        if  len(arr_out) != 0 and sumArrayElements(arr_out) == 0:
            print(str(arr_out))
    else:
        arr = arr_out.copy()
        subSets(arr_in[1:], arr)

        arr = arr_out.copy()
        arr.append(arr_in[0])
        subSets(arr_in[1:], arr)

def findSubsets(arr):
    print('subsets: ')
    subSets(arr, [])

arr = [2, 3, -5, -8, 6, -1]
findSubsets(arr)
