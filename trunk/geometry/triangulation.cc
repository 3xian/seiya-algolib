/**
 * Incremental Delaunay Triangulation
 * random_shuffle the points before use
 */

struct TriangleNode;

struct Edge {
    TriangleNode* tri;
    int side;

    Edge() : tri(NULL), side(0) {}
    Edge(TriangleNode* _tri, int _side) : tri(_tri), side(_side) {}
};

struct TriangleNode {
    const Point* p[3];
    Edge edge[3];
    TriangleNode* child[3];

    TriangleNode() {}
    TriangleNode(const Point* p0, const Point* p1, const Point* p2) {
        p[0] = p0;
        p[1] = p1;
        p[2] = p2;
        child[0] = NULL;
        child[1] = NULL;
        child[2] = NULL;
    }

    double side_length(int side) const {
        return (*p[(side + 1) % 3] - *p[(side + 2) % 3]).len();
    }
    bool contain(Point const& q) const {
        return cross(*p[0] - q, *p[1] - q) > -EPS
            && cross(*p[1] - q, *p[2] - q) > -EPS
            && cross(*p[2] - q, *p[0] - q) > -EPS;
    }
};

void link(const Edge& a, const Edge& b) {
    if (a.tri != NULL) a.tri->edge[a.side] = b;
    if (b.tri != NULL) b.tri->edge[b.side] = a;
}

struct Triangulation {
    struct Block {
        TriangleNode* tri;
        Block* prev;

        Block(Block* p) : prev(p) { tri = new TriangleNode[BLOCK_SIZE]; }
        ~Block() { delete prev; delete [] tri; }
    };

    static const int BLOCK_SIZE = 2048;
    int node_num;
    Block* block;
    TriangleNode* root;
    Point inf[3];

    Triangulation() {
        const double LOTS = 1e6;
        node_num = 0;
        block = NULL;

        inf[0] = Point(-LOTS, -LOTS);
        inf[1] = Point(+LOTS, -LOTS);
        inf[2] = Point(0, +LOTS);
        root = new_triangle(inf, inf + 1, inf + 2);
    }
    ~Triangulation() {
        delete block;
    }

    TriangleNode* new_triangle(const Point* p0, const Point* p1, const Point* p2) {
        int offset = node_num++ & (BLOCK_SIZE - 1);
        if (offset == 0) block = new Block(block);
        *(block->tri + offset) = TriangleNode(p0, p1, p2);
        return block->tri + offset;
    }
    TriangleNode* find(const Point& p) const {
        return find(root, p);
    }
    void add_point(const Point* p) {
        add_point(find(root, *p), p);
    }
    TriangleNode* find(TriangleNode* root, const Point& p) const {
        while (root->child[0] != NULL) {
            for (int i = 0 ; i < 3 && root->child[i] != NULL; ++i) {
                if (root->child[i]->contain(p)) {
                    root = root->child[i];
                    break;
                }
            }
        }
        return root;
    }
    void add_point(TriangleNode* root, const Point* p) {
        TriangleNode* tab = new_triangle(root->p[0], root->p[1], p);
        TriangleNode* tbc = new_triangle(root->p[1], root->p[2], p);
        TriangleNode* tca = new_triangle(root->p[2], root->p[0], p);

        link(Edge(tab, 0), Edge(tbc, 1));
        link(Edge(tbc, 0), Edge(tca, 1));
        link(Edge(tca, 0), Edge(tab, 1));
        link(Edge(tab, 2), root->edge[2]);
        link(Edge(tbc, 2), root->edge[0]);
        link(Edge(tca, 2), root->edge[1]);

        root->child[0] = tab;
        root->child[1] = tbc;
        root->child[2] = tca;

        flip(tab, 2);
        flip(tbc, 2);
        flip(tca, 2);
    }
    void flip(TriangleNode* tri, int pi) {
        TriangleNode* trj = tri->edge[pi].tri;
        int pj = tri->edge[pi].side;

        if (trj == NULL) return;
        if (!is_incircle(*trj->p[pj], *tri->p[0], *tri->p[1], *tri->p[2])) return;

        TriangleNode* trk = new_triangle(tri->p[(pi + 1) % 3], trj->p[pj], tri->p[pi]);
        TriangleNode* trl = new_triangle(trj->p[(pj + 1) % 3], tri->p[pi], trj->p[pj]);

        link(Edge(trk, 0), Edge(trl, 0));
        link(Edge(trk, 1), tri->edge[(pi + 2) % 3]);
        link(Edge(trk, 2), trj->edge[(pj + 1) % 3]);
        link(Edge(trl, 1), trj->edge[(pj + 2) % 3]);
        link(Edge(trl, 2), tri->edge[(pi + 1) % 3]);

        tri->child[0] = trk; tri->child[1] = trl; tri->child[2] = NULL;
        trj->child[0] = trk; trj->child[1] = trl; trj->child[2] = NULL;

        flip(trk, 1);
        flip(trk, 2);
        flip(trl, 1);
        flip(trl, 2);
    }
};
