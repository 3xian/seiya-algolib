/**
 * x,y�ֱ��ʾaģb����Ԫ��bģa����Ԫ
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

/**
 * ax + by = c
 */
bool linear_equation(ll a, ll b, ll c, ll& x, ll& y) {
	ll n = gcd(a, b, x, y);
	if (c % n != 0) {
		return false;
	}
	x *= c / n;
	y *= c / n;

	// ��С�Ǹ���
	ll p = abs(b / n);
	ll q = abs(a / n);
	x = (x % p + p) % p;
	y = (y % q + q) % q;

	return true;
}
