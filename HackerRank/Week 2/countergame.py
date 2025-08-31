#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'counterGame' function below.
#
# The function is expected to return a STRING.
# The function accepts LONG_INTEGER n as parameter.
#

def counterGame(n):
    # Write your code here
    turns = 0
    while n != 1:
        if (n & (n - 1)) == 0:
            n //= 2
        else:
            power = 1 << (n.bit_length() - 1)
            n -= power
        turns += 1
    return "Louise" if turns % 2 == 1 else "Richard"
    
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input().strip())

    for t_itr in range(t):
        n = int(input().strip())

        result = counterGame(n)

        fptr.write(result + '\n')

    fptr.close()
