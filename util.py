# generate 2 random LARGE number (128 bits), do some 3rd grade math and return the answer
# mainly for testing stuffs
# required bitstring to run

#!/usr/env/bin

import random
import time
from bitstring import Bits

def dec_to_bin(n):
    a = Bits(int = n, length = 128)
    return a.bin

def generate_random_binary_string(length = 128):
    n = Bits(int = random.randint(-2 ** (length / 2), 2 ** (length / 2) - 1), length = length)
    return n.bin

if __name__ == "__main__":
    a = Bits(bin = generate_random_binary_string(128))
    b = Bits(bin = generate_random_binary_string(128))
    ans = Bits(int = a.int * b.int, length = 128)
    print('({}) x ({}) = {}'.format(a.int, b.int, ans.int))
    print('{}\n{}\n{}'.format(a.bin, b.bin, ans.bin))
