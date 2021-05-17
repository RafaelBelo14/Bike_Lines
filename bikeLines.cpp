#include <iostream>
#include <vector>
#include <string> 
using namespace std;

// n - numero de POI's
// m - numero de conexões entre POI's
// q - numero de quetsões

vector<int> test;
void printMatrix(vector< vector<int> > matrix);

int main()
{
      int reps, n, m, q;
      int A, B, D;
      cin >> reps;

      for (int i = 0; i < reps; i++) {
            cin >> n;
            cin >> m;
            cin >> q;

            vector< vector <int> > matrix;

            for (int i = 0; i < n; i++) {
                  vector<int> row(n, 0);
                  matrix.push_back(row);
            }

            // VERIFICA CONDIÇÕES INICIAIS
            if (n > 1000 || n <= 0 || m > 100000 || m <= 0 || q > 4 || q <= 0) {
                  return 0;
            }

            for (int i = 0; i < m; i++) {
                  cin >> A;
                  cin >> B;
                  cin >> D;
                  matrix[A - 1][B - 1] = D;
                  matrix[B - 1][A - 1] = D;
            }
            
            printMatrix(matrix);
      }

      for (auto i = test.begin(); i != test.end(); ++i) 
            cout << *i << endl; 
      
      test.clear();
      return 0;
}

void printMatrix(vector< vector<int> > matrix) {

      cout << "-------------------" << endl;
      
      for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                  cout << matrix[i][j] << " ";
            } 
            cout << endl;
      }
}