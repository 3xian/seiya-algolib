#include <cassert>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <limits>
#include <vector>

const double EPS = 1E-5;
const double INF = std::numeric_limits<double>::max();

inline int sign(double x) {
  return x < -EPS ? -1 : x > EPS;
}

template <typename T>
inline int next(const std::vector<T>& vec, size_t i) {
  if (i + 1 < vec.size()) { return i + 1; }
  return 0;
}

template <typename T>
inline int prev(const std::vector<T>& vec, size_t i) {
  if (i > 0) { return i - 1; }
  return vec.size() - 1;
}

class Point {
 public:
  double x;
  double y;

 public:
  Point() { }
  Point(double x, double y) : x(x), y(y) { }

  bool operator < (const Point& rs) const;
  bool operator == (const Point& rs) const;
  Point operator + (const Point& rs) const;
  Point operator - (const Point& rs) const;
  Point operator * (double k) const;
  Point operator / (double k) const;

  void get_stdin();
  void print() const;
  double norm() const;
  double square_norm() const;
  Point turn_left() const;
  Point turn_right() const;
};

typedef std::vector<Point> Points;
typedef std::pair<Point, Point> Line;
typedef std::pair<Point, Point> Segment;

bool Point::operator < (const Point& rs) const {
  return x + EPS < rs.x || (x < rs.x + EPS && y + EPS < rs.y);
}

bool Point::operator == (const Point& rs) const {
  return sign(x - rs.x) == 0 && sign(y - rs.y) == 0;
}

Point Point::operator + (const Point& rs) const {
  return Point(x + rs.x, y + rs.y);
}

Point Point::operator - (const Point& rs) const {
  return Point(x - rs.x, y - rs.y);
}

Point Point::operator * (double k) const {
  return Point(x * k, y * k);
}

Point Point::operator / (double k) const {
  return Point(x / k, y / k);
}

//void Point::get_stdin() {
//  scanf("%lf%lf", &x, &y);
//}

void Point::get_stdin() {
  int a, b;
  scanf("%d%d", &a, &b);
  x = a;
  y = b;
}

void Point::print() const {
  printf("(%f, %f)\n", x, y);
}

double Point::norm() const {
  return sqrt(square_norm());
}

double Point::square_norm() const {
  return x * x + y * y;
}

Point Point::turn_left() const {
  return Point(-y, x);
}

Point Point::turn_right() const {
  return Point(y, -x);
}

inline double cross_prod(const Point& a, const Point& b) {
  return a.x * b.y - b.x * a.y;
}

inline double cross_prod(const Point& a, const Point& b, const Point& o) {
  return cross_prod(a - o, b - o);
}

inline double dot_prod(const Point& a, const Point& b) {
  return a.x * b.x + a.y * b.y;
}

double oppo_site(const Point& p1, const Point& p2, const Line& line) {
  return sign(cross_prod(p1, line.first, line.second)) * sign(cross_prod(p2, line.first, line.second)) < 0;
}

Point intersect(const Point& a, const Point& b, const Point& c, const Point& d) {
  double s1 = cross_prod(b - a, c - a);
  double s2 = cross_prod(b - a, d - a);
  return Point(c.x * s2 - d.x * s1, c.y * s2 - d.y * s1) / (s2 - s1);
}

Point foot(const Point& p, const Line& line) {
  return intersect(p, p + (line.second - line.first).turn_left(), line.first, line.second);
}

class Circle {
 public:
  Point center;
  double radius;

 public:
  Circle(const Point& center, double radius) : center(center), radius(radius) { }

  double area() const;
  int intersect_line(const Line& line, Point& p1, Point& p2) const;
};

double Circle::area() const {
  return M_PI * radius * radius;
}

int Circle::intersect_line(const Line& line, Point& p1, Point& p2) const {
  p1 = foot(center, line);
  double d = radius * radius - (p1 - center).square_norm();

  assert(d > EPS);

  if (d < -EPS) { return 0; }
  if (d < EPS) { p2 = p1; return 1; }
  Point v = line.second - line.first;
  double t = sqrt(d) / v.norm();
  p1 = p1 - v * t;
  p2 = p1 + v * (t * 2.0);
  return 2;
}

