#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
int r, c, k, ans;
int rowcnt = 3, colcnt = 3;
int arr[101][101], num[101], tmparr[101][101];
struct pos {
	int num; int numcnt;
};
vector<pos> tmp;
bool cmp(pos a, pos b) {
	if (a.numcnt == b.numcnt) {
		return a.num < b.num;
	}
	return a.numcnt < b.numcnt;
}

void init() {
	cin >> r >> c >> k;
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			cin >> arr[i][j];
}

void R() {
	int nxtcol = 0, maxi = 0;
	for (int i = 1; i <= rowcnt; i++) {//행
		maxi = 0;
		for (int j = 1; j <= colcnt; j++) {//열
			if (arr[i][j] > 0) {
				num[arr[i][j]]++;//숫자 사용횟수 저장
				maxi = max(maxi, arr[i][j]);
			}
		}
		for (int j = 1; j <= maxi; j++) {//임시 벡터에 저장
			if (num[j] > 0) {
				tmp.push_back({ j, num[j] });
				num[j] = 0;
			}
		}
		sort(tmp.begin(), tmp.end(), cmp);//임시 벡터 정렬
		nxtcol = max(nxtcol, (int)tmp.size() * 2);
		for (int j = 0; j < tmp.size(); j++) {
			tmparr[i][j * 2 + 1] = tmp[j].num;
			tmparr[i][j * 2 + 2] = tmp[j].numcnt;
		}
		tmp.clear();
	}
	colcnt = nxtcol;
	for (int i = 1; i <= rowcnt; i++) {
		for (int j = 1; j <= colcnt; j++) {
			arr[i][j] = tmparr[i][j];
		}
	}
	memset(tmparr, 0, sizeof(tmparr));
}

void C() {
	int nxtrow = 0, maxi = 0;
	for (int i = 1; i <= colcnt; i++) {//열
		maxi = 0;
		for (int j = 1; j <= rowcnt; j++) {//행
			if (arr[j][i] > 0) {
				num[arr[j][i]]++;
				maxi = max(maxi, arr[j][i]);
			}
		}
		for (int j = 1; j <= maxi; j++) {
			if (num[j] > 0) {
				tmp.push_back({ j,num[j] });
				num[j] = 0;
			}
		}
		sort(tmp.begin(), tmp.end(), cmp);
		nxtrow = max(nxtrow, (int)tmp.size() * 2);
		for (int j = 0; j < tmp.size(); j++) {
			tmparr[j * 2 + 1][i] = tmp[j].num;
			tmparr[j * 2 + 2][i] = tmp[j].numcnt;
		}
		tmp.clear();
	}
	rowcnt = nxtrow;
	for (int i = 1; i <= rowcnt; i++) {
		for (int j = 1; j <= colcnt; j++) {
			arr[i][j] = tmparr[i][j];
		}
	}
	memset(tmparr, 0, sizeof(tmparr));
}

void play() {
	int cnt = 0;
	int a = 5;
	while (1) {

		if (cnt > 100) {
			ans = -1; break;
		}
		if (arr[r][c] == k) {
			ans = cnt; break;
		}

		if (rowcnt >= colcnt) {
			R();
		}
		else C();

		cnt++;
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