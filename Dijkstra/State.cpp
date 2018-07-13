#include "State.h"
#include "algorithm"

bool State::operator == (const State& state_){
  return {x == state_.x && y == state_.y};
}

State State::operator + (const State& state_){
  return {x + state_.x, y + state_.y};
}
SpaceInformation::SpaceInformation(){
  direction = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0},
    {-1, -1}, {1, 1}, {-1, 1}, {1, -1}
  };
}

void SpaceInformation::setSpaceSize(const State& spaceSize_){
  spaceSize = spaceSize_;
}

void SpaceInformation::setDiagonalMovement(bool enable_){
  directions = enable_ ? 8 : 4;
}

bool SpaceInformation::isCollision(const State& state_){
  if (state_.x < 0 || state_.x >= spaceSize.x || state_.y < 0 || state_.y >= spaceSize.y || std::find(walls.begin(), walls.end(), state_) != walls.end()) {
  return true;
  }
  return false;
}

void SpaceInformation::removeCollision(const State& state_){
  auto it = std::find(walls.begin(),walls.end(), state_);
  if (it != walls.end()) {
    walls.erase(it);
  }
}

void SpaceInformation::clearCollisions(){
  walls.clear();
}

