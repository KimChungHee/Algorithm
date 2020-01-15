#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
int N, minans = 1e9, maxans = -1e9;
int op[4];// +, -, *, /
vector<int> v;

void init() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		int a; cin >> a;
		v.push_back(a);//주어진 수
	}
	for (int i = 0; i < 4; i++) {
		cin >> op[i];//연산자 수
	}
}

void dfs(int cnt, int sum) {
	if (cnt == N) {//N개의 수 모두 연산
		minans = min(sum, minans);
		maxans = max(sum, maxans);
		return;
	}

	if (op[0] > 0) {//+
		op[0]--;
		dfs(cnt + 1, sum + v[cnt]);
		op[0]++;
	}

	if (op[1] > 0) {//-
		op[1]--;
		dfs(cnt + 1, sum - v[cnt]);
		op[1]++;
	}

	if (op[2] > 0) {//*
		op[2]--;
		dfs(cnt + 1, sum * v[cnt]);
		op[2]++;
	}

	if (op[3] > 0) {// /
		op[3]--;
		dfs(cnt + 1, sum / v[cnt]);
		op[3]++;
	}
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	dfs(1, v[0]);
	cout << maxans << '\n' << minans;
	return 0;
}