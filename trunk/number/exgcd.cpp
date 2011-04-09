/*
 * x,y分别表示a模b的逆元和b模a的逆元
 */
template<typename T>
T gcd(const T& a, const T& b, T& x, T& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	T d = gcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

/*
 * ax + by = c
 */
bool linear_equation(llong a, llong b, llong c, llong& x, llong& y) {
	llong n = gcd(a, b, x, y);
	if (c % n != 0) {
		return false;
	}
	x *= c / n;
	y *= c / n;

	// 最小非负解
	int p = abs(b / n);
	int q = abs(a / n);
	x = (x % p + p) % p;
	y = (y % q + q) % q;

	return true;
}
