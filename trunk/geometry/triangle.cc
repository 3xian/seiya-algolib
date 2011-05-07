struct Triangle {
    Point p[3];

    Triangle() {}
    Triangle(const Point& a, const Point& b, const Point& c) {
        p[0] = a;
        p[1] = b;
        p[2] = c;
    }

    double area() const { return fabs(cross(p[0] - p[2], p[1] - p[2])) / 2.0; }
    // ����
    // 1) ��������������ƽ������С
    // 2) �����߾���֮�����
    Point centroid() const { return (p[0] + p[1] + p[2]) / 3.0; }
    bool is_clockwise() const { return cross(p[1] - p[0], p[2] - p[0]) < 0.0; }
};

// ����
Point circumcenter(const Point& a, const Point& b, const Point& c) {
    Point p[5];
    perpendicular_bisector(a, b, p[0], p[1]);
    perpendicular_bisector(b, c, p[2], p[3]);
    intersect(p[0], p[1], p[2], p[3], p[4]);
    return p[4];
}
// ����
Point incenter(const Point& a, const Point& b, const Point& c) {
    Point u1 = a, u2, v1 = b, v2, x;
    double t1 = (atan2(b.y - a.y, b.x - a.x) + atan2(c.y - a.y, c.x - a.x)) / 2.0;
    double t2 = (atan2(a.y - b.y, a.x - b.x) + atan2(c.y - b.y, c.x - b.x)) / 2.0;
    u2 = Point(u1.x + cos(t1), u1.y + sin(t1));
    v2 = Point(v1.x + cos(t2), v1.y + sin(t2));
    intersect(u1, u2, v1, v2, x);
    return x;
}
// ����
Point orthocenter(const Point& a, const Point& b, const Point& c) {
    Point u(c.x - a.y + b.y, c.y + a.x - b.x);
    Point v(b.x - a.y + c.y, b.y + a.x - c.x);
    Point x;
    intersect(c, u, b, v, x);
    return x;
}
