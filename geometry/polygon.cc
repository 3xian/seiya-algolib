typedef vector<Point> Polygon;

bool is_ccw(const Polygon &p) {
    int v = min_element(p.begin(), p.end()) - p.begin();
    return (p[nx(v, p.size())] - p[v]) % (p[pv(v, p.size())] - p[v]) > 0.0;
}

double polygon_area(const Polygon &p) { // 不加fabs则逆时针面积为正
    double sum = 0.0;
    for (int i = p.size() - 1, j = 0; j < p.size(); i = j++) {
        sum += p[i] % p[j];
    }
    return fabs(sum * 0.5);
}

Polygon cut(const Polygon &p, Point a, Point b) { // a->b左侧
    Polygon q;
    for (int i = 0; i < p.size(); ++i) {
        int j = nx(i, p.size());
        if ((b - a) % (p[i] - a) > -EPS) {
            q.push_back(p[i]);
        }
        if (is_opposide(p[i], p[j], a, b)) {
            q.push_back(intersect(p[i], p[j], a, b));
        }
    }
    return q;
}

Polygon cut(Polygon a, const Polygon &b) {
    for (int i = 0; i < b.size() && !a.empty(); ++i) {
        a = cut(a, b[i], b[nx(i, b.size())]);
    }
    return a;
}

void divide(const Polygon &p, vector<int> &ord, vector<Polygon> &tri) {
    if (ord.size() < 3) {
        return;
    }

    int n = ord.size();
    int v = 0;
    for (int i = 1; i < n; ++i) {
        if (p[ord[i]] < p[ord[v]]) v = i;
    }

    int u = pv(v, n);
    int w = nx(v, n);
    int x;
    double d = -1.0;

    for (int i = nx(w, n); i != u; i = nx(i, n)) {
        if (inside_triangle(p[ord[i]], p[ord[u]], p[ord[v]], p[ord[w]], true)) {
            double t = dis(p[ord[i]], p[ord[u]], p[ord[w]]);
            if (t > d) {
                x = i;
                d = t;
            }
        }
    }

    if (d < -EPS) {
        Polygon t(3);
        t[0] = p[ord[u]];
        t[1] = p[ord[v]];
        t[2] = p[ord[w]];
        tri.push_back(t);
        ord.erase(ord.begin() + v);
        divide(p, ord, tri);
    } else {
        vector<int> new_ord;
        for (int i = v; i != x; i = nx(i, n)) {
            new_ord.push_back(ord[i]);
        }
        new_ord.push_back(ord[x]);
        divide(p, new_ord, tri);

        new_ord.clear();
        for (int i = x; i != w; i = nx(i, n)) {
            new_ord.push_back(ord[i]);
        }
        divide(p, new_ord, tri);
    }
}

vector<Polygon> polygon_triangulation(const vector<Point> &p) {
    vector<Polygon> ret;
    vector<int> ord(p.size());
    for (int i = 0; i < p.size(); ++i) {
        ord[i] = i;
    }
    divide(p, ord, ret);
    return ret;
}

double intersect_area(const Polygon &a, Polygon b) {
    vector<Polygon> ta = polygon_triangulation(a);
    vector<Polygon> tb = polygon_triangulation(b);

    if (!is_ccw(b)) {
        reverse(b.begin(), b.end());
    }

    double sum = 0.0;
    for (int i = 0; i < ta.size(); ++i) {
        for (int j = 0; j < tb.size(); ++j) {
            sum += polygon_area(cut(ta[i], tb[j]));
        }
    }
    return sum;
}
