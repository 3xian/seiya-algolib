#include <algorithm>
#include <iostream>

#include <cmath>
#include <cstdio>
#include <limits>
#include <vector>

const double EPS = 1E-6;
const double INF = std::numeric_limits<double>::max();

inline int sign(double x) {
  return x < -EPS ? -1 : x > EPS;
}

template <typename T>
inline int next(const std::vector<T>& vec, size_t i) {
  if (i + 1 < vec.size()) { return i + 1; }
  return 0;
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

void Point::get_stdin() {
  int a, b;
  scanf("%d%d", &a, &b);
  x = a;
  y = b;
}

void Point::print() const {
  printf("(%f, %f)\n", x, y);
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

inline double cross_prod(const Segment& seg, const Point& p) {
  return cross_prod(seg.second - seg.first, p - seg.first);
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

double polygon_area(const Points& ps) {
  double sum = 0.0;
  for (size_t i = 0; i < ps.size(); i++) {
    sum += cross_prod(ps[i], ps[next(ps, i)]);
  }
  return fabs(sum * 0.5);
}

bool is_intersect_line_poly(const Line& line, const Points& ps) {
  if (ps.size() <= 1) { return false; }
  if (ps.size() == 2) { return oppo_site(ps[0], ps[1], line); }
  for (size_t i = 0; i < ps.size(); i++) {
    size_t j = next(ps, i);
    if (oppo_site(ps[i], ps[j], line)) { return true; }
    j = next(ps, j);
    if (oppo_site(ps[i], ps[j], line)) { return true; }
  }
  return false;
}

/**
 * @note ÏòÁ¿first->secondµÄ×ó±ß 
 */
Points cut_convex(const Points& ps, const Line& line) {
  Points cutted;
  for (size_t i = 0; i < ps.size(); i++) {
    if (cross_prod(line, ps[i]) > -EPS) {
      cutted.push_back(ps[i]);
    }

    size_t j = next(ps, i);
    if (oppo_site(ps[i], ps[j], line)) {
      cutted.push_back(intersect(ps[i], ps[j], line.first, line.second));
    }
  }
  return cutted;
}

const double OFFSET = 1E6;

std::vector<Points> foo(const std::vector<Points>& polys, const Line& line) {
  std::vector<Points> ret;
  for (size_t i = 0; i < polys.size(); i++) {
    if (is_intersect_line_poly(line, polys[i])) {
      ret.push_back(cut_convex(polys[i], line));
      ret.push_back(cut_convex(polys[i], Line(line.second, line.first)));
    } else {
      ret.push_back(polys[i]);
    }
  }
  return ret;
}

void display(const std::vector<double>& area) {
  std::vector<double> output;
  for (size_t i = 0; i < area.size(); i++) {
    if (area[i] > 1e-8) {
      output.push_back(area[i]);
    }
  }

  std::sort(output.begin(), output.end());
  printf("%u\n", output.size());
  for (size_t i = 0; i < output.size(); i++) {
    printf("%.4f\n", output[i]);
  }
}

bool valid(const Points& ps) {
  for (size_t i = 0; i < ps.size(); i++) {
    if (fabs(ps[i].x) + EPS >= OFFSET) { return false; }
    if (fabs(ps[i].y) + EPS >= OFFSET) { return false; }
  }
  return true;
}

int main() {
  using namespace std;

  vector<Point> poly;
  poly.push_back(Point(-OFFSET, -OFFSET));
  poly.push_back(Point(OFFSET, -OFFSET));
  poly.push_back(Point(OFFSET, OFFSET));
  poly.push_back(Point(-OFFSET, OFFSET));

  vector<Points> polys;
  polys.push_back(poly);

  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    Line line;
    line.first.get_stdin();
    line.second.get_stdin();
    polys = foo(polys, line);

    //printf("size => %u\n", polys.size());
    //for (size_t j = 0; j < polys.size(); j++) {
    //  printf("poly size => %u\n", polys[j].size());
    //  for (size_t k = 0; k < polys[j].size(); k++) {
    //    polys[j][k].print();
    //  }
    //}
  }

  vector<double> area;
  for (size_t i = 0; i < polys.size(); i++) {
    if (valid(polys[i])) {
      double cur = polygon_area(polys[i]);
      area.push_back(cur);

      //printf("i => %d, size => %f\n", i, cur);
    }
  }

  display(area);
  return 0;
}
