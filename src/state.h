#pragma once
#include<iostream>
#include<vector>

#include"common.h"

class State{
  public:
    State(std::vector<std::vector<int>> kingdom);
    ~State();

    bool apply(Direction dir);

    const std::vector<std::vector<int>>& kingdom() const{return kingdom_;}
    const Pos& pos() const {return pos_;}
    long long score() const{return score_;}
    int turn() const{return turn_;}

  private:
// @trace-pilot df333fb31bb50d819e5b717da0880a9ce331d21f
    struct MoveHistory{
      Direction dir;
      Pos from;
      Pos to;
      long long score_delta;
    };

    std::vector<std::vector<int>> init_kingdom_;
    std::vector<std::vector<int>> kingdom_;
    Pos pos_;
// @trace-pilot df333fb31bb50d819e5b717da0880a9ce331d21f
    std::vector<MoveHistory> history_;
    long long score_;
    int turn_;
};
