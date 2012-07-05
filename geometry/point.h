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

