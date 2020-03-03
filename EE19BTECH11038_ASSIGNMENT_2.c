#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	int value;
	struct node* row;
	struct node* coloumn;
}node;

int no_of_rows(char *str)
{
	char *p;
	int i=0;
	p = strtok(str,";");
	while(p!=NULL)
	{
		p = strtok(NULL,";");
		i++;
	}
	return i;
}

int total_elements(char *str)
{
	char *p;
	int j =0;
	p = strtok(str,",;");
	while(p!=NULL)
	{
		p=strtok(NULL,",;");
		j++;
	}
	return j;
}
int no_of_coloumns(char *str)
{

	char *p;
	int j =0;
	p = strtok(str,",");
	while(p!=NULL)
	{
		p=strtok(NULL,",");
		j++;
	}
	return j;
}
	

char *file_to_str(char *filename)
{
	FILE *fptr; 
    char c,str[100],*s; 
    fptr = fopen("matrix.dat", "r"); 
    if (fptr == NULL) 
    { 
        printf("Cannot open file \n"); 
        exit(0); 
    } 
  
    // Read contents from file 
    c = fgetc(fptr); 
    int i =0;
    while (c != EOF) 
    { 
		str[i] = c;
        c = fgetc(fptr); 
        i++;
    }
    fclose(fptr); 
    s = str;
    return s; 
}
char *row_from_file(char *filename,int row)
{	
	char *mat = file_to_str(filename);
	char *p,*temp;
	temp = mat;
	
	p = strtok(temp,";");
	if( row !=0)
	{
	for(int i =0;i<row;i++)
	{
		p = strtok(NULL,";");
	}
	}
	return p;
}

int element_from_file(char *filename,int row,int coloumn)
{
	char *r_str = row_from_file(filename,row);
	char *p,*temp;
	temp = r_str;

	p = strtok(temp,",");
	if( coloumn !=0)
	{
	for(int i =0;i<coloumn;i++)
	{
		p = strtok(NULL,",");
	}
	}
	return atoi(p);
}

void print_row(node* list)
{
	//printf("The list is:\n");
	while(list != NULL)
	{
		printf("%d  ",list->value);
		list = list->row;
	}
}

void print_coloumn(node* list)
{
	//printf("The list is:\n");
	while(list != NULL)
	{
		printf("%d\n",list->value);
		list = list->coloumn;
	}
}

node* row_list(char *filename,int i)
{
	node* head = NULL;
	node* temp = NULL;
	node* add = NULL;

	for(int j =0;j<no_of_coloumns(row_from_file(filename,0));j++)
	{
		temp = (node*)malloc(sizeof(node));
		temp->value=element_from_file(filename,i,j);
		if(head == NULL)
		{
			temp->coloumn=NULL;
			head = temp;
			add = head;
		}
		else
		{
			add->row = temp;
			temp->coloumn = NULL;
			add=add->row;
		}
	}
	temp->row = NULL;
	return head;
}

void link_row(node* row1,node* row2)
{
	static node* trav_row1 = NULL;
	static node* trav_row2 = NULL;
	trav_row1 = (node*)malloc(sizeof(node));
	trav_row2 = (node*)malloc(sizeof(node));
	trav_row1 = row1;
	trav_row2 = row2;
	while(trav_row1 != NULL)
	{
		trav_row1->coloumn = trav_row2;
		//printf("%d\n",trav_row1->coloumn->value);
		//trav_row2->coloumn = NULL;
		trav_row1 = trav_row1->row; 
		trav_row2 = trav_row2->row;
	}
}
int coloumn_len(node* list)
{
	struct node* temp = NULL;
	int i=1;
	temp = list;
	while(temp->row != NULL)
	{
		i = i+1;
		temp = temp->row;
	}
	return i;
}

int row_len(node* list)
{
	struct node* temp = NULL;
	int i=1;
	temp = list;
	while(temp->coloumn != NULL)
	{
		i = i+1;
		temp = temp->coloumn;
	}
	return i;
}

node* extract_row_from_matrix(node* matrix,int row)
{
	node* temp = NULL;
	temp = matrix;

	for(int i=0;i<(row+1);i++)
		temp = temp->coloumn;
	while(temp != NULL)
	{
		temp->coloumn = NULL;
		temp = temp->row;
	}
	temp = matrix;
	return temp;
}
int dot_product(node* row,node* col)
{
	node* trav_row = NULL;
	node* trav_coloumn = NULL;
	int product = 0;
	trav_row = row;
	trav_coloumn = col;
	int r = row_len(row);
	int c = coloumn_len(col);
	if(r == c)
	{
		while(trav_row != NULL)
		{
			product +=(trav_row->value)*(trav_coloumn->value);
			trav_row = trav_row->row;
			trav_coloumn = trav_coloumn->coloumn;
		}
	return product;
	}
	else
	{
		printf("Improper Diemensions.\n");
		return 0;
	}
}

