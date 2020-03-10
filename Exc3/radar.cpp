#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <tuple>

using namespace std;

void print_grid(long long int grid[180][180],int N,int M){
  for(int i=0; i<N; i++){
    for(int j=M-1; j>=0; j--){
      cout << grid[i][j] << " " ;
    }
    cout << endl;
  }
  cout << endl;
}

void mycopy(long long int oldgrid[180][180],long long int newgrid[180][180],int N,int M){
  for(int i=0; i<N; i++){
    for(int j=M-1; j>=0; j--){
      oldgrid[i][j]=newgrid[i][j];
      newgrid[i][j]=0;
    }
  }
  oldgrid[N-1][M-1] = 1;
  newgrid[N-1][M-1] = 1;
}

long long int max(long long int a,long long int b){
  if(a>b){
    return a;
  }
  return b;
}

string create(long long int i){
  return "put" + to_string(i) + ".txt";
}


int main(){
    long long int N,M,K,X;

    cin >>  N >> M >> K >> X;
    long long int oldgrid [180][180] = {0};
    long long int newgrid [180][180] = {0};
    tuple<long long int,long long int> bridges1 [180][180];
    tuple<long long int,long long int> bridges2 [180][180];
    for(int i=0; i<N; i++){
      for( int j=0; j<M; j++){
        bridges1[i][j] = make_tuple(-1,-1);
        bridges2[i][j] = make_tuple(-1,-1);
        oldgrid[i][j] = 0;
        newgrid[i][j] = 0;
      }
    }
    int minN=N-1, minM=M-1, minx=0;
    long long int tmp1,tmp2,x1,x2,y1,y2;
    for(int i=0; i<K; i++){

      cin >> tmp1 >> tmp2;
      x1 = tmp1/M;
      y1 = tmp1%M;
      x2 = tmp2/M;
      y2 = tmp2%M;
      bridges1[x2][y2] = make_tuple(x1,y1);
      bridges2[x1][y1] = make_tuple(x2,y2);
    }
    if (get<0>(bridges2[N-1][M-1]) != -1) {
        minN = get<0>(bridges2[N-1][M-1]);
        minM = get<1>(bridges2[N-1][M-1]);
        minx = 1;
    }
    for (int i = minN; i >= 0; i--){
        if (get<0>(bridges2[i][M-1]) == -1) {
            newgrid[i][M-1] = 1;
        }
        else {
            newgrid[i][M-1] = 1;;
            break;
        }
      }
    for (int j = minM; j >= 0; j--){
        if (get<0>(bridges2[N-1][j]) == -1) {
            newgrid[N-1][j] = 1;
        }
        else {
          newgrid[N-1][j] = 1;
          break;
        }
      }

    long long int answer = 0;
      for (int x = 0; x <= X; x++) {
          for (int i = minN-1; i >= 0; i--)
              for (int j = minM-1; j >= 0; j--) {
                  long long int sum = 0;
                  if (get<0>(bridges2[i+1][j]) == -1)
                      sum = newgrid[i+1][j]%1000000103;
                  if (get<0>(bridges2[i][j+1]) == -1)
                      sum = sum + newgrid[i][j+1]%1000000103;
                  if (get<0>(bridges1[i][j]) != -1)
                      sum += oldgrid[get<0>(bridges1[i][j])][get<1>(bridges1[i][j])]%1000000103;
                    newgrid[i][j]=sum%1000000103;
                  }
          answer += newgrid[0][0];
          answer = answer%1000000103;
          for (int i = minN; i >= 0; i--)
                  for (int j = minM; j >= 0; j--) {
                          if (get<0>(bridges2[i][j]) != -1)
                              oldgrid[i][j]=newgrid[i][j];
                          newgrid[i][j] = 0;
                  }
      }
    cout << answer << endl;
return 0;
}
