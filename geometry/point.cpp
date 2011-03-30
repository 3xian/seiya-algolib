const double AES = 1e-10;
const double EPS = 1e-7;
const double PI = acos(-1.0);

struct point_t
{
	double x, y;
	point_t() {}
	point_t(const double& x, const double& y) : x(x), y(y) {}
	template<typename T> point_t(const pair<T, T>& a) : x(a.first), y(a.second) {}
	bool operator < (const point_t& a) const {
		return x + EPS < a.x || x < a.x + EPS && y + EPS < a.y;
	}
	bool operator == (const point_t& a) const {
		return !((*this) < a) && !(a < (*this));
	}
	point_t operator + (const point_t& a) const {
		return point_t(x + a.x, y + a.y);
	}
	point_t operator - (const point_t& a) const {
		return point_t(x - a.x, y - a.y);
	}
	point_t operator * (const double& k) const {
		return point_t(x * k, y * k);
	}
	point_t operator / (const double& k) const {
		return point_t(x / k, y / k);
	}
	double norm() const {
		return x * x + y * y;
	}
	double len() const {
		return sqrt(norm());
	}
	point_t scale(const double& k) const {
		return  (*this) * (k / len());
	}
	point_t turn_left() {
		return point_t(-y, x);
	}
	point_t turn_right() {
		return point_t(y, -x);
	}
};
int sgn(const double& x) {
	return x < -EPS ? -1 : x > EPS;
}
double cross(const point_t& a, const point_t& b) {
	return a.x * b.y - b.x * a.y;
}
double dot(const point_t& a, const point_t& b) {
	return a.x * b.x + a.y * b.y;
}
