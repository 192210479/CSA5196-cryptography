#include<stdio.h>
int main()
{
	int rows,cols,i,j,a[100][100];
	printf("enter rows");
	scanf("%d",rows);
	printf("enter cols");
	scanf("%d",cols);
	printf("enter elements of the matrix");
	for(i=0;i<rows;i++)
	{
	 for(j=0;j<cols;j++)
	 {
	 	scanf("%d",a[i][j]);
	 }
	}
	
	for(i=0;i<rows;i++)
	{
	 for(j=0;j<cols;j++)
	 {
	 printf("%d",a[i][j]);
	 }
	}
}
