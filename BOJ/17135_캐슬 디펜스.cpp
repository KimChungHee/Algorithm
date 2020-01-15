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
		for (int i = 0; i < 3; i++) {//�ü� ����
			int dist = D; int r = 0; int c = 0;
			for (int j = 0; j < enemy.size(); j++) {
				if (dist >= abs(hunter[i].row - enemy[j].row) + abs(hunter[i].col - enemy[j].col)) {
					dist = abs(hunter[i].row - enemy[j].row) + abs(hunter[i].col - enemy[j].col);
					r = enemy[j].row; c = enemy[j].col;
				}
			}
			if (dist != 1e9) {//���� ��Ҵٸ�
				temp.push_back({ r,c });//���� �� ��ǥ ����
			}
		}

		for (int i = 0; i < temp.size(); i++) {//���� ���� ���鼭
			if (arr[temp[i].row][temp[i].col] == 1) {
				arr[temp[i].row][temp[i].col] = 0;//�� ����
				cnt++;//���� �� �� ����
			}
		}

		enemy.clear(); temp.clear();

		for (int i = 1; i <= M; i++) {//��
			for (int j = N; j >= 1; j--) {//��
				if (arr[j][i] == 1) {//���� �ִٸ�
					arr[j][i] = 0;
					arr[j + 1][i] = 1;//���� ������Ŵ
					if (j + 1 <= N) {//������ ���� ���� ���̸�
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

	for (int i = s; i <= M; i++) {//�ü��� ���� ��
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