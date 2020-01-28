#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <string>
#include <list>

using namespace std;
int T, N, ans = 1e9;
int arr[11][11];
struct pos {
    int row, col;
};
vector<pos> people, stair;
int val[3];//1,2계단 길이
int dist[11][3];
bool check[11];
deque<int> A, B, useA, useB, waitA, waitB;

void init() {
    cin >> N;
    ans = 1e9;
    people.clear(); stair.clear();
    int a = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 1) {
                people.push_back({ i,j });
            }
            if (arr[i][j] > 1) {
                stair.push_back({ i,j });
                val[a] = arr[i][j];
                a++;
            }
        }
    }

    for (int i = 0; i < people.size(); i++) {
        for (int j = 0; j < 2; j++) {
            dist[i + 1][j + 1] = abs(people[i].row - stair[j].row) + abs(people[i].col - stair[j].col);
        }
    }
}

void play() {
    int t = 0;
    while (1) {

        for (int i = 0; i < useA.size(); i++) {
            if (useA[i] == t) {//계단 이용이 끝나면
                useA.erase(useA.begin() + i); i--;
            }
        }
        for (int i = 0; i < useB.size(); i++) {
            if (useB[i] == t) {//계단 이용이 끝나면
                useB.erase(useB.begin() + i); i--;
            }
        }

        while (1) {
            if (useA.size() < 3 && waitA.size() > 0) {//계단 대기가 있고, 계단 이용 가능하면
                waitA.pop_front();
                useA.push_back(t + val[1]);//시간과 길이 더해서 저장
            }
            else break;
        }
        while (1) {
            if (useB.size() < 3 && waitB.size() > 0) {//계단 대기가 있고, 계단 이용 가능하면
                waitB.pop_front();
                useB.push_back(t + val[2]);//시간과 길이 더해서 저장
            }
            else break;
        }

        for (int i = 0; i < A.size(); i++) {
            if (A[i] == t) {//계단 도착하면 계단 대기에 넣어줌
                waitA.push_back(1);
                A.erase(A.begin() + i); i--;
            }
        }
        for (int i = 0; i < B.size(); i++) {
            if (B[i] == t) {//계단 도착하면 계단 대기에 넣어줌
                waitB.push_back(1);
                B.erase(B.begin() + i); i--;
            }
        }

        if (A.empty() && B.empty() && useA.empty() && useB.empty() && waitA.empty() && waitB.empty()) {
            break;
        }
        t++;
    }
    ans = min(ans, t);
}

void dfs(int s, int num, int cnt) {
    if (num == cnt) {
        for (int i = 1; i <= people.size(); i++) {
            if (check[i]) A.push_back(dist[i][1]);//거리 삽입
            else B.push_back(dist[i][2]);
        }
        play();
        return;
    }

    for (int i = s; i <= people.size(); i++) {
        check[i] = true;
        dfs(i + 1, num, cnt + 1);
        check[i] = false;
    }
}


int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        init();
        for (int i = 0; i <= people.size(); i++) {
            dfs(0, i, 0);
        }
        cout << "#" << tc << ' ' << ans << '\n';
    }
    return 0;
}