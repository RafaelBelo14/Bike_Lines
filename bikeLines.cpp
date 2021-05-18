#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <stack>
#include <list>
using namespace std;
typedef  pair<int, int> arc;

struct Edge
{
      int peso;
      arc pontos;
};

struct subsets
{
      int parent;
      int rank;
};


struct less_than_int
{
    inline bool operator() (const Edge& struct1, const Edge& struct2)
    {
        return (struct1.peso < struct2.peso);
    }
};

vector<Edge> kruskalAux;
vector<int> S;

vector<vector<int> > C;

int numCircuits;
int tamMaiorCircuit;
int custoMaiorCircuit;
int custoTotal;

vector<vector<int> > matriz;
vector<vector<int> > test;

void Tarjan(int V, int u, int dfs[], int low[], bool auxMember[], vector<vector<int> > matriz);
void intoTarjan(int V, vector<vector<int> > matriz);
void setEdges(vector<vector<int> > C, vector<vector<int> > matriz);
void answerQuestions(int q);
int kruskalMST(int V);
void union1(struct subsets sub[], int i, int j);
int find(struct subsets sub[], int i);


int find(struct subsets sub[], int i)
{
      if (sub[i].parent != i)
          sub[i].parent = find(sub, sub[i].parent);
      return sub[i].parent;
}

void union1(struct subsets sub[], int i, int j)
{
      int a = find(sub, i);
      int b = find(sub, j);
      if (sub[a].rank > sub[b].rank)
        sub[b].parent = a;
      else
        sub[a].parent = b;
      if (sub[a].rank == sub[b].rank)
        sub[b].rank++;
}

int kruskalMST(int V)
{
      int mincost = 0;

      struct subsets sub[V];

      for (int i = 0; i < V; i++)
      {
            sub[i].parent = i;
            sub[i].rank = 0;
      }
      sort(kruskalAux.begin(), kruskalAux.end(), less_than_int());
      for (int i = 0; i < (int)kruskalAux.size(); i++)
      {
            int u = kruskalAux[i].pontos.first;
            int v = kruskalAux[i].pontos.second;

            int set_u = find(sub,u);
            int set_v = find(sub, v);

            if (set_u != set_v)
            {
                  mincost += kruskalAux[i].peso;
                  union1(sub, set_u, set_v);
            }
      }
      return mincost;
}

void Tarjan(int V, int v, int dfs[], int low[], bool auxMember[], vector<vector<int> > matriz)
{
      static int t = 0;
      int aux = 0;

      dfs[v] = low[v] = ++t;
      S.push_back(v);
      auxMember[v] = true;

      for (int w = 0; w < V; w++)
      {
            if (matriz[v][w])
            {
                  if (dfs[w] == -1)
                  {
                        Tarjan(V, w, dfs, low, auxMember, matriz);
                        low[v] = min(low[v], low[w]);
                  }

                  else if (auxMember[w])
                  {
                        low[v] = min(low[v], dfs[w]);
                  }
            }
      }

      int popItem = 0;
      if (low[v] == dfs[v])
      {
            vector<int> row;
            while (S.back() != v)
            {
                  popItem = S.back();
                  auxMember[popItem] = false;
                  S.pop_back();
                  aux++;
                  row.push_back(popItem);
            }

            popItem = S.back();
            row.push_back(popItem);
            auxMember[popItem] = false;
            S.pop_back();

            if (row.size() > 1)
            {
                  aux++;
                  numCircuits++;
            }

            if (aux > tamMaiorCircuit)
            {
                  tamMaiorCircuit = aux;
            }

            if (row.size() > 1) {
                  C.push_back(row);
            }
      }
}

void intoTarjan(int V, vector<vector<int> > matriz)
{
      int dfs[V];
      int low[V];
      bool auxMember[V];
      numCircuits = 0;
      tamMaiorCircuit = 0;
      custoMaiorCircuit = 0;
      custoTotal = 0;

      S.clear();

      for (int i = 0; i < V; i++)
      {
            dfs[i] = low[i] = -1;
            auxMember[i] = false;
      }

      for (int i = 0; i < V; i++)
      {

            if (dfs[i] == -1)
            {
                  Tarjan(V, i, dfs, low, auxMember, matriz);
            }
      }
}

void answerQuestions(int q)
{

      vector<int> answer;

      if (q == 1)
      {
            answer.push_back(numCircuits);
      }
      else if (q == 2)
      {
            answer.push_back(numCircuits);
            answer.push_back(tamMaiorCircuit);
      }
      else if (q == 3)
      {

            answer.push_back(numCircuits);
            answer.push_back(tamMaiorCircuit);
            answer.push_back(custoMaiorCircuit);
      }
      else if (q == 4)
      {
            answer.push_back(numCircuits);
            answer.push_back(tamMaiorCircuit);
            answer.push_back(custoMaiorCircuit);
            answer.push_back(custoTotal);
      }

      test.push_back(answer);
}

void setEdges(int indice, vector<vector<int> > C, vector<vector<int> > matriz)
{
      Edge e;

      for (int i = 0; i < (int)C[indice].size(); i++)
      {

            for (int j = 0; j < (int)C[indice].size(); j++)
            {
                  if (i != j && matriz[C[indice][i]][C[indice][j]] != 0)
                  {
                        e.pontos.first = i;
                        e.pontos.second = j;
                        e.peso = matriz[C[indice][i]][C[indice][j]];
                        kruskalAux.push_back(e);
                  }
            }
      }
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
            numCircuits = 0;
            tamMaiorCircuit = 0;
            custoMaiorCircuit = 0;
            custoTotal = 0;

            // VERIFICA CONDIÇÕES INICIAIS
            if (n > 1000 || n <= 0 || m > 100000 || m <= 0 || q > 4 || q <= 0)
            {
                  return 0;
            }

            for (int i = 0; i < n; i++)
            {
                  vector<int> row(n, 0);
                  matriz.push_back(row);
            }

            for (int i = 0; i < m; i++)
            {
                  cin >> A;
                  cin >> B;
                  cin >> D;
                  matriz[A - 1][B - 1] = D;
            }
            intoTarjan(n, matriz);

            int auxCusto;
            for (int i = 0; i < (int)C.size(); i++)
            {
                  setEdges(i, C, matriz);
                  auxCusto = kruskalMST((int)C[i].size());
                  if (auxCusto > custoMaiorCircuit) {
                        custoMaiorCircuit = auxCusto;
                  }
                  custoTotal += auxCusto;
                  kruskalAux.clear();
            }

            answerQuestions(q);
            matriz.clear();
            C.clear();
      }

      for (auto i = test.begin(); i != test.end(); ++i)
      {
            for (auto j = i->begin(); j != i->end(); ++j)
            {
                  cout << *j << " ";
            }
            cout << endl;
      }
}
