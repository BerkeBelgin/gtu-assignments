def sumArrayElements(array):
    sum = 0
    for i in range(len(array)):
        sum += array[i]
    return sum

def mostValuable(arr_v_in, arr_v_out, arr_v_res, arr_w_in, arr_w_out, arr_w_res, w_cap):
    if len(arr_v_in) == 0 or len(arr_w_in) == 0:
        if sumArrayElements(arr_w_out) <= w_cap and sumArrayElements(arr_v_out) > sumArrayElements(arr_v_res):
            arr_v_res.clear()
            arr_v_res.extend(arr_v_out)
            arr_w_res.clear()
            arr_w_res.extend(arr_w_out)
    else:
        arr_v = arr_v_out.copy()
        arr_w = arr_w_out.copy()
        mostValuable(arr_v_in[1:], arr_v, arr_v_res, arr_w_in[1:], arr_w, arr_w_res, w_cap)

        arr_v = arr_v_out.copy()
        arr_v.append(arr_v_in[0])
        arr_w = arr_w_out.copy()
        arr_w.append(arr_w_in[0])
        mostValuable(arr_v_in[1:], arr_v, arr_v_res, arr_w_in[1:], arr_w, arr_w_res, w_cap)

def findMostValuable(v, w, w_cap):
    v_res =[]
    w_res = []
    mostValuable(v, [], v_res, w, [], w_res, w_cap)
    print('v = ', end='')
    print(v_res)
    print('w = ', end='')
    print(w_res)

v = [10, 4, 3]
w = [5, 4, 2]
w_cap = 9
findMostValuable(v, w, w_cap)
