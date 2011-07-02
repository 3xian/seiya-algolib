vector<string> split(const string& s) {
  vector<string> ret;
  char *ban = "\r\n\t ";
  for (size_t i = 0; i < s.size(); ) {
    size_t p = i + strspn(s.c_str() + i, ban);
    if (p >= s.size()) break;
    i = p + strcspn(s.c_str() + p, ban);
    ret.push_back(string(s.begin() + p, s.begin() + i));
  }
  return ret;
}

vector<int> get_numbers(const char* str) {
  const char* p = str;
  vector<int> ret;
  while (true) {
    while (!isdigit(*p) && *p != '\0') ++p;
    if (*p == '\0') break;
    int val = 0;
    while (isdigit(*p)) {
      val = val * 10 + *p - '0';
      ++p;
    }
    ret.push_back(val);
  }
  return ret;
}
