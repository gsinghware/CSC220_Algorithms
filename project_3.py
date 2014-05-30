import time
import random
import sys
import matplotlib.pyplot as plt

functionToStats = {}

problem_sizes = [50, 100, 200, 300, 400, 500, 750, 1000, 1500, 2000]
#problem_sizes = [10, 20, 30, 40, 50, 75, 100]
cap_mults = [0.1, 0.25, 0.5, 1.0, 2.0, 4.0]

cap_index_to_color = {
    0:"yellow",
    1:"blue",
    2:"green",
    3:"cyan",
    4:"black",
    5:"red",
    6: "pink",
    7: "orange"
}

"""
pad a string with spaces for prettier printing
"""
def spacepad(s):
    s= s+":"
    total = 30
    l = len(s)
    return s + "".join([' ' for i in range(total - l)])

"""
decorator for timing and collecting stats, as well as printing those stats
as functions run
"""
mult_index = 0

def runtimeandstats(method):
    def timed(*args):
        global cap_mults
        global mult_index
        ts = time.time()
        result = method(*args)
        te = time.time()
        delta = float(te-ts)
        ms = delta*1000
        padded_name = spacepad(method.__name__)
        size = len(args[1])
        capacity = args[0]
        cap_mult = cap_mults[(mult_index/2)%len(cap_mults) -1]
        mult_index+=1
        print "{0} problem size={1} capacity={2} time={3} cap_mult={4}".format(padded_name, size, capacity, delta, cap_mult)
        key = "{0}, cap_mult={1}".format(method.__name__,cap_mult)
        try:
            functionToStats[key].append( (size,ms) )
        except KeyError:
            functionToStats[key] = [ (size,ms) ]

        return result
    return timed

"""
Wrapper for the greedy algorithm. Call this to run the algorithm on a certain 
problem with default parameters. 
"""
def knapsack_fractional_wrapper(M, profit_weight):
    l = [(0,0)]+sorted(profit_weight, key=lambda t: float(t[1])/t[0])
    return knapsack_fractional(len(l), l, M, 0, 0, 0)

"""
Use a greedy algorithm to solve the fractional knapsack problem. item, weight, and profit
are parameters so that this function can be used within the backtracking algorithm.
"""
def knapsack_fractional(n, profit_weight, capacity, item, weight, profit):
    potential = profit;
    totalweight = weight;
    i = item + 1;

    while i < n and totalweight + profit_weight[i][1] <= capacity :
        potential += profit_weight[i][0];
        totalweight += profit_weight[i][1];
        i+=1
    if (i < n):
        potential += (capacity - totalweight) * (float(profit_weight[i][0])/profit_weight[i][1]);
    return potential


"""
Find the maximum profit for the knapsack problem using dynamic programming.
"""
@runtimeandstats
def knapsack_dynamic(M, profit_weight):
    n = len(profit_weight)
    #initialize a 0-to-n by 0-to-M, W, matrix with zeros
    W = [[0] * (M + 1) for i in xrange(n + 1)]
    Keep = [[0] * (M + 1) for i in xrange(n + 1)]

    #i = 0, 1, 2, ..., n
    for i, (profit, weight) in enumerate(profit_weight):
        #capacity = 0, 1, 2, ..., M+1 
        for capacity in xrange(M + 1):
            if (weight <= capacity):
                if (profit + W[i][capacity-weight] > W[i][capacity]):
                    W[i+1][capacity] = profit + W[i][capacity-weight]
                    Keep[i+1][capacity] = 1
                else:
                    W[i+1][capacity] = W[i][capacity]
            else:
                W[i+1][capacity] = W[i][capacity]
    #return the lower right corner value as the max
    return W[n][M], Keep

"""
For a size and a capacity multipliers, generate a capacity and a profit_weight array,
then run the dynamic programming and backtracking algorithms.

profit_weight is generated randomly, where profit is a random integer between
10 and 100. Weight is a random integer between 2 and 10.

To ensure correctness, there is an assertion that halts the program if the results
obtained by the two algoorithms differ.
"""
def randomTestForN(size, cap_mult):
    profit_weight = []
    capacity = int(size*cap_mult)
    for i in range(size):
        profit = random.randint(10,100)
        weight = random.randint(2,10)
        profit_weight.append((profit, weight))

    max_dynamic, x = knapsack_dynamic(capacity, list(profit_weight))
    max_backtracking, y = knapsack_backtracking_wrapper(capacity, list(profit_weight))
    assert max_dynamic == max_backtracking

"""
Use system time to measure the performance of backtracking and dynamic programming
algorithms for some random inputs. For a specific problem size, the problem is created and
tested by randomTestForN. This just calls that function for several problem sizes and
capacity multipliers
Because the dynamic programming algorithms is impacted by changes of the capacity,
also test for different. See randomTestForN()
"""
def performanceTest():
    #problem_sizes = [10, 100, 500]
    #cap_mults = [1, 2, 4]
    global problem_sizes
    global cap_mults
    for size in problem_sizes:
        for cap_mult in cap_mults:
            sys.setrecursionlimit(3*size)
            randomTestForN(size, cap_mult)
    plot()


