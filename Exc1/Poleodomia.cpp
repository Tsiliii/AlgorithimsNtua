#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>

using namespace std;

class coord {
public:
    long long int place;
    long long int value;
    long long int count;

    coord(long long int a,long long int b,long long int c){
        place=a;
        value=b;
        count=c;
    }

    long long int get_place(){
        return place;
    }

    long long int get_value(){
        return value;
    }

    long long int get_count(){
      return count;
    }
};

int main(int argc, char** argv){
  long long int N;
  long long int i,j;
  ifstream infile;
  infile.open(argv[1]);
  infile >>  N ;
  //cin >> N;
  long long int *height = new long long int[N];
  long long int *left = new long long int[N];
  long long int *right = new long long int[N];
  stack <coord> l1,r1;
  for (i=0; i<N; i++){
    //cin >> height[i];
    infile >> height[i];
  }
  infile.close();
  left[0] = height[0];
  right[N-1] = height[N-1];
  long long int currmax = height[0];
  long long count = 1;
  long long increase;
  coord some(1,1,1);
  l1.push((coord(0,height[0],1)));
  for(i=1; i<N; i++){
    if(height[i]==height[i-1]){
      some = l1.top();
      l1.pop();
      l1.push(coord(some.get_place()+1,some.get_value(),some.get_count()+1));
      left[i] = left[i-1] + some.get_value();
      //cout<< "Sum = " << left[i] << " ,i = " << i << endl;
    }
    else if (height[i] < height[i-1]){
      left[i] = left[i-1] + height[i];
      l1.push(coord(i,height[i],1));
      //cout<< "Sum = " << left[i] << " ,i = " << i << endl;
    }
    else{
      count = 1;
      increase = height[i];
      while(!l1.empty()){
        some = l1.top();
        ////cout<< "Place = " << some.get_place() << " ,value = " << some.get_value() <<" , count = " << some.get_count() << endl;
        if(some.get_value()>height[i]){
          left[i] = left[i-1] + increase;
          l1.push(coord(i,height[i],count));
          //cout<< "Sum = " << left[i] << " ,i = " << i << endl;
          break;
        }
        else if(some.get_value() == height[i]){
          l1.pop();
          l1.push(coord(i,height[i],count+some.get_count()));
          left[i] = left[i-1] + increase;
          //cout<< "Sum = " << left[i] << " ,i = " << i << endl;
          break;
        }
        else{
          increase = increase + some.get_count()*(height[i] - some.get_value());
          count = count + some.get_count();
          ////cout<< "increase = " << increase << " count = " << count << endl;
          l1.pop();
          if(l1.empty()){
            l1.push(coord(i,height[i],count));
            left[i] = left[i-1] + increase;
            //cout<< "Sum = " << left[i] << " ,i = " << i << endl;
            break;
          }
          else{
            continue;
          }
        }
      }
    }
  }
  r1.push((coord(N-1,height[N-1],1)));
  for(i=N-2; i>=0; i--){
    if(height[i]==height[i+1]){
      some = r1.top();
      r1.pop();
      r1.push(coord(some.get_place()+1,some.get_value(),some.get_count()+1));
      right[i] = right[i+1] + some.get_value();
      //cout<< "Sum = " << right[i] << " ,i = " << i << endl;
    }
    else if (height[i] < height[i-1]){
      right[i] = right[i+1] + height[i];
      r1.push(coord(i,height[i],1));
      //cout<< "Sum = " << right[i] << " ,i = " << i << endl;
    }
    else{
      count = 1;
      increase = height[i];
      while(!r1.empty()){
        some = r1.top();
        ////cout<< "Place = " << some.get_place() << " ,value = " << some.get_value() <<" , count = " << some.get_count() << endl;
        if(some.get_value()>height[i]){
          right[i] = right[i+1] + increase;
          r1.push(coord(i,height[i],count));
          //cout<< "Sum = " << right[i] << " ,i = " << i << endl;
          break;
        }
        else if(some.get_value() == height[i]){
          r1.pop();
          r1.push(coord(i,height[i],count+some.get_count()));
          right[i] = right[i+1] + increase;
          //cout<< "Sum = " << right[i] << " ,i = " << i << endl;
          break;
        }
        else{
          increase = increase + some.get_count()*(height[i] - some.get_value());
          count = count + some.get_count();
          ////cout<< "increase = " << increase << " count = " << count << endl;
          r1.pop();
          if(r1.empty()){
            r1.push(coord(i,height[i],count));
            right[i] = right[i+1] + increase;
            //cout<< "Sum = " << right[i] << " ,i = " << i << endl;
            break;
          }
          else{
            continue;
          }
        }
      }
    }
  }
  long long temp = left[0] + right[0] - height[0];
  for(i = 1; i<N; i++){
    temp = min(temp,left[i] + right[i] - height[i]);
  }
  cout<< temp << endl;
  return 0;
}
