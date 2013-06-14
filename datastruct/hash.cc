template<typename Key, typename Value>
class GoodMap {
public:
    GoodMap() : kv_(NULL), kv_tail_(NULL) {}
    void reserve(int n) {
        heads_.resize(n, -1);
        kv_ = new Node[n];
        kv_tail_ = kv_;
    }
    void clear() {
        fill(heads_.begin(), heads_.end(), -1);
        kv_tail_ = kv_;
    }
    Value& operator [](const Key& key) {
        int h = std::abs(key % heads_.size());
        int p = heads_[h];
        while (p != -1) {
            Node& cur = kv_[p];
            if (cur.key == key) {
                return cur.value;
            }
            p = cur.next;
        }
        kv_tail_->key = key;
        kv_tail_->value = 0;
        kv_tail_->next = heads_[h];
        heads_[h] = kv_tail_ - kv_;
        return (kv_tail_++)->value;
    }
    Value get(const Key& key, const Value& df) {
        int h = std::abs(key % heads_.size());
        int p = heads_[h];
        while (p != -1) {
            const Node& cur = kv_[p];
            if (cur.key == key) {
                return cur.value;
            }
            p = cur.next;
        }
        return df;
    }
private:
    struct Node {
        Key key;
        Value value;
        int next;
    };
    vector<int> heads_;
    Node* kv_;
    Node* kv_tail_;
};
