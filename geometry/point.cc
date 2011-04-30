const double AES = 1e-10;
const double EPS = 1e-7;
const double PI = acos(-1.0);

struct Point
{
    double x;
    double y;

    Point() {}
    Point(const double& x, const double& y)
        : x(x), y(y) {
    }
    template<typename T> Point(const pair<T, T>& a)
        : x(a.first), y(a.second) {
    }
    bool operator < (const Point& a) const {
        return x + EPS < a.x || x < a.x + EPS && y + EPS < a.y;
    }
    bool operator ==(const Point& a) const {
        return !(*this < a || a < *this);
    }
    Point operator + (const Point& a) const {
        return Point(x + a.x, y + a.y);
    }
    Point operator - (const Point& a) const {
        return Point(x - a.x, y - a.y);
    }
    Point operator * (const double& k) const {
        return Point(x * k, y * k);
    }
    Point operator / (const double& k) const {
        return Point(x / k, y / k);
    }
    double norm() const {
        return x * x + y * y;
    }
    double len() const {
        return sqrt(norm());
    }
    Point scale(const double& k) const {
        return (*this) * (k / len());
    }
    Point turn_left() {
        return Point(-y, x);
    }
    Point turn_right() {
        return Point(y, -x);
    }
    Point rotate(const double& arc) {
        double co = cos(arc);
        double si = sin(arc);
        return Point(x * co - y * si, x * si + y * co);
    }
};

int sgn(const double& x) {
    return x < -EPS ? -1 : x > EPS;
}
double cross(const Point& a, const Point& b) {
    return a.x * b.y - b.x * a.y;
}
double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}
// arc(b)-arc(a)
// (-PI,PI]
double arc(const Point& a, const Point& b) {
    double c = cross(a, b);
    double t = atan2(fabs(c), dot(a, b));
    return c >= 0.0 ? t : -t;
}
