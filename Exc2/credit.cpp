#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
string create(int i){
  return "put" + to_string(i) + ".txt";
}

int main(int argc, char** argv){
  for(int x=1; x<=40; x++){
    string temp1= "in" +create(x);
    string temp2= "out" + create(x);
    int N,K;
    ifstream infile;
    infile.open(temp1);
    infile >>  N >> K ;
    //cin >>  N >> K ;
    int** cost = new int*[N];
    for(int i = 0; i < N; ++i)
      cost[i] = new int[K+1];
    int * arr =  new int[N];
    for(int i=0; i<N; i++){
      infile >> arr[i];
      //cin >> arr[i];
      for (int j=0; j<=K; j++){
        cost[i][j] = 1;
      }
    }
    int mymax = 0;
    for(int k=0; k<=K; k++){
      if (k==0){
        for(int i=0; i<N; i++){
          for (int j=0; j<i; j++){
            if(arr[j]<arr[i]){
              cost[i][0] = max(cost[j][0]+1,cost[i][0]);
            }
          }
          mymax = max(cost[i][0],mymax);
        }
      }
      else{
        for(int i=0; i<N; i++){
          for (int j=0; j<i; j++){
            if (arr[j]>=arr[i]){
              cost[i][k] = max(cost[j][k-1]+1,cost[i][k]);
            }
            else {
              cost[i][k] = max(cost[i][k],cost[j][k]+1);
            }
          }
          //cout << cost[i][k] << ' ';
          mymax = max(cost[i][k],mymax);
        }
      }
    }
    //cout << mymax << endl;
    ifstream infile2;
    int temp3;
    infile2.open(temp2);
    infile2 >> temp3;
    cout << "For the " << x << " file the results are " << mymax << " " << temp3 << " so " << to_string(mymax==temp3) <<endl;
  }
  return 0;
}
//9 1
//3 9 4 5 8 6 1 3 7
//
//
