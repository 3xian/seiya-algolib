template<typename T>
class KuhnMunkres {
public:
    T INF;  // set me yourself, and be careful about overflow.
    T w[MAX_N][MAX_N];
    int linky[MAX_N];
    int _n;

    KuhnMunkres(int n)
        : _n(n) {
    }

    void run() {
        for (int i = 0; i < _n; i++) {
            lx[i] = *std::max_element(w[i], w[i] + _n);
        }
        fill(ly, ly + _n, 0);
        fill(linky, linky + _n, -1);
        for (int x = 0; x < _n; x++){
            fill(slack, slack+ _n, INF);
            while (true) {
                fill(mkx, mkx + _n, false);
                fill(mky, mky + _n, false);
                if (dfs(x)) break;
                T d = INF;
                for (int i=0; i<_n; i++) if (!mky[i] and slack[i] < d) d = slack[i];
                for (int i=0; i<_n; i++) if (mkx[i]) lx[i] -= d;
                for (int i=0; i<_n; i++) mky[i] ? ly[i] += d : slack[i] -= d;
            }
        }
    }

private:
    bool dfs(int x) {
        mkx[x] = true;
        for (int y = 0; y < _n; y++){
            if (mky[y]) continue;
            T t = lx[x] + ly[y] - w[x][y];
            if (t == 0) {
                mky[y] = true;
                if (linky[y] < 0 or dfs(linky[y])) {
                    linky[y] = x;
                    return true;
                }
            } else {
                slack[y] = min(slack[y], t);
            }
        }
        return false;
    }

    T lx[MAX_N];
    T ly[MAX_N];
    T slack[MAX_N];
    bool mkx[MAX_N];
    bool mky[MAX_N];
};
