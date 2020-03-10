#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

string create(long long int i){
  return "put" + to_string(i) + ".txt";
}

class bi{
public:
    long long int weight;
    long long int node;

    bi(long long int a,long long int b){
        weight=a;
        node=b;
    }

    long long int get_weight(){
        return weight;
    }

    long long int get_node(){
        return node;
    }

    bool operator = (bi &obj) {
         return (this->get_weight() == obj.get_weight() && this->get_node() == obj.get_node());
    }

};

long long int myfind(long long int x, long long int *parent, long long int *rank){
  if (x!=parent[x]){
    parent[x] = myfind(parent[x],parent,rank);
  }
  return parent[x];
}

void myunion (long long int x, long long int y, long long int *parent, long long int *rank){
    long long int rx = myfind(x,parent,rank);
    long long int ry = myfind(y,parent,rank);
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

void mymakeset(long long int x, long long int *parent, long long int *rank){
  parent[x] = x;
  rank[x] = 0;
}

int main(/*long long int argc, char** argv*/){
  for(long long int x=1; x<=20; x++){
    long long int N,M;
     std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
     string temp1= "in" +create(x);
     string temp2= "out" + create(x);
     ifstream infile;
     infile.open(temp1);
     infile >> N >> M ;
    //cin >>  N >> M ;
    list<long long int> *tree = new list<long long int>[N+1];
    list<char> final;
    long long int *sortededge1 = new long long int[M];
    long long int *sortededge2 = new long long int[M];
    long long int *parent = new long long int[N+1];
    long long int *rank = new long long int[N+1];
    long long int tmp1,tmp2,tmp3;
    long long int *node_count = new long long int[N+1];
    long long int *node_children = new long long int[N+1];
    bool *stays = new bool[M];
    long long int smth = (M + floor(log2(N)) + 1);
    long long int *answer = new long long int[smth];
    queue <long long int> leaves;
    for(long long int i=1; i<N+1; i++){
      mymakeset(i,parent,rank);
      node_count[i] = 0;
      node_children[i] = 1;
    }
    for(long long int i=0; i<M+floor(log2(N))+1; i++){
      answer[i] = 0;
    }
    for(long long int i=0; i<M; i++){
      infile >> tmp1 >> tmp2 >> tmp3;
      //cin >> tmp1 >> tmp2 >> tmp3;
      sortededge1[tmp3] = tmp1;
      sortededge2[tmp3] = tmp2;
      stays[i] = false;
    }
    long long int ConnComp = N;
    long long int i = 0;
    while(ConnComp>1){
      if(myfind(sortededge1[i],parent,rank)!=myfind(sortededge2[i],parent,rank)){
        tree[sortededge1[i]].push_front(i);
        tree[sortededge2[i]].push_front(i);
        node_count[sortededge1[i]]++;
        node_count[sortededge2[i]]++;
        myunion(sortededge1[i],sortededge2[i],parent,rank);
        ConnComp--;
        stays[i] = false;
      }
      i++;
    }
    for(long long int i=1; i<N+1; i++){
      if (node_count[i] == 1){
          leaves.push(i);
      }
    }
    for(long long int i=1; i<N+1; i++){std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        for (list<long long int>::iterator it=tree[i].begin(); it != tree[i].end(); ++it){
          //cout << i << " " << *it << endl;
        }
        //cout << "Node " << i << " has " <<  node_count[i] << endl;
    }
    long long int maximum = 0;
    while(!leaves.empty()){
      if(node_count[leaves.front()] == 1){
        long long int current = leaves.front();
        long long int weight = tree[current].front();
        long long int parent;
        answer[weight] += (node_children[current] ) * (N-node_children[current]);
        maximum =max(maximum,weight);
        if(current== sortededge1[weight])
          parent = sortededge2[weight];
        else
          parent = sortededge1[weight];
        //cout << "Removing from " << parent << " the weight " << weight << endl << endl;
        tree[parent].remove(weight);
        node_count[parent] --;
        if(node_count[parent] == 1){
          leaves.push(parent);
        }
        node_children[parent] += node_children[current];
        //cout << "Calculated " << answer[weight] << endl;
        leaves.pop();
      }
      else if(node_count[leaves.front()] == 0){
          leaves.pop();  //  }
      }
      else{
        leaves.push(leaves.front());
        leaves.pop();
      }
    }
    for(long long int i=1; i<N+1; i++){
        for (list<long long int>::iterator it=tree[i].begin(); it != tree[i].end(); ++it){
          //cout << i << " " << *it << endl;
        }
        //cout << "Node " << i << " has " <<  node_count[i] << endl;
    }
    for(long long int i=0; i<=maximum; i++){
      ////cout << answer[i] << endl;
      long long int temporary = answer[i]/2;
      long long int nextone = i + 1;
      while (temporary>0){
        if(temporary%2==1){
          answer[nextone]++;
        }
        temporary = temporary /2;
        nextone ++;
      }
      nextone--;
      maximum = max(maximum,nextone);
      if (answer[i]%2 == 0){
        final.push_front('0');
      }
      else{
        final.push_front('1');
      }
    }
    // cout << x << ':' << endl;
    cout << endl;
    ifstream infile2;
    infile2.open(temp2);
    char tmp4;
    bool ok = true;
    long long int a = 0;
    for (list<char>::iterator it=final.begin(); it != final.end(); ++it){
      infile2 >> tmp4;
      if (*it != tmp4){
        ok = false;
        cout << "Mistake at " << a << endl;
      }
      a++;
    }
    if(ok){
      cout << "true" << endl;
    }
    else{
      cout << "False" << endl;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
   }
return 0;
}
