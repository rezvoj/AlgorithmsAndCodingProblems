import sys


def main():
    inclist = [(i, j) for j in range(-1, 2) for i in range(-1, 2) if j != 0 or i != 0]
    
    counter = 1
    while True:
        h, w = map(int, sys.stdin.readline().rstrip().split())
        if h == 0 and w == 0:
            break
        if counter > 1:
            print()
        arr = [[0] * (w + 2) for _ in range(h + 2)]
        bombs = [[False] * w for _ in range(h)]
        for i in range(1, h + 1):
            line = sys.stdin.readline().rstrip()
            for j, char in enumerate(line, start=1):
                if char == '*':
                    bombs[i - 1][j - 1] = True
                    for i_, j_ in inclist:
                        arr[i + i_][j + j_] += 1
        print(f"Field #{counter}:")
        for i in range(1, h + 1):
            for j in range(1, w + 1):
                if bombs[i - 1][j - 1]:
                    print('*', end='')
                else:
                    print(arr[i][j], end='')
            print()
        counter += 1

if __name__ == '__main__':
    main()
