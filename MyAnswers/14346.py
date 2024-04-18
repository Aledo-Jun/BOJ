#
# Grid로 생각
# (-10, A)에서 시작, x 방향으로 조금씩 움직이면서 현재 위치 기준으로 주변 cell 값을
# 계산해 column 별로 dp를 관리
# y -> more densely?
#
import math
import sys
from sys import float_info

from typing import Tuple

read = sys.stdin.readline

X_MIN, X_MAX = -10, 10
Y_MIN, Y_MAX = -20, 20  # 섬이 -10~10이니 -20~20 밖으로는 안 나갈 듯?
X_STEP_SIZE = 0.1
Y_STEP_SIZE = 0.005
N_COL = int((X_MAX - X_MIN) / X_STEP_SIZE)  # -> 200
N_ROW = int((Y_MAX - Y_MIN) / Y_STEP_SIZE)  # -> 8000
N_NEIGHBORS = 32  # 현재 위치 기준 위 아래로 N_NEIGHBORS 칸 만큼만 고려


# return the radiation per unit-time at the 'pos' of the grid
def radiation(islands: list, pos: Tuple[float, float]) -> float:
    res = 0.
    for island in islands:
        dist_squared = pos[0] ** 2 + (pos[1] - island) ** 2
        if dist_squared < float_info.epsilon:  # too close
            return float_info.max
        res += 1 / dist_squared
    return res


# calculate the amount of radiation we got while traveling from start to end
def calc(islands: list, start: Tuple[int, int], end: Tuple[int, int]) -> float:
    dx = end[0] - start[0]
    dy = end[1] - start[1]
    ds = (X_STEP_SIZE * dx) ** 2 + (Y_STEP_SIZE * dy) ** 2
    # NOTE: 1 is for the nature environment radiation
    return (1 + radiation(islands, (X_MIN + X_STEP_SIZE * start[0], Y_MIN + Y_STEP_SIZE * start[1]))) * math.sqrt(ds)


def solve() -> float:
    n, a, b = map(float, read().split())
    islands = list(map(float, read().split()))
    curr_col = [float_info.max for _ in range(N_ROW + 1)]
    a_idx = int((a - Y_MIN) / Y_STEP_SIZE)
    b_idx = int((b - Y_MIN) / Y_STEP_SIZE)
    curr_col[a_idx] = 0.

    for i in range(1, N_COL + 1):
        next_col = [float_info.max for _ in range(N_ROW + 1)]
        for j in range(N_ROW + 1):
            for k in range(max(0, j - N_NEIGHBORS), min(j + N_NEIGHBORS, N_ROW) + 1):
                next_col[j] = min(next_col[j], curr_col[k] + calc(islands, (i - 1, k), (i, j)))
        curr_col = next_col
    return curr_col[b_idx]


def main():
    t = int(read())
    for tc in range(t):
        print(f'Case #{tc + 1}: {solve()}')


if __name__ == '__main__':
    main()
