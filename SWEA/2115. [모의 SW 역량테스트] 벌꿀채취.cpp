#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, M, C, tmp;
int ans = -1e9;
int arr[11][11], maxi[11][11];
//maxi배열에는 꿀벌 시작 초기좌표에 - 최대값 저장
vector<int> pos;
struct info {
	int row, col;
};
vector<info> bee;

void init() {
	ans = -1e9;
	cin >> N >> M >> C;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void find_honey(int s, int cnt, int sum, int val) {
	if (sum > C) return;//꿀의 합이 허용수준을 초과하면 종료

	if (cnt == M) {
		tmp = max(tmp, val);
		return;
	}

	for (int i = s; i < M; i++) {
		sum += pos[i]; val += pos[i] * pos[i];
		find_honey(i + 1, cnt + 1, sum, val);
		sum -= pos[i]; val -= pos[i] * pos[i];

		find_honey(i + 1, cnt + 1, sum, val);
	}
}

void find_val() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N - M + 1; j++) {
			for (int k = j; k <= j + M - 1; k++) {
				pos.push_back(arr[i][k]);
			}
			find_honey(0, 0, 0, 0);//최대값 찾기
			pos.clear();
			maxi[i][j] = tmp; tmp = 0;//최대값 저장 후, tmp 초기화
		}
	}
}

void dfs(int r, int c) {
	if (bee.size() == 2) {//벌이 모두 통을 찾으면
		ans = max(ans, maxi[bee[0].row][bee[0].col] + maxi[bee[1].row][bee[1].col]);
		return;
	}

	if (c > N - M + 1) {
		r++; c = 1;
	}
	for (int i = r; i <= N; i++) {
		if (i > r) c = 1;
		for (int j = c; j <= N - M + 1; j++) {
			bee.push_back({ i, j });
			dfs(i, j + M);
			bee.pop_back();
		}
	}

}



int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		find_val();
		dfs(1, 1);
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}