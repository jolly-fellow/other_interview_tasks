#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;


int slidingPuzzle(const vector<vector<int>> &board) {
    string target("123450");
    string start("");

    for (auto row : board) {
        for (auto item : row) {
            start += to_string(item);
        }
    }

    unordered_set<string> visited;
    // all the positions 0 can be swapped to
    const vector<vector<int>> directions { { 1, 3 }, { 0, 2, 4 }, { 1, 5 }, { 0, 4 }, { 1, 3, 5 }, { 2, 4 } };

    queue<string> queue;
    queue.push(start);
    visited.insert(start);
    int res = 0;
    while (!queue.empty()) {
        // level count, has to use size control here, otherwise not needed
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            string cur = queue.front(); queue.pop();
            if (cur == target) {
                return res;
            }
            int zero = cur.find('0');
            // swap if possible
            for (int dir : directions[zero]) {
                string next(cur);
                swap(next[zero], next[dir]);
                if (visited.count(next) == 0) {
                    visited.insert(next);
                    queue.push(next);
                }
            }
        }
        res++;
    }
    return -1;
}

/*
int slidingPuzzle(const vector<vector<int>> &board) {
    unordered_map<int, vector<int>> path{{0, {1, 3}},
                                         {1, {0, 2, 4}},
                                         {2, {1, 5}},
                                         {3, {0, 4}},
                                         {4, {1, 3, 5}},
                                         {5, {2, 4}}};
    unordered_map<string, int> cost;

    // Init start string from the state of the board
    string start = "";
    for (auto row : board) {
        for (auto f : row) {
            start += to_string(f);
        }
    }
    cost[start] = 0;

    queue<pair<string, int>> pool;
    for (int idx = 0; idx < start.size(); idx++)
        if (start[idx] == '0') pool.push({start, idx});;

    while (!pool.empty()) {
        auto cur = pool.front();
        pool.pop();
        for (auto e : path[cur.second]) {
            string s = cur.first;
            swap(s[cur.second], s[e]);
            if (cost.count(s)) continue;
            cost[s] = cost[cur.first] + 1;
            if (s == "123450") return cost[s];
            pool.push({s, e});
        }
    }

    return -1;
}
*/




int main() {

    vector<vector<int>> board {{1,2,3},{4,0,5}};

    vector<vector<int>> board2 {{1,2,3},{5,4,0}};

    vector<vector<int>> board3 {{4,1,2},{5,0,3}};

    vector<vector<int>> board4 {{3,2,4},{1,5,0}};


    cout << "\nResult: " << slidingPuzzle(board) << " Expected: 1" << endl;
    cout << "\nResult: " << slidingPuzzle(board2) << " Expected: -1" << endl;
    cout << "\nResult: " << slidingPuzzle(board3) << " Expected: 5" << endl;
    cout << "\nResult: " << slidingPuzzle(board4) << " Expected: 14" << endl;

    return 0;
}

