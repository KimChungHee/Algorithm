#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, ans = 1e9;
int arr[17][17];
bool check[17];
vector<int> teamA, teamB;

void init() {
	ans = 1e9; teamA.clear();
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void play() {
	int A = 0, B = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i == j) continue;
			if (check[i] && check[j]) {
				A += arr[i][j];
			}
			if (!check[i] && !check[j]) {
				B += arr[i][j];
			}
		}
	}
	ans = min(ans, abs(A - B));
}

void dfs(int s, int cnt) {
	if (cnt == N / 2) {
		for (int i = 1; i <= N; i++) {
			if (!check[i]) {
				teamB.push_back(i);
			}
		}
		play();
		teamB.clear();
		return;
	}

	for (int i = s; i <= N; i++) {
		check[i] = true;
		teamA.push_back(i);
		dfs(i + 1, cnt + 1);
		teamA.pop_back();
		check[i] = false;
	}
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		teamA.push_back(1);
		check[1] = true;
		dfs(2, 1);
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}