double arc(const Point& a, const Point& b) {
  double c = cross_prod(a, b);
  double t = atan2(fabs(c), dot_prod(a, b));
  return c >= 0.0 ? t : -t;
}

double bow_area(const Point& p1, const Point& p2, const Circle& o) {
  double a = arc(p1 - o.center, p2 - o.center);
  //printf("a => %f\n", a);
  double arch = fabs(o.radius * o.radius * (a - sin(a)) / 2.0);
  return a >= 0.0 ? o.area() - arch : arch; 
}

Point axes;

inline int dir(const Points& p, int i) {
	return sign(cross_prod(axes, p[next(p, i)] - p[i]));
}

inline bool is_extreme(const Points& p, int i) {
	return dir(p, i) <= 0 && dir(p, prev(p, i)) >= 0;
}

Point extreme_Point(const Points& p, const Point& l1, const Point& l2) {
	axes = l2 - l1;
  int n = p.size();
	int a = 0, b = n - 1, c;
	while (1) {
		c = (a < b) ? (a + b) / 2 : (a + b + n) / 2 % n;
		
		if (is_extreme(p, a)) return p[a];
		if (is_extreme(p, b)) return p[b];
		if (is_extreme(p, c)) return p[c];
		
		if (dir(p, a) >= 0) {
			if (dir(p, c) < 0) b = c;
			else if (sign(cross_prod(axes, p[c] - p[a])) >= 0) a = c;
			else b = c;		
		}
		else {
			if (dir(p, c) >= 0) a = c;
			else if (sign(cross_prod(axes, p[c] - p[a])) < 0) a = c;
			else b = c;
		}
	}
}

bool is_intersect(const Line& line, const Points& p) {
	if (p.size() <= 1) { return false; }
	if (p.size() == 2) return oppo_site(p[0], p[1], line);
	
	Point e1 = extreme_Point(p, line.first, line.second);
	Point e2 = extreme_Point(p, line.second, line.first);
	return oppo_site(e1, e2, line);
}

Points get_convex_hull(Points p) {
  std::sort(p.begin(), p.end());
  //p.erase(std::unique(p.begin(), p.end()), p.end());
  if (p.size() <= 2) { return p; }

  Points hull(p.begin(), p.begin() + 2);

  for (size_t i = 2; i < p.size(); i++) {
    while (hull.size() >= 2 && cross_prod(hull.back(), p[i], hull[hull.size() - 2]) <= 0) {
      hull.pop_back();
    }
    hull.push_back(p[i]);
  }

  size_t half = hull.size();
  for (int i = p.size() - 2; i >= 0; i--) {
    while (hull.size() > half && cross_prod(hull.back(), p[i], hull[hull.size() - 2]) <= 0) {
      hull.pop_back();
    }
    hull.push_back(p[i]);
  }

  hull.pop_back();
  return hull;
}

Line get_best_line(const Point& p, double r) {
  if (sign(p.x) == 0 && sign(p.y) == 0) {
    return Line(p, Point(100.0, 0.0)); // Ëæ±ã
  } else {
    return Line(p, p + p.turn_right());
  }
}

Line get_tan1(const Points& p1, const Points& p2) {
  size_t i = 0;
  size_t j = 0;
  for (i = 0; i < p1.size(); i++) {
    while (cross_prod(p2[j], p2[next(p2, j)], p1[i]) > EPS) { j = next(p2, j); }
    while (cross_prod(p2[j], p2[prev(p2, j)], p1[i]) > EPS) { j = prev(p2, j); }
    if (cross_prod(p2[j], p1[next(p1, i)], p1[i]) > -EPS
        && cross_prod(p2[j], p1[prev(p1, i)], p1[i]) > -EPS) {
      break;
    }
  }
  return Line(p1[i], p2[j]);
}