"""
The assignment asked to solve the knapsack problem using the greedy algorithm given
certain parameters. Do that, and additionally solve the same problem using
dynamic and backtracking algorithms.
"""
def assignment():
    capacity = 15

    profits = [10, 5, 15, 7, 6, 18, 3]
    weights = [2, 3, 5, 7, 1, 4, 1]

    profit_weight = zip(profits, weights)
    sorted_profit_weight = sorted(profit_weight, key=lambda t: float(t[1])/t[0])

    val1, back_list = knapsack_backtracking_wrapper(capacity, profit_weight);
    val2, dyn_matrix = knapsack_dynamic(capacity, profit_weight)

    val3 = knapsack_fractional_wrapper(capacity, profit_weight)
    print "solution using fractional knapsack algorithm: "+str(val3)

    #make sure we got the same answer for dynamic and backtracking solutions
    assert val1 == val2
    print "solution using dynamic and backtracking algorithms: "+str(val2)
    n = len(profit_weight)
    w = capacity
    
    dyn_list = []
    while (n != 0):
        if (dyn_matrix[n][w] == 1):
            #print "Object {0} with profit {1}".format(n, profits[n - 1])
            dyn_list.append( (profits[n - 1], weights[n-1]) )
            n = n - 1
            w = w - weights[n]
        else:
            n = n - 1

    back_list = sorted([sorted_profit_weight[x-1] for x in back_list], key=lambda t: float(t[1])/t[0])
    dyn_list = sorted(dyn_list, key=lambda t: float(t[1])/t[0])

    #make sure the actual list of objects return from dynamic and backtracking is the same
    assert back_list == dyn_list

    functionToStats = {}

maxProfit = 0.0
kept = []

"""
Wrapper for starting the knapsack backtracking.
Does setup by sorting profit_weight, finding its length, prepending a dummy value to it,
resetting global variables, and starting the search with appropriate starting parameters
for knapsack_backtracking()
"""
@runtimeandstats
def knapsack_backtracking_wrapper(M, profit_weight):
    #prepend a dummy value to our list of pofit,weight sorted by profit/weight non-decreased
    items = [(0,0)] + sorted(profit_weight, key=lambda t: float(t[0])/t[1], reverse=True)

    #reset global variables
    global maxProfit
    global kept
    maxProfit = 0.0
    kept = []

    #kick off the dfs for the implicit backtracking state tree
    knapsack_backtracking(len(items), items, M, 0, 0, 0, [])
    return maxProfit, kept

"""
knapsack problem solution:
1) Check if the current solution is the best one. If so, keep it
2) Check if the current node is promsing
    -if it is, continue the search. First on the left child, then on the right
    -left child represents including the item at index
    -right child represents leaving it out of the solution
    -if this node is not promising, do nothing (prune the state tree here)
"""
def knapsack_backtracking(n, profit_weight, capacity, index, weight, profit, curList):
    global maxProfit
    global kept

    if weight <= capacity and profit > maxProfit :
        #this is currently the best we can do! save it... 
        maxProfit = profit;
        kept = curList
    #check if this node is promising
    if promising(n, profit_weight, index, capacity, weight, profit):

        #depth first search the left node (where we keep the next element)
        visitedList = list(curList)
        visitedList.append(index + 1);
        knapsack_backtracking(n, profit_weight, capacity, index + 1, weight + profit_weight[index+1][1], profit + profit_weight[index+1][0], visitedList);
        
        #depth first search the right node (where we dont keep the next element)
        notVisitedList = list(curList)
        knapsack_backtracking(n, profit_weight, capacity, index + 1, weight, profit, notVisitedList);

"""
Is this node promising? i.e. Is the current weight less than the sack's capacity?
Does the maximum potential value of the children nodes (the "potential") exceed 
the maximum profit we've observed so far? This bound is calculated in the same way 
that the fractional knapsack problem is solved. The actual maximum value under this 
node is propably not as good as the bound we calculate here, but this works as a way
to prune the state tree.
"""
def promising(n, profit_weight, item, capacity, weight, profit):
    #our current weight already exceeds the capacity, prune this node
    if (weight > capacity) :
        return False;
    #get the potential max. value using the fractional knapsack solution
    potential = knapsack_fractional(n, profit_weight, capacity, item, weight, profit)
    return potential > maxProfit;

"""
create a plot from the stats collected by the @runtimeandstats decorator
"""
def plot():
    global cap_index_to_color
    global cap_mults
    fig = plt.figure()
    dpi = fig.dpi 
    fig.set_size_inches(1300 / dpi, 850 / dpi) 
    plt.ylabel("run time (ms)")
    plt.xlabel("problem size")

    for key in functionToStats:
        points = functionToStats[key]
        x = [t[0] for t in points]
        y = [t[1] for t in points]
        if key.find('dyn') != -1:
            style = '--'
            w = 2
        else:
            style = ''
            w =1
        cap_mult = float(key[key.find('=')+1:])
        color = cap_index_to_color[cap_mults.index(cap_mult)]
        #use plt.semilogy for logarithmic scale
        line = plt.plot(x, y, style, label=key, linewidth=w, color=color)

    plt.title("knapsack problem: dynamic prog. vs. backtracking performance")
    plt.legend(loc="best", prop={'size':10})
    plt.savefig("stats", bbox_inches='tight')

"""
Solve the assigned problem, and test performance for dynamic and backtracking algorithms
"""
def main():
    assignment()
    performanceTest()

if __name__ == '__main__':
    main()
