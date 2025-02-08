import sys
from collections import *
from math import *


INF = float('inf')
eps = sys.float_info.epsilon

read = sys.stdin.readline

n = int(read())
v = [tuple(map(float, read().split())) for _ in range(n)]


class Parabola:
    def __init__(self, x, r):
        self.x = x
        self.r = r

    def __call__(self, x, r):
        return min(r, (x - self.x)**2 / (4 * self.r))


def cross(a: Parabola, b: Parabola) -> float:
    sqrt_r1 = max(eps, sqrt(a.r))
    sqrt_r2 = max(eps, sqrt(b.r))
    return (a.x / sqrt_r1 - b.x / sqrt_r2) / (1 / sqrt_r1 - 1 / sqrt_r2)


class LowerEnvelope:
    def __init__(self):
        self.st: deque[Parabola] = deque()  # order of decreasing cross values

    def add(self, new: Parabola):
        while self.st and self.st[-1].r <= new.r + eps:
            self.st.pop()
        while len(self.st) > 1 and cross(self.st[-1], self.st[-2]) < cross(new, self.st[-1]):
            self.st.pop()
        self.st.append(new)

    def get(self, x: float, r: float):
        mn = r
        while len(self.st) > 1 and cross(self.st[-1], self.st[-2]) <= x:
            mn = self.st[-1](x, mn)
            self.st.pop()
        return self.st[-1](x, mn) if len(self.st) != 0 else mn


def main():
    lowerEnvelope = LowerEnvelope()
    for x, r in v:
        print(R := lowerEnvelope.get(x, r))
        lowerEnvelope.add(Parabola(x, R))


if __name__ == "__main__":
    main()
