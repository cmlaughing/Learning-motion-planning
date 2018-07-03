#pragma once 
#include <unordered_set>
#include "State.h"

typedef unsigned char uchar;
typedef unsigned int uint;

struct Node{
    uint F, G, H;
    State state;
    Node* parent;
  
    Node(State state_, Node *parent_ = nullptr);
    uint getCost();
};

typedef std::unordered_set<Node*> NodeSet;
 
class AStar{
  Node* findNodeOnSet(NodeSet& nodes_, State state_);
  void releaseNodes(NodeSet& nodes_);

 public:
  AStar(const SpaceInformationPtr si);
  void setSpaceInformation(const SpaceInformation& si);
  StateList findPath(State start_, State goal_);

 private:
  SpaceInformationPtr si_;
  NodeSet openSet, closeSet; 
  StateList path;
};


