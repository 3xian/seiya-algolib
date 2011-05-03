int trans[N + 1][C];
int pf[N + 1];

void solo_auto(const string& s) {
	memset(trans, -1, sizeof(int) * (s.size() + 1) * C);
	for (int j = 0; j < C; ++j) trans[0][j] = 0;
	for (size_t i = 0; i < s.size(); ++i) trans[i][s[i] - 'a'] = i + 1;
	for (size_t i = 1; i <= s.size(); ++i) {
		pf[i] = (i == 1) ? 0 : trans[pf[i - 1]][s[i - 1] - 'a'];
		for (int j = 0; j < C; ++j) {
			if (trans[i][j] == -1) trans[i][j] = trans[pf[i]][j];
		}
	}
}
