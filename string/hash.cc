struct hstring {
	int length;
	int h1[LOGN][N];
	int h2[LOGN][N];
	int hash1(int a, int b) { return a * a ^ b; }
	int hash2(int a, int b) { return a * 131 + b; }
	void assign(const char *s, int n) {
		length = n;
		for (int j = 0; j < n; j++)
			h1[0][j] = h2[0][j] = s[j];
		for (int i = 0; 1 << i + 1 <= n; i++)
			for (int j = 0; j + (1 << i + 1) <= n; j++) {
				h1[i + 1][j] = hash1(h1[i][j], h1[i][j + (1 << i)]);
				h2[i + 1][j] = hash2(h2[i][j], h2[i][j + (1 << i)]);
			}
	}
};

int lcp(const hstring &a, int ap, const hstring &b, int bp, int len) {
	int diff = len;
	for (int i = LOGN - 1; i >= 0; i--)
		if (1 << i <= diff && a.h1[i][ap] == b.h1[i][bp] && a.h2[i][ap] == b.h2[i][bp])
			ap += 1 << i, bp += 1 << i, diff -= 1 << i;
	return len - diff;
}

int cmp(const hstring &a, int ap, const hstring &b, int bp, int len) {
	int p = lcp(a, ap, b, bp, len);
	return p == len ? 0 : a.h1[0][ap + p] - b.h1[0][bp + p];
}
