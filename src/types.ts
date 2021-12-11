interface Node
{
  x: number // x coordinate
  y: number // y coordinate
};

interface Edge
{
  sourceNodeArrayIdx: number; // node array index
  targetNodeArrayIdx: number; // node array index
};

interface Point
{
  x: number
  y: number
};

interface Center{
  x: number;
  y: number;
};

interface Cluster
{
  nodes: Node[];
  cx: number;
  cy: number;
};
