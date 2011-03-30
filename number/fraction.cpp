template<typename T>
struct frac_t
{
	T a, b;
	frac_t(const T& x = 0, const T& y = 1) {
		T g = gcd(abs(x), abs(y));
		a = x / g;
		b = y / g;
		if (b < 0) a = -a, b = -b;
	}
	T abs(const T& x) const {
		return x < 0 ? -x : x;
	}
	frac_t operator + (const frac_t& r) const {
		T g = gcd(b, r.b);
		return frac_t(r.b / g * a + b / g * r.a, b / g * r.b);
	}
	frac_t operator - (const frac_t& r) const {
		return *this + frac_t(-r.a, r.b);
	}
	frac_t operator * (const frac_t& r) const {
		return frac_t(a * r.a, b * r.b);
	}
	frac_t operator / (const frac_t& r) const {
		return frac_t(a * r.b, b * r.a);
	}
	bool operator < (const frac_t& r) const {
		return (*this - r).a < 0;
	}
	friend istream& operator >> (istream& is, frac_t& r) {
		char ch;
		is >> r.a; is.get(ch);
		if (ch == '/') is >> r.b;
		else { is.putback(ch); r.b = 1; }
		r = frac_t(r.a, r.b);
		return is;
	}
	friend ostream& operator << (ostream& os, const frac_t& r) {
		if (r.a == 0) os << 0;
		else if (r.b == 1) os << r.a;
		else os << r.a << '/' << r.b;
		return os;
	}
};
