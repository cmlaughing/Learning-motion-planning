#include <vector>
#include <unordered_set>
#include "State.h"

struct Node{
  State state;
  Node* parent;
  int cost;
  Node(State state_, Node* parent_ = nullptr);
};  

typedef std::unordered_set<Node*> NodeSet;

class Dijkstra{
  Node* findNodeOnSet(NodeSet& nodes_, State state_);
  void releaseNodes(NodeSet& nodes_);

 public:
  Dijkstra(const SpaceInformationPtr si);
  StateList findPath(State start_, State goal_);

 private:
  SpaceInformationPtr si_;
  NodeSet openSet, closeSet;
};
