// ‘ –Ìœ‡µ»
template<typename T>
int lis(const vector<T>& arr) {
    vector<T> inc;
    for (auto x : arr) {
        auto ins_pos = upper_bound(inc.begin(), inc.end(), x);
        if (ins_pos == inc.end()) {
            inc.push_back(x);
        } else {
            *ins_pos = x;
        }
    }
    return inc.size();
}
