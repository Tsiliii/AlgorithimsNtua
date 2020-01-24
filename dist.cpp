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

int main(int argc, char** argv){
  for(int x=0; x<=0; x++){
    string temp1= "in" +create(x);
    string temp2= "out" + create(x);
    int N,M;
    ifstream infile;
    infile.open(temp1);
    infile >> N >> M ;
    //cin >>  N >> M ;
    list<int> *tree = new list<int>[N+1];
    int *sortededge1 = new int[M];
    int *sortededge2 = new int[M];
    int *parent = new int[N+1];
    int *rank = new int[N+1];
    int tmp1,tmp2,tmp3;
    int *node_count = new int[N+1];
    bool *stays = new bool[M];
    queue <int> leaves;
    for(int i=1; i<N+1; i++){
      mymakeset(i,parent,rank);
      node_count[i] = 0;
    }
    for(int i=0; i<M; i++){
      //cin >> tmp1 >> tmp2 >> tmp3;
      infile >> tmp1 >> tmp2 >> tmp3;
      sortededge1[tmp3] = tmp1;
      sortededge2[tmp3] = tmp2;
      stays[i] = false;
    }
    int ConnComp = N;
    int i = 0;
    while(ConnComp>1){
      if(myfind(sortededge1[i],parent,rank)!=myfind(sortededge2[i],parent,rank)){
        tree[sortededge1[i]].push_front(sortededge2[i]);
        node_count[sortededge1[i]]++;
        node_count[sortededge2[i]]++;
        tree[sortededge2[i]].push_front(sortededge1[i]);
        myunion(sortededge1[i],sortededge2[i],parent,rank);
        ConnComp--;
        stays[i] = false;
      }
      i++;
    }
    for(int i=1; i<N+1; i++){
      if (node_count[i] == 1){
          leaves.push(i);
      }
    }
    for(int i=1; i<N+1; i++){
        for (list<int>::iterator it=tree[i].begin(); it != tree[i].end(); ++it){
          cout << i << " " << *it << endl;
        }
        cout << "Node " << i << " has " <<  node_count[i] << endl;
    }
    // mymakeset(1,parent,rank);
    // mymakeset(2,parent,rank);
    // mymakeset(3,parent,rank);
    // myunion(1,2,parent,rank);
    // myunion(3,2,parent,rank);
    // cout << myfind(1,parent,rank) << " " << rank[1] << endl << myfind(2,parent,rank) << " " << rank[2] << endl << myfind(3,parent,rank) << " " << rank[3] << endl;
  }
  return 0;
  }
