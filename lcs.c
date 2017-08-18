#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lcs(char *file_name){
	char c;
	int size=0;
	int size_one=0;
	int size_two=0;

  	FILE * file_ptr;
	file_ptr = fopen(file_name, "r");
	
  	if (file_ptr == NULL)
    {
    	printf("\nNo input file provided\n");
    	exit(EXIT_FAILURE);
    }else{
	    while((c=fgetc(file_ptr))!=EOF){
	    	if(c=='\n'){
				size_one=size-1;
	    		size=0;
	    	}
	    	size++;	
	    }
	}
	size_two=size-1;
	int max_size=size_one>size_two?size_one:size_two;

	char array[size];
	int i;
	char first_arr[size_one]; 
	int j=0;
	char second_arr[size_two];
	rewind(file_ptr);
	
	for(i=0;(c=fgetc(file_ptr))!=EOF; i++){
		array[i]=c;
		if(c=='\n'){
			memcpy(first_arr,array,size_one*sizeof(char));
			memset(array,'\0',max_size);
			i=-1;
		}
	}
	
	memcpy(second_arr,array,size_two*sizeof(char));
	fclose(file_ptr);

	printf("\nFirst String :");	
	
	for(i=0;i<size_one; i++){
		printf("%c",first_arr[i]);
	}

	printf("\n\nSecond String : ");	
	
	for(i=0;i<size_two;i++){
		printf("%c",second_arr[i]);
	}

	printf("\n\n");

	int lcs_matrix[size_one+1][size_two+1];
	int arrow_matrix[size_one+1][size_two+1];
	
	memset(lcs_matrix,0,(size_one+1)*(size_two+1)*sizeof(int));	

	
	for(i=0;i<(size_one+1);i++){
		lcs_matrix[i][0]=0;
	}

    for(j=0;j<(size_two+1);j++){
		lcs_matrix[0][j]=0;
	}
	
	
	for(i=1;i<=size_one;i++){
		for(j=1;j<=size_two;j++){
			if(first_arr[i-1]==second_arr[j-1])
			{
				lcs_matrix[i][j]=1+lcs_matrix[i-1][j-1];
				arrow_matrix[i][j]=1;
			}
			else{
				lcs_matrix[i][j]=lcs_matrix[i-1][j]>lcs_matrix[i][j-1]?lcs_matrix[i-1][j]:lcs_matrix[i][j-1];
			
				if(lcs_matrix[i][j]==lcs_matrix[i-1][j])
				{
					arrow_matrix[i][j]=-2;
				}
				else{
					arrow_matrix[i][j]=-1;
				}
			}
		}
	}

	i=size_one;
	j=size_two;
	int length=lcs_matrix[size_one][size_two];
	char final_result[length];	 
	LOOP:do{
		if(i==0 || j==0){
			break;
		}
		if(arrow_matrix[i][j]==1)
		{
			final_result[length-1]=first_arr[i-1];
		    i--;j--;
		    length--;
		    goto LOOP;
		}else if(arrow_matrix[i][j]==-2){
			i--;
			goto LOOP;
		}else{
		    j--;
			goto LOOP;
		}
	}while(length>0);

	printf("Longest Common Subsequence : ");
	
	
	for(i=0;i<lcs_matrix[size_one][size_two];i++){
		printf("%c",final_result[i]);
	}
	printf("\n\nLength of LCS : %d\n",lcs_matrix[size_one][size_two]);
}

int main(int argc, char *args[]){
	lcs(args[1]);
	printf("\n");
	return 0;
} 