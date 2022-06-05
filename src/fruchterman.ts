// const SPEED_DIVISOR = 800;

import { Edge, Node, Point } from "./types";

export function layout(nodes: Node[], edges: Edge[], displacements: Point[], k: number, k2: number) {
  calRepulsive(nodes, displacements, k2);
  if (edges) calAttractive(nodes, edges, displacements, k);
}

export function calRepulsive(nodes: Node[], displacements: Point[], k2: number) {
  nodes.forEach((v, i) => {
    displacements[i] = { x: 0, y: 0 };
    nodes.forEach((u, j) => {
      if (i === j) {
        return;
      }
      if (
        !isNumber(v.x) ||
        !isNumber(u.x) ||
        !isNumber(v.y) ||
        !isNumber(u.y)
      ) {
        return;
      }
      let vecX = v.x - u.x;
      let vecY = v.y - u.y;
      let vecLengthSqr = vecX * vecX + vecY * vecY;
      if (vecLengthSqr === 0) {
        vecLengthSqr = 1;
        const sign = i > j ? 1 : -1;
        vecX = 0.01 * sign;
        vecY = 0.01 * sign;
      }
      const common = k2 / vecLengthSqr;
      displacements[i].x += vecX * common;
      displacements[i].y += vecY * common;
    });
  });
  return displacements;
}

export function calAttractive(nodes: Node[], edges: Edge[], displacements: Point[], k: number) {
  edges.forEach((e) => {

    const uIndex = e.sourceNodeArrayIdx;
    const vIndex = e.targetNodeArrayIdx;
    if (!uIndex || !vIndex) return;
    if (uIndex === vIndex) {
      return;
    }
    const u = nodes[uIndex];
    const v = nodes[vIndex];
    if (!isNumber(v.x) || !isNumber(u.x) || !isNumber(v.y) || !isNumber(u.y)) {
      return;
    }
    const vecX = v.x - u.x;
    const vecY = v.y - u.y;
    const vecLength = Math.sqrt(vecX * vecX + vecY * vecY);
    const common = (vecLength * vecLength) / k;
    displacements[vIndex].x -= (vecX / vecLength) * common;
    displacements[vIndex].y -= (vecY / vecLength) * common;
    displacements[uIndex].x += (vecX / vecLength) * common;
    displacements[uIndex].y += (vecY / vecLength) * common;
  });
}

function isNumber(value: any) {
  return typeof value === 'number' && !isNaN(value);
}
