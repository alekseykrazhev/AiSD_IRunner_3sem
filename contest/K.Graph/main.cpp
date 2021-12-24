#include <iostream>
#include <set>
#include <vector>

using namespace std;
const int INF = 1000000000;
 
int main() {
	int n, m;
	std::cin >> n >> m;
	vector < vector < pair<int,int> > > g (n);
    int u, v1, w;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v1 >> w;
        g[u][v1].second = w;
    }
	int s = 0; // стартовая вершина
 
	vector<int> d (n, INF),  p (n);
	d[s] = 0;
	set < pair<int,int> > q;
	q.insert (make_pair (d[s], s));
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase (q.begin());
 
		for (size_t j=0; j<g[v].size(); ++j) {
			int to = g[v][j].first,
				len = g[v][j].second;
			if (d[v] + len < d[to]) {
				q.erase (make_pair (d[to], to));
				d[to] = d[v] + len;
				p[to] = v;
				q.insert (make_pair (d[to], to));
			}
		}
	}
}