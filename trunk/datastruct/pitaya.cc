struct Pitaya
{
    Pitaya *l, *r, *f;
    int sub_size;

    Pitaya()
        : l(NULL), r(NULL), f(NULL) {
        sub_size = 1;
    }

    bool is_root() const {
        return f == NULL || f->l != this && f->r != this;
    }

    void update() {
        sub_size = 1;
        if (l != NULL) {
            sub_size += l->sub_size;
        }
        if (r != NULL) {
            sub_size += r->sub_size;
        }
    }

    void lc(Pitaya *p) {
        l = p; if (p != NULL) p->f = this; update();
    }

    void rc(Pitaya *p) {
        r = p; if (p != NULL) p->f = this; update();
    }

    void rotate(int c) {
        Pitaya *g = f->f;
        if (!f->is_root()) (g->l == f) ? g->l = this : g->r = this;
        (c == 0) ? (f->lc(r), rc(f)) : (f->rc(l), lc(f));
        f = g;
    }

    Pitaya *raise() {
        while (!is_root()) {
            if (f->is_root()) {
                f->l == this ? rotate(0) : rotate(1);
            } else if (f->f->l == f) {
                f->l == this ? (f->rotate(0), rotate(0)) : (rotate(1), rotate(0));
            } else {
                f->r == this ? (f->rotate(1), rotate(1)) : (rotate(0), rotate(1));
            }
        }
        return this;
    }
};

void expose(Pitaya *u) {
    for (Pitaya *v = NULL; u != NULL; u = u->f) {
        u->raise();
        u->r = v;
        u->update();
        v = u;
    }
}
