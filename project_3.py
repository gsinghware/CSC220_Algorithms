
# Fractional Knapsack problem
def _frac_knapsack(M, profit_weight):
    n = len(profit_weight)
    l = sorted(profit_weight, key=lambda t: float(t[0])/t[1], reverse=True)
    x = []

    for i in range(n):
        if (l[i][1] > M):
            break
        x.append(1.0)
        M -= l[i][1]

    if i < n:
        x.append(float(M)/l[i][1])

    profit = 0.0
    for i in range(len(x)):
        profit += (x[i]*l[i][0])

    print "Max Profit: " + str(profit)


# 0/1 Knapsack problem using dynamic programming
def _01_Knapsack(M, profit_weight):
    n = len(profit_weight)
    #initialize an n by M matrix with zeros
    Matrix = [[0] * (M + 1) for i in xrange(n + 1)]
    for i, (profit, weight) in enumerate(profit_weight):
        for capacity in xrange(M + 1):
            if (weight <= capacity):
                if (profit + Matrix[i][capacity-weight] > Matrix[i][capacity]):
                    Matrix[i+1][capacity] = profit + Matrix[i][capacity-weight]
                else:
                    Matrix[i+1][capacity] = Matrix[i][capacity]
            else:
                Matrix[i+1][capacity] = Matrix[i][capacity]

    print "Max Profit: ", str(Matrix[n][M])


# 0/1 Knapsack problem solution using backtracking

max_profit = 0
current_profit = 0.0
current_weight = 0.0

def pack(i, M, n, profit_weight): 
    left_c = M - current_weight                             # remaining knapsack capacity 
    b = current_profit
    while (i < n and profit_weight[i][1] <= left_c):        # weight of the items decay loaded items 
        left_c -= profit_weight[i][1]
        b += profit_weight[i][0] 
        i += 1
    
    if (i < n):
        b += profit_weight[i][0] * (left_c/profit_weight[i][1])
    return b

def backtrackto(i, M, n, profit_weight):
    #print "backtrackto("+", ".join([str(x) for x in [i, M, n, profit_weight]])+")"

    global max_profit
    global current_profit, current_weight

    if(i > n):
        if (current_profit > max_profit): 
            max_profit = current_profit
        return

    elif (i < n):
        if (current_weight + profit_weight[i][1] <= M): 
            current_weight += profit_weight[i][1] 
            current_profit += profit_weight[i][0] 
            backtrackto (i + 1, M, n, profit_weight);
            current_weight -= profit_weight[i][1] 
            current_profit -= profit_weight[i][0]

    if ((pack(i+1, M, n, profit_weight)) >= max_profit):
        backtrackto (i+1, M, n, profit_weight)       

def _01_Knapsack_backtracking(M, profit_weight):
    n = len(profit_weight)

    global max_profit

    temp_profit = 0.0
    temp_weight = 0.0

    for i in xrange(len(profit_weight)):
        temp_profit += profit_weight[i][0]
        temp_weight += profit_weight[i][1]

    global max_profit
    if (temp_weight <= M):
        max_profit = temp_profit
    else:
        #print "No backtrackto"
        backtrackto(0, M, n, profit_weight)

    print "Max Profit: " + str(max_profit)
    max_profit = 0 # for next function call need to set this to zero


def main():
    # Fractional Knapsack problem solution
    print "Test 1 - Fractional Knapsack problem"
    M = 20      # capacity
    n = 3       # size
    profit_weight = [(25, 18), (24, 15), (15, 10)]
    _frac_knapsack(M, profit_weight)
    
    # 0/1 Knapsack problem using Dynamic Programming
    print "\nTest 2 - 01 Knapsack problem using dynamic programming"
    profit_weight_2 = [(3,2), (4,3), (5,4), (6,5)]
    M_2 = 5
    n_2 = 4
    _01_Knapsack(M_2, profit_weight_2)

    print "\nTest 3 - 01 Knapsack problem using dynamic programming"
    M_3 = 10
    n_3 = 4
    profit_weight_3 = [(10,5), (40,4), (30,6), (50,3)]
    profit_weight_a = [(1,1), (2,2), (3,3), (4,4), (5,5), (6,6), (7,7), (8,8), (9,9), (10,10)]
    _01_Knapsack(M_3, profit_weight_3)
    _01_Knapsack(50, profit_weight_a)

    print "\nTest 4 - 01 knapsack problem using backtracking technique"
    M_4 = 10
    n_4 = 4
    profit_weight_4 = [(10,5), (40,4), (30,6), (50,3)]
    _01_Knapsack_backtracking(M_4, profit_weight_4)
    #_01_Knapsack_backtracking(50, 10, profit_weight_a)    

if __name__ == '__main__':
    main()
