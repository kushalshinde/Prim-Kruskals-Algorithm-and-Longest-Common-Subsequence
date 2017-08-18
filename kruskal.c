#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int size=0;

/*-----------------Edge Structure---------------------------*/
struct edge
{
	int start;
	int end;
	int weight;
	int tested;
	int selected;
}edge; 
/*----------------------------------------------------------*/


/*---------------Swapping Function--------------------------*/
void swap(struct edge *second, struct edge *first)
{ 
	struct edge bottom;
	bottom = *first;
	*first=*second;
	*second=bottom;
}
/*---------------------------------------------------------*/
 int struct_cmp_by_weight(const void *a, const void *b) 
 { 
     struct edge *ia = (struct edge *)a;
     struct edge *ib = (struct edge *)b;
     return (int)(100.f*ia->weight - 100.f*ib->weight);
 } 




int indexPartition(int start,int end, int num, struct edge pivotal[num])
{	
	int i;
	int indexPivot = start+ rand()%(end - start + 1);    // Implemented randomized quick sort ;
	int index = start-1; 

	int pivot = pivotal[indexPivot].weight;
	swap(&pivotal[indexPivot], &pivotal[end]);
	
	for(i = start; i < end ; ++i)
	{
		if(pivot > pivotal[i].weight)
		{
			index++;
			swap(&pivotal[i],&pivotal[index]);
		}
	}
	
	swap(&pivotal[index+1],&pivotal[end]);
	return index+1;
}

void quickSort(int start, int end, int num, struct edge link[num])
{
	int i;
	if(end > start){
		int index = indexPartition(start, end, num,link);  // getting an Index
		quickSort(start,index-1,num,link);  // recursion call to qucik sort function for start to Index-1 element
		quickSort(index+1,end,num,link); // recursion call to qucik sort function for Index+1 to end element
	}
}
/*--------------------------------------------------------------------------------*/


/*---------------------- Matrix Printing------------------------------*/

void matrixPrint(int coloumn, int (*ptr_arr)[coloumn]){
  int i,j;
  for (i = 0; i < coloumn; ++i)
  {
    for ( j = 0; j < coloumn; ++j)
      {
        if(ptr_arr[i][j]>=999){
        printf("%7s","INF");
        }else{
        printf("%7d",ptr_arr[i][j]);
        }
        
      }
      printf("\n");
  }
}
/*--------------------------------------------------------------------*/


/*------------------------Height Calculation--------------------------*/

int length(int * array, int x)
{
  int height=0;
  int i=x;
  int parent;
  
	while(x!=*(array+i)){
		i=*(array+i);
		height++;
	}
  
  return height;
}
/*-------------------------------------------------------------------*/



/*--------------------- Union 3--------------------------------------*/

void union3(int l, int *array, int m )
{
  int x_height = length(array, l);
  
  int y_height=length(array, m);
  
	if(y_height<x_height){
		*(array+m)=l;
	}
	else if(y_height==x_height){
		*(array+m)=l;
	}
	else{
		*(array+l)=m;
	}
}

/*--------------------------------------------------------------*/


/*--------------------------Find3------------------------------*/

int find3(int *arr, int f)
{
	int root=f;
	
	while(root!=*(arr+root))
	{
		root=*(arr+root);
	}
	int n=f;
	int parent;
	
	while(n!=root){
		parent=*(arr+n);
		*(arr+n)=root;
		n=parent;
	}
  return root;
}
/*--------------------------------------------------------------*/



/*------------------------ Kruskal Algorithm-------------------------*/

void kruskal(int c,int (*arr_ptr)[c])
{    
    matrixPrint(c,arr_ptr);
	int i,j,k=0; int edgeNum=0;
	
	for(i=0; i<c; ++i)
    {
		for(j=0; j<i; ++j)
		{
			if(arr_ptr[i][j]!=999)
			{
              edgeNum++;
			}
      }
    }
	
    struct edge link[edgeNum];
	
	for (i=0; i<c; ++i)
    {
      for (j=0; j<i; ++j)
      {  
        if(arr_ptr[i][j]!=999){
			link[k].start=i;
			link[k].end=j;
			link[k].weight=arr_ptr[i][j];
			link[k].selected=0;
			link[k].tested=0;
			k++;
          }
      }
    }

  printf("------------Graph Edges-------------\n");
  
  
  for(i=0;i < edgeNum; ++i){
      printf("Edge %d to %d -> %d\n",link[i].start+1,link[i].end+1,link[i].weight);
  }
  
  int structs_len = sizeof(link)/sizeof(struct edge);
  
  qsort(link, structs_len, sizeof(struct edge), struct_cmp_by_weight);
   printf("----------Printing Edges After Sorting-----------\n");
   for (i = 0; i < structs_len; ++i)
   { 
       printf("Edge %d to %d -> %d\n",link[i].start,link[i].end,link[i].weight);
   }

  
  int array[c];
  for (i=0; i<c; ++i) // self value to index 
  {
    array[i]=i;
  }
  
  int z;
 
 for(i=0;i<structs_len; ++i)
 {   
      int ucomp=find3(array, link[i].start);
      int vcomp=find3(array, link[i].end);
      
      if(ucomp!=vcomp)
	  {
		link[i].selected=1;
        union3(ucomp,array,vcomp);
      }
  }
  printf("----------------Selected Graph Edges----------------\n");
  printf("Edge\tWeight\n");
  printf("-----------------\n");  
  

  for(i = 0; i < edgeNum; ++i){
      if(link[i].selected==1){
		printf("[%d,%d]\t%d\n",link[i].start+1,link[i].end+1,link[i].weight);
      }      
  }
   printf("\n"); 
}
/*---------------------------------------------------------------------------*/


int main(int argc, char *args[])
{
	const char *s = ",";
	char * line = NULL;  	
	FILE * ptr_file; 
	ptr_file = fopen(args[1], "r");
  	size_t len=0;
  	ssize_t read;
  	int i=0;
	int j=0;
	int k=0;
	
	if (ptr_file == NULL)
    {
    	printf("\nError opening a file\n");
		exit(EXIT_FAILURE);
    }
	else
	{
	    while ((read=getline(&line, &len, ptr_file)) != -1)
		{
	     	size++;	
	    }
	}
	
    int graph[size][size];
	
	for(i=0;i < size; ++i){
		for(j=0;j < size; ++j){
      		graph[i][j]=0;
      	}
    }  
    size_t len2=0;
    ssize_t read2;

    char *token=NULL; 
     i=0;
     j=0;

     FILE * file_ptr_two;
	 file_ptr_two = fopen(args[1], "r");
     
	 while((read2=getline(&token, &len2, file_ptr_two))!=-1){
     	char *v;
		v=strtok(token,",");
		while(v){	
     		graph[i][j]=atoi(v);
     		j++;
			v=strtok(NULL,",");
     	}	
     	j=0;
     	i++;
     }
     kruskal(size,graph);
	fclose(ptr_file);
	fclose(file_ptr_two);
}