/**
 * 返回{1..n}的第k排列
 * k从1开始计数
 * n的全排列少于k则返回空向量
 */
vector<int> kth_permutation(int n, int k)
{
  vector<int> p;
  vector<ll> f(n + 1, 1);
  for (int i = 1; i <= n; i++)
  {
    f[i] = f[i - 1] * i;
  }
  if (k > f[n] || k < 1) return p;
  k--;
  int* rank = new int[n];
  for (int i = 0; i < n; i++) rank[i] = i + 1;
  for (int i = 0; i < n; i++)
  {
    int t = k / f[n - i - 1];
    k -= t * f[n - i - 1];
    p.push_back(rank[t]);
    //debug(t);
    for (int j = t; j + 1 + i < n; j++) rank[j] = rank[j + 1];
  }
  delete[] rank;
  return p;
}