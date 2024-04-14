import sys, math
from decimal import *

getcontext().prec = 200
read = sys.stdin.readline
eps = Decimal("1e-50")


def main():
    n = int(read())
    for _ in range(n):
        x = Decimal(read())

        x = x ** Decimal("0."+"3"*153)

        x = round(x, 101)
        x = x.quantize(Decimal("1e-10"), rounding=ROUND_DOWN)
        print(x)


if __name__ == '__main__':
    main()
