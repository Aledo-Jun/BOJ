import math
import sys

read = sys.stdin.readline
pi = 3.14159_26535_89793_23846_26433_83279
a, b, h, steps = 0, 0, 0, 0


def f(x: float):
    r: float = a * math.exp(-x * x) + b * math.sqrt(x)
    return pi * r * r


def simpson(l: float, r: float):
    m1: float = (l * 2 + r) / 3
    m2: float = (l + r * 2) / 3
    return (r - l) / 8 * (f(l) + 3 * f(m1) + 3 * f(m2) + f(r))


def calc_volume() -> float:
    res = 0.
    dx = h / steps
    for i in range(steps):
        res += simpson(i * dx, (i + 1) * dx)

    return res


def main():
    target, n = read().split()
    target = float(target)
    n = int(n)

    ans = 0
    closest = 1e10
    for i in range(n):
        global a, b, h, steps
        a, b, h = map(float, read().split())
        steps = int(h / 0.00005)

        res: float = calc_volume()
        print(res)
        if abs(target - res) < closest:
            ans = i
            closest = abs(target - res)

    print(ans)


if __name__ == '__main__':
    main()
