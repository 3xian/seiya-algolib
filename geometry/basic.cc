const double AES = 1e-10;
const double EPS = 1e-6;
const double PI = acos(-1.0);

inline int sgn(double x) {
    return x < -EPS ? -1 : x > EPS;
}

struct Point
{
    double x;
    double y;

    Point() {
    }

    Point(const double &_x, const double &_y)
        : x(_x), y(_y) {
    }

    template<typename A, typename B> Point(const pair<A, B> &a)
        : x(a.first), y(a.second) {
    }

    bool operator <(const Point &a) const {
        return x + EPS < a.x || x < a.x + EPS && y + EPS < a.y;
    }

    bool operator ==(const Point &a) const {
        return !(*this < a || a < *this);
    }

    Point operator +(const Point &a) const {
        return Point(x + a.x, y + a.y);
    }

    Point operator -(const Point &a) const {
        return Point(x - a.x, y - a.y);
    }

    Point operator *(double k) const {
        return Point(x * k, y * k);
    }

    Point operator /(double k) const {
        return Point(x / k, y / k);
    }

    double operator *(const Point &rhs) const {
        return x * rhs.x + y * rhs.y;
    }

    double operator %(const Point &rhs) const {
        return x * rhs.y - y * rhs.x;
    }

    double norm() const {
        return x * x + y * y;
    }

    double len() const {
        return sqrt(norm());
    }

    Point scale(double k) const {
        return (*this) * (k / len());
    }

    Point turn_left() const {
        return Point(-y, x);
    }

    Point turn_right() const {
        return Point(y, -x);
    }

    Point rotate(double arc) const {
        double co = cos(arc);
        double si = sin(arc);
        return Point(x * co - y * si, x * si + y * co);
    }
};

double arc(const Point &a, const Point &b) { // arc(b)-arc(a), (-PI,PI]
    double c = a % b;
    double t = atan2(fabs(c), a * b);
    return c >= 0.0 ? t : -t;
}

double dis(const Point &p, const Point &a, const Point &b) {
    return fabs((p - b) % (a - b)) / (a - b).len();
}

bool is_onsegment(const Point &p, const Point &s1, const Point &s2, bool endpoint = true) {
    return sgn((p - s2) % (s1 - s2)) == 0 && (s1 - p) * (s2 - p) < (endpoint ? EPS : -EPS);
}

bool is_opposide(const Point &a1, const Point &a2, const Point &b1, const Point &b2) {
    return sgn((a1 - b2) % (b1 - b2)) * sgn((a2 - b2) % (b1 - b2)) < 0;
}

bool is_incircle(const Point &p, const Point &a, const Point &b, const Point &c) { // ccw
    return (c - b) % (p - b) * a.norm() - (c - a) % (p - a) * b.norm()
         + (b - a) % (p - a) * c.norm() - (b - a) % (c - a) * p.norm() > EPS;
}

bool is_segment_intersect(const Point &a1, const Point &a2, const Point &b1, const Point &b2, bool endpoint = true) {
    if (is_opposide(a1, a2, b1, b2) && is_opposide(b1, b2, a1, a2)) return true;
    return endpoint && (is_onsegment(a1, b1, b2) || is_onsegment(a2, b1, b2)
                     || is_onsegment(b1, a1, a2) || is_onsegment(b2, a1, a2));
}

bool intersect(const Point &a, const Point &b, const Point &c, const Point &d, Point &out) {
    double t = (b - a) % (d - c);
    if (sgn(t) == 0) return false;
    out = a + (b - a) * ((c - a) % (d - c) / t);
    return true;
}

void perpendicular_bisector(const Point &p1, const Point &p2, Point &q1, Point &q2) {
    q1 = (p1 + p2) / 2.0;
    q2 = q1 + (p2 - p1).turn_left();
}
