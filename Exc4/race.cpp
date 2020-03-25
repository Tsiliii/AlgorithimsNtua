#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

class bi{
public:
    long long int weight;
    long long int node;

    bi(long long int a,long long int b){
        node=a;
        weight=b;
    }

    long long int get_weight() const{
        return weight;
    }

    long long int get_node() const{
        return node;
    }

    bool operator < (const bi &obj) const {
      return this->get_weight() > obj.get_weight();
    }

};

int main(){
  long long int N,M,K,L,B;
    cin >> N >> M >> K >> L >> B;
    list<bi> *graphlist = new list<bi>[N+1];
    list<long long int> trip;
    list<long long int> gas;
    long long int tmp1,tmp2,tmp3;
    int nodex,nodey,weight;
    long long int station;
    long long int sum = 0;
    long long int candidate = 0;
    long long int Distances[60001];
    long long int triplength = 0;
    priority_queue <bi> pq,lq;

    for(int i=0; i<M; i++){
      cin >> nodex >> nodey >> weight;
      graphlist[nodex].push_front(bi(nodey,weight));
      graphlist[nodey].push_front(bi(nodex,weight));
    }

    for(int i=0; i<K; i++){
      cin >> station;
      trip.push_front(station);
    }

    for(int i=0; i<B; i++){
      cin >> station;
      gas.push_front(station);
    }

    for(int i=0; i<60001; i++){
      Distances[i] = -1;
    }

    for(list<long long int>::iterator it=gas.begin(); it != gas.end(); ++it){
      Distances[*it] = 0;
      for(list<bi>::iterator it2=graphlist[*it].begin(); it2 != graphlist[*it].end(); ++it2){
        long long int targetStation = it2->get_node();
        long long int weight = it2->get_weight();
        if(Distances[targetStation] == -1){
          Distances[targetStation] = weight;
          pq.push(bi(targetStation,Distances[targetStation]));
        }
        else if(Distances[targetStation] > Distances[*it] + weight){
          Distances[targetStation] = Distances[*it] + weight;
          pq.push(bi(targetStation,Distances[targetStation]));
        }
      }
    }

    while(!pq.empty()){
      bi current = pq.top();
      long long int currentStation = current.get_node();
      long long int currentWeight = current.get_weight();
      if(Distances[currentStation] >= currentWeight){
        for(list<bi>::iterator it=graphlist[currentStation].begin(); it != graphlist[currentStation].end(); ++it){
          long long int targetStation = it->get_node();
          long long int weight = it->get_weight();
          if(Distances[targetStation] == -1){
            Distances[targetStation] = Distances[currentStation] + weight;
            pq.push(bi(targetStation,Distances[targetStation]));
          }
          else if(Distances[targetStation] > Distances[currentStation] + weight){
            Distances[targetStation] = Distances[currentStation] + weight;
            pq.push(bi(targetStation,Distances[targetStation]));
          }
        }
      }
      pq.pop();
    }

    for(list<long long int>::iterator it=trip.begin(); it != trip.end(); ++it){
      for(list<bi>::iterator it2=graphlist[*it].begin(); it2 != graphlist[*it].end(); ++it2){
        long long int targetStation = it2->get_node();
        long long int weight = it2->get_weight();
        if (*next(it) == targetStation && next(it)!=trip.end()){
          sum += weight;
          if(triplength !=0 && triplength!=  K-1)
            lq.push(bi(*it,Distances[*it]));
        }
      }
      triplength++;
    }
    for(int i=0; i<L; i++){
      bi current = lq.top();
      sum += current.get_weight();
      lq.pop();
    }
    cout << sum << endl;
return 0;
}
