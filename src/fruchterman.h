#include <string>
#include "graph.h"

float center[2];
float gravity;
float speed;
float k;
float k2;
bool clustering;
struct Point
{
  float x;
  float y;
};
struct Cluster
{
  std::string name;
  float cx;
  float cy;
  int count;
};

const int SPEED_DIVISOR = 800;

void applyCalculate(Node *nodes, Edge *edges, Point *displacements, float k, float k2);

void calRepulsive(Node *nodes, Point *displacements, float k2);

void calAttractive(Edge *edges, Point *displacements, float k);

void calCluster(float gravity, Node *nodes, Cluster *clusters);

void calGravity(Node *nodes, float gravity, float k);

void reCalNodesPosition(Node *nodes, Point *displacements, float speed);
