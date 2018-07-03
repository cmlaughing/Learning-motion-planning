#include <iostream>
#include "State.h"
#include "AStar.h"

int main(){
  
  // construct space
  SpaceInformationPtr si(new SpaceInformation());
  si->setSpaceSize(State({25, 25}));
  si->setHeuristic(Heuristic::euclidean);
  si->setDiagonalMovement(true);

  // find path
  AStar astar(si); 

  std::cout << "find path ... \n";
  auto path = astar.findPath({0, 0}, {20, 20});

  for (auto& state : path) {
    std::cout << state.x << " " << state.y << "\n";
  }
}
