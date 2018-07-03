#include "AStar.h"
#include <iostream>
#include <algorithm>

Node::Node(State state_, Node* parent_){
  parent = parent_;
  state = state_;
  G = H = 0;
}

uint Node::getCost(){
  return G + H;
}

AStar::AStar(SpaceInformationPtr si) : si_(std::move(si)){
    std::cout << "space information loading ... \n";
}

StateList AStar::findPath(State start_, State goal_){
  Node* current = nullptr;
  openSet.insert(new Node(start_));

  while (!openSet.empty()) {
    current = *openSet.begin();
    for (auto node : openSet) {
      if (node->getCost() <= current->getCost()) {
        current = node;
      }
    }
    
    if (current->state == goal_) {
      break;
    }

    closeSet.insert(current);
    openSet.erase(openSet.find(current));
    
    for (uint i = 0; i < si_->directions; ++i) {
      State newState(current->state + si_->direction[i]);
      if (si_->isCollision(newState) || findNodeOnSet(closeSet, newState)) {
        continue;
      }

      uint totalCost = current->G + ((i < 4) ? 10 : 14);

      Node* successor = findNodeOnSet(openSet, newState);
      if (successor == nullptr) {
        successor = new Node(newState, current);
        successor->G = totalCost;
        successor->H = si_->heuristic(successor->state, goal_);
        openSet.insert(successor);
      }
      else if (totalCost < successor->G) {
        successor->parent = current;
        successor->G = totalCost;
      }
    }
  }
  
  while (current != nullptr) {
    path.push_back(current->state);
    current = current->parent;
  }

  releaseNodes(openSet);
  releaseNodes(closeSet);

  return path;
}

Node* AStar::findNodeOnSet(NodeSet& nodes_, State state_){
  for (auto node : nodes_) {
    if (node->state == state_) {
      return node;
    }
  }
  return nullptr;
}

void AStar::releaseNodes(NodeSet& nodes_){
  for (auto it = nodes_.begin(); it != nodes_.end();) {
    delete *it;
    it = nodes_.erase(it);
  }
}

