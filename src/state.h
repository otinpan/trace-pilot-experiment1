#pragma once
#include<iostream>
#include<vector>

#include"common.h"

class State{
  public:
    State(std::vector<std::vector<int>> kingdom);
    ~State();

    bool apply(Direction dir);
// @trace-pilot 732c54cd0e983c353bcd276a862b9b17a9eabfd6
    void undo();

    const std::vector<std::vector<int>>& kingdom() const{return kingdom_;}
    const Pos& pos() const {return pos_;}
    long long score() const{return score_;}
    int turn() const{return turn_;}

  private:
    struct MoveHistory{
      Direction dir;
      Pos from;
      Pos to;
      long long score_delta;
    };

    std::vector<std::vector<int>> init_kingdom_;
    std::vector<std::vector<int>> kingdom_;
    Pos pos_;
    std::vector<MoveHistory> history_;
    long long score_;
    int turn_;
};
