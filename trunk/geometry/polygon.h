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
 * @note 向量first->second的左边 
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

// ---------------------------------------------------------------------

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

/**
 * @note 逆时针
 */
bool is_intersect_line_convex(const Line& line, const Points& p) {
	if (p.size() <= 1) { return false; }
	if (p.size() == 2) return oppo_site(p[0], p[1], line);
	
	Point e1 = extreme_Point(p, line.first, line.second);
	Point e2 = extreme_Point(p, line.second, line.first);
	return oppo_site(e1, e2, line);
}

