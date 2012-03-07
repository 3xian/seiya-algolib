vector<int> order;
vector<int> rank;
vector<int> common_prefix;

vector<int> _tmp;
int _suffix_len;

struct suffix_cmp {
    bool operator ()(int l, int r) {
        if (rank[l] != rank[r]) return rank[l] < rank[r];
        if ((l += _suffix_len) >= order.size()) return l > r;
        if ((r += _suffix_len) >= order.size()) return l > r;
        return rank[l] < rank[r];
    }
};

void suffix_sort(const char* s, int n) {
    order.resize(n);
    for (int i = 0; i < n; i++) order[i] = i;
    rank.assign(s, s + order.size());
    _tmp.resize(n);
    for (_suffix_len = 1; ; _suffix_len *= 2) {
        std::sort(order.begin(), order.end(), suffix_cmp());
        for (int i = 1; i < n; i++) _tmp[i] = _tmp[i - 1] + suffix_cmp()(order[i - 1], order[i]);
        for (int i = 0; i < n; i++) rank[order[i]] = _tmp[i];
        if (_tmp[order.size() - 1] == order.size() - 1) break;
    }
}

void get_common_prefix(const char* s, int n) {
    common_prefix.resize(n);
    int cur_len = 0;
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) continue; 
        if (cur_len > 0) cur_len--;
        for (int j = order[rank[i] + 1]; s[i + cur_len] == s[j + cur_len]; cur_len++) ;
        common_prefix[rank[i]] = cur_len;
    }
}
