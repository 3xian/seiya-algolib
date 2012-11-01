#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

int e[7][7];
map<pii, vector<int> > id; 
vector<int> route;

void dfs(int u) {
  for (int v = 0; v < 7; v++) {
    if (e[u][v]) {
      e[u][v]--;
      e[v][u]--;
      dfs(v);
    }
  }
  route.push_back(u);
}

int no_solution() {
  cout << "No solution";
  return 0;
}

int main() {
  int n;
  int degree[7] = {};

  cin >> n;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    e[a][b]++;
    e[b][a]++;
    degree[a]++;
    degree[b]++;
    id[pii(a, b)].push_back(i + 1);
  }

  int src = 0;
  int odd = 0;
  for (int i = 0; i < 7; i++) {
    if (degree[i] > 0) {
      src = i;
    }
  }
  for (int i = 0; i < 7; i++) {
    if (degree[i] & 1) {
      odd++;
      src = i;
    }
  }

  if (odd > 2) {
    return no_solution();
  } else {
    dfs(src);
    if ((int)route.size() != n + 1) {
      return no_solution();
    }
    reverse(route.begin(), route.end());
    for (size_t i = 0; i + 1 < route.size(); i++) {
      int u = route[i];
      int v = route[i + 1];
      if (id.count(pii(u, v)) and !id[pii(u, v)].empty()) {
        cout << id[pii(u, v)].back() << " +\n";
        id[pii(u, v)].pop_back();
      } else {
        cout << id[pii(v, u)].back() << " -\n";
        id[pii(v, u)].pop_back();
      }
    }
  }

  return 0;
}
