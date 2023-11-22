#include<stdio.h>
int main()
{
	int in,out,n,i,temp;
	printf("enter a number");
	scanf("%d",&n);
	for (out=0;out<n;out++)
	{
		scanf("%d",&out);
	}
		for (out=0;out<n;out++)
		{
			for (in=out+1;in<n;in++)
			{
				if (out>in)
				{
					temp=out;
				out=in;
					in=temp;
				}
			}
		}
		for (out=0;out<n;out++)
		printf("%d\n",out);
		return 0;
}
