struct Node
{
  float x; // x coordinate
  float y; // y coordinate
};

struct Edge
{
  int sourceNodeArrayIdx; // node array index
  int targetNodeArrayIdx; // node array index
};

struct Point
{
  float x;
  float y;
};

struct Center{
  float x;
  float y;
};
struct Cluster
{
  int * nodeArrayIdx;
  int nodeSize;
  float cx;
  float cy;
  int count;
};

void calRepulsive(Node *nodes, size_t nodeSize, Point *displacements, float k2);

void calAttractive(Node *nodes, size_t nodeSize, Edge *edges, size_t edgeSize, Point *displacements, float k);

void calCluster(Node *nodes, size_t nodeSize, Cluster *clusters, size_t clusterSize, float clusterGravity);

void calGravity(Node *nodes, size_t nodeSize, Point *displacements, float gravity, float k, Center *center);

// void reCalNodesPosition(Node *nodes, size_t nodeSize, Point *displacements, unsigned int clusterSize, float speed);
