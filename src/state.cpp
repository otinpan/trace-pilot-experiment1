#include"state.h"

State::State(std::vector<std::vector<int>> kingdom)
  :kingdom_(kingdom)
  ,init_kingdom_(kingdom)
  ,pos_(Pos(0,0))
  ,turn_(0)
  ,score_(0)
  ,path_({})
{

}

State::~State()=default;

bool State::apply(Direction dir){
  return true;
}

void State::undo(){

}

