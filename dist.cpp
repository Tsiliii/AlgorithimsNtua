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

class bi{
public:
    int weight;
    int node;

    bi(int a,int b){
        weight=a;
        node=b;
    }

    int get_weight(){
        return weight;
    }

    int get_node(){
        return node;
    }

};

int myfind(int x, int *parent, int *rank){
  if (x!=parent[x]){
    parent[x] = myfind(parent[x],parent,rank);
  }
  return parent[x];
}

void myunion (int x, int y, int *parent, int *rank){
    int rx = myfind(x,parent,rank);
    int ry = myfind(y,parent,rank);
    if (rx==ry){
      return;
    }
    if (rank[rx]>rank[ry]){
      parent[ry] = rx;
    }
    else {
      parent[rx] = ry;
      if(rank[rx] == rank[ry])
        rank[ry] = rank[ry] + 1;
    }
    return;
}

void mymakeset(int x, int *parent, int *rank){
  parent[x] = x;
  rank[x] = 0;
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
    int tmp1,tmp2,tmp3;
    list<bi> *arr = new list<bi>[N+1];
    for(int i=0; i<K; i++){
      cin >> tmp1 >> tmp2;
      arr[tmp1].push_front(bi(tmp2,tmp3));
      arr[tmp2].push_front(bi(tmp1,tmp3));
    }
    int *array = new int[N+1];
    int *parent = new int[N+1];
    int *rank = new int[N+1];

  return 0;
  }