void recur_link_row(node* prev,node* row)
{
	static node* trav = NULL;
	static node* trav_row = NULL;
	trav = (node*)malloc(sizeof(node));
	trav_row = (node*)malloc(sizeof(node));
	trav = prev;
	trav_row = row;
	while(trav != NULL)
		trav = trav->coloumn;
	while(trav != NULL)
	{
		trav->coloumn = trav_row;
		//printf("%d\n",trav_row1->coloumn->value);
		//trav_row2->coloumn = NULL;
		trav = trav->row; 
		trav_row = trav_row->row;
	}
	//return prev;
}

void square_check(char* filename,node* matrix)
{
	if(filename == NULL)
	{
	if(row_len(matrix) == coloumn_len(matrix))
		printf("Given matrix in %s is a square matrix.\n",filename);
	 
	else
		printf("Given matrix in %s is not a square matrix.\n",filename);
	}
	else
	{
	if(row_len(matrix) == coloumn_len(matrix))
		printf("Given matrix is a square matrix.\n");
	 
	else
		printf("Given matrix is not a square matrix\n");
	}
}

node* Matrix(char *filename)
{
	int rows = no_of_rows(file_to_str(filename));
	static node* head = NULL;
	static node* temp_head = NULL;
	static node* row = NULL;
	static node* temp_row = NULL;
	static node* add = NULL;
	head = row_list(filename,0);
	temp_head = head;
	for(int i =0;i<(rows-1);i++)
	{
		row = row_list(filename,i+1);
		
		if(i == 0)
		{
			temp_row = row;
			while(temp_head != NULL)
			{
				temp_head->coloumn = temp_row;
				temp_row->coloumn = NULL;
				temp_head =temp_head->row; 
				temp_row =temp_row->row; 
			}
			add = row;
		}
		else
		{
			temp_head = add;
			temp_row = row;
			while(temp_head != NULL)
			{
				temp_head->coloumn = temp_row;
				temp_row->coloumn = NULL;
				temp_head =temp_head->row; 
				temp_row =temp_row->row; 
			}
			add = row;
		}	
	}
	for(int j=0;j<(rows-1);j++)
		free(row_list(filename,j));
	//print_coloumn(head);
	return head;
}

//~ node* transpose(node* matrix)
//~ {
	//~ node** ROW = NULL;
	//~ node* head = matrix;

node* CreateMatrix(char *matrix)
{
		int rows = no_of_rows(file_to_str(filename));
	static node* head = NULL;
	static node* temp_head = NULL;
	static node* row = NULL;
	static node* temp_row = NULL;
	static node* add = NULL;
	head = row_list(filename,0);
	temp_head = head;
	for(int i =0;i<(rows-1);i++)
	{
		row = row_list(filename,i+1);
		
		if(i == 0)
		{
			temp_row = row;
			while(temp_head != NULL)
			{
				temp_head->coloumn = temp_row;
				temp_row->coloumn = NULL;
				temp_head =temp_head->row; 
				temp_row =temp_row->row; 
			}
			add = row;
		}
		else
		{
			temp_head = add;
			temp_row = row;
			while(temp_head != NULL)
			{
				temp_head->coloumn = temp_row;
				temp_row->coloumn = NULL;
				temp_head =temp_head->row; 
				temp_row =temp_row->row; 
			}
			add = row;
		}	
	}
	for(int j=0;j<(rows-1);j++)
		free(row_list(filename,j));
	//print_coloumn(head);
	return head;

		
node** extract_rows_from_matrix(node* matrix)
void printMatrix(node* matrix)
{
	node* temp = matrix;
	//print_row(matrix);
	while(temp != NULL)
	{
		print_row(temp);
		printf("\n");
		temp = temp->coloumn;
	}
}

void print_dimension(node* matrix)
{
	printf("(%d,%d)\n",row_len(matrix),coloumn_len(matrix));
}
	

int main() 
{ 
node* mat = NULL;
node* pe = NULL;
mat = Matrix("matrix.dat");
printMatrix(mat);
print_dimension(mat);
square_check(NULL,mat);
//pe = extract_row_from_matrix(mat,1);
print_row(mat->coloumn);
}
