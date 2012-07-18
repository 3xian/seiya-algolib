class Pitaya
{
 public:
  enum dir_t { LEFT,RIGHT };
  Pitaya* l;
  Pitaya* r;
  Pitaya* f;
  int sub_size;

  Pitaya() : l(NULL),r(NULL),f(NULL),sub_size(1) { }
  dir_t dir() const { return f->r==this ? RIGHT : LEFT; }
  bool is_root() const { return f==NULL || f->l!=this && f->r!=this; }
  void lc(Pitaya* p) { l = p; if (p!=NULL) p->f=this; fresh(); }
  void rc(Pitaya* p) { r = p; if (p!=NULL) p->f=this; fresh(); }

  void fresh() {
    sub_size = 1;
    if (l!=NULL) { sub_size+=l->sub_size; }
    if (r!=NULL) { sub_size+=r->sub_size; }
  }

  void raise() {
    while (!is_root()) {
      if (f->is_root()) { rotate(); break; }
      if (dir()==f->dir()) { f->rotate(); rotate(); }
      else { rotate(); rotate(); }
    }
  }

 private:
  void rotate() {
    Pitaya* g = f->f;
    if (!f->is_root()) { if (g->l==f) g->l=this; else g->r=this; }
    if (dir()==RIGHT) { f->rc(l); lc(f); } else { f->lc(r); rc(f); }
    f = g;
  }
};

void crack(Pitaya* u) {
  for (Pitaya* v = NULL; u != NULL; u = u->f) {
    u->raise();
    u->r = v;
    u->fresh();
    v = u;
  }
}

