/*
 * 单串自动机
 */

int trans[N + 1][C];
int pf[N + 1];

void solo_auto(const string& s) {
	memset(trans, -1, sizeof(int) * (s.length() + 1) * C);
	for (int j = 0; j < C; j++) {
		trans[0][j] = 0;
	}
	for (int i = 0; i < s.length(); i++) {
		trans[i][s[i] - 'a'] = i + 1;
	}
	for (int i = 1; i <= s.length(); i++) {
		if (i == 1) {
			pf[i] = 0;
		} else {
			pf[i] = trans[pf[i - 1]][s[i - 1] - 'a'];
		}
		for (int j = 0; j < C; j++) {
			if (trans[i][j] == -1) {
				trans[i][j] = trans[pf[i]][j];
			}
		}
	}
}

