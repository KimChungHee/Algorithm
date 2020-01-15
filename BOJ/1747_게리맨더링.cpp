#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
int N, ans = 1e9;
int arr[11];
vector<int> v[11], A, B;
bool check[11], Acheck[11], Bcheck[11];

void init() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> arr[i];
	}
	for (int i = 1; i <= N; i++) {
		int a; cin >> a;
		for (int j = 1; j <= a; j++) {
			int b; cin >> b;
			v[i].push_back(b);
		}
	}
}

void findA(int s) {
	Acheck[s] = true;

	for (int i = 0; i < v[s].size(); i++) {
		int nxt = v[s][i];
		if (check[nxt] && !Acheck[nxt]) {
			Acheck[nxt] = true;
			findA(nxt);
		}
	}
}

void findB(int s) {
	Bcheck[s] = true;

	for (int i = 0; i < v[s].size(); i++) {
		int nxt = v[s][i];
		if (!check[nxt] && !Bcheck[nxt]) {
			Bcheck[nxt] = true;
			findB(nxt);
		}
	}
}

bool possible() {
	for (int i = 0; i < A.size(); i++) {
		if (check[A[i]] != Acheck[A[i]]) return false;
	}
	for (int i = 0; i < B.size(); i++) {
		if (check[B[i]] == Bcheck[B[i]]) return false;
	}
	return true;
}

void dfs(int s, int num, int cnt) {
	if (num == cnt) {
		for (int i = 1; i <= N; i++) {
			if (check[i]) A.push_back(i);//A는 트루, B는 FALSE
			else B.push_back(i);
		}

		findA(A[0]); findB(B[0]);

		if (possible()) {
			int a = 0, b = 0;
			for (int i = 1; i <= N; i++) {
				if (check[i]) a += arr[i];
				else b += arr[i];
			}
			ans = min(ans, abs(a - b));
		}
		A.clear(); B.clear();
		memset(Acheck, false, sizeof(Acheck));
		memset(Bcheck, false, sizeof(Bcheck));
		return;
	}

	for (int i = s; i <= N; i++) {
		check[i] = true;
		dfs(i + 1, num, cnt + 1);
		check[i] = false;
	}
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	for (int i = 1; i <= N / 2; i++) {
		dfs(1, i, 0);
	}
	if (ans == 1e9) {
		cout << -1;
	}
	else cout << ans;
}