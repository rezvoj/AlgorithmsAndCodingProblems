import sys



dirs = [(i, j) for j in range(-1, 2) for i in range(-1, 2) if j != 0 or i != 0]
horse_dirs = [(-1, -2), (1, -2), (-1, 2), (1, 2), (-2, -1), (2, -1), (-2, 1), (2, 1)]


def is_in_check(arr, king_pos, is_white):
    chars = ('n', 'r', 'q', 'b', 'p', -1) if is_white else ('N', 'R', 'Q', 'B', 'P', 1)
    for x, y in horse_dirs:
        new_x, new_y = king_pos[0] + x, king_pos[1] + y
        if new_x in range(8) and new_y in range(8) and arr[new_x][new_y] == chars[0]:
            return True
    for a, b in dirs:
        i, j = king_pos[0] + a, king_pos[1] + b 
        while i in range(8) and j in range(8):
            if arr[i][j] != '.':
                if (a == 0 or b == 0): 
                    if arr[i][j] in (chars[1], chars[2]):
                        return True
                else:
                    if arr[i][j] in (chars[2], chars[3]):
                        return True
                    if arr[i][j] == chars[4] and (i - king_pos[0] == chars[5] and abs(j - king_pos[1]) == 1):
                        return True
                break
            i += a
            j += b
    return False


def main():
    count = 1
    while True:
        arr = [list(sys.stdin.readline().rstrip()) for _ in range(8)]
        k = K = None
        for i in range(8):
            for j in range(8):
                if arr[i][j] == 'K':
                    K = (i, j)
                elif arr[i][j] == 'k':
                    k = (i, j)
        if k is None and K is None:
            break
        if is_in_check(arr, k, False):
            print(f"Game #{count}: black king is in check.")
        elif is_in_check(arr, K, True):
            print(f"Game #{count}: white king is in check.")
        else:
            print(f"Game #{count}: no king is in check.")
        count += 1
        sys.stdin.readline()

if __name__ == '__main__':
    main()