Line get_tan2(const Points& p1, const Points& p2) {
  size_t i = 0;
  size_t j = 0;
  for (i = 0; i < p1.size(); i++) {
    while (cross_prod(p2[j], p2[next(p2, j)], p1[i]) < -EPS) { j = next(p2, j); }
    while (cross_prod(p2[j], p2[prev(p2, j)], p1[i]) < -EPS) { j = prev(p2, j); }
    if (cross_prod(p2[j], p1[next(p1, i)], p1[i]) < EPS
        && cross_prod(p2[j], p1[prev(p1, i)], p1[i]) < EPS) {
      break;
    }
  }
  return Line(p2[j], p1[i]);
}

std::vector<Line> get_candi(const Points& p1, const Points& p2, double r) {
  std::vector<Line> candi;
  candi.reserve(p1.size() * 3);

  for (size_t i = 0; i < p1.size(); i++) {
    candi.push_back(get_best_line(p1[i], r));
  }

  if (p1.size() <= 3 || p2.size() <= 3) {
    for (size_t i = 0; i < p1.size(); i++) {
      for (size_t j = 0; j < p2.size(); j++) {
        candi.push_back(Line(p1[i], p2[j]));
        candi.push_back(Line(p2[j], p1[i]));
      }
    }
  } else {
    Line tan1 = get_tan1(p1, p2);
    Line tan2 = get_tan2(p1, p2);
    candi.push_back(tan1);
    candi.push_back(tan2);
  }

  return candi;
}

bool on_the_right(const Line& line, const Points& p) {
  for (size_t i = 0; i < 3 && i < p.size(); i++) {
    if (cross_prod(line.second, p[i], line.first) > EPS) {
      return false;
    }
  }
  return !is_intersect(line, p);
}

bool valid(const Line& line, const Points& p1, const Points& p2) {
  for (size_t i = 0; i < 3 && i < p1.size(); i++) {
    if (cross_prod(line.second, p1[i], line.first) < -EPS) { return false; }
  }
  for (size_t i = 0; i < 3 && i < p2.size(); i++) {
    if (cross_prod(line.second, p2[i], line.first) > EPS) { return false; }
  }

  return !is_intersect(line, p1) && !is_intersect(line, p2);
}

double get_area(const Line& line, const Circle& cir) {
  Point p1;
  Point p2;
  cir.intersect_line(line, p1, p2);
  return bow_area(p1, p2, cir);
}

double foo(int radius, const Points& p1, const Points& p2) {
  using namespace std;
  vector<Line> candi = get_candi(p1, p2, radius);
  double min_area = INF;
  Circle cir(Point(0.0, 0.0), radius);
  for (size_t i = 0; i < candi.size(); i++) {
    if (!valid(candi[i], p1, p2)) {
      continue;
    }

    double cur_area = get_area(candi[i], cir);

    //candi[i].first.print();
    //candi[i].second.print();
    //printf("cur_area => %f\n", cur_area);

    if (cur_area < min_area) {
      min_area = cur_area;
    }
  }

  for (size_t i = 0; i < p1.size(); i++) {
    size_t j = (i + 1) % p1.size();
    if (i == j) { continue; }
    Line line = Line(p1[i], p1[j]);
    if (!on_the_right(line, p2)) {
      continue;
    }
    double cur_area = get_area(line, cir);
    if (cur_area < min_area) {
      min_area = cur_area;
    }
  }

  return min_area;
}

int main() {
  int radius;
  int n1;
  int n2;

  scanf("%d", &radius);

  scanf("%d", &n1);
  Points p1(n1);
  for (int i = 0; i < n1; i++) { p1[i].get_stdin(); }

  scanf("%d", &n2);
  Points p2(n2);
  for (int i = 0; i < n2; i++) { p2[i].get_stdin(); }

  p1 = get_convex_hull(p1);
  p2 = get_convex_hull(p2);

  double area1 = foo(radius, p1, p2);
  double area2 = foo(radius, p2, p1);

  printf("%.15f %.15f\n", area1, M_PI * radius * radius - area2);

  return 0;
}
