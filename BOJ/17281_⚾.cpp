#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <string>

using namespace std;
int N, ans;
int hit[10], player[10];
int arr[10][51];
int roo[5];
vector<int> v;
bool check[10];

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> arr[j][i];
		}
	}
}

void play() {
	int cnt = 0; int nxt = 1;//nxt�� ���� Ÿ��
	for (int i = 1; i <= N; i++) {//�̴� �� ��ŭ
		memset(roo, 0, sizeof(roo));
		for (int j = 1; j <= 9; j++) {//Ÿ�� �� ĥ ����
			hit[j] = arr[player[j]][i];
		}
		int out = 0; bool flag = false; bool flag2 = false;
		while (1) {
			if (!flag2) {
				for (int k = nxt; k <= 9; k++) {
					if (hit[k] >= 1 && hit[k] <= 3) {//��Ÿ
						for (int h = 3; h >= 1; h--) {
							if (roo[h] > 0) {//�翡 ��� ������
								if (h + hit[k] >= 4) {//Ȩ�� ����������
									cnt++;
									roo[h] = 0;
								}
								else {//�ƴϸ� ����
									roo[h] = 0;
									roo[h + hit[k]] = 1;
								}
							}
						}
						roo[hit[k]] = 1;//ģ ���� ����
					}
					else if (hit[k] == 4) {//Ȩ��
						for (int h = 3; h >= 1; h--) {
							if (roo[h] > 0) {
								cnt++;
								roo[h] = 0;
							}
						}
						cnt++;
					}
					else {
						out++;//�ƿ�
						if (out == 3) {
							flag = true;
							if (k == 9) {
								nxt = 1;
							}
							else nxt = k + 1;
							break;
						}
					}
				}
				flag2 = true;
			}

			if (flag) break;

			for (int k = 1; k <= 9; k++) {
				if (hit[k] >= 1 && hit[k] <= 3) {//��Ÿ
					for (int h = 3; h >= 1; h--) {
						if (roo[h] > 0) {//�翡 ��� ������
							if (h + hit[k] >= 4) {//Ȩ�� ����������
								cnt++;
								roo[h] = 0;
							}
							else {//�ƴϸ� ����
								roo[h] = 0;
								roo[h + hit[k]] = 1;
							}
						}
					}
					roo[hit[k]] = 1;//ģ ���� ����
				}
				else if (hit[k] == 4) {//Ȩ��
					for (int h = 3; h >= 1; h--) {
						if (roo[h] > 0) {
							cnt++;
							roo[h] = 0;
						}
					}
					cnt++;
				}
				else {
					out++;//�ƿ�
					if (out == 3) {
						flag = true;
						if (k == 9) {
							nxt = 1;
						}
						else nxt = k + 1;
						break;
					}
				}
			}
		}
		ans = max(ans, cnt);
	}
}

void dfs() {
	if (v.size() == 8) {
		int tmp = 0;
		for (int i = 1; i <= 9; i++) {
			if (i >= 1 && i <= 3) {
				player[i] = v[i - 1];
			}
			if (i == 4) {
				player[i] = 1;
			}
			if (i >= 5) {
				player[i] = v[i - 2];
			}
		}
		play();
		return;
	}

	for (int i = 2; i <= 9; i++) {
		if (check[i]) continue;
		check[i] = true;
		v.push_back(i);
		dfs();
		v.pop_back();
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