#include "Dijkstra.h"
#include <iostream>

Node::Node(State state_, Node* parent_){
  state = state_;
  parent = parent_;
  cost = 0;
}

Dijkstra::Dijkstra(SpaceInformationPtr si) : si_(std::move(si)){
  std::cout << "space information loading... \n";
}

StateList Dijkstra::findPath(State start_, State goal_){
  Node* current = nullptr;
  openSet.insert(new Node(start_));  
  
  while (!openSet.empty()) {
    current = *openSet.begin();
    for (auto node : openSet) {
      if (node->cost <= current->cost) {
        current = node;
      }
    }
    
    if (current->state == goal_) {
      break;
    }

    closeSet.insert(current);
    openSet.erase(openSet.find(current));

    for (uint i=0; i<si_->directions; ++i) {
      State newState(current->state + si_->direction[i]);
      if (si_->isCollision(newState) || findNodeOnSet(closeSet, newState)) {
        continue;
      }

      uint newcost = current->cost + ((i < 4) ? 10 : 14);

      Node* successor = findNodeOnSet(openSet, newState);
      if (successor == nullptr) {
        successor = new Node(newState, current);
        successor->cost = newcost;
        openSet.insert(successor);
      } 
      else if (newcost < successor->cost) {
        successor->parent = current;
        successor->cost = newcost;
      }
    }
  }
  
  StateList path;
  while (current != nullptr) {
    path.push_back(current->state);
    current = current->parent;
  }

  releaseNodes(openSet);
  releaseNodes(closeSet);

  return path;
}
     
Node* Dijkstra::findNodeOnSet(NodeSet& nodes_, State state_){
  for (auto node : nodes_) {
    if (node->state == state_) {
      return node;
    }
  }
  return nullptr;
}

void Dijkstra::releaseNodes(NodeSet& nodes_){
  for (auto it = nodes_.begin(); it != nodes_.end();) {
    delete *it;
    it = nodes_.erase(it);
  }
} 
    

