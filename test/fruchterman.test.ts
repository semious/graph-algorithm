import { calRepulsive } from '../src/fruchterman';
import { Edge, Node } from '../src/types';

function createRandomNodes(count: number): Node[] {
  const nodes = [];
  for (let i = 0; i < count; i++) {
    nodes.push({
      id: String(i),
      x: Math.floor(Math.random() * 1000),
      y: Math.floor(Math.random() * 1000)
    });
  }
  return nodes;
}

function createRandomEdges(count: number, nodeSize: number): Edge[] {
  const edges: Edge[] = [];
  const counts = Math.min(count, 2 * nodeSize - 2);
  for (let i = 0; i < counts; i++) {
    edges.push({
      sourceNodeArrayIdx: Math.floor(Math.random() * nodeSize),
      targetNodeArrayIdx: Math.floor(Math.random() * nodeSize)
    })
  }
  return edges;
}

describe('src/fruchterman.ts', () => {
  describe('calRepulsive', () => {
    it('calRepulsive should success', () => {
      const nodeSize = 8323;
      const edgeSize = 5421;
      const nodes = createRandomNodes(nodeSize);
      const edges = createRandomEdges(edgeSize, nodeSize);
      // console.log('nodes :>> ', nodes[0]);
      // console.log('edges :>> ', edges[0]);
      const displacements = nodes.map(() => ({ x: 0, y: 0 }));
      const start = Date.now();
      const result = calRepulsive(nodes, displacements , 123,);
      const end = Date.now();
      console.log('calRepulsive time :>> ', end - start);
      // console.log('result :>> ', result);
      // expect(result).toBe(0);
    });
  });
});
