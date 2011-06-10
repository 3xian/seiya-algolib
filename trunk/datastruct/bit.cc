struct BIT
{
    int n;
    int *c;
    int d;

    BIT(int _n)
        : n(_n), c(new int[n + 1]) {
        fill(c, c + n + 1, 0);
        d = 1 << (31 - __builtin_clz(n));
    }

    ~BIT() {
        if (c != NULL) delete [] c;
    }

    void modi(int p, int d) {
        for (; p <= n; p += p & -p) c[p] += d;
    }

    int sum(int p) const {
        int s = 0;
        for (; p > 0; p -= p & -p) s += c[p];
        return s;
    }

    int operator [](int id) const {
        int p = 0;
        int s = 0;
        for (int i = d; i > 0; i >>= 1) {
            if (p + i < n && s + c[p + i] <= id) {
                p += i;
                s += c[p];
            }
        }
        return p + 1;
    }
};
