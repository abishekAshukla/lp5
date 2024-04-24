#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
using namespace std;

class Graph
{
    int v;
    vector<vector<int>> adj;

public:
    Graph(int v) : v(v), adj(v) {}

    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }

    void dfs(int st)
    {
        vector<bool> visited(v, false);
        dfsUtil(st, visited);
    }

    void dfsUtil(int st, vector<bool> &visited)
    {
        visited[st] = true;
        cout << st << " ";
#pragma omp parallel for
        for (int i = 0; i < adj[st].size(); i++)
        {
            int n = adj[st][i];
            if (!visited[n])
            {
                dfsUtil(n, visited);
            }
        }
    }

    void bfs(int st)
    {
        vector<bool> visited(v, false);
        queue<int> q;
        visited[st] = true;
        q.push(st);

        while (!q.empty())
        {
            int elem = q.front();
            q.pop();
            cout << elem << " ";
#pragma omp parallel for
            for (int i = 0; i < adj[elem].size(); i++)
            {
                int n = adj[elem][i];
                if (!visited[n])
                {
                    visited[n] = true;
                    q.push(n);
                }
            }
        }
    }
};

int main()
{
    int v = 5;
    int e = 4;
    Graph g(v);
    for (int i = 0; i < e; i++)
    {
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(1, 4);
    }
    g.dfs(0);
    cout << endl;
    g.bfs(0);

    // int v, e;
    // cout << "number of vertex: " << endl;
    // cin >> v;
    // cout << "number of edges: " << endl;
    // cin >> e;
    // Graph g(v);
    // cout << "enter edges" << endl;
    // for (int i = 0; i < e; i++)
    // {
    //     int v, w;
    //     cin >> v >> w;
    //     g.addEdge(v, w);
    // }
    // g.dfs(0);
    // cout << endl;
    // g.bfs(0);

    return 0;
}