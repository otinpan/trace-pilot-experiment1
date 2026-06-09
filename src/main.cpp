#include<iostream>
#include<vector>

#include"common.h"
#include"strategy/greedy.h"
#include"strategy/turn_back.h"
#include"state.h"
#include"simulator.h"
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

  State state(g);
  Logger logger("log.txt");

  TurnBack strategy;
  std::vector<Pos> result=strategy.solve(state,logger);

  for(const auto& res:result){
    std::cout<<res.i<<" "<<res.j<<'\n';
  }

  return 0;
}
