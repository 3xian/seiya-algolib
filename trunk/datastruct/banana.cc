struct Banana
{
    static const int PERIOD = 666;

    int op_cnt;
    vector<vector<int>> v;

    Banana()
        : op_cnt(0) {
    }

    void insert(int x) {
        if (v.empty()) {
            vector<int> t = {x};
            v.push_back(t);
            return;
        }
        size_t p = 0;
        for (size_t i = 0; i < v.size(); ++i) {
            if (!v[i].empty()) {
                if (x < v[i].front()) break;
                p = i;
                if (x <= v[i].back()) break;
            }
        }
        v[p].push_back(x);
        inplace_merge(v[p].begin(), v[p].begin() + v[p].size() - 1, v[p].end());
        maintain();
    }

    void erase(int x) {
        for (size_t i = 0; i < v.size(); ++i) {
            if (!v[i].empty() && v[i].front() <= x && x <= v[i].back()) {
                v[i].erase(lower_bound(v[i].begin(), v[i].end(), x));
                break;
            }
        }
        maintain();
    }

    int prev(int x) {
        int ret;
        for (size_t i = 0; i < v.size(); ++i) {
            if (!v[i].empty()) {
                if (v[i].back() < x) {
                    ret = v[i].back();
                } else {
                    auto it = lower_bound(v[i].begin(), v[i].end(), x);
                    if (it != v[i].begin()) ret = *--it;
                    break;
                }
            }
        }
        maintain();
        return ret;
    }

    int next(int x) {
        int ret;
        for (int i = (int)v.size() - 1; i >= 0; --i) {
            if (!v[i].empty()) {
                if (v[i].front() > x) {
                    ret = v[i].front();
                } else {
                    auto it = upper_bound(v[i].begin(), v[i].end(), x);
                    if (it != v[i].end()) ret = *it;
                    break;
                }
            }
        }
        maintain();
        return ret;
    }

    int rank(int x) {
        int ret;
        for (size_t i = 0; i < v.size(); ++i) {
            if (!v[i].empty()) {
                if (v[i].back() < x) {
                    ret += v[i].size();
                } else {
                    ret += lower_bound(v[i].begin(), v[i].end(), x) - v[i].begin();
                    break;
                }
            }
        }
        maintain();
        return ret;
    }

    void maintain() {
        if (++op_cnt >= PERIOD) {
            op_cnt = 0;
            vector<int> a;
            for (auto& it : v) copy(it.begin(), it.end(), back_inserter(a));
            int ele_size = (int)sqrt(a.size() + 0.1);
            int ele_cnt = a.empty() ? 0 : (a.size() + ele_size - 1) / ele_size;
            v.clear();
            v.resize(ele_cnt, vector<int>());
            for (int i = 0; i < ele_cnt; ++i) {
                v[i].assign(a.begin() + i * ele_size, a.begin() + min((i + 1) * ele_size, (int)a.size()));
            }
        }
    }
};
