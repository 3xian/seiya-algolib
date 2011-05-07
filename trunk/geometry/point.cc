const double AES = 1e-10;
const double EPS = 1e-7;
const double PI = acos(-1.0);

struct Point {
    double x;
    double y;

    Point() {}
    Point(const double& _x, const double& _y) : x(_x), y(_y) {}
    template<typename T> Point(const pair<T, T>& a) : x(a.first), y(a.second) {}

    bool operator < (const Point& a) const { return x + EPS < a.x || x < a.x + EPS && y + EPS < a.y; }
    bool operator == (const Point& a) const { return !(*this < a || a < *this); }
    Point operator + (const Point& a) const { return Point(x + a.x, y + a.y); }
    Point operator - (const Point& a) const { return Point(x - a.x, y - a.y); }
    Point operator * (const double& k) const { return Point(x * k, y * k); }
    Point operator / (const double& k) const { return Point(x / k, y / k); }
    double norm() const { return x * x + y * y; }
    double len() const { return sqrt(norm()); }
    Point scale(const double& k) const { return (*this) * (k / len()); }
    Point turn_left() const { return Point(-y, x); }
    Point turn_right() const { return Point(y, -x); }
    Point rotate(const double& arc) const {
        double co = cos(arc);
        double si = sin(arc);
        return Point(x * co - y * si, x * si + y * co);
    }
};

int sgn(const double& x) { return x < -EPS ? -1 : x > EPS; }
double cross(const Point& a, const Point& b) { return a.x * b.y - b.x * a.y; }
double dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
double arc(const Point& a, const Point& b) {  // arc(b)-arc(a), (-PI,PI]
    double c = cross(a, b);
    double t = atan2(fabs(c), dot(a, b));
    return c >= 0.0 ? t : -t;
}
bool is_incircle(const Point& p, const Point& a, const Point& b, const Point& c) {
    return a.norm() * cross(c - b, p - b) - b.norm() * cross(c - a, p - a)
         + c.norm() * cross(b - a, p - a) - p.norm() * cross(b - a, c - a) > EPS;
}
bool intersect(const Point& a, const Point& b, const Point& c, const Point& d, Point& x) {
    double s1 = cross(b - a, c - a);
    double s2 = cross(b - a, d - a);
    if (sgn(s2 - s1) == 0) return false;
    x = Point(c.x * s2 - d.x * s1, c.y * s2 - d.y * s1) / (s2 - s1);
    return true;
}
void perpendicular_bisector(const Point& p1, const Point& p2, Point &q1, Point &q2) {
    q1 = (p1 + p2) / 2.0;
    q2 = q1 + (p2 - p1).turn_left();
}
