vector<int> pref(const string& s) {
	vector<int> pf(s.length());
	if (s.length() > 0) {
		pf[0] = 0;
	}
	for (int i = 1; i < s.length(); i++) {
		pf[i] = pf[i - 1];
		while (pf[i] > 0 && s[i] != s[pf[i]]) {
			pf[i] = pf[pf[i] - 1];
		}
		if (s[i] == s[pf[i]]) {
			pf[i]++;
		}
	}
	return pf;
}
