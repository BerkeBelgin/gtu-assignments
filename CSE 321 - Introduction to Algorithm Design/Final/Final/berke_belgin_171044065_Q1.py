def subArray(arr):
    arr_size = len(arr)
    res_arr = []
    tmp_arr = []
    for i in range(arr_size):
        if i != 0 and arr[i] == arr[i - 1]:
            tmp_arr = arr[i-1:i+1]
        else:
            tmp_arr = arr[i]

        for n_r in range(i + 1, arr_size):
            n_l = n_r - len(tmp_arr) - 1
            if n_r < arr_size and n_l >= 0 and arr[n_r] == arr[n_l]:
                tmp_arr = arr[n_l] + tmp_arr + arr[n_r]
            else:
                break

        if len(tmp_arr) >= len(res_arr):
            res_arr = tmp_arr
    print('string: ' + res_arr)
    print('size: ' + str(len(res_arr)))

subArray('The eekee aabaa cccbbccc ada')
