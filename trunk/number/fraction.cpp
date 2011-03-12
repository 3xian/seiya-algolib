template<typename T>
struct Frac
{
	T a, b;

	Frac(const T& x = 0, const T& y = 1) {
		T g = gcd(abs(x), abs(y));
		a = x / g;
		b = y / g;
		if (b < 0) a = -a, b = -b;
	}
	T abs(const T& x) const {
		return x < 0 ? -x : x;
	}
	T gcd(T x, T y) const {
		while (y) { T t = x % y; x = y; y = t; }
		return x;
	}
	Frac operator + (const Frac& r) const {
		T g = gcd(b, r.b);
		return Frac(r.b / g * a + b / g * r.a, b / g * r.b);
	}
	Frac operator - (const Frac& r) const {
		return *this + Frac(-r.a, r.b);
	}
	Frac operator * (const Frac& r) const {
		return Frac(a * r.a, b * r.b);
	}
	Frac operator / (const Frac& r) const {
		return Frac(a * r.b, b * r.a);
	}
	bool operator < (const Frac& r) const {
		return (*this - r).a < 0;
	}
	friend istream& operator >> (istream& is, Frac& r) {
		char ch;
		is >> r.a; is.get(ch);
		if (ch == '/') is >> r.b;
		else { is.putback(ch); r.b = 1; }
		r = Frac(r.a, r.b);
		return is;
	}
	friend ostream& operator << (ostream& os, const Frac& r) {
		if (r.a == 0) os << 0;
		else if (r.b == 1) os << r.a;
		else os << r.a << '/' << r.b;
		return os;
	}
};
