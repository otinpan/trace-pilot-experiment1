// 小さい方を先に通り、大きい方を後で回収する

#include"turn_back.h"

TurnBack::TurnBack()
  :Strategy()
{

}

TurnBack::~TurnBack()=default;


std::vector<Pos> TurnBack::solve(State& state,Logger& logger){
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


std::vector<Pos> TurnBack::zigzag_horizontal(State& state,Logger& logger){
  std::vector<Pos> result;
  result.emplace_back(state.pos());
  logger.log(state);

  for(int i=0;i<map_size;i+=2){
    while(true){
      Pos now=state.pos();
      int j=i%4==0 ? now.j+1 : now.j-1;
      assert(j>=1&&j<map_size-1);
      int up=state.kingdom()[i][j];
      int down=state.kingdom()[i+1][j];
      Pos next=up>down ? Pos(i+1,j) : Pos(i,j);

      // 下の行との接続
      if(j==map_size-2&&i%4==0){
        next=Pos(i+1,j);
      }
      if(j==1&&i%4!=0){
        next=Pos(i+1,j);
      }

      Direction dir=get_direction(now,next);

      if(!state.apply(dir)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);

      if(i%4==0&&state.pos().j==map_size-2){
        break;
      }
      if(i%4!=0&&state.pos().j==1){
        break;
      }
    }
    if(i+2>=map_size){
      break;
    }

    int j=i%4==0 ? map_size-2 : 1;
    Pos next=Pos(i+2,j);
    Direction dir=get_direction(state.pos(),next);

    if(!state.apply(dir)){
      return result;
    }
    result.emplace_back(state.pos());
    logger.log(state);
  }

  if(map_size>=2 && state.pos()==Pos(map_size-1,1)){
    const std::vector<Pos> last_edge={
      Pos(map_size-2,0),
      Pos(map_size-1,0),
      Pos(map_size-2,1),
    };

    for(const Pos& next:last_edge){
      Direction dir=get_direction(state.pos(),next);
      if(!state.apply(dir)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);
    }
  }

  // 折り返し
  logger.log("start back\n");
  for(int i=map_size-2;i>=0;i-=2){
    while(true){
      Pos now=state.pos();
      int j=i%4==0 ? now.j-1 : now.j+1;
      assert(j>=0 && j<map_size);

      Pos next=state.kingdom()[i][j]!=-1 ? Pos(i,j) :Pos(i+1,j);
      //下のマスを拾っていく
      if(j==0 || j==map_size-1){
        next=Pos(i+1,j);
      }

      Direction dir=get_direction(now,next);
      if(!state.apply(dir)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);

      if(i%4==0&&state.pos().j==0){
        break;
      }
      if(i%4!=0&&state.pos().j==map_size-1){
        break;
      }
    }
    if(i==0){
      break;
    }

    // 端は3個登る
    while(true){
      if(!state.apply(Direction::UP)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);

      if(state.pos().i==i-2){
        break;
      }
    }

  }
  for(int i=0;i<map_size;i++){
    for(int j=0;j<map_size;j++){
      if(state.kingdom()[i][j]!=-1){
        logger.log("("+std::to_string(i)+","+std::to_string(j)+")");
      }
    }
  }
  return result;
}

std::vector<Pos> TurnBack::zigzag_vertical(State& state,Logger& logger){
  std::vector<Pos> result;
  result.emplace_back(state.pos());
  logger.log(state);

  for(int j=0;j<map_size;j+=2){
    while(true){
      Pos now=state.pos();
      int i=j%4==0 ? now.i+1 : now.i-1;
      assert(i>=1&&i<map_size-1);
      int left=state.kingdom()[i][j];
      int right=state.kingdom()[i][j+1];
      Pos next=left>right ? Pos(i,j+1) : Pos(i,j);

      // 右の列との接続
      if(i==map_size-2&&j%4==0){
        next=Pos(i,j+1);
      }
      if(i==1&&j%4!=0){
        next=Pos(i,j+1);
      }

      Direction dir=get_direction(now,next);

      if(!state.apply(dir)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);

      if(j%4==0&&state.pos().i==map_size-2){
        break;
      }
      if(j%4!=0&&state.pos().i==1){
        break;
      }
    }
    if(j+2>=map_size){
      break;
    }

    int i=j%4==0 ? map_size-2 : 1;
    Pos next=Pos(i,j+2);
    Direction dir=get_direction(state.pos(),next);

    if(!state.apply(dir)){
      return result;
    }
    result.emplace_back(state.pos());
    logger.log(state);
  }

  if(map_size>=2 && state.pos()==Pos(1,map_size-1)){
    const std::vector<Pos> last_edge={
      Pos(0,map_size-2),
      Pos(0,map_size-1),
      Pos(1,map_size-2),
    };

    for(const Pos& next:last_edge){
      Direction dir=get_direction(state.pos(),next);
      if(!state.apply(dir)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);
    }
  }

  // 折り返し
  logger.log("start back\n");
  for(int j=map_size-2;j>=0;j-=2){
    while(true){
      Pos now=state.pos();
      int i=j%4==0 ? now.i-1 : now.i+1;
      assert(i>=0 && i<map_size);

      Pos next=state.kingdom()[i][j]!=-1 ? Pos(i,j) :Pos(i,j+1);
      // 右のマスを拾っていく
      if(i==0 || i==map_size-1){
        next=Pos(i,j+1);
      }

      Direction dir=get_direction(now,next);
      if(!state.apply(dir)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);

      if(j%4==0&&state.pos().i==0){
        break;
      }
      if(j%4!=0&&state.pos().i==map_size-1){
        break;
      }
    }
    if(j==0){
      break;
    }

    // 端は3個左に進む
    while(true){
      if(!state.apply(Direction::LEFT)){
        return result;
      }
      result.emplace_back(state.pos());
      logger.log(state);

      if(state.pos().j==j-2){
        break;
      }
    }

  }
  for(int i=0;i<map_size;i++){
    for(int j=0;j<map_size;j++){
      if(state.kingdom()[i][j]!=-1){
        logger.log("("+std::to_string(i)+","+std::to_string(j)+")");
      }
    }
  }
  return result;
}
