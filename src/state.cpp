#include"state.h"

State::State(std::vector<std::vector<int>> kingdom)
  :kingdom_(kingdom)
  ,init_kingdom_(kingdom)
  ,pos_(Pos(0,0))
  ,turn_(0)
  ,score_(0)
// @trace-pilot df333fb31bb50d819e5b717da0880a9ce331d21f
  ,history_({})
{

  kingdom_[pos_.i][pos_.j]=-1;
}

State::~State()=default;

// dirの方向に1手移動する
bool State::apply(Direction dir){
  Pos next_pos=pos_+DIRS[static_cast<int>(dir)];
  if(!next_pos.is_on_map()){
    return false;
  }
  if(kingdom_[next_pos.i][next_pos.j]==-1){
    return false;
  }

// @trace-pilot df333fb31bb50d819e5b717da0880a9ce331d21f
  int next_turn=turn_+1;
  long long score_delta=1LL*next_turn*init_kingdom_[next_pos.i][next_pos.j];
  history_.push_back({dir,pos_,next_pos,score_delta});

  pos_=next_pos;
  kingdom_[pos_.i][pos_.j]=-1;
// @trace-pilot df333fb31bb50d819e5b717da0880a9ce331d21f
  turn_=next_turn;
  score_+=score_delta;
  return true;
}

void State::undo(){
// @trace-pilot df333fb31bb50d819e5b717da0880a9ce331d21f
  if(history_.empty()){
    return;
  }

// @trace-pilot df333fb31bb50d819e5b717da0880a9ce331d21f
  MoveHistory last=history_.back();
  history_.pop_back();

// @trace-pilot df333fb31bb50d819e5b717da0880a9ce331d21f
  kingdom_[last.to.i][last.to.j]=init_kingdom_[last.to.i][last.to.j];
  pos_=last.from;
  score_-=last.score_delta;
  --turn_;
}
