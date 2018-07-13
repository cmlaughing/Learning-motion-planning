#include <iostream>
#include "State.h"
#include "Dijkstra.h"

int main(){
  
  // construct space
  SpaceInformationPtr si(new SpaceInformation());
  si->setSpaceSize(State({25, 25}));
  si->setDiagonalMovement(true);

  // find path
  Dijkstra Dijkstra(si); 

  std::cout << "find path ... \n";
  auto path = Dijkstra.findPath({0, 0}, {20, 20});

  for (auto& state : path) {
    std::cout << state.x << " " << state.y << "\n";
  }
}
