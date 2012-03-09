struct Bit {
    int  _n;
    int* _c;
    int  _d;

    Bit() {
    }
    Bit(int n) {
        _n = n;
        _c = (int*) calloc(n + 1, sizeof(int));
        _d = 1 << (31 - __builtin_clz(n));
    }
    ~Bit() {
        free(_c);
    }
    void modi(int p, int d) {
        for (; p <= _n; p += p & -p) _c[p] += d;
    }
    int sum(int p) const {
        int s = 0;
        for (; p > 0; p -= p & -p) s += _c[p];
        return s;
    }
    int operator [](int id) const {
        int p = 0;
        int s = 0;
        for (int i = _d; i > 0; i >>= 1) {
            if (p + i < _n && s + _c[p + i] <= id) {
                p += i;
                s += _c[p];
            }
        }
        return p + 1;
    }
};
