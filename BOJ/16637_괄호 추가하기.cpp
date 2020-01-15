#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstring>
#include <string>

using namespace std;
int N, numcnt, opcnt;
int ans = -2e31;
int num[12];
char op[12];
bool check[12], numcheck[12];
string s;

void init() {
	cin >> N;
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		if (i % 2 == 0) {
			numcnt++;
			num[numcnt] = s[i] - '0';
		}
		else {
			opcnt++;
			op[opcnt] = s[i];
		}
	}
}

void cal() {
	vector<int> newnum;
	vector<char> newop;
	queue<int> temp;

	for (int i = 1; i <= opcnt; i++) {
		if (check[i]) {
			if (op[i] == '+') {
				temp.push(num[i] + num[i + 1]);
			}
			else if (op[i] == '-') {
				temp.push(num[i] - num[i + 1]);
			}
			else temp.push(num[i] * num[i + 1]);
		}
		else {
			newop.push_back(op[i]);
		}
	}

	for (int i = 1; i <= numcnt; i++) {
		if (numcheck[i]) {
			newnum.push_back(temp.front());
			temp.pop();
			i++;
		}
		else {
			newnum.push_back(num[i]);
		}
	}

	int tmp = newnum[0];
	for (int i = 0; i < newop.size(); i++) {
		if (newop[i] == '+') {
			tmp += newnum[i + 1];
		}
		else if (newop[i] == '-') {
			tmp -= newnum[i + 1];
		}
		else tmp *= newnum[i + 1];
	}

	ans = max(ans, tmp);
}

void dfs(int s, int num, int cnt) {
	if (num == cnt) {
		cal();
		return;
	}

	for (int i = s; i <= opcnt; i++) {
		if (!check[i - 1] && !check[i + 1]) {
			check[i] = true; numcheck[i] = true; numcheck[i + 1] = true;
			dfs(i + 1, num + 1, cnt);
			check[i] = false; numcheck[i] = false; numcheck[i + 1] = false;
		}
	}
}


int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();

	if (opcnt == 0) {
		cout << num[1];
	}
	else {
		for (int i = 1; i <= numcnt / 2; i++) {
			dfs(1, 0, i);//³õÀ» °ýÈ£ ¼ö
		}
		cout << ans;
	}
}