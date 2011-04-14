/**
 * @brief simple addition
 *
 * @param a
 * @param b
 *
 * @return a + b
 */
vector<char> operator + (vector<char> a, const vector<char>& b) {
	reverse(a.begin(), a.end());
	for (size_t i = 0, t = 0; i < b.size() || t; ++i) {
		if (i >= a.size()) {
			a.push_back('0');
		}
		if (i < b.size()) {
			t += b[b.size() - 1 - i] - '0';
		}
		a[i] += t;
		if (a[i] > '9') {
			a[i] -= 10;
			t = 1;
		} else {
			t = 0;
		}
	}
	reverse(a.begin(), a.end());
	return a;
}

