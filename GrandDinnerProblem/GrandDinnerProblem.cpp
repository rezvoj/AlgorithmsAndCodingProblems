#include <iostream>
#include <array>
#include <algorithm>


struct Team {
    std::array<int, 50> table_ids;
    int size;
};

struct Teams {
    int count;
    std::array<Team, 70> arr;
};

struct Table {
    int id;
    int capacity;
};

struct Tables {
    int count;
    std::array<Table, 50> arr;
};


int calc(Teams& teams, Tables& tables) {
    for (int i = 0; i < teams.count; ++i) {
        Team& team = teams.arr[i];
        int lcapcty = tables.arr[team.size - 1].capacity;
        if (team.size > tables.count || !lcapcty) {
            return 0;
        }
        int pos = 0;
        int bound = team.size;
        for (; pos < bound; ++pos) {
            if (tables.arr[pos].capacity == lcapcty) {
                break;
            }
            team.table_ids[pos] = tables.arr[pos].id;
            tables.arr[pos].capacity--;
        }
        int j = pos;
        for (; bound < tables.count && tables.arr[bound].capacity == lcapcty; ++pos, ++bound);
        for (; pos < bound; ++pos, ++j) {
            team.table_ids[j] = tables.arr[pos].id;
            tables.arr[pos].capacity--;
        }
    }
    return 1;
}


int main(int argc, char const *argv[]) {    
    Teams teams;
    Tables tables;
    while (true) {
        std::cin >> teams.count >> tables.count;
        if (!teams.count && !tables.count) {
            break;
        }
        for (int i = 0; i < teams.count; ++i) {
            std::cin >> teams.arr[i].size;
        } 
        for (int i = 0; i < tables.count; ++i) {
            std::cin >> tables.arr[i].capacity;
            tables.arr[i].id = i + 1;
        }
        std::sort(tables.arr.begin(), tables.arr.begin() + tables.count, 
            [](const Table& a, const Table& b) {
                return a.capacity > b.capacity;
            }
        );
        int res = calc(teams, tables);
        std::cout << res << "\n";
        if (res) {
            for (int i = 0; i < teams.count; ++i) {
                Team& team = teams.arr[i];
                for (int j = 0; j < team.size - 1; ++j) {
                    std::cout << team.table_ids[j] << " ";
                }
                std::cout << team.table_ids[team.size - 1] << "\n";
            }
        }
    }
    return 0;
}
