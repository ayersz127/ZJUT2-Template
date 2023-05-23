///
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int inf=0x3f3f3f3f,N=2e5+9;

int n,m;
vector<int>e[N],g[N*2];

int cnt,dfn[N],low[N],dfc;
int stk[N],tp;

void tarjan(int u) {
    low[u] = dfn[u] = ++dfc;                // low ��ʼ��Ϊ��ǰ�ڵ� dfn
    stk[++tp] = u;                          // ����ջ��
    for (int v : e[u]) {                    // ���� u �����ڽڵ�
        if (!dfn[v]) {                        // ���δ���ʹ�
            tarjan(v);                          // �ݹ�
            low[u] = std::min(low[u], low[v]);  // δ���ʵĺ� low ȡ min
            if (low[v] == dfn[u]) {  // ��־���ҵ�һ���� u Ϊ���ĵ�˫��ͨ����
                ++cnt;                 // ���ӷ������
                // ����˫�г��� u �ĵ���ջ������Բ����������
                for (int x = 0; x != v; --tp) {
                    x = stk[tp];
                    g[cnt].push_back(x);
                    g[x].push_back(cnt);
                }
                // ע�� u ����ҲҪ���ߣ�������ջ��
                g[cnt].push_back(u);
                g[u].push_back(cnt);
            }
        }
        else low[u] = std::min(low[u], dfn[v]); // �ѷ��ʵĺ� dfn ȡ min
    }
}

int main() {
    #ifdef ONLINE_JUDGE
        //std::ios::sync_with_stdio(false);
    #else
        //freopen("in.txt","r",stdin);
        //freopen("out.txt","w",stdout);
    #endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);  // ��˫���
        e[v].push_back(u);
    }
    cnt = n;  // ��˫ / �����Ŵ� N ��ʼ
    for (int u = 1; u <= n; ++u)// �������ͨͼ
        if (!dfn[u]){
            tarjan(u),--tp;
        }
    return 0;
}
