from math import log2

def preprocess(arr: list, n: int):
    for i in range(n):
        lookup[i][0] = i
 
    j = 1
    while (2 ** j) <= n:
        i = 0
        while i + (2 ** j) - 1 < n:
            if (arr[lookup[i][j - 1]] < arr[lookup[i + (2 ** (j - 1))][j - 1]]):
                lookup[i][j] = lookup[i][j - 1]
            else:
                lookup[i][j] = lookup[i + (2 ** (j - 1))][j - 1]
            i += 1
        j += 1

def query(arr: list, L: int, R: int) -> int:
    j = int(log2(R - L + 1))

    if (arr[lookup[L][j]] <= arr[lookup[R - (2 ** j) + 1][j]]):
        return arr[lookup[L][j]]
    else:
        return arr[lookup[R - (2 ** j) + 1][j]]
 
def RMQ(arr: list, n: int, left: int, right: int):
    preprocess(arr, n)
    print("Minimum of [%d, %d] is %d" % (left, right, query(arr, left, right)))

lookup = [[0 for i in range(500)] for j in range(500)]
a = [7, 2, 3, 0, 5, 10, 3, 12, 18]
n = len(a) 
RMQ(a, n, 4, 7)
