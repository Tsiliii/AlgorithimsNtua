#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
int solve(int a,int b,int Ts,int Tf,int c,int d){
  if(c-a*d<0){
    return -1;
  }
  int temp = (c-a*d)/(b-a);
  if(d - b*temp < 0){
      temp --;
  }
  //cout << temp*Tf + (d-temp)*Ts << endl;
  return temp*Tf + (d-temp)*Ts;
}

int main(int argc, char** argv){
  int N,K,D,T,time,fast,slow,Ts,Cs,Tf,Cf,currentD,currentN,j;
  unordered_map<int, int> Costs;
  ifstream infile;
  infile.open(argv[1]);
  infile >>  N >> K >> D >> T ;
  int * dist = new int[K];
  int cost;
  int *cap = new int[N];
  for(int i=0; i<N; i++){
    infile >> cost >> cap[i];
    if (Costs.find(cap[i]) == Costs.end()){
        Costs[cap[i]] = cost;
    }
    else if (Costs[cap[i]] > cost){
        Costs[cap[i]] = cost;
    }
  }
  sort(cap,cap + N);
  for(int i=0; i<K; i++){
    infile >> dist[i];
  }
  infile >> Ts >> Cs >> Tf >> Cf;
  int temp;
  int distance;
  int step = N;
  currentN = N/2;
  while(step!=0){
    step = step / 2;
    currentD = 0;
    time = 0;
    distance = 0;
        for(j=0; j<K+1; j++){
        if(j!=K){
            distance = dist[j] + distance;
            temp = solve(Cs,Cf,Ts,Tf,cap[currentN],dist[j]);
        }
        else{
            distance = D - distance;
            temp = solve(Cs,Cf,Ts,Tf,cap[currentN],distance);
        }
        if(temp==-1){
            break;
        }
        time = time + temp;
        //cout << "Time = " <<  time  << " currentN = " << currentN << endl;
        currentD = dist[j];
        }
        if(temp == -1 || time > T){
            if(step!=0){
                currentN = currentN+step;
            }
            else{
                currentN = currentN + 1;
                break;
            }
            continue;
        }
        currentN = currentN-step;
    }
    //cout << "Last call bitches" << endl;
    currentD = 0;
    time = 0;
    distance = 0;
    for(j=0; j<K+1; j++){
        if(j!=K){
            distance = dist[j] + distance;
            temp = solve(Cs,Cf,Ts,Tf,cap[currentN],dist[j]);
        }
        else{
            distance = D - distance;
            temp = solve(Cs,Cf,Ts,Tf,cap[currentN],distance);
        }
    if(temp==-1){
        break;
        currentN = currentN + 1;
        time = time + temp;
    }
    //cout << "Time = " <<  time  << " currentN = " << currentN << endl;
    currentD = dist[j];
    }
    if (currentN >= N){
        cout << -1 <<endl;
        return 0;
    }
    else{
        cout << Costs[cap[currentN]] << endl;
    }
  return 0;
}
