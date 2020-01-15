#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
int N, ans;
int arr[21][21];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
bool check[21][21];

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void move(int dir) {//배열 이동 함수
	memset(check, false, sizeof(check));

	if (dir == 0) {//상
		for (int i = 1; i <= N; i++) {//열
			for (int j = 2; j <= N; j++) {//행
				if (arr[j][i] == 0) continue;//빈칸은 건너뜀
				for (int k = j - 1; k >= 1; k--) {
					if (arr[k][i] == 0) {//위에가 빈칸이면
						arr[k][i] = arr[k + 1][i];
						arr[k + 1][i] = 0;
					}
					else if ((arr[k][i] == arr[k + 1][i]) && !check[k][i]) {//값이 같으면
						arr[k][i] *= 2;
						arr[k + 1][i] = 0;
						check[k][i] = true;
						break;
					}
					else {
						break;//값 다르면 나감
					}
				}
			}
		}
	}
	else if (dir == 1) {//하
		for (int i = 1; i <= N; i++) {//열
			for (int j = N - 1; j >= 1; j--) {//행
				if (arr[j][i] == 0) continue;//빈칸은 건너뜀
				for (int k = j + 1; k <= N; k++) {
					if (arr[k][i] == 0) {//위에가 빈칸이면
						arr[k][i] = arr[k - 1][i];
						arr[k - 1][i] = 0;
					}
					else if ((arr[k][i] == arr[k - 1][i]) && !check[k][i]) {//값이 같으면
						arr[k][i] *= 2;
						arr[k - 1][i] = 0;
						check[k][i] = true;
						break;
					}
					else {
						break;//값 다르면 나감
					}
				}
			}
		}
	}
	else if (dir == 2) {//좌
		for (int i = 1; i <= N; i++) {//행
			for (int j = 2; j <= N; j++) {//열
				if (arr[i][j] == 0) continue;//빈칸은 건너뜀
				for (int k = j - 1; k >= 1; k--) {
					if (arr[i][k] == 0) {//위에가 빈칸이면
						arr[i][k] = arr[i][k + 1];
						arr[i][k + 1] = 0;
					}
					else if ((arr[i][k] == arr[i][k + 1]) && !check[i][k]) {//값이 같으면
						arr[i][k] *= 2;
						arr[i][k + 1] = 0;
						check[i][k] = true;
						break;
					}
					else {
						break;//값 다르면 나감
					}
				}
			}
		}
	}
	else if (dir == 3) {//우
		for (int i = 1; i <= N; i++) {//행
			for (int j = N - 1; j >= 1; j--) {//열
				if (arr[i][j] == 0) continue;//빈칸은 건너뜀
				for (int k = j + 1; k <= N; k++) {
					if (arr[i][k] == 0) {//위에가 빈칸이면
						arr[i][k] = arr[i][k - 1];
						arr[i][k - 1] = 0;
					}
					else if ((arr[i][k] == arr[i][k - 1]) && !check[i][k]) {//값이 같으면
						arr[i][k] *= 2;
						arr[i][k - 1] = 0;
						check[i][k] = true;
						break;
					}
					else {
						break;//값 다르면 나감
					}
				}
			}
		}
	}
}

void print() {
	cout << '\n';
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}


void dfs(int cnt) {

	int tmp[21][21];
	for (int i = 1; i <= N; i++) {//임시 배열에 저장
		for (int j = 1; j <= N; j++) {
			tmp[i][j] = arr[i][j];
			if (arr[i][j] > ans) ans = arr[i][j];
		}
	}


	if (cnt == 5) {
		return;
	}

	for (int i = 0; i < 4; i++) {
		move(i);//이동
		dfs(cnt + 1);
		for (int j = 1; j <= N; j++) {//복사본을 원래 배열로 옮김
			for (int k = 1; k <= N; k++) {
				arr[j][k] = tmp[j][k];
			}
		}
	}

}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	dfs(0);
	cout << ans;
}