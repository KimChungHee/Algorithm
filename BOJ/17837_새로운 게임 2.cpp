#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
int N, K, ans;
int arr[14][14];
struct pos {
	int row; int col; int dir;
};
pos horse[11];
int dy[5] = { 0, 0,0,-1,1 };
int dx[5] = { 0, 1,-1,0,0 };
int nd[5] = { 0, 2, 1, 4, 3 };
vector<int> v[14][14];//�� ����

void init() {
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 1; i <= N; i++) {
		arr[i][0] = 2; arr[i][N + 1] = 2;
		arr[0][i] = 2; arr[N + 1][i] = 2;
	}
	for (int i = 1; i <= K; i++) {
		int a, b, c; cin >> a >> b >> c;
		horse[i] = { a,b,c };
		v[a][b].push_back(i);//�ʿ� �� �߰�
	}
}

void play() {
	int cnt = 0;
	while (1) {
		cnt++;
		if (cnt > 1000) {
			ans = -1; break;
		}

		for (int i = 1; i <= K; i++) {//�� ������� �̵�
			int r = horse[i].row; int c = horse[i].col; int d = horse[i].dir;
			int nr = r + dy[d]; int nc = c + dx[d];//������ǥ

			if (arr[nr][nc] == 0) {//���
				vector<int> tmp;
				for (int j = v[r][c].size() - 1; j >= 0; j--) {
					tmp.push_back(v[r][c][j]);//�ӽú��Ϳ� ����
					if (v[r][c][j] == i) break;//�ش� ���̸� ����
				}
				for (int j = tmp.size() - 1; j >= 0; j--) {
					v[nr][nc].push_back(tmp[j]);//���� ��ǥ�� �߰�
					horse[tmp[j]].row = nr; horse[tmp[j]].col = nc;
				}
				v[r][c].erase(find(v[r][c].begin(), v[r][c].end(), i), v[r][c].end());
				//���� ��ǥ ����
			}

			if (arr[nr][nc] == 1) {//����
				vector<int> tmp;
				for (int j = v[r][c].size() - 1; j >= 0; j--) {
					tmp.push_back(v[r][c][j]);//�ӽú��Ϳ� ����
					if (v[r][c][j] == i) break;//�ش� ���̸� ����
				}
				for (int j = 0; j < tmp.size(); j++) {
					v[nr][nc].push_back(tmp[j]);//���� ��ǥ�� �߰�
					horse[tmp[j]].row = nr; horse[tmp[j]].col = nc;
				}
				v[r][c].erase(find(v[r][c].begin(), v[r][c].end(), i), v[r][c].end());
				//���� ��ǥ ����
			}

			if (arr[nr][nc] == 2) {//�Ķ�

				horse[i].dir = nd[d]; d = horse[i].dir;//�� �������� ����
				nr = r + dy[d]; nc = c + dx[d];

				if (arr[nr][nc] == 0) {//���
					vector<int> tmp;
					for (int j = v[r][c].size() - 1; j >= 0; j--) {
						tmp.push_back(v[r][c][j]);//�ӽú��Ϳ� ����
						if (v[r][c][j] == i) break;//�ش� ���̸� ����
					}
					for (int j = tmp.size() - 1; j >= 0; j--) {
						v[nr][nc].push_back(tmp[j]);//���� ��ǥ�� �߰�
						horse[tmp[j]].row = nr; horse[tmp[j]].col = nc;
					}
					v[r][c].erase(find(v[r][c].begin(), v[r][c].end(), i), v[r][c].end());
					//���� ��ǥ ����
				}

				if (arr[nr][nc] == 1) {//����
					vector<int> tmp;
					for (int j = v[r][c].size() - 1; j >= 0; j--) {
						tmp.push_back(v[r][c][j]);//�ӽú��Ϳ� ����
						if (v[r][c][j] == i) break;//�ش� ���̸� ����
					}
					for (int j = 0; j < tmp.size(); j++) {
						v[nr][nc].push_back(tmp[j]);//���� ��ǥ�� �߰�
						horse[tmp[j]].row = nr; horse[tmp[j]].col = nc;
					}
					v[r][c].erase(find(v[r][c].begin(), v[r][c].end(), i), v[r][c].end());
					//���� ��ǥ ����
				}
			}

			if (v[nr][nc].size() >= 4) {
				ans = cnt;
				break;
			}
		}

		if (ans > 0) break;
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