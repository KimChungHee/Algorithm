#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>

using namespace std;
int N;
int ans = 1e9;
int arr[21][21];
vector<int> teamA, teamB;
bool check[21];

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void play() {
	for (int i = 1; i <= N; i++) {
		if (!check[i]) teamB.push_back(i);
	}
	int scoreA = 0, scoreB = 0;

	for (int i = 0; i < teamA.size(); i++) {
		for (int j = 0; j < teamA.size(); j++) {
			scoreA += arr[teamA[i]][teamA[j]];
		}
	}

	for (int i = 0; i < teamB.size(); i++) {
		for (int j = 0; j < teamB.size(); j++) {
			scoreB += arr[teamB[i]][teamB[j]];
		}
	}

	ans = min(ans, abs(scoreA - scoreB));
	teamB.clear();
}


void dfs(int s, int num) {
	if (num == N / 2) {
		play();
		return;
	}

	for (int i = s; i <= N; i++) {
		check[i] = true;
		teamA.push_back(i);
		dfs(i + 1, num + 1);
		teamA.pop_back();
		check[i] = false;
	}
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	check[1] = true; teamA.push_back(1);
	//팀을 두 개로 나누기 때문에, 1을 A팀에 무조건 넣는다고 가정, 중복 연산 제거
	dfs(2, 1);
	cout << ans;
	return 0;
}