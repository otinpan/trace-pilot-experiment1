#pragma once
#include<iostream>

#include"strategy.h"

class Greedy: public Strategy{
  public:
    Greedy();
    ~Greedy() override;

    std::vector<Pos> solve(State &state,Logger& logger) override;
  private:
    std::vector<Pos> zigzag_horizontal(State& state,Logger& logger);
    std::vector<Pos> zigzag_vertical(State& state,Logger& logger);
};
