#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <map>
#include <stack>

using namespace std;

/*
vector<int> expand(vector<vector<int>> &m, int row, int col) {
    vector<int> res;
    int rows = m.size();
    int cols = m[0].size();


    // For vertical and horizontal neighbors only
    vector<int> row_dir = { -1,  0, 1, 0 };
    vector<int> col_dir = {  0, -1, 0, 1 };

    for (auto i = 0; i < row_dir.size(); ++i) {
        int new_row = row + row_dir[i];
        int new_col = col + col_dir[i];

        if (new_row < 0 || new_row >= rows || new_col < 0 || new_col >= cols) {
            continue;
        }
        res.emplace_back(node_t{ new_row, new_col });
    }
    return res;
}
*/

/*
 Lets consider all possible states of the board as a graph.
 Therefore we start from the initial state, check if it is not a target state
 then we generate all states which we can move from the initial state and check them.
 Each step of generation of a new set of states adds one step between of the initial and target states
 It looks like an initial state into a center of the image and all possible states arount this point make a circle
 All possible state where we can move from the first circle form a next circle.
 Thus when we traverse this graph from the initial state using BFS algorithm, processing states circle by circle gives
 us the shortest way to the target state. We just need to count the processed circles and return the number of them.
*/
int slidingPuzzle(const vector<vector<int>> &board) {
    string target("123450");
    string start("");

    for (auto row : board) {
        for (auto cell : row) {
            start += to_string(cell);
        }
    }

    unordered_set<string> visited;
    // all the positions 0 can be swapped to
    // |0|1|2|
    // |3|4|5|
    const vector<vector<int>> directions { /*0*/ { 1, 3 }, /*1*/{ 0, 2, 4 }, /*2*/{ 1, 5 }, /*3*/{ 0, 4 }, /*4*/{ 1, 3, 5 }, /*5*/{ 2, 4 } };

    queue<string> queue;
    queue.push(start);
    visited.insert(start);
    int res = 0;
    while (!queue.empty()) {
        // this loop needs for count of steps to the solution
        // we process all nodes around of already processed nodes on the previous step
        // so each step of processing of all items in the queue adds one more step to the
        // solution
        int size = queue.size();
        for (int i = 0; i < size; i++) {
            string cur = queue.front(); queue.pop();
            if (cur == target) {
                return res;
            }
            int zero = cur.find('0');
            // generate all possible moves and add them to the queue
            for (int dir : directions[zero]) {
                string next(cur);
                // do a sliding move
                swap(next[zero], next[dir]);
                // if this new state was not processed add it to the queue to precess on the next step
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


#include<algorithm>



int test () {

    vector<int > a;

    return 0;
}

void print_vector(const vector<int> &v) {
    for(auto i: v) {
        cout << i << " ";
    }
    cout << endl;
}

// Pure storage solutions

// size stack

int ss(const vector<int> & v) {
    std::stack<int> st;
    for(auto i : v) {
        if(i % 2 != 0) {
            st.push(i);
        }
        else {
            int old = st.top(); st.pop();
            if(old > i) {
                st.push(i);
            }
        }
    }
    return st.size();
}

// find doubles
void fd (const vector<int> & v) {

    vector<int> res;
    unordered_map<int, int> m;

    for (auto i: v) {
        m[i]++;
    }

    for (auto i: v) {
        auto s = m.find(i*2);
        if( s != m.end() && s->second == 1 ) {
            res.push_back(i);
        }
    }

    std::sort(res.begin(), res.end());

    print_vector(res);
}

void racers(const vector<vector<int>> & racers_list) {

    vector<vector<int>> points {{1,10},{2,6},{3,4},{4,3},{5,2},{6,1}};


    unordered_map<int,int> players;
    vector<int> losers;

    for(auto i : racers_list) {
        int race = i[0];
        int racer_name = i[1];
        int pos = i[2];
            players[racer_name] += (pos < 7) ? points[pos - 1][1] : 0;
    }

    vector<pair<int,int>> winners;

    for(auto [racer_name, points] : players) {
        if(points > 0) {
            winners.emplace_back(points, racer_name);
        }
        else {
            losers.push_back(racer_name);
        }
    }

    sort(winners.begin(), winners.end());
    sort(losers.begin(), losers.end());

    cout << winners.rbegin()->second << " " << winners.rbegin()->first << endl;

    for(auto i: losers) {
        cout << i << " ";
    }
    cout << endl;
}

struct Point {
    int x;
    int y;
};

vector<Point> GetRestPints(Point a, Point c) {
//    vector<Point> res(2);

    int midX = (a.x + c.y) / 2;
    int midY = (a.y + c.y) / 2;

    int Ax = a.x - midX;
    int Ay = a.y - midY;
    int bX = midX - Ay;
    int bY = midY + Ax;
    Point b{bX,bY};

    int cX =  (c.x - midX);
    int cY =  (c.y - midY);
    int dX = midX - cY;
    int dY = midY + cX;
    Point d{dX,dY};

    return {b, d};

//    res[0] = b;
//    res[1] = d;
//    return res;

}


int SquareCount(const vector<Point> & input) {
    int count = 0;

//    HashSet<Point> set = new HashSet<Point>();
//    foreach (var point in input)
//    set.Add(point);

    unordered_set<Point> set(input.begin(), input.end());

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input.size(); j++) {
            if (i == j)
                continue;
            //For each Point i, Point j, check if b&d exist in set.
            auto DiagVertex = GetRestPints(input[i], input[j]);
            if ( set.count(DiagVertex[0]) && set.count(DiagVertex[1]))
            {
                count++;
            }
        }
    }
    return count;
}


int main()
{

/*
 * answers:
 * 1
 * 2
 * 3 A
 * 4 C = 3
 * 5 B D E
 * 6 A
 * 7 E = 8
 * 8 D
 * 9 D
 * 10 A, B, C, D
 * 11 C
 */


    cout << "\nstack: " << ss({3,3,10,7,4,3,0}) << endl;

    vector<vector<int>> inp {
        {2001,1001,3},
        {2001,1002,2},
        {2002,1003,1},
        {2002,1001,2},
        {2002,1002,3},
        {2001,1003,1},

        {2001,1004,10},
        {2001,1005,11},
        {2001,1006,12},
    };

    racers(inp);

    fd({1,2,3,4,5,6,7,8,9,0,8});

    cout << endl;

    fd({1,1,2});

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

