#include <cctype>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

void trans(string& s, string from, string to) {
  while (1) {
    size_t i = s.find(from);
    if (i == string::npos) {
      return;
    }
    s.replace(i, from.size(), to);
  }
}

int main() {
  string s;
  cin >> s;
  trans(s, "<UP>", "\1");
  trans(s, "<DOWN>", "\2");
  trans(s, "</UP>", "\3");
  trans(s, "</DOWN>", "\4");
  //cout << s << endl;

  stack<char> tag;
  string ans;
  int n = s.size();
  for (int i = 0; i < n; i++) {
    if (s[i] <= '\2') {
      tag.push(s[i]);
    } else if (s[i] <= '\4') {
      tag.pop();
    } else {
      if (tag.empty()) {
        ans += s[i];
      } else if (tag.top() == '\1') {
        ans += toupper(s[i]);
      } else {
        ans += tolower(s[i]);
      }
    }
  }

  cout << ans;

  return 0;
}
