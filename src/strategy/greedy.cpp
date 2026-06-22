// ジグザグ動く


#include"greedy.h"

Greedy::Greedy()
  :Strategy()
{

}

Greedy::~Greedy()=default;

std::vector<Pos> Greedy::solve(State& state,Logger& logger){
  State horizontal_state=state;
  State vertical_state=state;

  std::vector<Pos> horizontal_result=zigzag_horizontal(horizontal_state,logger);
  std::vector<Pos> vertical_result=zigzag_vertical(vertical_state,logger);

  if(horizontal_state.score()>=vertical_state.score()){
    state=horizontal_state;
    logger.log(state);
    return horizontal_result;
  }

  state=vertical_state;
  logger.log(state);
  return vertical_result;
}

std::vector<Pos> Greedy::zigzag_horizontal(State& state,Logger& logger){
  std::vector<Pos> result;
  result.reserve(map_size*map_size);
  result.push_back(state.pos());

  for(int i=0;i<map_size;i++){
    if(i%2==0){
      while(state.pos().j+1<map_size){
        bool ok=state.apply(Direction::RIGHT);
        assert(ok);
        result.push_back(state.pos());
        logger.log(state);
      }
    }else{
      while(state.pos().j>0){
        bool ok=state.apply(Direction::LEFT);
        assert(ok);
        result.push_back(state.pos());
        logger.log(state);
      }
    }

    if(i+1<map_size){
      bool ok=state.apply(Direction::DOWN);
      assert(ok);
      result.push_back(state.pos());
      logger.log(state);
    }
  }

  return result;
}


std::vector<Pos> Greedy::zigzag_vertical(State& state,Logger& logger){
  (void)logger;

  std::vector<Pos> result;
  result.reserve(map_size*map_size);
  result.push_back(state.pos());

  for(int j=0;j<map_size;j++){
    if(j%2==0){
      while(state.pos().i+1<map_size){
        bool ok=state.apply(Direction::DOWN);
        assert(ok);
        result.push_back(state.pos());
      }
    }else{
      while(state.pos().i>0){
        bool ok=state.apply(Direction::UP);
        assert(ok);
        result.push_back(state.pos());
      }
    }

    if(j+1<map_size){
      bool ok=state.apply(Direction::RIGHT);
      assert(ok);
      result.push_back(state.pos());
    }
  }

  return result;
}
