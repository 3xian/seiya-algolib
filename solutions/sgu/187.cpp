#include <cstdio> 
#include <algorithm>
#include <vector>

class Segment {
 public:
  Segment(int st, int ed, int reserved = 0)
      : _st(st), _ed(ed), _reversed(reserved) { }

  bool inside(int st, int ed) const {
    return _st >= st && _ed <= ed;
  }

  int length() const {
    return _ed + 1 - _st;
  }

  std::pair<Segment, Segment> split(int offset) const {
    offset--;
    //printf("st:%d off:%d\n", _st, offset);
    if (!_reversed) {
      return std::pair<Segment, Segment>(
          Segment(_st, _st + offset - 1, 0),
          Segment(_st + offset, _ed, 0)
          );
    } else {
      return std::pair<Segment, Segment>(
          Segment(_ed - offset + 1, _ed, 1),
          Segment(_st, _ed - offset, 1)
          );
    }
  }

  void display() const {
    if (!_reversed) {
      for (int i = _st; i <= _ed; i++) { printf("%d ", i); }
    } else {
      for (int i = _ed; i >= _st; i--) { printf("%d ", i); }
    }
  }

  int _st;
  int _ed;
  int _reversed;
};

typedef std::vector<Segment> Vector;

void split_all(Vector& segments, int pos) {
  int prefix_sum = 0;
  for (size_t i = 0; i < segments.size(); i++) {
    int offset = pos - prefix_sum;
    if (offset == 1) {
      break;
    }
    if (offset <= segments[i].length()) {
      std::pair<Segment, Segment> splited_segments = segments[i].split(offset);
      segments[i] = splited_segments.first;
      segments.insert(segments.begin() + i + 1, splited_segments.second);
      break;
    }
    prefix_sum += segments[i].length();
  }
}

void reverse(Vector& segments, int st, int ed) {
  split_all(segments, st);
  split_all(segments, ed + 1);

  int begin = -1;
  int end = -1;
  int prefix_sum = 0;
  for (size_t i = 0; i < segments.size(); i++) {
    prefix_sum += segments[i].length();
    if (prefix_sum >= st && begin < 0) { begin = i; }
    if (prefix_sum >= ed && end < 0) { end = i; }
  }
  end++;

  for (int i = begin; i < end; i++) {
    segments[i]._reversed ^= 1;
  }
  std::reverse(segments.begin() + begin, segments.begin() + end);
}

void display(const Vector& segments) {
  for (size_t i = 0; i < segments.size(); i++) {
    segments[i].display();
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  Vector segments;
  segments.reserve(m);
  segments.push_back(Segment(1, n));

  for (int i = 0; i < m; i++) {
    //display(segments);
    //putchar('\n');

    int s, t;
    scanf("%d%d", &s, &t);
    reverse(segments, s, t);
  }

  display(segments);

  return 0;
}
