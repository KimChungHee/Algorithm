#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
int T, N, M, K, ans, minr = 1e9, minc = 1e9, maxr = -1e9, maxc = -1e9;
struct pos {
	int x, y, z;
};
pos arr[351][351];
bool check[351][351];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void init() {
	ans = 0;
	memset(arr, 0, sizeof(arr));
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int a; cin >> a;
			arr[i + K / 2 + 1][j + K / 2 + 1] = { a,a,a };
			minr = min(minr, i + K / 2 + 1); maxr = max(maxr, i + K / 2 + 1);
			minc = min(minc, j + K / 2 + 1); maxc = max(maxc, j + K / 2 + 1);
		}
	}
}

void play() {
	int a = minr, b = maxr, c = minc, d = maxc;
	while (K--) {

		memset(check, false, sizeof(check));

		for (int i = minr; i <= maxr; i++) {
			for (int j = minc; j <= maxc; j++) {
				if (check[i][j]) continue;

				if (arr[i][j].x > 0) {//������ ������
					pos cur = arr[i][j];
					int x = arr[i][j].x; int y = arr[i][j].y; int z = arr[i][j].z;
					if (z == 0) continue;//��������

					if (x == z && y > 0) {//��Ȱ������
						arr[i][j].y--; continue;
					}
					if (x > 0 && z > 0 && y == 0) {//Ȱ������
						if (x == z) {//�ʱ�Ȱ��������
							for (int q = 0; q < 4; q++) {
								int nr = i + dy[q]; int nc = j + dx[q];
								if (check[nr][nc]) {//�湮�ߴ����̸�
									if (arr[nr][nc].x < x) {//�� ũ�� �ٲܼ�������
										arr[nr][nc].x = x;
										arr[nr][nc].y = x;
										arr[nr][nc].z = x;
									}
								}
								else if (arr[nr][nc].x == 0) {//����̸�
									arr[nr][nc].x = x;
									arr[nr][nc].y = x;
									arr[nr][nc].z = x;
									check[nr][nc] = true;//�湮����
									a = min(a, nr); b = max(b, nr);
									c = min(c, nc); d = max(d, nc);
								}
							}
							arr[i][j].z--;
							continue;
						}
						else {//�ʱ�� �ƴ� Ȱ��������
							arr[i][j].z--;
						}
					}

				}
			}
		}
		minr = a; maxr = b; minc = c; maxc = d;
	}



	for (int i = minr; i <= maxr; i++) {
		for (int j = minc; j <= maxc; j++) {
			if (arr[i][j].x > 0 && arr[i][j].z > 0) {
				ans++;
			}
		}
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