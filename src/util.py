# generate 2 random LARGE number (128 bits), do some 3rd grade math and return the answer
# mainly for testing stuffs
# required bitstring to run

# !/usr/env/bin

import random
from bitstring import Bits


def gen_random_binary(k=128):
    return "".join(i for i in random.choices("01", k=k))


def gen_qint_conversion():
    bases = [2, 10]
    for f in bases:
        for t in bases:
            if f != t:
                a = Bits(bin=gen_random_binary())

                if f == 2:
                    a = a.bin
                elif f == 10:
                    a = a.float
                elif f == 16:
                    a = a.hex.upper()

                print("{} {} {}".format(f, t, a))


def gen_qint_operation():
    operators = ['+', '-', '*', '/']
    bases = [2, 10]
    for operator in operators:
        base = bases[random.randint(0, len(bases) - 1)]
        a = Bits(bin=gen_random_binary())
        b = Bits(bin=gen_random_binary())

        if base == 2:
            a = a.bin
            b = b.bin
        elif base == 10:
            a = a.float
            b = b.float
        else:
            a = a.hex.upper()
            b = b.hex.upper()

        # if operator in ['>>', '<<', 'rol', 'ror']:
        #     r = random.randint(1, 128)
        #     print('{} {} {} {}'.format(base, a, operator, r))
        # else:
        print('{} {} {} {}'.format(base, a, operator, b))

    # base = bases[random.randint(0, len(bases) - 1)]
    # a = Bits(float = gen_random_binary())
    # if base == 2:
    #     a = a.bin
    # elif base == 10:
    #     a = a.int
    # else:
    #     a = a.hex.upper()
    # print('{} ~{}'.format(base, a))


def main():
    gen_qint_conversion()
    gen_qint_operation()


if __name__ == '__main__':
    main()
