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

/**
 * @note p1->p2×ó²à
 */
double bow_area(const Point& p1, const Point& p2, const Circle& o) {
  double a = arc(p1 - o.center, p2 - o.center);
  double arch = fabs(o.radius * o.radius * (a - sin(a)) / 2.0);
  return a >= 0.0 ? o.area() - arch : arch; 
}

