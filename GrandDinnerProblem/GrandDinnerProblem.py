import sys



def calculateLayout(teams: list[tuple[int, list]], tables: list[list]):
    for team in teams:
        if team[0] > len(tables):
            return False
        for idx in range(team[0]):
            tables[idx][1] -= 1
            team[1].append(tables[idx][0])
        tables = filter(lambda x: x[1] > 0, tables)
        tables = sorted(tables, key=lambda x: x[1], reverse=True)
    return True            


if __name__ == '__main__':
    while True:
        teamCount, tableCount = map(int, sys.stdin.readline().strip().split(" "))
        if teamCount == 0 and tableCount == 0:
            break
        teams = list(map(int, sys.stdin.readline().strip().split(" ")))
        tables = list(map(list, enumerate(map(int, sys.stdin.readline().strip().split(" ")), 1)))
        tables = sorted(tables, key=lambda x: x[1], reverse=True)
        teams = [(number, list()) for number in teams]
        if calculateLayout(teams, tables):
            print("1")
            for _, teamTables in teams:
                for tableNumber in sorted(teamTables):
                    print(f"{tableNumber}", end=" ")
                print()
        else:
            print("0")
