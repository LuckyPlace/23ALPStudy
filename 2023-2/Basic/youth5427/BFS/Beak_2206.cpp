/*
	Day: 2023.10.10
	참고 : 너비우선탐색(BFS)_실패
*/
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
using namespace std;
int dist[1002][1002][2];		// 1. 벽을 부순 경우. 2. 벽을 하나만 부순 경우
char board[1002][1002];			// 판
int n, m;
int dx[4] = { 1,0,-1,0 };	// 방향
int dy[4] = { 0,1,0,-1 };
int bfs() {
	queue<tuple<int, int, int>> Q;
	
	// 시작점은 index 1부터. 따라서 index 0은 1로 접근 금지
	dist[0][0][0] = 1;
	dist[0][0][1] = 1;
	Q.push({ 0,0,0 });
	int sum = 0;

	while (!Q.empty()) {
		int x, y, broken;
		tie(x, y, broken) = Q.front();

		if (x == n && y == m) {
			return dist[x][y][broken];
		}
		Q.pop();
		int next_dist = dist[x][y][broken] + 1;
		for (int dir = 0; dir < 4; dir++) {		// 상하좌우 탐색
			int nx = x + dx[dir];
			int ny = y + dy[dir];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)	continue;		// 주어진 크기 넘어가기
			if (board[nx][ny] == '0' && dist[nx][ny][broken] == -1) {		// 거리>0?? 이동할 수 없는 칸이면 패스
				dist[nx][ny][broken] = next_dist;
				Q.push({ nx,ny, broken });
			}
			// (nx,ny)를 부수는 경우
			if (!broken && board[nx][ny] == '1' && dist[nx][ny][broken] == -1) {	// 거리>0?? 이동할 수 없는 칸이면 패스
				dist[nx][ny][1] = next_dist;
				Q.push({ nx,ny, 1 });
			}
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(false);	// 지연시간 줄이기
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	
	for (int i = 1; i < n+1; i++) {
		for (int j = 1; j < m+1; j++) {
			cin >> board[i][j];
			dist[i][j][0] = -1;
			dist[i][j][1] = -1;
		}
	}
	cout << bfs();
}
