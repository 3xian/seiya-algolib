void get_next(const char* s, int n, int* next) {
    if (n <= 0) return;
    next[0] = -1;
    for (int i = 1, j = -1; i < n; ++i) {
        while (true) {
            if (s[i] == s[j + 1]) {
                next[i] = ++j;
                break;
            }
            if (j == -1) {
                next[i] = -1;
                break;
            }
            j = next[j];
        }
    }
}
