#include "algraph.h"
#include "squeue.h"
#define INT_MAX 65535
int CreateGraphAL(ALGraph *G, VBox *V, VRBox *VR){
	for(int i = 0; i < MaxVertexNum; i++){
		G->adjlist[i] = NULL;
		G->visited[i] = false;
		G->indegree[i] = 0;

		G->table[i].known = false;
		G->table[i].dist = INT_MAX;
		G->table[i].path = NotAVertex;
	}
	G->vertex_num = 0;
	G->edge_num = 0;
	for(int i = 0; i < V->vnum; i++){
		InsertVex(G, V->Vbox[i]);
	}
	for(int i = 0; i < VR->vrnum; i++){
		InsertArc(G, VR->VRbox[i].tail, VR->VRbox[i].head, VR->VRbox[i].cost);
	}
	return 0;
}
int DestroyGraphAL(ALGraph *G){
	for(int i = 0; i < G->vertex_num; i++){
		EdgeNodeAL *e;
		while(G->adjlist[i]->firstedge != NULL){
			e = G->adjlist[i]->firstedge;
			G->adjlist[i]->firstedge = G->adjlist[i]->firstedge->nextedge;
			free(e);
		}
		free( G->adjlist[i]);
		G->adjlist[i] = NULL;
	}
	return 0;
}
int LocateVex(ALGraph *G, VertexType value){
	for(int i = 0; i < G->vertex_num; i++){
		if(G->adjlist[i]->data == value){
			return i;
		}
	}
	printf("LocateVex failed\r\n");
	return -1;
}
VertexType GetVex(ALGraph *G, int v){
	if( v < G->vertex_num){
		return G->adjlist[v]->data;
	}else
	{
		printf("GetVex failed\r\n");
		return -1;
	}
}
int PutVex(ALGraph *G, int v, VertexType value){
	if( v < G->vertex_num){
		G->adjlist[v]->data = value;
		return 0;
	}else
	{
		printf("PutVex failed\r\n");
		return -1;
	}	
}
int FirstAdjVex(ALGraph *G, int v){
	if(G->adjlist[v]->firstedge != NULL){
		return G->adjlist[v]->firstedge->adjvex;
	}
	else{
		//printf("Get FirstAdjVex Failed\r\n");
		return -1;
	}	
}
int NextAdjVex(ALGraph *G, int v, int w){
	EdgeNodeAL *e;
	e = G->adjlist[v]->firstedge;
	while(e != NULL){
		if(e->adjvex == w)
		{
			if(e->nextedge == NULL){//这句不能忘
				break;
			}else{
				return e->nextedge->adjvex;
			}
			
		}else{
			e = e->nextedge;	
		}
	}
	//printf("GetNextAdjVex Failed\r\n");
	return -1;
}
int InsertVex(ALGraph *G, VertexType value){	
	G->adjlist[G->vertex_num] = (VertexNodeAL*)malloc(sizeof(VertexNodeAL));
	G->adjlist[G->vertex_num]->data = value;
	G->adjlist[G->vertex_num]->firstedge = NULL;
	G->vertex_num++;
	return 0;
}
int DeleteVex(ALGraph *G, VertexType value){//由于用数组来存储顶点，用数组下标来标志顶点位置，这种方式应该只允许从数组的末端开始删除顶点。
	int v =  LocateVex(G,value);
	for(int i = 0; i < G->vertex_num; i++)//delete the arc whose head is v
	{
		DeleteArc(G, i, v);
	}
	EdgeNodeAL *e;
	while(G->adjlist[v]->firstedge != NULL){//delete the arc whose tail is v
		e = G->adjlist[v]->firstedge;
		G->adjlist[v]->firstedge = G->adjlist[v]->firstedge->nextedge;
		free(e);
	}
	free( G->adjlist[v]);//delete the vertexnode;
	G->adjlist[v] = NULL;//adjlist[]  变得不连续了。
	return 0;
}
int InsertArc(ALGraph *G, int v, int w, int cost){
	
	EdgeNodeAL *newedge = (EdgeNodeAL*)malloc(sizeof(EdgeNodeAL));
	newedge->adjvex = w;
	newedge->nextedge = G->adjlist[v]->firstedge;
	newedge->cost = cost;
	G->cost[v][w] = cost;
	G->adjlist[v]->firstedge = newedge;
	G->edge_num++;	
	G->indegree[w]++;
	return 0;
}
int DeleteArc(ALGraph *G, int v, int w){

	EdgeNodeAL *e = G->adjlist[v]->firstedge;
	if(e != NULL){//是否有弧
		if(e->adjvex == w){//是否是第一条弧
			G->adjlist[v]->firstedge = e->nextedge;
			free(e);
			return 0;
		}
		else{
			EdgeNodeAL *p = e;		
			while(e->nextedge != NULL){//是否还有下一条弧	
				p = e;
				e = e->nextedge;
				if(e->adjvex == w){
					p->nextedge = e->nextedge;
					free(e);
					return 0;
				}
			}			
		}	
	}
	printf("DeleteArc failed\r\n");
	return -1;
	
}
void DFS(ALGraph *G,int i){
	G->visited[i] = true;
	printf("%d->",G->adjlist[i]->data);
	for(int w = FirstAdjVex(G,i); w != -1; w = NextAdjVex(G,i,w)){
		if(!G->visited[w]){
			DFS(G,w);		
		}
	}

}
void DFSTraverse(ALGraph *G){
	for(int i = 0; i < MaxVertexNum; i++){
		G->visited[i] = false;
	}
	for(int i = 0; i < G->vertex_num; i ++){
		if(!G->visited[i]){
			printf("new\r\n");
			DFS(G,i);
		}
	}	
}
void BFS(ALGraph *G, int v){
	
}
void BFSTraverse(ALGraph *G){
	Queue *Q = QCreate();
	for(int i = 0; i < G->vertex_num; i++){
		G->visited[i] = false;
	}
	for(int i = 1; i < G->vertex_num; i++){
		if(!G->visited[i]){
			printf("new\r\n");
			G->visited[i] = true;//标志visited再进入队列, 避免重复进入队列
			EnQueue(Q,i);
			while(!QueueEmpty(Q)){
				int v = DeQueue(Q);
				printf("%d->",G->adjlist[v]->data);
				for(int w = FirstAdjVex(G,v); w != -1; w = NextAdjVex(G,v,w)){
					if(!G->visited[w]){
						G->visited[w] = true;
						EnQueue(Q,w);
					}	
				}
			}
		}	
	}
}
void TopSort(ALGraph *G){
	Queue *Q = QCreate();
	int indegree[MaxVertexNum];
	for(int i = 0; i < G->vertex_num; i++){
		indegree[i] = G->indegree[i];	
		printf("indegree[%d]:%d\r\n",i,indegree[i]);
	}
	for(int i = 0; i < G->vertex_num; i++){
		if( G->indegree[i] == 0){
			EnQueue(Q,i);
			/*
			while(!QueueEmpty(Q)){
				int v = DeQueue(Q);
				printf("%d->",G->adjlist[v]->data);
				for(int w = FirstAdjVex(G,v); w != -1; w = NextAdjVex(G,v,w)){
					indegree[w]--;//已经进入队列的元素在这里的indegree会变成负数，不会重复进入队列
					if(indegree[w] == 0){						
					EnQueue(Q,w);
					}	
				}		
			}*/
		}
	}
	while(!QueueEmpty(Q)){
		int v = DeQueue(Q);
		printf("%d->",G->adjlist[v]->data);
		for(int w = FirstAdjVex(G,v); w != -1; w = NextAdjVex(G,v,w)){
			indegree[w]--;//已经进入队列的元素在这里的indegree会变成负数，不会重复进入队列
			if(indegree[w] == 0){						
				EnQueue(Q,w);
			}	
		}		
	}

}

