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

/**
 * area of union of triangles
 * O(n^2logn)
 */
double area_union(vector<Triangle> a) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i].is_clockwise()) swap(a[i].p[1], a[i].p[2]);
    }
    vector<double> xs;
    for (size_t i = 0; i < a.size(); ++i) {
        for (int j = 0; j < 3; ++j) xs.push_back(a[i].p[j].x);
        for (size_t j = i + 1; j < a.size(); ++j) {
            Point t;
            for (int u = 0; u < 3; ++u) {
                for (int v = 0; v < 3; ++v) {
                    if (is_segment_intersect(a[i].p[u], a[i].p[(u + 1) % 3], a[j].p[v], a[j].p[(v + 1) % 3], false)) {
                        Point t;
                        intersect(a[i].p[u], a[i].p[(u + 1) % 3], a[j].p[v], a[j].p[(v + 1) % 3], t);
                        xs.push_back(t.x);
                    }
                }
            }
        }
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    double ret = 0.0;
    for (size_t i = 0; i + 1 < xs.size(); ++i) {
        double lf = xs[i];
        double rt = xs[i + 1];
        vector<pair<Point, char> > ys;  // {{left,right},close/open}
        for (vector<Triangle>::iterator it = a.begin(); it != a.end(); ++it) {
            for (int j = 0; j < 3; ++j) {
                Point* u = it->p + j;
                Point* v = it->p + (j + 1) % 3;
                double d = v->x - u->x;
                if (d > EPS && u->x - EPS < lf && rt < v->x + EPS) {  // open
                    double k = (v->y - u->y) / (v->x - u->x);
                    double b = u->y - k * u->x;
                    ys.push_back(make_pair(Point(k * lf + b, k * rt + b), (char)-1));
                }
                if (d < -EPS && v->x - EPS < lf && rt < u->x + EPS) {  // close
                    double k = (u->y - v->y) / (u->x - v->x);
                    double b = u->y - k * u->x;
                    ys.push_back(make_pair(Point(k * lf + b, k * rt + b), (char)1));
                }
            }
        }
        sort(ys.begin(), ys.end());
        int cnt = 0;
        int bot = 0;
        for (size_t j = 0; j < ys.size(); ++j) {
            if (ys[j].second == -1) {
                if (++cnt == 1) bot = j;
            } else {
                if (--cnt == 0) {
                    ret += Triangle(Point(lf, ys[bot].first.x), Point(rt, ys[bot].first.y), Point(lf, ys[j].first.x)).area()
                         + Triangle(Point(lf, ys[j].first.x), Point(rt, ys[j].first.y), Point(rt, ys[bot].first.y)).area();
                }
            }
        }
    }
    return ret;
}
