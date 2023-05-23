// graph
template <typename T>
class graph {
 public:
  struct edge {
    int from;
    int to;
    T cost;
  };
  vector<edge> edges;
  vector<vector<int> > g;
  int n;
  graph(int _n) : n(_n) { g.resize(n); }
  virtual int add(int from, int to, T cost) = 0;
};

// undirectedgraph
template <typename T>
class undirectedgraph : public graph<T> {
 public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  undirectedgraph(int _n) : graph<T>(_n) {}
  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int)edges.size();
    g[from].push_back(id);
    g[to].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
};

// blossom / find_max_unweighted_matching
template <typename T>
vector<int> find_max_unweighted_matching(const undirectedgraph<T> &g) {
  std::mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  vector<int> match(g.n, -1);   // ƥ��
  vector<int> aux(g.n, -1);     // ʱ�����
  vector<int> label(g.n);       // "o" or "i"
  vector<int> orig(g.n);        // ����
  vector<int> parent(g.n, -1);  // ���ڵ�
  queue<int> q;
  int aux_time = -1;

  auto lca = [&](int v, int u) {
    aux_time++;
    while (true) {
      if (v != -1) {
        if (aux[v] == aux_time) {  // �ҵ��ݷù��ĵ� Ҳ����LCA
          return v;
        }
        aux[v] = aux_time;
        if (match[v] == -1) {
          v = -1;
        } else {
          v = orig[parent[match[v]]];  // ��ƥ���ĸ��ڵ����Ѱ��
        }
      }
      swap(v, u);
    }
  };  // lca

  auto blossom = [&](int v, int u, int a) {
    while (orig[v] != a) {
      parent[v] = u;
      u = match[v];
      if (label[u] == 1) {  // ��ʼ����Ϊ"o" ������·
        label[u] = 0;
        q.push(u);
      }
      orig[v] = orig[u] = a;  // ����
      v = parent[u];
    }
  };  // blossom

  auto augment = [&](int v) {
    while (v != -1) {
      int pv = parent[v];
      int next_v = match[pv];
      match[v] = pv;
      match[pv] = v;
      v = next_v;
    }
  };  // augment

  auto bfs = [&](int root) {
    fill(label.begin(), label.end(), -1);
    iota(orig.begin(), orig.end(), 0);
    while (!q.empty()) {
      q.pop();
    }
    q.push(root);
    // ��ʼ����Ϊ "o", ������"0"����"o", "1"����"i"
    label[root] = 0;
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : g.g[v]) {
        auto &e = g.edges[id];
        int u = e.from ^ e.to ^ v;
        if (label[u] == -1) {  // �ҵ�δ�ݷõ�
          label[u] = 1;        // ��� "i"
          parent[u] = v;
          if (match[u] == -1) {  // �ҵ�δƥ���
            augment(u);          // Ѱ������·��
            return true;
          }
          // �ҵ���ƥ��� ������ƥ��ĵ㶪��queue ���콻����
          label[match[u]] = 0;
          q.push(match[u]);
          continue;
        } else if (label[u] == 0 && orig[v] != orig[u]) {
          // �ҵ��Ѱݷõ� �ұ��ͬΪ"o" �����ҵ�"��"
          int a = lca(orig[v], orig[u]);
          // ��LCA Ȼ������
          blossom(u, v, a);
          blossom(v, u, a);
        }
      }
    }
    return false;
  };  // bfs

  auto greedy = [&]() {
    vector<int> order(g.n);
    // ������� order
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end(), rng);

    // ������ƥ��ĵ�ƥ��
    for (int i : order) {
      if (match[i] == -1) {
        for (auto id : g.g[i]) {
          auto &e = g.edges[id];
          int to = e.from ^ e.to ^ i;
          if (match[to] == -1) {
            match[i] = to;
            match[to] = i;
            break;
          }
        }
      }
    }
  };  // greedy

  // һ��ʼ�����ƥ��
  greedy();
  // ��δƥ���������·
  for (int i = 0; i < g.n; i++) {
    if (match[i] == -1) {
      bfs(i);
    }
  }
  return match;
}
