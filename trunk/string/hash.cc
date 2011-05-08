struct Hstring {
	int size;
	int layer;
    vector<vector<pii>> h;

	Hstring() {}
	Hstring(const string& s) {
	    size = s.size();
	    layer = max(32 - __builtin_clz(size), 1);
	    h.resize(layer, vector<pii>(size));
		for (int j = 0; j < size; ++j) h[0][j].first = h[0][j].second = s[j];
		for (int i = 0; i + 1 < layer; ++i)
			for (int j = 0; j + (1 << i + 1) <= size; ++j)
				h[i + 1][j] = fun(h[i][j], h[i][j + (1 << i)]);
	}

    pii fun(const pii& a, const pii& b) const {
        return pii(a.first * a.first ^ b.first, a.second * 131 + b.second);
    }
};

int lcp(const Hstring& a, int pa, const Hstring& b, int pb) {
    int ret = 0;
	for (int i = min(a.layer, b.layer) - 1; i >= 0; --i) {
		if (pa + (1 << i) <= a.size && pb + (1 << i) <= b.size && a.h[i][pa] == b.h[i][pb]) {
			ret += 1 << i;
			pa += 1 << i;
			pb += 1 << i;
		}
	}
	return ret;
}

int cmp(const Hstring& a, int pa, const Hstring& b, int pb, int len = __INT_MAX__) {
	int n = lcp(a, pa, b, pb);
	if (n >= len || pa + n >= a.size && pb + n >= b.size) return 0;
    if (pa + n >= a.size) return -1;
    if (pb + n >= b.size) return 1;
    return a.h[0][pa + n].first - b.h[0][pb + n].first;
}
