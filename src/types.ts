export interface Node
{
  x: number // x coordinate
  y: number // y coordinate
};

export interface Edge
{
  sourceNodeArrayIdx: number; // node array index
  targetNodeArrayIdx: number; // node array index
};

export interface Point
{
  x: number
  y: number
};

export interface Center{
  x: number;
  y: number;
};

export interface Cluster
{
  nodes: Node[];
  cx: number;
  cy: number;
};
