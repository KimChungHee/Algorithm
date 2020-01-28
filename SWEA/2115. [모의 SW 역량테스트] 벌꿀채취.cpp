#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, M, C, tmp;
int ans = -1e9;
int arr[11][11], maxi[11][11];
//maxi�迭���� �ܹ� ���� �ʱ���ǥ�� - �ִ밪 ����
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
	if (sum > C) return;//���� ���� �������� �ʰ��ϸ� ����

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
			find_honey(0, 0, 0, 0);//�ִ밪 ã��
			pos.clear();
			maxi[i][j] = tmp; tmp = 0;//�ִ밪 ���� ��, tmp �ʱ�ȭ
		}
	}
}

void dfs(int r, int c) {
	if (bee.size() == 2) {//���� ��� ���� ã����
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