# import sys
from decimal import *

getcontext().prec = 100

# input = sys.stdin.readline

precision = 20
epsilon = Decimal(1e-20)
MAX = Decimal(1e6)


def main():
    for _ in range(int(input())):
        a, b, c, d = map(Decimal, input().split())

        def f(_x) -> Decimal:
            return a * _x ** 3 + b * _x ** 2 + c * _x + d

        def binary_search(low, high) -> Decimal:
            while high - low > epsilon:
                mid = (high + low) / 2
                if f(low) * f(mid) > 0:
                    low = mid
                else:
                    high = mid
            return low

        ans = []
        e = b ** 2 - 3 * a * c
        if e <= 0:
            ans.append(binary_search(-MAX, MAX))
        else:
            x = (-b - e ** Decimal(0.5)) / (3 * a)
            y = (-b + e ** Decimal(0.5)) / (3 * a)
            if x > y:
                x, y = y, x

            if round(f(x) * f(y), precision) > 0:
                if a > 0:
                    if round(f(x), precision) > 0:
                        ans.append(binary_search(-MAX, x))
                    else:
                        ans.append(binary_search(y, MAX))
                else:
                    if round(f(y), precision) > 0:
                        ans.append(binary_search(y, MAX))
                    else:
                        ans.append(binary_search(-MAX, x))
            elif round(f(x), precision) == 0:
                ans = [x, binary_search(y, MAX)]
            elif round(f(y), precision) == 0:
                ans = [binary_search(-MAX, x), y]
            else:
                ans = [binary_search(-MAX, x),
                       binary_search(x, y),
                       binary_search(y, MAX)]

        ans = [f'{i:.9f}' for i in ans]
        print(*ans)


if __name__ == '__main__':
    main()
