#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
int N, M, K, ans;
int arr[11][11];
int origin[11][11];
struct pos {
	int row; int col; int age;
};
int dy[8] = { -1,-1,-1,0,0,1,1,1 };
int dx[8] = { -1,0,1,-1,1,-1,0,1 };
vector<int> tree[11][11];

void init() {
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
			origin[i][j] = 5;
		}
	}
	for (int i = 1; i <= M; i++) {
		int a, b, c; cin >> a >> b >> c;
		tree[a][b].push_back(c);
	}
}

void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int tmp = 0;
			if (tree[i][j].size() > 0) {
				sort(tree[i][j].begin(), tree[i][j].end());//나무가 있으면 나이 어린순 정렬
				for (int k = 0; k < tree[i][j].size(); k++) {
					int cur = tree[i][j][k];
					if (origin[i][j] >= cur) {//양분을 먹을 수 있으면
						origin[i][j] -= cur;
						tree[i][j][k] += 1;//양분 먹고 나무 나이 + 1
					}
					else {
						tmp += tree[i][j][k] / 2;
						tree[i][j].erase(tree[i][j].begin() + k);
						k--;
					}
				}
				if (tmp > 0) origin[i][j] += tmp;
			}
		}
	}
}

void fall() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (tree[i][j].size() > 0) {
				for (int k = 0; k < tree[i][j].size(); k++) {
					if (tree[i][j][k] % 5 == 0) {//나이가 5의 배수면
						for (int a = 0; a < 8; a++) {
							int nr = i + dy[a]; int nc = j + dx[a];
							if (nr<1 || nr>N || nc<1 || nc>N) continue;
							tree[nr][nc].push_back(1);//나무 나이 1 짜리 추가
						}
					}
				}
			}
		}
	}
}

void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			origin[i][j] += arr[i][j];
		}
	}
}

void play() {
	while (K--) {
		spring();
		fall();
		winter();
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			ans += tree[i][j].size();
		}
	}
}



int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	play();
	cout << ans;
	return 0;
}