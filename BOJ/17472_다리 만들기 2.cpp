#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
int N, M, ans, num;
int arr[101][101];
bool check[101][101];
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
vector<int> v, h;
struct pos {
	int row, col;
};
struct edge {
	int v1, v2, w;
};
bool cmp(edge a, edge b) {
	return a.w < b.w;
}
vector<pos> land[7];
vector<edge> e;
struct uf {
	uf(int a) {
		v.resize(a + 1); h.resize(a + 1, 1);
		for (int i = 0; i <= a; i++) v[i] = i;
	}
	int find(int a) {
		if (v[a] == a) return a;
		return v[a] = find(v[a]);
	}
	void _union(int a, int b) {
		a = find(a); b = find(b);
		if (h[a] > h[b]) swap(a, b);
		v[a] = b;
		if (h[a] == h[b]) h[b]++;
	}
	bool same_set(int a, int b) {
		return find(a) == find(b);
	}
};

void init() {
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
		}
	}
}

void land_number(int r, int c) {
	queue<pos> q; q.push({ r,c }); arr[r][c] = num;
	land[num].push_back({ r,c });
	while (!q.empty()) {
		pos cur = q.front(); q.pop();
		int cr = cur.row; int cc = cur.col;
		for (int i = 0; i < 4; i++) {
			int nr = cr + dy[i]; int nc = cc + dx[i];
			if (nr<1 || nr>N || nc<1 || nc>M || check[nr][nc] || arr[nr][nc] == 0) continue;
			q.push({ nr,nc });
			check[nr][nc] = true;
			arr[nr][nc] = num;
			land[num].push_back({ nr,nc });
		}
	}
}

void find_dist(int num) {
	for (int i = 0; i < land[num].size(); i++) {
		int nr = land[num][i].row; int nc = land[num][i].col;
		for (int j = 0; j < 4; j++) {
			int d = 0;
			while (1) {
				nr += dy[j]; nc += dx[j];
				if (nr<1 || nr>N || nc<1 || nc>M || arr[nr][nc] == num) break;
				if (arr[nr][nc] == 0) {
					d++; continue;
				}
				else {
					if (d == 1) break;
					else {
						e.push_back({ num,arr[nr][nc],d });
						break;
					}
				}
			}
		}
	}
}

int kruskal(int a) {
	uf u(a);
	sort(e.begin(), e.end(), cmp);
	for (int i = 0; i < e.size(); i++) {
		if (!u.same_set(e[i].v1, e[i].v2)) {
			u._union(e[i].v1, e[i].v2);
			ans += e[i].w;
		}
	}

	int tmp = u.find(1);
	for (int i = 2; i <= num; i++) {
		if (tmp != u.find(i)) {
			ans = -1;
			break;
		}
	}
	return ans;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	init();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (arr[i][j] == 1 && !check[i][j]) {
				check[i][j] = true;
				num++;
				land_number(i, j);
			}
		}
	}

	for (int i = 1; i <= num; i++) {
		find_dist(i);
	}
	cout << kruskal(num);
}