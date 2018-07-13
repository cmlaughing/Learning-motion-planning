#pragma once
#include <vector>
#include <memory>

typedef unsigned int uint;

struct State{
  int x, y;

  bool operator == (const State& state_);
  State operator + (const State& state_);
};

typedef std::vector<State> StateList;

class SpaceInformation{
 public:
  SpaceInformation();
  void setSpaceSize(const State& spaceSize_);
  void setDiagonalMovement(bool enable_);
  bool isCollision(const State& state_);
  void addCollision(const State& state_);
  void removeCollision(const State& state_);
  void clearCollisions();

  StateList direction, walls;
  State spaceSize;
  uint directions;
}; 

typedef std::shared_ptr<SpaceInformation> SpaceInformationPtr;
