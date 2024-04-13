import decimal
import sys
import math
from decimal import *

getcontext().prec = 100
eps = Decimal(1e-60)
pi = Decimal("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348")


def sin(x: Decimal) -> Decimal:
    """Return the sine of x as measured in radians.

    The Taylor series approximation works best for a small value of x.
    For larger values, first compute x = x % (2 * pi).

    >>> print(sin(Decimal('0.5')))
    0.4794255386042030002732879352
    >>> print(sin(0.5))
    0.479425538604
    >>> print(sin(0.5+0j))
    (0.479425538604+0j)
    """
    x = x % (2 * pi)
    getcontext().prec += 2
    i, lasts, s, fact, num, sign = 1, 0, x, 1, x, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    getcontext().prec -= 2
    return +s


def main():
    a, b, c = map(Decimal, input().split())

    def check(x: Decimal) -> bool:
        val = a * x + b * sin(x) - c
        return val < -eps

    l = Decimal(0)
    r = Decimal(1_000_000)

    while abs(r - l) >= eps:
        m: Decimal = (l + r) / 2
        if check(m):
            l = m
        else:
            r = m - eps

    print(f'{l:.6f}')


if __name__ == '__main__':
    main()