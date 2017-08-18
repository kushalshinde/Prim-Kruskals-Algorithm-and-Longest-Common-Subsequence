#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int size=0;

/*----------------------- Matrix Printing-----------------------------*/

void matrixPrint (int x, int (*array_ptr)[x]){
  int l,m;
  
  printf("\n");
  for(l=0; l < x; ++l){
	for(m=0; m < x; ++m){
        if(array_ptr[l][m] >= 999){
			printf("%7s","INF");
        }
		else{
			printf("%7d",array_ptr[l][m]);
        }
    }
      printf("\n");
  }
}
/*--------------------------------------------------------------------*/


/*-------------MST Print----------------------------------------------*/

void mstPrint(int V, int (*graph)[V], int parent[])
{
   printf("\n\n");
   printf("Edge\tWeight\n");
   printf("------------------\n"); 
   int i;
   for(i=1;i < V; i++){
      printf("[%d,%d]\t %d \n", parent[i]+1, i+1, graph[i][parent[i]]);  
   }
   printf("\n");
}
/*--------------------------------------------------------------------*/


/*--------------------Minimum Find------------------------------------*/

int minimumFind(int status[], int key[],int size)
{
  int i; 
  int minIndex;
  int min=999;
  
  for(i = 0;i < size; ++i){
    if(key[i]< min){
	    if(status[i]==0){
		    min = key[i];
            minIndex = i;
		}
    }
  }
  return minIndex;
}
/*-------------------------------------------------------------------*/


/*--------------------- Prim's Algorithm-----------------------------*/

void prim(int column,int (*graph)[column])
{
    int parent[column], key[column], status[column];
    int i,v,z;
	
    for(i = 0;i < column; ++i){
        key[i]=999;
        status[i]=0;
        parent[i]=-1;
    }

    key[0]=0;
    parent[0]=-1; 

	
    for(i = 0;i < column-1; ++i){
        int u = minimumFind(status,key,column);
        status[u]=1;

        for(v=0; v < column; ++v){
            if(graph[u][v]){
				if(status[v]==0){
					if(key[v] > graph[u][v]){
						parent[v]=u;key[v]=graph[u][v];
					}
				}
            }
        }
    }
   mstPrint(column, graph, parent);
}
/*-------------------------------------------------------------*/


int main(int argc, char *args[]){
	
	int i,j,k;
	
	FILE * file_ptr;
	file_ptr = fopen(args[1], "r");
  	
	char * line = NULL;  	
	const char *s = ",";
  	
	size_t len = 0;
  	ssize_t read;
	
  	i=0;j=0;k=0;
	if (file_ptr == NULL){
	    printf("\nError in opening a file\n");
		exit(EXIT_FAILURE);
	}
	else{
		while ((read=getline(&line, &len, file_ptr)) != -1){    	
		    size++;	
		}
	}

    int graph[size][size];

	for(i=0;i < size; ++i){         // intializing grpah with 0
        for(j=0; j < size; ++j){
      		graph[i][j]=0;
	    }
    } 
	  
    size_t len_two=0; ssize_t read_two; 
	char *token=NULL; 
    i=0;j=0;
	 
    FILE * file_ptr_two = fopen(args[1], "r");
	 
	while((read_two = getline(&token, &len_two, file_ptr_two))!=-1){
        char *value;
		value=strtok(token,",");
     	while(value){	
     	    graph[i][j]=atoi(value); j++;
			value=strtok(NULL,",");
     	}	
     	j=0; i++;
     }
    fclose(file_ptr);
    fclose(file_ptr_two);

    matrixPrint(size,graph);
    prim(size,graph);
	
}