#pragma once
#include<iostream>
#include<vector>

#include"common.h"

class State{
  public:
    State(std::vector<std::vector<int>> kingdom);
    ~State();

    bool apply(Direction dir);
    void undo();


  private:
    std::vector<std::vector<int>> init_kingdom_;
    std::vector<std::vector<int>> kingdom_;
    Pos pos_;
    std::vector<Direction> path_;
    long long score_;
    int turn_;
};
