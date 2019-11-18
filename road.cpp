#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
long long int solve(long long int Cs,long long int Cf,long long int Ts,long long int Tf,long long int c,long long int d){
  if(c-d*Cs<0){
    //cout << "Exit distance is " << d << endl;
    return -1;
  }
  long long int temp = (c-d*Cs)/(Cf-Cs);
  while( (d-temp)< 0){
      //cout << temp << endl;
      temp --;
  }
  //cout << Cf << " " << temp << " " << Cs  << " " << d - temp << " " << Cf*temp << " " << Cs*(d-temp) << " " << d << " " << c << endl;
  //cout << "Final time is " << temp*Tf + (d-temp)*Ts << " for the distance " << d <<  endl;
  if(temp*Tf+(d-temp)*Ts < 0){
      cout << "FUCKING HELL" << endl;
  }
  return temp*Tf + (d-temp)*Ts;
}

int main(int argc, char** argv){
  long long int N,K,D,T,time,fast,slow,Ts,Cs,Tf,Cf,currentN,j;
  unordered_map<long long int, long long int> Costs;
  ifstream infile;
  infile.open(argv[1]);
  infile >>  N >> K >> D >> T ;
  long long int * dist = new long long int[K+1];
  long long int cost;
  long long int *cap = new long long int[N];
  for(long long int i=0; i<N; i++){
    infile >> cost >> cap[i];
    if(cost == 1){
        cout << endl << endl << cap[i] << endl << endl;
    }
    if (Costs.find(cap[i]) == Costs.end()){
        Costs[cap[i]] = cost;
    }
    else if (Costs[cap[i]] > cost){
        Costs[cap[i]] = cost;
    }
  }
  sort(cap,cap + N);
  for(long long int i=0; i<K; i++){
    infile >> dist[i];
  }
  dist[K+1] = D;
  sort(dist,dist+K+1);
  long long int maxDistance=dist[0];
  for(long long int l=1; l<K+1; l++){
    maxDistance = max(maxDistance,dist[l]-dist[l-1]);
  }
  if(cap[N-1]<maxDistance){
    cout << -1 << endl;
    return 0;
  }
  infile >> Ts >> Cs >> Tf >> Cf;
  infile.close();
  bool Acceptable = false;
  bool Faulty = false;
  long long int temp;
  long long int distance;
  long long int step = N/2;
  currentN = N/2;
  while(step!=0){
    step = step / 2;
    time = 0;
    distance = 0;
        for(j=0; j<K; j++){
          if(cap[currentN]<maxDistance){
            temp=-1;
            break;
          }
          distance = dist[j+1] - dist[j];
          long long int what = j;
          if(distance < cap[currentN]/Cf){
              while(distance < cap[currentN]/Cf && j<K){
                distance = dist[j++] - dist[what];
              }
              if (j<K){
                  distance = dist[--j] - dist[what];
              }
          }
          cout << endl << "Distance is " << distance << " ,capacity is " << cap[currentN] << endl;
          cout << "CurrentN = " << currentN << endl;
          temp = solve(Cs,Cf,Ts,Tf,cap[currentN],distance);
          if(temp==-1 || time > T){
              Faulty = true;
              //cout << "Time is " << time << " when it should have been " << T <<endl;
              break;
            }
            time = time + temp;
        //    cout << "Time = " <<  time  << " ,CurrentN = " << currentN << " ,Capacity = "<< cap[currentN] << " ,Current station is " << dist[j] << endl;
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
        //cout << "CurrentN = " << currentN << endl;
        currentN = currentN-step;
        Acceptable = true;
      //  cout << endl;
    }
    if (currentN >= N){
        cout << -1 <<endl;
        return 0;
    }
    if(!Faulty && Acceptable){
        //cout << "HERE" << endl;
        for(long long int i = currentN; i>=0; i--){
            time = 0;
            distance = 0;
                for(j=0; j<K; j++){
                  if(cap[i]<maxDistance){
                    temp=-1;
                    break;
                  }
                  distance = dist[j+1] - dist[j];
                  long long int what = j;
                  if(distance < cap[i]/Cf){
                      //cout << "FUCK" << endl;
                      while(distance < cap[i]/Cf && j<K){
                        distance = dist[j++] - dist[what];
                      }
                      if (j<K){
                          distance = dist[--j] - dist[what];
                      }
                  }
                  //cout << endl << "Distance is " << distance << " ,capacity is " << i << endl;
                //          cout << "CurrentN = " << i << endl;
                  temp = solve(Cs,Cf,Ts,Tf,cap[i],distance);
                  if(temp==-1 || time > T){
                      break;
                    }
                    time = time + temp;
                    //cout << "Time = " <<  time  << " ,CurrentN = " << i << " ,Capacity = "<< cap[currentN] << " ,Current station is " << dist[j] << endl;
                }
                if(temp == -1 || time > T){
                    currentN = i;
                    break;
                }
                currentN = i;
        }
    }
    if(!Acceptable && Faulty){
        for(long long int i = currentN; i<N; i++){
            time = 0;
            distance = 0;
                for(j=0; j<K; j++){
                  if(cap[i]<maxDistance){
                    temp=-1;
                    break;
                  }
                  distance = dist[j+1] - dist[j];
                  long long int what = j;
                  if(distance < cap[i]/Cf){
                      while(distance < cap[i]/Cf && j<K){
                        distance = dist[j++] - dist[what];
                      }
                      if (j<K){
                          distance = dist[--j] - dist[what];
                      }
                  }
                  //cout << endl << "Distance is " << distance << " ,capacity is " << cap[i] << endl;
                  //cout << "CurrentN = " << i << endl;
                  temp = solve(Cs,Cf,Ts,Tf,cap[i],distance);
                  if(temp==-1 || time > T){
                      break;
                    }
                    time = time + temp;
                    //cout << "Time = " <<  time  << " ,CurrentN = " << i << " ,Capacity = "<< cap[currentN] << " ,Current station is " << dist[j] << endl;
                }
                if(temp != -1 && time <= T){
                    currentN = i;
                    break;
                }
                if(i==N-1){
                    cout << -1 << endl;
                    return 0;
                }
        }
    }
    if (currentN >= N){
        cout << -1 <<endl;
        return 0;
    }
    else{
      long long int temp1 = Costs[cap[currentN]];
        for(long long int i=currentN; i<N; i++){
          temp1 = min(Costs[cap[i]],temp1);
    }
    cout << temp1 << endl;
    return 0;
  }
  return 0;
}
