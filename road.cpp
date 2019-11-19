#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;
long long unsigned int solve(long long unsigned int Cs,long long unsigned int Cf,long long unsigned int Ts,long long unsigned int Tf,long long unsigned int c,long long unsigned int d){
  if(c-d*Cs<0){
    cout << "Exit distance is " << d << endl;
    return -1;
  }
  long long unsigned int temp = (c-d*Cs)/(Cf-Cs);
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
  long long unsigned int N,K,D,T,time,fast,slow,Ts,Cs,Tf,Cf,currentN;
  int j;
  unordered_map<long long unsigned int, long long unsigned int> Costs;
  ifstream infile;
  infile.open(argv[1]);
  infile >>  N >> K >> D >> T ;
  //cin >>  N >> K >> D >> T ;
  long long unsigned int * dist = new long long unsigned int[K+1];
  long long unsigned int cost;
  long long unsigned int *cap = new long long unsigned int[N];
  for(int i=0; i<N; i++){
    infile >> cost >> cap[i];
    //cin >> cost >> cap[i];
    if(cost == 229258151){
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
  for(long long unsigned int i=0; i<K; i++){
    infile >> dist[i];
  //cin >> dist[i];
  }
  dist[K] = D;
  sort(dist,dist+K+1);
  long long unsigned int maxDistance=dist[0];
  for(long long unsigned int l=1; l<K+1; l++){
    maxDistance = max(maxDistance,dist[l]-dist[l-1]);
  }
  if(cap[N-1]<maxDistance){
    cout << -1 << endl;
    return 0;
  }
  infile >> Ts >> Cs >> Tf >> Cf;
  //cin >> Ts >> Cs >> Tf >> Cf;
  infile.close();
  bool Acceptable = false;
  bool Faulty = false;
  long long unsigned int temp;
  long long unsigned int distance;
  long long unsigned int step = N/2;
  currentN = N/2;
  while(step!=0){
    step = step / 2;
    time = 0;
    distance = 0;
        for(j=0; j<K; j++){
          if(cap[currentN]<maxDistance){
            cout << "hERE" << endl;
            temp=-1;
            break;
          }
          distance = dist[j+1] - dist[j];
          long long unsigned int what = j;
          if(distance < cap[currentN]/Cf){
              while(distance < cap[currentN]/Cf && j<K){
                distance = dist[++j] - dist[what];
              }
              if (j<K){
                  j--;
                  distance = dist[j] - dist[what];
              }
          }
          //cout << endl << "Distance is " << distance << " ,capacity is " << cap[currentN] << endl;
          //cout << "CurrentN = " << currentN << endl;
          temp = solve(Cs,Cf,Ts,Tf,cap[currentN],distance);
          if(temp==-1 || time > T){
              //cout << "Time is " << time << " when it should have been " << T <<endl;
              break;
            }
            time = time + temp;
            cout << "Time = " <<  time  << " ,CurrentN = " << currentN << " ,Capacity = "<< cap[currentN] << " ,Current station is " << dist[j] << endl;
        }
        //cout << "STOP" << endl;
        if(temp == -1 || time > T){
          Faulty = true;
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
        delete dist;
        delete cap;
        return 0;
    }
    if(!Faulty && Acceptable){
        for(int i = currentN; i>=0; i--){
            time = 0;
            distance = 0;
                for(j=0; j<K; j++){
                  if(cap[i]<maxDistance){
                    temp=-1;
                    break;
                  }
                  distance = dist[j+1] - dist[j];
                  long long unsigned int what = j;
                  if(distance < cap[i]/Cf){
                      //cout << "FUCK" << endl;
                      while(distance < cap[i]/Cf && j<K){
                        distance = dist[++j] - dist[what];
                      }
                      if (j<K){
                          distance = dist[--j] - dist[what];
                      }
                  }
                  //cout << endl << "Distance is " << distance << " ,capacity is " << i << endl;
                  //        cout << "CurrentN = " << i << endl;
                  temp = solve(Cs,Cf,Ts,Tf,cap[i],distance);
                  if(temp==-1 || time > T){
                      break;
                    }
                    time = time + temp;
                    //cout << "Time = " <<  time  << " ,CurrentN = " << i << " ,Capacity = "<< cap[currentN] << " ,Current station is " << dist[j] << endl;
                }
                if(temp == -1 || time > T){
                    currentN = i+1;
                    break;
                }
                currentN = i;
        }
    }
    if(!Acceptable && Faulty){
        for(int i = currentN; i<N; i++){
            time = 0;
            distance = 0;
                for(j=0; j<K; j++){
                  if(cap[i]<maxDistance){
                    temp=-1;
                    break;
                  }
                  distance = dist[j+1] - dist[j];
                  long long unsigned int what = j;
                  if(distance < cap[i]/Cf){
                      while(distance < cap[i]/Cf && j<K){
                        distance = dist[++j] - dist[what];
                      }
                      if (j<K){
                        j--;
                          distance = dist[j] - dist[what];
                      }
                  }
                  //cout << endl << "Distance is " << distance << " ,capacity is " << cap[i] << endl;
                  //cout << "CurrentN = " << i << endl;
                  temp = solve(Cs,Cf,Ts,Tf,cap[i],distance);
                  if(temp==-1 || time > T){
                      break;
                    }
                    time = time + temp;
                    cout << "Time = " <<  time  << " ,CurrentN = " << i << " ,Capacity = "<< cap[currentN] << " ,Current station is " << dist[j] << endl;
                }
                if(temp != -1 && time <= T){
                    currentN = i;
                    break;
                }
                if(i==N-1){
                    cout << -1 << endl;
                    delete dist;
                    delete cap;
                    return 0;
                }
        }
    }
          cout << "FAT" << endl;
    if (currentN >= N){
        cout << -1 <<endl;
        delete dist;
        delete cap;
        return 0;
    }
    else{
      long long unsigned int temp1 = Costs[cap[currentN]];
        for(int i=currentN; i<N; i++){
          temp1 = min(Costs[cap[i]],temp1);
    }
    cout << temp1 << endl;
    delete dist;
    delete cap;
    return 0;
  }
  return 0;
}
