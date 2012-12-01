template <typename WeightType>
class SPFA {
public:
    SPFA(int n) :
        edges_(std::vector<Edges>(n)),
        distance_(std::vector<WeightType>(n)),
        visit_times_(std::vector<int>(n)),
        in_queue_(std::vector<bool>(n)) { }

    void add_edge(int u, int v, const WeightType& weight) {
        edges_[u].push_back(Edge(v, weight));
    }

    bool process(int source) {
        std::deque<int> candi_queue;
        candi_queue.push_back(source);

        distance_[source] = 0;
        visit_times_[source] = 1;
        in_queue_[source] = true;
        int nodes_number = distance_.size();

        while (!candi_queue.empty()) {
            int u = candi_queue.front();
            candi_queue.pop_front();

            for (size_t i = 0; i < edges_[u].size(); ++i) {
                int v = edges_[u][i].v;
                WeightType alter = distance_[u] + edges_[u][i].weight;

                if (visit_times_[v] == 0 || alter < distance_[v]) {
                    if (++visit_times_[v] >= nodes_number) {
                        return false;
                    }
                    distance_[v] = alter;

                    if (!in_queue_[v]) {
                        in_queue_[v] = true;
                        if (!candi_queue.empty() && distance_[v] < distance_[candi_queue.front()]) {
                            candi_queue.push_front(v);
                        } else {
                            candi_queue.push_back(v);
                        }
                    }
                }
            }
            in_queue_[u] = false;
        }

        return true;
    }

    bool can_arrive(int u) const {
        return visit_times_[u] > 0;
    }

    WeightType get_distance(int u) const {
        return distance_[u];
    }

private:
    struct Edge {
        int v;
        WeightType weight;
        Edge(int v, const WeightType& w) : v(v), weight(w) { }
    };

    typedef std::vector<Edge> Edges;

    std::vector<Edges> edges_;
    std::vector<WeightType> distance_;
    std::vector<int> visit_times_;
    std::vector<bool> in_queue_;
};