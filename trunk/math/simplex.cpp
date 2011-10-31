namespace simplex
{
const double eps = 1e-8;
const double inf = 1e15;
#define OPTIMAL -1
#define UNBOUNDED -2
#define FEASIBLE -3
#define INFEASIBLE -4
#define PIVOT_OK 1

int basic[maxn], row[maxm], col[maxn];
double c0[maxn];

inline double dcmp(double x)
{
  if (x > eps) return 1;
  if (x < -eps) return -1;
  return 0;
}

int Pivot(int n, int m, double* c, double a[maxm][maxn], double* rhs, int& i, int& j)
{
  double min = inf;
  int k = -1;
  for (j = 0; j <= n; j++)
    if (!basic[j] && dcmp(c[j]) > 0)
      if (k < 0 || dcmp(c[j] - c[k]) > 0)
        k = j;
  j = k;
  if(k < 0) return OPTIMAL;
  for (k = -1, i = 1; i <= m; i++) if (dcmp(a[i][j]) > 0)
    if (dcmp(rhs[i] / a[i][j] - min) < 0) { min = rhs[i] / a[i][j]; k = i; }
  i = k;
  if (k < 0) return UNBOUNDED;
  else return PIVOT_OK;
}

int PhaseII(int n, int m, double* c, double a[maxm][maxn], double* rhs, double& ans, int PivotIndex)
{
  int i, j, k, l;
  while (k = Pivot(n,m,c,a,rhs,i,j), k == PIVOT_OK || PivotIndex) {
    if (PivotIndex) {
      j = 0;
      i = PivotIndex;
      PivotIndex = 0;
    }
    basic[row[i]] = 0; col[row[i]] = 0; basic[j] = 1;col[j] = i;row[i]= j;
    double tmp = a[i][j];
    for (k = 0; k <= n; k++) a[i][k] /= tmp; rhs[i] /= tmp;
    for (k = 1; k <= m; k++)
      if (k != i && dcmp(a[k][j])) {
        tmp = -a[k][j];
        for (l = 0; l <= n; l++)
          a[k][l] += tmp * a[i][l];
        rhs[k] += tmp*rhs[i];
      }
    tmp = -c[j];
    for (l = 0; l <= n; l++) c[l] += a[i][l] * tmp;
    ans -= tmp * rhs[i];
  }
  return k;
}

int PhaseI(int n, int m, double* c, double a[maxm][maxn], double* rhs, double& ans)
{
  int i, j, k = -1;
  double tmp, min = 0, ans0 = 0;
  for (i = 1; i <= m; i++)
    if (dcmp(rhs[i] - min) < 0) {
      min = rhs[i];
      k = i;
    }
  if (k < 0) return FEASIBLE;
  for (i = 1; i <= m; i++) a[i][0] = -1;
  for (j = 1; j <= n; j++) c0[j] = 0;
  c0[0] = -1;
  PhaseII(n, m, c0, a, rhs, ans0, k);
  if (dcmp(ans0) < 0) return INFEASIBLE;
  for (i = 1; i <= m; i++) a[i][0] = 0;
  for (j = 1; j <= n; j++)
    if (dcmp(c[j]) && basic[j]) {
      tmp = c[j];
      ans += rhs[col[j]] * tmp;
      for ( i = 0; i <= n ; i++)
        c[i] -= tmp * a[col[j]][i];
    }
  return FEASIBLE;
}

int simplex(int n, int m, double c[maxm], double a[maxm][maxn],
    double rhs[maxm], double& ans, double x[maxn])
{
  int i, j, k;
  for (i = 1; i <= m; i++) {
    for (j = n + 1; j <= n + m; j++)
      a[i][j] = 0;
    a[i][n + i] = 1;
    a[i][0] = 0;
    row[i] = n + i;
    col[n + i] = i;
  }
  k = PhaseI(n + m, m, c, a, rhs, ans);
  if (k == INFEASIBLE) return k;
  k = PhaseII(n + m, m, c, a, rhs, ans, 0);
  for (j = 0; j <= n + m; j++) x[j] = 0;
  for (i = 1; i <= m; i++) x[row[i]] = rhs[i];
  return k;
}
}