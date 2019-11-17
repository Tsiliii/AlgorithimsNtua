#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
int solve(int Cs,int Cf,int Ts,int Tf,int c,int d){
  if(c-d*Cs<0){
    //cout << "Exit distance is " << d << endl;
    return -1;
  }
  int temp = (c-d*Cs)/(Cf-Cs);
  while( (d-temp)< 0){
      //cout << temp << endl;
      temp --;
  }
  //cout << Cf << " " << temp << " " << Cs  << " " << d - temp << " " << Cf*temp << " " << Cs*(d-temp) << " " << d << " " << c << endl;
  //cout << "Final time is " << temp*Tf + (d-temp)*Ts << " for the distance " << d <<  endl;
  return temp*Tf + (d-temp)*Ts;
}

int main(int argc, char** argv){
  int N,K,D,T,time,fast,slow,Ts,Cs,Tf,Cf,currentD,currentN,j;
  unordered_map<int, int> Costs;
  ifstream infile;
  infile.open(argv[1]);
  infile >>  N >> K >> D >> T ;
  int * dist = new int[K+1];
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
  dist[K+1] = D;
  sort(dist,dist+K+1);
  int tempe=dist[0];
  for(int l=1; l<K+1; l++){
    tempe = max(tempe,dist[l]-dist[l-1]);
  }
  if(cap[N-1]<tempe){
    //cout << cap[N-1] << " " << tempe << endl;
    cout << -1 << endl;
    return 0;
  }
  //cout << tempe << endl;
  //return 0;
  infile >> Ts >> Cs >> Tf >> Cf;
  int temp;
  int distance;
  int step = N/2;
  currentN = N/2;
  while(step!=0){
    step = step / 2;
    currentD = 0;
    time = 0;
    distance = 0;
        for(j=0; j<K; j++){
          if(cap[currentN]<tempe){
            temp=-1;
            break;
          }
          distance = dist[j+1] - dist[j];
          int what = j;
          while(distance/cap[currentN] < Cf && j<K){
            distance = dist[j++] - dist[what];
          }
          cout << endl << "Distance is " << distance << " ,capacity is " << cap[currentN] << endl;
                  cout << "CurrentN = " << currentN << endl;
          temp = solve(Cs,Cf,Ts,Tf,cap[currentN],distance);
          if(temp==-1 || time > T){
              break;
            }
            time = time + temp;
            cout << "Time = " <<  time  << " ,CurrentN = " << currentN << " ,Capacity = "<< cap[currentN] << " ,Current station is " << dist[j] << endl;
            currentD = dist[j];
        }
        //cout << "STOP" << endl;
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
        cout << "CurrentN = " << currentN << endl;
        currentN = currentN-step;
      //  cout << endl;
    }
/*    return 0;
    cout << "Last call bitches" << endl;
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
    */
    if (currentN >= N){
        cout << -1 <<endl;
        return 0;
    }
    else{
      int temp1 = Costs[cap[currentN]];
        for(int i=currentN; i<N; i++){
          temp1 = min(Costs[cap[i]],temp1);
    }
    cout << temp1 << endl;
    return 0;
  }
  return 0;
}
