/*
 * 分数类
 * 自动约分
 */

template<typename T>
class Fraction {
public:
	Fraction(const T& x = 0, const T& y = 1) {
		T g = gcd(abs(x), abs(y));
		a = x / g;
		b = y / g;
		if (b < 0)
			a = -a, b = -b;
	}
	T abs(const T& x) const {
		return x < 0 ? -x : x;
	}
	Fraction operator +(const Fraction& r) const {
		T g = gcd(b, r.b);
		return Fraction(r.b / g * a + b / g * r.a, b / g * r.b);
	}
	Fraction operator -(const Fraction& r) const {
		return *this + Fraction(-r.a, r.b);
	}
	Fraction operator *(const Fraction& r) const {
		return Fraction(a * r.a, b * r.b);
	}
	Fraction operator /(const Fraction& r) const {
		return Fraction(a * r.b, b * r.a);
	}
	bool operator <(const Fraction& r) const {
		return (*this - r).a < 0;
	}
	friend istream& operator >>(istream& is, Fraction& r) {
		char ch;
		is >> r.a;
		is.get(ch);
		if (ch == '/') {
			is >> r.b;
		} else {
			is.putback(ch);
			r.b = 1;
		}
		r = Fraction(r.a, r.b);
		return is;
	}
	friend ostream& operator <<(ostream& os, const Fraction& r) {
		if (r.a == 0)
			os << 0;
		else if (r.b == 1)
			os << r.a;
		else
			os << r.a << '/' << r.b;
		return os;
	}

	T a;
	T b;
};
