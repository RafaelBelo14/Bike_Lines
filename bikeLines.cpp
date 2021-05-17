// C++ program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <stack>
#include <list>
#define NIL -1
using namespace std;

#define edge pair<int, int>

stack<int> S;
stack<int> C;
stack<stack<int> >Scc;
int numOfCircuits = 0;

class Graph
{
private:
      vector< pair<int, edge> > G;
      vector< pair<int, edge> > T;
      int *parent;
      int V;
public:
      Graph(int V);
      void AddWeightedEdge(int u, int v, int w);
      int find_set(int i);
      void union_set(int u, int v);
      void kruskal();
      void printTotalWeight();
      void SCCUtil(int u, int disc[], int low[], bool stackMember[]);
      void SCC();
};

Graph::Graph(int V)
{
      this->V = V;
      parent = new int[V];

      for (int i = 1; i <= V; i++)
            parent[i] = i;

      G.clear();
      T.clear();
}
void Graph::AddWeightedEdge(int u, int v, int w)
{
      G.push_back(make_pair(w, edge(u, v)));
}
int Graph::find_set(int i)
{
      if (i == parent[i])
            return i;
      else
            return find_set(parent[i]);
}

void Graph::union_set(int u, int v)
{
      parent[u] = parent[v];
}
void Graph::kruskal()
{
      int i, uRep, vRep;
      sort(G.begin(), G.end());

      for (i = 0; i < G.size(); i++)
      {
            uRep = find_set(G[i].second.first);
            vRep = find_set(G[i].second.second);
            if (uRep != vRep)
            {
                  T.push_back(G[i]);
                  union_set(uRep, vRep);
            }
      }
}

void Graph::SCCUtil(int v, int disc[], int low[], bool stackMember[])
{
      static int time = 0;

      disc[v] = low[v] = ++time;
      S.push(v);
      stackMember[v] = true;

      vector< pair<int, edge> >::iterator i;
      for (i = G.begin(); i != G.end(); ++i)
      {
            int w = i->second.second;

            if (disc[w] == -1)
            {
                  SCCUtil(w, disc, low, stackMember);
                  low[v] = min(low[v], low[w]);
            }

            else if (stackMember[w] == true)
                  low[v] = min(low[v], disc[w]);
      }

      int w = 0; 
      if (low[v] == disc[v])
      {
            numOfCircuits++;

             while (S.top() != v) {
                  w = S.top();
                  stackMember[w] = false;
                  S.pop();
                  C.push(w);
            }
            
            w = S.top();
            stackMember[w] = false;
            S.pop();
            Scc.push(C);
      }
}

void Graph::SCC()
{
      int *disc = new int[V];
      int *low = new int[V];
      bool *stackMember = new bool[V];

      while (!S.empty()) {
            S.pop();
      }
      while (!C.empty()) {
            C.pop();
      }
      while (!Scc.empty()) {
            Scc.pop();
      }

      for (int i = 0; i < V; i++)
      {
            disc[i] = NIL;
            low[i] = NIL;
            stackMember[i] = false;
      }

      for (int i = 0; i < V; i++) {
            if (disc[i] == NIL) {
                   SCCUtil(i, disc, low, stackMember);
            }          
      }
            
}

void Graph::printTotalWeight()
{

      int weight = 0;
      for (int i = 0; i < T.size(); i++)
      {
            weight += T[i].first;
      }
      cout << weight << endl;
}

int main()
{
      int reps, n, m, q;
      int A, B, D;
      cin >> reps;

      for (int i = 0; i < reps; i++)
      {
            cin >> n;
            cin >> m;
            cin >> q;

            int aux = 0;
            int bestCircuit = 0;

            // VERIFICA CONDIÇÕES INICIAIS
            if (n > 1000 || n <= 0 || m > 100000 || m <= 0 || q > 4 || q <= 0)
            {
                  return 0;
            }

            Graph g(n);

            for (int i = 0; i < m; i++)
            {
                  cin >> A;
                  cin >> B;
                  cin >> D;
                  g.AddWeightedEdge(A, B, D);
            }

            g.SCC();

            cout << Scc.size() << " ";

            while (!Scc.empty())
            {
                  while (!Scc.top().empty()) {
                        Scc.top().pop();
                        aux++;
                  }
                  Scc.pop();
                  if (aux > bestCircuit) {
                        bestCircuit = aux;
                  }
                  aux = 0;
            }

            cout << bestCircuit << " ";
            
            g.kruskal();
            g.printTotalWeight();
      }
}
