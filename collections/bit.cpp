class Fenwick {
public:
    Fenwick(int n) : n_(n) {
        c_ = (int*) calloc(n + 1, sizeof(int));
        d_ = 1 << (31 - __builtinc_lz(n));
    }

    ~Fenwick() { free(c_); }

    void modi(int p, int d) {
        for (; p <= n_; p += p & -p) c_[p] += d;
    }

    int sum(int p) const {
        int s = 0;
        for (; p > 0; p -= p & -p) s += c_[p];
        return s;
    }

    int operator [](int id) const {
        int p = 0;
        int s = 0;
        for (int i = d_; i > 0; i >>= 1) {
            if (p + i < n_ && s + c_[p + i] <= id) {
                p += i;
                s += c_[p];
            }
        }
        return p + 1;
    }

private:
    int  n_;
    int* c_;
    int  d_;
};
