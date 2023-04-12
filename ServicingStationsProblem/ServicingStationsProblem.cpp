#include <iostream>
#include <array>
#include <bitset>


struct GlobData {
    int comp;
    int nbr_ct = 0;
    std::array<int, 35> nbrs;
    bool colored = false;
    int cid;
};

struct CompData  {
    std::bitset<35> completed;
    std::array<std::bitset<35>, 35> apply;
    std::array<std::bitset<35>, 35> skip_reach;
};


void cc_dfs(std::array<GlobData, 35>& data, int pos, int parent) {
    GlobData& elem = data[pos];
    for (int i = 0; i < elem.nbr_ct; ++i) {
        if (data[elem.nbrs[i]].comp != parent) {
            data[elem.nbrs[i]].comp = parent;
            cc_dfs(data, elem.nbrs[i], parent);
        }
    }
}


int create_comps(std::array<GlobData, 35>& data, int N) {
    int count = 0;
    for (int i = 0; i < N; ++i) {
        if (data[i].comp == i) {
            data[i].comp = count;
            cc_dfs(data, i, count++);
        }
    }
    return count;
}


int rec(const CompData& data, std::bitset<35> curr, int curr_pos, int curr_count, int best_count) {
    if (curr == data.completed) {
        return curr_count;
    }
    if (curr_count >= (best_count - 1)) {
        return best_count;
    }
    std::bitset<35> ncurr = curr | data.apply[curr_pos];
    if (curr != ncurr) {
        best_count = rec(data, ncurr, curr_pos + 1, curr_count + 1, best_count);
    }
    if ((curr | data.skip_reach[curr_pos]) == data.completed) {
        best_count = rec(data, curr, curr_pos + 1, curr_count, best_count);
    }
    return best_count;
}


int main(int argc, char const *argv[]) {
    int N, M, a, b;
    while (true) {
        std::cin >> N >> M;
        if (!N && !M) {
            break;
        }
        int result = 0;
        std::array<GlobData, 35> glob;
        for (int i = 0; i < N; ++i) {
            glob[i].comp = i;
        }
        for (int i = 0; i < M; ++i) {
            std::cin >> a >> b;
            a--; b--;
            glob[a].nbrs[glob[a].nbr_ct++] = b;
            glob[b].nbrs[glob[b].nbr_ct++] = a;
        }
        int comp_ct = create_comps(glob, N);
        for (int i = 0; i < comp_ct; ++i) {
            for (int j = 0; j < N; ++j) {
                if (glob[j].comp == i && glob[j].nbr_ct == 1 && !glob[j].colored) {
                    result++;
                    GlobData& nbr = glob[glob[j].nbrs[0]];
                    glob[j].comp = nbr.comp = glob[j].cid = nbr.cid = -1;
                    for (int k = 0; k < nbr.nbr_ct; k++) {
                        glob[nbr.nbrs[k]].colored = true;
                    }
                }
            }
            int node_count = 0;
            std::array<int, 35> reduce_arr;
            for (int j = 0; j < N; ++j) {
                if (glob[j].comp == i) {
                    glob[j].cid = node_count;
                    reduce_arr[node_count++] = j;
                }
            }
            CompData comp;
            comp.completed |= ((1ULL << node_count) - 1);
            std::bitset<35> start;
            for (int j = 0; j < node_count; ++j) {
                GlobData& globn = glob[reduce_arr[j]];
                if (globn.colored) {
                    start.set(j);
                }
                comp.apply[j].set(j);
                for (int k = 0; k < globn.nbr_ct; ++k) {
                    int cid = glob[globn.nbrs[k]].cid;
                    if (cid >= 0) {
                        comp.apply[j].set(glob[globn.nbrs[k]].cid);    
                    }
                }
            }
            for (int j = node_count - 2; j >= 0; --j)
                comp.skip_reach[j] = comp.skip_reach[j + 1] | comp.apply[j + 1];
            result += rec(comp, start, 0, 0, node_count);
        }
        std::cout << result << '\n';
    }
    return 0;
}
