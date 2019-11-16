#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;
int solve(int a,int b,int Ts,int Tf,int c,int d){
  if(c-a*d<0){
    return -1;
  }
  int temp = (c-a*d)/(b-a);
  return temp*Tf + (D-temp)*Ts;
}

int main(){
  int N,K,D,T,time,fast,slow,Ts,Cs,Tf,Cf,currentD,j;
  unordered_map<int, int> Costs;
  cin >>  N >> K >> D >> T ;
  int * dist = new int[K];
  int cost;
  int *cap = new int[N];
  for(int i=0; i<N; i++){
    cin >> cost >> cap[i];
    Costs[cap[i]] = cost;
  }
  sort(cap,cap + N);
  for(int i=0; i<N; i++){
    cout << cap[i] << " " << Costs[cap[i]] << endl;
  }
  for(int i=0; i<K; i++){
    cin >> dist[i];
  }
  cin >> Ts >> Cs >> Tf >> Cf;
  int temp;
  int distance;
  int currentN;
  int j;
  currentN = N/2;
  while(true){
    currentD = 0;
    time = 0;
    for(j=0; j<K-1; j++){
      distance = dist[j] - currentD;
      temp = solve(Cs,Cf,Ts,Tf,distance);
      if(temp==-1)
        break;
      time = time + temp;
      currentD = dist[j];
    }
  }
  return 0;
}
