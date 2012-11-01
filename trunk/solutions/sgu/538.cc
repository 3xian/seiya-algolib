#include <cctype>
#include <cstring>
#include <cstdio>

bool is_left_bracket(char c) {
  return c == '(';
}

bool is_right_bracket(char c) {
  return c == ')';
}

bool is_bracket(char c) {
  return is_left_bracket(c) || is_right_bracket(c);
}

bool is_soso(char c) {
  return c == ' ' || isalpha(c);
}

int main() {
  static char s[100000 + 2];
  gets(s);
  int n = strlen(s);
  int emotion_num = 0;

  for (int i = 0; i < n; i++) {
    //printf("%d\n", i);
    char c = s[i];
    if (is_bracket(c)) {
      //printf(" %d\n", i);
      if (is_left_bracket(c)) {
        int j = i + 1;
        for (; j < n; j++) {
          if (is_left_bracket(s[j])) {
            i = j - 1;
            emotion_num++;
            goto LOOP_TAIL;
          }

          if (is_right_bracket(s[j])) {
            i = j;
            goto LOOP_TAIL;
          }

          if (!is_soso(s[j])) {
            i = j;
            break;
          }
        }
        emotion_num++;
      } else {
        emotion_num++;
      }
    }

LOOP_TAIL: ;
    //printf("  %d\n", emotion_num);
  }

  printf("%d", emotion_num);
  return 0;
}
