# generate 2 random LARGE number (128 bits), do some 3rd grade math and return the answer
# mainly for testing stuffs
# required bitstring to run

#!/usr/env/bin

import random
import time
from bitstring import Bits

_BINARY_LENGTH = 128

def dec_to_bin(n):
    a = Bits(int = n, length = _BINARY_LENGTH)
    return a.bin

def generate_random_binary_string(length = _BINARY_LENGTH):
    n = Bits(int = random.randint(-2 ** (length / 2), 2 ** (length / 2) - 1), length = length)
    return n.int

if __name__ == "__main__":
    # a = Bits(int = (-2247711972460109982), length = _BINARY_LENGTH)
    # b = Bits(int = (1801822347250296720), length = _BINARY_LENGTH)

    # ans = Bits(int = int(str(a.int / b.int).split('.')[0]), length = _BINARY_LENGTH)

    # print('({}) / ({}) = {}'.format(a.int, b.int, ans.int))
    # print('{}\n{}\n{}'.format(a.bin, b.bin, ans.bin))

    # ans = Bits(int = abs(a.int - (b.int * int(str(a.int / b.int).split('.')[0]))), length = _BINARY_LENGTH)

    # print('({}) % ({}) = {}'.format(a.int, b.int, ans.int))
    # print('{}\n{}\n{}'.format(a.bin, b.bin, ans.bin))

    a = Bits(float = 0.125, length = 32)
    b = Bits(float = 3.125, length = 32)

    print(Bits(float = a.float * b.float, length = 32).float)
    print(Bits(float = a.float * b.float, length = 32).bin)
