struct Node
{
    vector<int> a;
    ll s[5];

    Node() {
        update();
    }

    int size() const {
        return a.size();
    }

    void insert(int x) {
        a.insert(upper_bound(a.begin(), a.end(), x), x);
        update();
    }

    void erase(int x) {
        a.erase(lower_bound(a.begin(), a.end(), x));
        update();
    }

    void update() {
        memset(s, 0, sizeof s);
        for (size_t i = 0; i < a.size(); ++i) s[i % 5] += a[i];
    }
};

struct Kiwi
{
    list<Node> li;
    int size;

    Kiwi()
        : size(0) {
    }

    void insert(int x) {
        ++size;
        auto it = li.begin();
        for (; it != li.end(); ++it) {
            auto nx = it;
            ++nx;
            int right_bound = (nx == li.end()) ? INF : nx->a[0];
            if (x <= right_bound) break;
        }
        if (it == li.end()) it = li.insert(it, Node());
        it->insert(x);

        if (sq(it->size()) >= size * 4) {
            Node node;
            node.a.assign(it->a.begin() + it->size() / 2, it->a.end());
            node.update();

            it->a.erase(it->a.begin() + it->size() / 2, it->a.end());
            it->update();

            li.insert(++it, node);
        }
    }

    void erase(int x) {
        --size;
        auto it = li.begin();
        while (x > it->a.back()) ++it;
        it->erase(x);
        if (it->size() == 0) {
            li.erase(it);
        } else if (it != li.begin()) {
            auto pv = it;
            --pv;
            if (sq(pv->size() + it->size()) < size * 1.35) {
                copy(it->a.begin(), it->a.end(), back_inserter(pv->a));
                pv->update();
                li.erase(it);
            }
        }
    }

    ll sum() const {
        ll ret = 0;
        int p = 2;
        for (auto it = li.begin(); it != li.end(); ++it) {
            ret += it->s[p];
            p = ((p - (int)it->a.size()) % 5 + 5) % 5;
        }
        return ret;
    }
};
