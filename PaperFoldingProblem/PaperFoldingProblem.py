import sys


trns = str.maketrans("01", "10")
trnslist = [
    ((3, -1, -1), (1, 1, -1), '|'), 
    ((0, 1, 0), (2, 1, 1), '_'),
    ((1, 1, 0), (3, -1, 0), '|'),
    ((2, -1, 1), (0, -1, 0), '_'),
]


def get_path(num: int):
    strr = ""
    for _ in range(0, num):
        strr = strr + '0' + strr[::-1].translate(trns)
    return strr

def get_mat(st: str):
    x = y = max_x = max_y = min_x = min_y = 0
    move = 1
    for c in st:
        c = int(c)
        x, y = x + trnslist[move][c][1], y + trnslist[move][c][2]
        max_x, max_y = max(max_x, x), max(max_y, y)
        min_x, min_y = min(min_x, x), min(min_y, y)
        move = trnslist[move][c][0]
    mat = [[' '] * (max_x + 1 - min_x) for _ in range(0, max_y + 1 - min_y)]
    x, y = - min_x, - min_y
    move = 1
    mat[y][x] = '_'
    for c in st:
        c = int(c)
        x, y = x + trnslist[move][c][1], y + trnslist[move][c][2]
        move = trnslist[move][c][0]
        mat[y][x] = trnslist[move][2]
    return mat


if __name__ == "__main__":
    for line in sys.stdin:
        its = int(line.rstrip())
        if its == 0:
            break
        for ln in get_mat(get_path(its)):
            space_ct = 0
            for c in ln:
                if c != ' ':
                    print(f"{' ' * space_ct}{c}", end='')
                    space_ct = 0
                else:
                    space_ct += 1
            print()
        print("^")
