#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <string>

using namespace std;
int N, M, D, ans;
int arr[20][20], arrcopy[20][20];
struct pos {
	int row; int col;
};
bool cmp(pos a, pos b) {
	return a.col > b.col;
}
vector<pos> hunter, origin, enemy;

void init() {
	cin >> N >> M >> D;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
			arrcopy[i][j] = arr[i][j];
			if (arr[i][j] == 1) {
				origin.push_back({ i,j });
			}
		}
	}
}

void play() {
	int cnt = 0;
	enemy = origin;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			arr[i][j] = arrcopy[i][j];

	while (1) {
		vector<pos> temp;
		sort(enemy.begin(), enemy.end(), cmp);
		for (int i = 0; i < 3; i++) {//궁수 별로
			int dist = D; int r = 0; int c = 0;
			for (int j = 0; j < enemy.size(); j++) {
				if (dist >= abs(hunter[i].row - enemy[j].row) + abs(hunter[i].col - enemy[j].col)) {
					dist = abs(hunter[i].row - enemy[j].row) + abs(hunter[i].col - enemy[j].col);
					r = enemy[j].row; c = enemy[j].col;
				}
			}
			if (dist != 1e9) {//적을 잡았다면
				temp.push_back({ r,c });//잡은 적 좌표 저장
			}
		}

		for (int i = 0; i < temp.size(); i++) {//잡은 적을 돌면서
			if (arr[temp[i].row][temp[i].col] == 1) {
				arr[temp[i].row][temp[i].col] = 0;//적 제거
				cnt++;//잡은 적 수 증가
			}
		}

		enemy.clear(); temp.clear();

		for (int i = 1; i <= M; i++) {//열
			for (int j = N; j >= 1; j--) {//행
				if (arr[j][i] == 1) {//적이 있다면
					arr[j][i] = 0;
					arr[j + 1][i] = 1;//적을 전진시킴
					if (j + 1 <= N) {//전진한 적이 범위 안이면
						enemy.push_back({ j + 1,i });
					}
				}
			}
		}

		if (enemy.size() == 0) {
			ans = max(ans, cnt);
			break;
		}
	}
}

void dfs(int s) {
	if (hunter.size() == 3) {
		play();
		return;
	}

	for (int i = s; i <= M; i++) {//궁수를 놓을 열
		hunter.push_back({ N + 1,i });
		dfs(i + 1);
		hunter.pop_back();
	}
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	dfs(1);
	cout << ans;
}