vector<int> e[N];
int com;
int color[N];
vector<int> st;
int dfn[N], dep;

int dfs(int u, int f) {
    int ret = dfn[u] = ++dep;
    bool b = true;

    //st.push_back(u);

    for (int& v : e[u]){
        if (v == f && b) {
            b = false;
            continue;
        }
        if (dfn[v]) {
            ret = min(ret, dfn[v]);
        } else {
            int low = dfs(v, u);
            if (low > dfn[u]) {
                mark_bridge(u, v);
            }
            ret = min(ret, low);
        }
    }

    /*
    if (ret == dfn[u]) {
        while (st.back() != u){
            color[st.back()] = com;
            st.pop_back();
        }
        color[u] = com;
        st.pop_back();
        com++;
    }
    */

    return ret;
}

void get_bridge(int n) {
    com = 0;
    dep = 0;
    st.clear();
    fill(dfn, dfn + n, 0);
    for (int i = 0; i < n; i++) {
        if (not dfn[i])
            dfs(i, -1);
    }
}
