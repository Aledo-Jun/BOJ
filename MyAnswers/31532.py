import sys
from decimal import *

read = sys.stdin.readline
getcontext().prec = 100


def main():
    n, b = map(int, read().split())
    points = [tuple(map(int, read().split())) for _ in range(n)]
    sum_x3, sum_x2, sum_x1, sum_y3, sum_y2, sum_y1 = 0, 0, 0, 0, 0, 0
    sum_x2y1, sum_x1y1, sum_x1y2 = 0, 0, 0
    for x, y in points:
        sum_x3 += x * x * x
        sum_x2 += x * x
        sum_x1 += x
        sum_y3 += y * y * y
        sum_y2 += y * y
        sum_y1 += y
        sum_x2y1 += x * x * y
        sum_x1y1 += x * y
        sum_x1y2 += x * y * y

    poly = [-sum_x3,
            -3 * b * sum_x2 + 3 * sum_x2y1,
            -3 * b * b * sum_x1 + 6 * b * sum_x1y1 - 3 * sum_x1y2,
            -b * b * b * n + 3 * b * b * sum_y1 - 3 * b * sum_y2 + sum_y3]

    if poly[0] < 0:
        for i in range(4):
            poly[i] = -poly[i]

    poly = list(map(Decimal, poly))

    def f(x: Decimal) -> Decimal:
        res = Decimal('0')
        for coef in poly:
            res *= x
            res += coef
        return res

    l, r = Decimal('-1e8'), Decimal('1e8')
    eps = Decimal('1e-50')
    while r - l > eps:
        m: Decimal = (l + r) / 2
        if f(m) > 0:
            r = m
        else:
            l = m

    print(l)


if __name__ == '__main__':
    main()
