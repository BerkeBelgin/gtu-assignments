def maxRevenue(min_distance, total_distance, distances, revenue, size): 
    maxRev = [0] * (total_distance + 1) 
    next_bb = 0
    for i in range(1, total_distance + 1):  
        if (next_bb < size):  
            if (distances[next_bb] != i): 
                maxRev[i] = maxRev[i - 1]  
            else: 
                if (i <= min_distance): 
                    maxRev[i] = max(maxRev[i - 1], revenue[next_bb]) 
                else: 
                    maxRev[i] = max(maxRev[i - min_distance - 1] + revenue[next_bb], maxRev[i - 1]) 
                next_bb += 1
        else: 
            maxRev[i] = maxRev[i - 1]  
    return maxRev[total_distance] 

min_distance = 4
total_distance = 50

distances = [5, 8, 17, 27, 31, 43]
revenue = [5, 2,  7,  4,  11,  8]
size = len(distances) 


print(maxRevenue(min_distance, total_distance, distances, revenue, size))