int SmallestUnknowDistanceVertex(ALGraph *G)
{
	int dist = INT_MAX;
	int smallest;
	for(int i = 0 ; i < G->vertex_num; i++){
		if( G->table[i].known == false){
			if(G->table[i].dist < dist){
				dist = G->table[i].dist;
				smallest = i;
			}
		}	
	}
	return smallest;
}
void ShortestRoute(ALGraph *G,VertexType startpoint,VertexType destinationpoint){
	int start = LocateVex(G,startpoint);
	int destin = LocateVex(G,destinationpoint);
	
	G->table[start].dist = 0;
	for(int i = 0; i < G->vertex_num; i++){	
		//find the smallest nuknow distance vertex;
		int v = SmallestUnknowDistanceVertex(G);
		printf("%d,smallest:%d\r\n",i,v);
		G->table[v].known = true;

		for(int w = FirstAdjVex(G,v); w != -1; w = NextAdjVex(G,v,w)){
			if((G->table[v].dist + G->cost[v][w])<(G->table[w].dist)){
				G->table[w].dist = G->table[v].dist + G->cost[v][w];
				G->table[w].path = v;
			}		
		}
	}
	for(int i = 0; i < G->vertex_num; i++){		
		printf("table[%d]:know:%d,dis:%d,path:%d\r\n",i,G->table[i].known,G->table[i].dist,G->table[i].path);
	}
	int p;
	
	for(p = destin; p != NotAVertex; p = G->table[p].path)
	{
		printf("%d<- ",G->adjlist[p]->data);	
	}
	printf("\r\n");	
}
