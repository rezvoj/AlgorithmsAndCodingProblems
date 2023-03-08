import sys
chararr = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']


def mls(srtd: list[str], unsrtd: list[str], dpt = 0):
    if not len(unsrtd):
        print(f"{'  ' * dpt}writeln({','.join(srtd)})")
    else:
        for i in range(len(srtd), 0, -1):
            print(f"{'  ' * dpt}{'else ' if i < len(srtd) else ''}if {srtd[i - 1]} < {unsrtd[0]} then")
            mls(srtd[:i] + [unsrtd[0]] + srtd[i:], unsrtd[1:], dpt + 1)
        print(f"{'  ' * dpt}else")
        mls([unsrtd[0]] + srtd, unsrtd[1:], dpt + 1)


if __name__ == "__main__":
    num = int(sys.stdin.readline().rstrip())
    sys.stdin.readline()
    for i in range(0, num):
        cnt = int(sys.stdin.readline().rstrip())
        sys.stdin.readline()
        esc = '\n' if i else ''
        print(f"{esc}program sort(input,output);")
        print("var")
        print(f"{','.join(chararr[:cnt])} : integer;")
        print("begin")
        print(f"  readln({','.join(chararr[:cnt])});")
        mls(chararr[0:1], chararr[1:cnt], 1)
        print("end.")
