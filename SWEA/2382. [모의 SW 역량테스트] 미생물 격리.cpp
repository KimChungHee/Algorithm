#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, M, K, ans;
int dy[5] = { 0,-1,1,0,0 };// �� , �� , ��, ��
int dx[5] = { 0,0,0,-1,1 };
struct pos {
	int cnt; int dir;
	//�̻��� ��, �̵�����
};
struct info {
	int r, c, cnt, dir;
};
vector<pos> v[101][101];
vector<info> cluster;
bool cmp(pos a, pos b) {
	return a.cnt > b.cnt;
}


void init() {
	ans = 0; cluster.clear();

	cin >> N >> M >> K;
	for (int i = 1; i <= K; i++) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		cluster.push_back({ a,b,c,d });
	}
}

void play() {
	while (M--) {
		for (int i = 0; i < cluster.size(); i++) {//������ ����
			info cur = cluster[i];
			int nr = cur.r; int nc = cur.c; int ncnt = cur.cnt; int ndir = cur.dir;

			nr += dy[ndir]; nc += dx[ndir];//���� ��ǥ

			if (nr == 0 || nr == N - 1 || nc == 0 || nc == N - 1) {//�ܰ��̸�
				ncnt /= 2;//�̻��� ���� �������� ����
				if (ncnt == 0) continue;//�̻����� 0�̵Ǹ� ���� �����

				if (ndir == 1) ndir = 2;//���� ����
				else if (ndir == 2) ndir = 1;
				else if (ndir == 3) ndir = 4;
				else ndir = 3;

				v[nr][nc].push_back({ ncnt,ndir });//���� �ʿ� ����
			}
			else {//�ܰ��� �ƴϸ�
				v[nr][nc].push_back({ ncnt,ndir });//���� �ʿ� ����
			}
		}

		cluster.clear();//���� ����

		for (int i = 0; i < N; i++) {//���� ���� ���鼭, Ȯ��
			for (int j = 0; j < N; j++) {
				if (v[i][j].size() == 1) {//������ �� �� ������
					cluster.push_back({ i,j,v[i][j][0].cnt,v[i][j][0].dir });
					//������ �ٽ� �߰�
					v[i][j].clear();//�� Ŭ����
				}
				else if (v[i][j].size() > 1) {//������ ��������
					sort(v[i][j].begin(), v[i][j].end(), cmp);//�̻��� �� ����
					int ccnt = v[i][j][0].cnt; int cdir = v[i][j][0].dir;//���� ū ������ ����
					for (int k = 1; k < v[i][j].size(); k++) {
						ccnt += v[i][j][k].cnt;//������ �̻������� �� ����
					}
					v[i][j].clear();
					cluster.push_back({ i,j,ccnt,cdir });//������ ��ģ ���� �߰�
				}
			}
		}
	}

	for (int i = 0; i < cluster.size(); i++) {
		ans += cluster[i].cnt;
	}
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		init();
		play();
		cout << "#" << tc << ' ' << ans << '\n';
	}
	return 0;
}