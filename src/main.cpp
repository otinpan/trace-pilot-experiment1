#include<iostream>
#include<vector>

int map_size=0;

int main(){
  int n;
  std::cin>>n;

  map_size=n;

  std::vector<std::vector<int>> g(n,std::vector<int>(n));

  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      std::cin>>g[i][j];
    }
  }
}
