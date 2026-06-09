#pragma once
#include<iostream>

#include"strategy.h"

class TurnBack: public Strategy{
  public:
    TurnBack();
    ~TurnBack();

    std::vector<Pos> solve(State& state,Logger& logger) override;
  private:
    std::vector<Pos> zigzag_horizontal(State& state,Logger& logger);
    std::vector<Pos> zigzag_vertical(State& state,Logger& logger);

};
