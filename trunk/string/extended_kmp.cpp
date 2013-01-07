class ExtendedKmp {
public:
    static void pref(const char* a, int len_a, int* pre_a) {
        if (len_a <= 0) return;
        pre_a[0] = len_a;
        if (len_a == 1) return;
        pre_a[1] = mismatch(a, a + len_a - 1, a + 1).first - a;
        for (int i = 2, k = 1; i < len_a; i++) {
            int len1 = k + pre_a[k];
            int len2 = pre_a[i - k];
            if (len2 < len1 - i) {
                pre_a[i] = len2;
            } else {
                int j = max(len1 - i, 0);
                while (i + j < len_a && a[j] == a[i + j]) j++;
                pre_a[i] = j;
                k = i;
            }
        }
    }

    static void pref(const char* a, int len_a, const int* pre_a,
                     const char* b, int len_b, int* pre_b) {
        if (len_b <= 0) return;
        pre_b[0] = mismatch(a, a + min(len_a, len_b), b).first - a;
        for (int i = 1, k = 0; i < len_b; i++) {
            int len1 = k + pre_b[k];
            int len2 = pre_a[i - k];
            if (len2 < len1 - i) {
                pre_b[i] = len2;
            } else {
                int j = max(len1 - i, 0);
                while (j < len_a && i + j < len_b && a[j] == b[i + j]) j++;
                pre_b[i] = j;
                k = i;
            }
        }
    }
};
