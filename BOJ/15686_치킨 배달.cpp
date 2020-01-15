#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
int N, M;
int ans = 1e9;
int dist[15][102];
int arr[51][51];
vector<int> v;
struct pos {
	int row; int col;
};
vector<pos> chicken, home;

void init() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) home.push_back({ i,j });
			else if (arr[i][j] == 2) chicken.push_back({ i,j });
		}
	}
}

void find_dist() {
	for (int i = 0; i < chicken.size(); i++) {
		for (int j = 0; j < home.size(); j++) {
			dist[i + 1][j + 1] = abs(chicken[i].row - home[j].row) + abs(chicken[i].col - home[j].col);
			//dist[치킨집번호][집번호] = 치킨-집 사이 거리 저장
		}
	}
}

void play() {
	int total = 0;
	for (int i = 0; i < home.size(); i++) {
		int tmp = 1e9;
		for (int j = 0; j < v.size(); j++) {
			tmp = min(tmp, dist[v[j]][i + 1]);
		}
		total += tmp;
		if (total >= ans) return;
	}
	ans = min(ans, total);
}

void dfs(int s) {
	if (v.size() == M) {
		play();
		return;
	}

	for (int i = s; i < chicken.size(); i++) {
		v.push_back(i + 1);//치킨집 번호
		dfs(i + 1);
		v.pop_back();
	}
}



int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	find_dist();
	dfs(0);
	cout << ans;
	return 0;
}