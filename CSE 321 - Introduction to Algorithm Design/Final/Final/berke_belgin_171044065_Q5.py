def merge(arr, temp_arr, left, mid, right): 
    inv_count = 0
    i = left 
    j = mid 
    k = left 
  
    while i <= mid - 1 and j <= right: 
        if arr[i] > 2 * arr[j]: 
            inv_count += (mid - i) 
            j += 1
        else: 
            i += 1
  
    i = left 
    j = mid 
    k = left 
  
    while i <= mid - 1 and j <= right: 
        if arr[i] <= arr[j]: 
            temp_arr[k] = arr[i] 
            i = i + 1
            k = k + 1
        else: 
            temp_arr[k] = arr[j] 
            j = j + 1
            k = k + 1
  
    while i <= mid - 1: 
        temp_arr[k] = arr[i] 
        i = i + 1
        k = k + 1
  
    while j <= right: 
        temp_arr[k] = arr[j] 
        j = j + 1
        k = k + 1
        
    for i in range(left, right + 1): 
        arr[i] = temp_arr[i] 
  
    return inv_count 

def mergeSort_h(arr, temp_arr, left, right): 
    inv_count = 0
    if right > left:
        left_l = left
        left_r = (right + left) // 2
        right_l = (right + left) // 2 + 1
        right_r = right

        inv_count = mergeSort_h(arr, temp_arr, left_l, left_r)
        inv_count += mergeSort_h(arr, temp_arr, right_l, right_r)
        inv_count += merge(arr, temp_arr, left, right_l, right_r)
    return inv_count

def mergeSort(arr):
    n = len(arr)
    temp_arr = [0 for i in range(n)] 
    return mergeSort_h(arr, temp_arr, 0, n - 1)

arr = [1, 20, 12, 6, 4, 5]
print ('Inversion count: ', mergeSort(arr))
