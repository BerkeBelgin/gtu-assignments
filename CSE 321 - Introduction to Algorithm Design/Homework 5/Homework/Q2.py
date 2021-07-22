def sumArrayElements(array):
    sum = 0
    for i in range(len(array)):
        sum += array[i]
    return sum

def smallestPath(arr_in, y, x, arr_out, arr_res):
    if y == len(arr_in):
        if not arr_res or sumArrayElements(arr_out) < sumArrayElements(arr_res):
            arr_res.clear()
            arr_res.extend(arr_out)
    else:
        arr = arr_out.copy()
        arr.append(arr_in[y][x])
        smallestPath(arr_in, y + 1, x, arr, arr_res)
        smallestPath(arr_in, y + 1, x + 1, arr, arr_res)

def findSmallestPath(arr):
    res = []
    smallestPath(arr, 0, 0, [], res)
    print('res = ', end='')
    print(res)

arr = [
    [2],
    [5, 4],
    [1, 4, 7],
    [8, 6, 9, 6]
]
findSmallestPath(arr)
