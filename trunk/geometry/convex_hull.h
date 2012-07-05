/**
 * @brief GrahamÀ„∑®(offline)
 * @note  ƒÊ ±’Î∑µªÿ
 */
Points get_convex_hull(Points p) {
  std::sort(p.begin(), p.end());
  p.erase(std::unique(p.begin(), p.end()), p.end());
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

