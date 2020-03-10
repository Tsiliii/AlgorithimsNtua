#include <iostream>
#include <bits/stdc++.h>
#include <stack>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

string create(int i){
  return "put" + to_string(i) + ".txt";
}

int main(/*int argc, char** argv*/){
//  for(int x=1; x<=24; x++){
//    string temp1= "in" +create(x);
//    string temp2= "out" + create(x);
    int answer = 0;
    int N,K;
    //ifstream infile;
    //infile.open(temp1);
    //infile >> N >> K ;
    cin >>  N >> K ;
    int tmp1,tmp2;
    if(K!=N-1){
      int *count = new int[N+1];
      for(int i=0; i<N+1; i++){
        count[i] = 0;
      }
      unordered_set<int>  *arr = new unordered_set<int>[N+1];
      int completemax = 0;
      for(int i=1; i<N; i++){
        //infile >> tmp1 >> tmp2;
        cin >> tmp1 >> tmp2;
        count[tmp1]++;
        count[tmp2]++;
        arr[tmp1].insert(tmp2);
        arr[tmp2].insert(tmp1);
      }
      int currentsum = 0;
      while(1!=0){
        int mymax = count[1];
        int curr=1;
          for(int i=2; i<=N; i++){
            if (count[i] > mymax){
                mymax = count[i];
                curr = i;
            }
          }
        currentsum = currentsum + mymax;
        answer ++;
        if (currentsum >= K){
          break;
        }
        int sizetemp = count[curr];
        for (auto elem : arr[curr]){
  	       arr[elem].erase(curr);
           count[elem]--;
         }
        arr[curr].clear();
        count[curr] = 0;
      }
    }
    else{
      int *count = new int[N+1];
      for(int i=0; i<N+1; i++){
        count[i] = 0;
      }
      list<int> *arr = new list<int>[N+1];
      list<int> leaves;
      for(int i=1; i<N; i++){
        //infile >> tmp1 >> tmp2;
        cin >> tmp1 >> tmp2;
        arr[tmp1].push_front(tmp2);
        arr[tmp2].push_front(tmp1);
        count[tmp1]++;
        count[tmp2]++;
      }
      for(int i=1; i<N; i++){
        if(count[i]==1){
          leaves.push_front(i);
        }
      }
      int currentsum = 0;
      while(K>currentsum){
        int currleaf = leaves.front();
        if(count[currleaf]==0){
          leaves.pop_front();
          continue;
        }
        int currparent = arr[currleaf].front();
        count[currleaf] = 0;
        while(!arr[currparent].empty()){
          int temporary = arr[currparent].front();
          if(count[temporary] != 0){
            count[temporary]--;
            arr[temporary].remove(currparent);
            if(count[temporary]==1){
              leaves.push_front(temporary);
            }
          }
          arr[currparent].pop_front();
        }
        currentsum = currentsum + count[currparent];
        count[currparent] = 0;
        answer++;
      }
    }
    cout << answer << endl;
  //  ifstream infile2;
  //  infile2.open(temp2);
  //  int tmp4;
  //  infile2 >> tmp4;
  //  cout << tmp4 << endl;
//  }
  return 0;
}
