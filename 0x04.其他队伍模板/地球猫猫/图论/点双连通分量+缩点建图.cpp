#include <bits/stdc++.h>

#define ll long long
using namespace std;
const int N = 10010;
const int M = 10010 * 4;
int head[N];
int ver[M];
int Next[M];
int tot, n, m;

void add(int x, int y) {
    ver[++tot] = y;
    Next[tot] = head[x];
    head[x] = tot;
}

int root;
vector<int> dcc[N];
int stackk[N];
int dfn[N], low[N];
int num = 0;//ʱ���
int top;//stackk
int cnt = 0;//��ͨ����Ŀ
bool cut[N];//����ж�
void tarjan(int x) {
    dfn[x] = low[x] = ++num;
    stackk[++top] = x;
    if (x == root && head[x] == 0) {
        dcc[++cnt].push_back(x);//cnt��ͨ����
        return;
    }
    int flag = 0;
    for (int i = head[x]; i; i = Next[i]) {
        int y = ver[i];
        if (!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
            if (low[y] >= dfn[x]) {
                flag++;
                if (x != root || flag > 1)cut[x] = true;
                cnt++;
                int z;
                do//������Ԫ����xһ�𹹳�һ����ͨ��(����˵���������еĽڵ�+���?)
                {
                    z = stackk[top--];
                    dcc[cnt].push_back(z);
                } while (z != y);
                dcc[cnt].push_back(x);
            }
        } else low[x] = min(low[x], dfn[y]);
    }
}

int tot2 = 1;
int new_id[N];

int hc[N];
int vc[M];
int nc[M];

void add_c(int x, int y) {
    vc[++tot2] = y;
    nc[tot2] = hc[x];
    hc[x] = tot2;
}

int main() {
    while (cin >> n >> m) {
        tot = 1;//������^������ʸ��ߵ��յ�
        for (int i = 1; i <= m; ++i) {
            int x, y;
            cin >> x >> y;
            if (x == y)continue;
            add(x, y);
            add(y, x);
        }
        for (int i = 1; i <= n; ++i) {
            if (!dfn[i])root = i, tarjan(i);
        }
        /*for(int i=1;i<=n;++i)
            if(cut[i])printf("%d ",i);*/
        //��������ͬʱ��V-DCC
        //�������ÿ����ͨ���еĵ�
        for (int i = 1; i <= cnt; ++i) {
            for (int j = 0; j < dcc[i].size(); ++j)cout << i << " " << dcc[i][j] << endl;
        }

        //����
        tot2 = 1;
        int num2 = cnt;
        for (int i = 1; i <= n; ++i) {
            if (cut[i])new_id[i] = ++num2;//���������±��,�൱��ÿ����㵥����Ϊһ����ͨ��
        }
        for (int i = 1; i <= cnt; ++i) {
            for (int j = 0; j < dcc[i].size(); ++j) {
                int x = dcc[i][j];
                if (cut[x])//һ����ͨ��������ֻ��һ����㣬ͨ������ǰ���Щ��ͨ����������;
                {
                    add_c(i, new_id[x]);
                    add_c(new_id[x], i);
                } else new_id[x] = i;//������ֻ����һ����ͨ��
            }
        }

        //���������ͼ�и���֮����ڽӹ�ϵ���ٴ�ע��^���ŵ�ʹ�ã�i��2��ʼ��ÿ�μ�2��<tot2����<=��
        for (int i = 2; i < tot2; i += 2)
            cout << vc[i ^ 1] << "   " << vc[i] << endl;


    }
    return 0;
}

/*
 * tot2Ϊ��������2��ʼ����
 * num2Ϊ����֮��ĵ���
 * ��˫���㣬�����Խ��Խ�࣬ע��N��С
*/
