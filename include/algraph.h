#ifndef _ALGRAPH_H
#define _ALGRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
#define NotAVertex -1
#define VertexType int
//边节点
typedef struct EdgeNodeAL{
	int adjvex;
	int cost;
	EdgeNodeAL *nextedge;
}EdgeNodeAL;

//顶点节点
typedef struct VertexNodeAL{
	VertexType data;
	EdgeNodeAL *firstedge;
}VertexNodeAL;
typedef struct TABLE{
	int vertex;
	bool known;
	int dist;
	int path;
}TABLE;

typedef struct ALGraph{
	VertexNodeAL *adjlist[MaxVertexNum];
	bool visited[MaxVertexNum];
	int indegree[MaxVertexNum];
	TABLE table[MaxVertexNum];
	int cost[MaxVertexNum][MaxVertexNum];
	int vertex_num;
	int edge_num;
}ALGraph;

typedef struct VBox{
	VertexType Vbox[MaxVertexNum];
	int vnum;
}VBox;

typedef struct VR{
	VertexType tail;
	VertexType head;
	int cost;
}VR;
typedef struct VRBox{
	VR VRbox[MaxVertexNum];
	int vrnum;
}VRBox;


int CreateGraphAL(ALGraph *G, VBox *V, VRBox *VR);
int DestroyGraphAL(ALGraph *G);
int LocateVex(ALGraph *G, VertexType value);
VertexType GetVex(ALGraph *G, int v);
int PutVex(ALGraph *G, int v, VertexType value);
int FirstAdjVex(ALGraph *G, int v);
int NextAdjVex(ALGraph *G, int v, int w);
int InsertVex(ALGraph *G, VertexType value);
int DeleteVex(ALGraph *G, VertexType value);
int InsertArc(ALGraph *G, int v, int w, int cost);
int DeleteArc(ALGraph *G, int v, int w);
void DFSTraverse(ALGraph *G);
void BFSTraverse(ALGraph *G);
void TopSort(ALGraph *G);
void ShortestRoute(ALGraph *G,VertexType start,VertexType destination);

#endif
