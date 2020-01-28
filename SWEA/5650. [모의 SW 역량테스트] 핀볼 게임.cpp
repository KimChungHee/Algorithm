#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, ans;
struct pos {
	int row, col;
};
vector<pos> warm[5];//¿úÈ¦
int arr[102][102];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int nextdir[6][4] = {
{0,0,0,0},
{1, 3, 0, 2},
{3,0,1,2},
{2, 0, 3, 1},
{1, 2, 3, 0},
{1, 0, 3, 2}
};

void init() {
	ans = 0;
	for (int i = 0; i < 5; i++) warm[i].clear();
	memset(arr, 0, sizeof(arr));

	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] >= 6) {//¿úÈ¦
				warm[arr[i][j] - 6].push_back({ i,j });//¿úÈ¦ ÁÂÇ¥ ÀúÀå
			}
		}
	}
	for (int i = 0; i <= N + 1; i++) {
		arr[0][i] = 5; arr[N + 1][i] = 5;
		arr[i][0] = 5; arr[i][N + 1] = 5;
	}
}

void play(int r, int c, int dir) {
	int nr = r; int nc = c; int cd = dir;
	int cnt = 0;
	while (1) {
		nr += dy[cd]; nc += dx[cd];
		if (arr[nr][nc] == -1 || (r == nr && c == nc)) break;
		if (arr[nr][nc] >= 1 && arr[nr][nc] <= 5) {
			cnt++;
			cd = nextdir[arr[nr][nc]][cd];
		}
		else if (arr[nr][nc] >= 6 && arr[nr][nc] <= 10) {
			int tmp = arr[nr][nc] - 6;
			if (warm[tmp][0].row == nr && warm[tmp][0].col == nc) {
				nr = warm[tmp][1].row; nc = warm[tmp][1].col;
			}
			else {
				nr = warm[tmp][0].row; nc = warm[tmp][0].col;
			}
		}
	}
	if (cnt > ans) ans = cnt;
}




int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (arr[i][j] == 0) {
					play(i, j, 0);
					play(i, j, 1);
					play(i, j, 2);
					play(i, j, 3);
				}
			}
		}
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}