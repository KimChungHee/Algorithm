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
	int cnt = 0; int nxt = 1;//nxt는 다음 타자
	for (int i = 1; i <= N; i++) {//이닝 수 만큼
		memset(roo, 0, sizeof(roo));
		for (int j = 1; j <= 9; j++) {//타자 별 칠 정보
			hit[j] = arr[player[j]][i];
		}
		int out = 0; bool flag = false; bool flag2 = false;
		while (1) {
			if (!flag2) {
				for (int k = nxt; k <= 9; k++) {
					if (hit[k] >= 1 && hit[k] <= 3) {//안타
						for (int h = 3; h >= 1; h--) {
							if (roo[h] > 0) {//루에 사람 있으면
								if (h + hit[k] >= 4) {//홈에 들어갈수있으면
									cnt++;
									roo[h] = 0;
								}
								else {//아니면 전진
									roo[h] = 0;
									roo[h + hit[k]] = 1;
								}
							}
						}
						roo[hit[k]] = 1;//친 주자 전진
					}
					else if (hit[k] == 4) {//홈런
						for (int h = 3; h >= 1; h--) {
							if (roo[h] > 0) {
								cnt++;
								roo[h] = 0;
							}
						}
						cnt++;
					}
					else {
						out++;//아웃
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
				if (hit[k] >= 1 && hit[k] <= 3) {//안타
					for (int h = 3; h >= 1; h--) {
						if (roo[h] > 0) {//루에 사람 있으면
							if (h + hit[k] >= 4) {//홈에 들어갈수있으면
								cnt++;
								roo[h] = 0;
							}
							else {//아니면 전진
								roo[h] = 0;
								roo[h + hit[k]] = 1;
							}
						}
					}
					roo[hit[k]] = 1;//친 주자 전진
				}
				else if (hit[k] == 4) {//홈런
					for (int h = 3; h >= 1; h--) {
						if (roo[h] > 0) {
							cnt++;
							roo[h] = 0;
						}
					}
					cnt++;
				}
				else {
					out++;//아웃
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