/*
 * 大数类
 * CPS暂不可调
 */

class BigInteger {
public:
	BigInteger() {
	}
	BigInteger(long long x) {
		while (x != 0) {
			d.push_back(x % CPS);
			x /= CPS;
		}
	}
	BigInteger(const char* s) {
		for (int i = strlen(s) - 1, e = CPS; i >= 0; --i) {
			if (e == CPS) {
				d.push_back(s[i] - '0');
				e = 10;
			} else {
				d.back() += (s[i] - '0') * e;
				e *= 10;
			}
		}
		trim();
	}
	int size() const {
		return d.size();
	}
	bool operator <(const BigInteger& r) const {
		if (size() != r.size()) {
			return size() < r.size();
		}
		int i = size() - 1;
		while (i >= 0 && d[i] == r.d[i]) {
			i--;
		}
		return i >= 0 && d[i] < r.d[i];
	}
	BigInteger operator +(const BigInteger& r) const {
		BigInteger o;
		int n = max(size(), r.size());
		int t = 0;
		for (int i = 0; i < n || t; ++i) {
			if (i < size()) {
				t += d[i];
			}
			if (i < r.size()) {
				t += r.d[i];
			}
			o.d.push_back(t % CPS);
			t /= CPS;
		}
		return o;
	}
	BigInteger operator -(const BigInteger& r) const {
		BigInteger o(*this);
		for (size_t i = 0; i < r.size(); ++i) {
			o.d[i] -= r.d[i];
		}
		for (int i = 0; i < size(); i++) {
			if (o.d[i] < 0) {
				o.d[i] += CPS;
				--o.d[i + 1];
			}
		}
		o.trim();
		return o;
	}
	BigInteger operator *(const BigInteger& r) const {
		BigInteger o;
		o.d.resize(size() + r.size(), 0);
		for (int i = 0; i < size(); ++i) {
			long long t = 0;
			for (int j = 0; j < r.size() || t; ++j) {
				t += o.d[i + j];
				if (j < r.size()) {
					t += (long long)d[i] * r.d[j];
				}
				o.d[i + j] = t % CPS;
				t /= CPS;
			}
		}
		o.trim();
		return o;
	}
	BigInteger operator /(int r) const {
		BigInteger c(*this);
		long long t = 0;
		for (int i = size() - 1; i >= 0; --i) {
			t = t * CPS + d[i];
			c.d[i] = t / r;
			t %= r;
		}
		c.trim();
		return c;
	}
	int operator %(int r) const {
		long long t = 0;
		for (int i = size() - 1; i >= 0; --i) {
			t = (t * CPS + d[i]) % r;
		}
		return t;
	}
	friend ostream& operator <<(ostream& os, const BigInteger& r) {
		if (r.d.empty()) {
			os << 0;
		} else {
			os << r.d.back();
			for (int i = r.size() - 2; i >= 0; --i) {
				os << setw(9) << setfill('0') << r.d[i];
			}
		}
		return os;
	}

private:
	void trim() {
		while (!d.empty() && d.back() == 0) {
			d.pop_back();
		}
	}

	static const int CPS = 1000000000;
	vector<int> d;
};
