void all_father() {
  for (int j = 0; j + 1 < L; j++) {
    for (int i = 0; i < n; i++) {
      if (father[i][j] != -1) {
        father[i][j + 1] = father[father[i][j]][j];
      }
    }
  }
}

int lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y); 
  int step = 0;
  while ((1 << (step + 1)) <= dep[x]) step++;

  for (int i = step; i >= 0; i--) {
    if (dep[x] - (1 << i) >= dep[y]) {
      x = father[x][i];
    }
  }

  if (x == y) return x;

  for (int i = step; i >= 0; i--) {
    if (father[x][i] != father[y][i]) {
      x = father[x][i];
      y = father[y][i];
    }
  }

  return father[x][0];
}
