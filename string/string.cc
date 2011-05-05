vector<string> split(const string& s) {
    vector<string> ret;
    char* ban = "\10\13\t ";
    for (size_t i = 0; i < s.size(); ) {
        size_t p = i + strspn(s.c_str() + i, ban);
        if (p >= s.size()) break;
        i = p + strcspn(s.c_str() + p, ban);
        ret.push_back(string(s.begin() + p, s.begin() + i));
    }
    return ret;
}
