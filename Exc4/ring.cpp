#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <algorithm>

using namespace std;

string create(int i){
  return "put" + to_string(i) + ".txt";
}

class bi{
public:
    int currentdepth;
    int currentpath;

    bi(int a,int b){
        currentdepth=a;
        currentpath=b;
    }

    int get_currentdepth(){
        return currentdepth;
    }

    int get_currentpath(){
        return currentpath;
    }

};

bi mydepth(int *left,int *right,int currentnode){
  if(left[currentnode] == 0){
    return bi(1,1);
  }
  else if(right[currentnode] == 0){
    bi some = mydepth(left,right,left[currentnode]);
    return bi(some.get_currentdepth() + 1,max(some.get_currentpath(),some.get_currentdepth() + 1));
  }
  else{
    bi someleft = mydepth(left,right,left[currentnode]);
    bi someright = mydepth(left,right,right[currentnode]);
    int max1 = max(someleft.get_currentpath(),someright.get_currentpath());
    return bi(max(someleft.get_currentdepth(),someright.get_currentdepth()) + 1,max(max1,someleft.get_currentdepth() + someright.get_currentdepth() + 1));
  }
}
int main(){
  int K,N;
  cin >> K ;
  int * M = new int[K];
  int * maxpath = new int[K];
  int sum = 0;
  int index = 0;
  int result = 0;
  int newsum = 0;
  for(int i=0; i<K; i++){
    cin >> N ;
    if ( N == 1 ){
      M[i] = 1;
      maxpath[i] = 1;
      cin >> N;
    }
    else{
      int * left = new int[N+2];
      int * right = new int[N+2];
      int temp;
      for (int j = 0; j<N+2; j++){
        left[j] = 0;
        right[j] = 0;
      }
      for(int j=2; j<N+1; j++){
        cin >> temp;
        if(left[temp] == 0){
          left[temp] = j;
        }
        else{
          right[temp] = j;
        }
      }
      bi some = mydepth(left,right,1);
      M[i] = some.get_currentdepth();
      maxpath[i] = some.get_currentpath();
      delete left;
      delete right;
    }
  }

  for(int i = 1; i < K; i++){
      int total = M[i] + M[index] + i- index - 1;
      result = max(result, total);
      if(M[i] - i < M[index] - index){
          index = i;
      }
  }
  sum = max(result,sum);

  index = 0;
  result = 0;
  for(int i = 1; i < K; i++){
      int total = M[i] + M[index] + K-(i-index) - 1;
      result = max(result, total);
      if(M[i] - index > M[index] - i){
          index = i;
      }
  }
  sum = max(result,sum);

  for(int i=0; i<K; i++){
    newsum = max(newsum,maxpath[i]);
  }
  sum = max(newsum,sum);

  cout << sum -1 << endl;

  return 0;
}
