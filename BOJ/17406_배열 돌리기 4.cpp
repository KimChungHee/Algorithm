#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
int N, M, K, ans = 1e9;
int arr[51][51], origin[51][51];
struct pos {
	int r, c, s;
};
vector<pos> v, tmp;
bool check[7];

void init() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
			origin[i][j] = arr[i][j];
		}
	}
	for (int i = 1; i <= K; i++) {
		int a, b, c; cin >> a >> b >> c;
		v.push_back({ a,b,c });
	}
}

void play() {
	for (int k = 0; k < K; k++) {
		int r = tmp[k].r; int c = tmp[k].c; int s = tmp[k].s;
		for (int t = 1; t <= s; t++) {
			int tmp = arr[r - t][c - t];//ÃÊ±â
			for (int i = c - t + 1; i <= c + t; i++) {
				int tmp2 = arr[r - t][i];
				arr[r - t][i] = tmp;
				tmp = tmp2;
			}
			for (int i = r - t + 1; i <= r + t; i++) {
				int tmp2 = arr[i][c + t];
				arr[i][c + t] = tmp;
				tmp = tmp2;
			}
			for (int i = c + t - 1; i >= c - t; i--) {
				int tmp2 = arr[r + t][i];
				arr[r + t][i] = tmp;
				tmp = tmp2;
			}
			for (int i = r + t - 1; i >= r - t; i--) {
				int tmp2 = arr[i][c - t];
				arr[i][c - t] = tmp;
				tmp = tmp2;
			}
		}
	}

	int cnt = 0;
	for (int i = 1; i <= N; i++) {
		cnt = 0;
		for (int j = 1; j <= M; j++) {
			cnt += arr[i][j];
		}
		ans = min(ans, cnt);
	}
}

void recover() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			arr[i][j] = origin[i][j];
		}
	}
}

void dfs() {
	if (tmp.size() == K) {
		play();
		recover();
		return;
	}
	for (int i = 0; i < K; i++) {
		if (check[i]) continue;
		check[i] = true;
		tmp.push_back(v[i]);
		dfs();
		tmp.pop_back();
		check[i] = false;
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	dfs();
	cout << ans;
}