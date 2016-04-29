// datastructure.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include "algraph.h"



int main()
{
	/*
	FILE *fd;
	fd = fopen("data.txt","w");	
	for( int i = 1; i < 100; i++){
		printf("%d\r\n",putc(i,fd));
	}
	fclose(fd);
	fd = fopen("data.txt","r");	
	int a;	
	while((a = getc(fd)) != EOF){	
		//printf("%d\r\n",getc(fd));
	}
	fclose(fd);
	*/
	VBox *vbox = (VBox *)malloc(sizeof(VBox));
	VRBox *vrbox = (VRBox *)malloc(sizeof(VRBox));
	ALGraph *G = (ALGraph *)malloc(sizeof(ALGraph));

	vbox->vnum = 7;
	for(int i = 0; i < vbox->vnum; i++){
		vbox->Vbox[i] = i+1;
	}

	vrbox->vrnum = 12;
	vrbox->VRbox[0].tail = 0;vrbox->VRbox[0].head = 1;vrbox->VRbox[0].cost = 2;
	vrbox->VRbox[1].tail = 0;vrbox->VRbox[1].head = 3;vrbox->VRbox[1].cost = 1;
	vrbox->VRbox[2].tail = 1;vrbox->VRbox[2].head = 3;vrbox->VRbox[2].cost = 3;
	vrbox->VRbox[3].tail = 1;vrbox->VRbox[3].head = 4;vrbox->VRbox[3].cost = 10;
	vrbox->VRbox[4].tail = 2;vrbox->VRbox[4].head = 0;vrbox->VRbox[4].cost = 4;
	vrbox->VRbox[5].tail = 2;vrbox->VRbox[5].head = 5;vrbox->VRbox[5].cost = 5;
	vrbox->VRbox[6].tail = 3;vrbox->VRbox[6].head = 2;vrbox->VRbox[6].cost = 2;
	vrbox->VRbox[7].tail = 3;vrbox->VRbox[7].head = 5;vrbox->VRbox[7].cost = 8;
	vrbox->VRbox[8].tail = 3;vrbox->VRbox[8].head = 6;vrbox->VRbox[8].cost = 4;
	vrbox->VRbox[9].tail = 3;vrbox->VRbox[9].head = 4;vrbox->VRbox[9].cost = 2;
	vrbox->VRbox[10].tail = 4;vrbox->VRbox[10].head = 6;vrbox->VRbox[10].cost = 6;
	vrbox->VRbox[11].tail = 6;vrbox->VRbox[11].head = 5;vrbox->VRbox[11].cost = 1;

	int state = CreateGraphAL(G,vbox, vrbox);
	for(int i = 0; i < G->vertex_num; i++){
		printf("%d\r\n",GetVex(G, i));
	}	
/*	for(int i = 0; i <= G->vertex_num; i++){
		printf("%d\r\n",LocateVex(G, i));
	}
	
	printf("putvex\r\n");
	for(int i = 0; i < G->vertex_num; i++){
		printf("%d\r\n",PutVex(G, i, i+5));
	}
	for(int i = 0; i < G->vertex_num; i++){
		printf("%d\r\n",GetVex(G, i));
	}	
	int a;
	printf("firstadj:%d\r\n", a = FirstAdjVex(G,0));
	printf("nextadj:%d\r\n", a = NextAdjVex(G,0,a));
	printf("nextadj:%d\r\n", a = NextAdjVex(G,0,a));
	printf("nextadj:%d\r\n", a = NextAdjVex(G,0,a));
	printf("firstadj:%d\r\n", a = FirstAdjVex(G,3));
	printf("nextadj:%d\r\n", a = NextAdjVex(G,3,a));
	printf("nextadj:%d\r\n", a = NextAdjVex(G,3,a));	
*/	
	printf("DFS:\r\n");
	DFSTraverse(G);
	printf("BFS:\r\n");
	BFSTraverse(G);
	printf("TopSort:\r\n");
	TopSort(G);
	printf("shortest path:\r\n");
	ShortestRoute(G,1,7);

	DeleteArc(G, 0, 1);
	DeleteArc(G, 0, 3);	
	DeleteArc(G, 0, 2);

	DeleteArc(G, 0, 1);
	DeleteArc(G, 0, 3);	
	DeleteArc(G, 0, 2);

	DeleteArc(G, 3, 2);
	DeleteArc(G, 3, 5);
	DeleteArc(G, 3, 6);
	
	DeleteArc(G, 3, 2);
	DeleteArc(G, 3, 5);
	DeleteArc(G, 3, 6);
	DFSTraverse(G);
	
	
	state = DestroyGraphAL(G);

	return 0;
}

