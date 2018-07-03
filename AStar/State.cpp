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

void SpaceInformation::setHeuristic(HeuristicFunction heuristic_){
  heuristic = heuristic_;
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

State Heuristic::getDelta(State start_, State goal_){
  return {abs(start_.x - goal_.x), abs(start_.y - goal_.y)};
}

uint Heuristic::manhattan(State start_, State goal_){
  auto delta = std::move(getDelta(start_, goal_));
  return static_cast<uint>(10 * (delta.x + delta.y));
}

uint Heuristic::euclidean(State start_, State goal_){
  auto delta = std::move(getDelta(start_, goal_));
  return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

uint Heuristic::octagonal(State start_, State goal_){
  auto delta = std::move(getDelta(start_, goal_));
  return 10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y);}
