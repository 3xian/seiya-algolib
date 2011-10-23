// s[0..p[i]) = s(i-p[i]..i]
vector<int> prefix_function(const string& s) {
  vector<int> p(s.length());
  if (!s.empty()) {
    p[0] = 0;
    for (size_t i = 1; i < s.size(); i++) {
      p[i] = p[i - 1];
      while (p[i] > 0 && s[i] != s[p[i]]) p[i] = p[p[i] - 1];
      if (s[i] == s[p[i]]) ++p[i];
    }
  }
  return p;
}
