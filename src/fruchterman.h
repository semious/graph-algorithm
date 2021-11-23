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


void calRepulsive(const Node *nodes, const size_t nodeSize, Point *displacements, const float k2);

void calAttractive(const Node *nodes, const size_t nodeSize, const Edge *edges, const size_t edgeSize, Point *displacements, const float k);

void calCluster(const Node *nodes, const size_t nodeSize, const Cluster *clusters, const size_t clusterSize, Point *displacements, const float clusterGravity, const float k);

void calGravity(Node *nodes, size_t nodeSize, Point *displacements, float gravity, float k, Center *center);

// void reCalNodesPosition(Node *nodes, size_t nodeSize, Point *displacements, unsigned int clusterSize, float speed);
