#pragma once
#include <functional>
#include <vector>
#include <memory>

typedef unsigned int uint;

struct State{
  int x, y;

  bool operator == (const State& state_);
  State operator + (const State& state_);
};

typedef std::vector<State> StateList;

class Heuristic{
  static State getDelta(State start_, State target_);
 
 public:
  static uint manhattan(State start_, State target_);
  static uint euclidean(State start_, State target_);
  static uint octagonal(State start_, State target_);
};

typedef std::function<uint(State, State)> HeuristicFunction;

class SpaceInformation{
 public:
  SpaceInformation();
  void setSpaceSize(const State& spaceSize_);
  void setDiagonalMovement(bool enable_);
  void setHeuristic(HeuristicFunction heuristic_);
  bool isCollision(const State& state_);
  void addCollision(const State& state_);
  void removeCollision(const State& state_);
  void clearCollisions();

  HeuristicFunction heuristic;
  StateList direction, walls;
  State spaceSize;
  uint directions;
}; 

typedef std::shared_ptr<SpaceInformation> SpaceInformationPtr;
