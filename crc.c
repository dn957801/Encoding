#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	
	char *mx = (char *)malloc(50*sizeof(char));
	int gx[] = {1,0,0,1,0};
	char *px = (char *)malloc(50*sizeof(char));
	char *rx = (char *)malloc(50*sizeof(char));
	char *m_x = (char *)malloc(50*sizeof(char));
	int *ptr = NULL;
	int *ptr1;
	int degree = 4, i=0, j=0, n=0;
	int size_ptr_array = 0, latest_size=0;
	char *c,ch='N';

	printf("Enter the bit string m(x) : \t");
	scanf("%s",mx);

	printf("\nEntered bit string m(x) is = %s\n",mx);

	printf("g(x) already defined is : %d%d%d%d%d\n",gx[0],gx[1],gx[2],gx[3],gx[4]);

	strcpy(m_x,mx);
	
	c = m_x;
	while(*c != '\0')
		c++;

	/* c is pointing to null character */
	for( i=0;i<degree;i++) {
		*c++ = '0';
	}
	*c = '\0';

	printf("After appending degree = %d zeros, m_x is : %s\nAnd the original message is still same mx = %s\n",degree,m_x,mx);


	/* now convert m_x to integer array to perform long division */
	/* Anyways, contents are either 0s or 1s, hence it is easy */
	
	ptr = (int *)malloc(50*sizeof(int));
	
	for(i=0;i<(strlen(m_x));i++)
	{
		if(m_x[i] == '1')
			ptr[i]=1;
		else
			ptr[i]=0;

		size_ptr_array++;
	}

	/* LONG DIVISION */

	latest_size=size_ptr_array;

	for (i=0;((i<size_ptr_array) && (latest_size > degree)) ;i++)
	{
		if( ptr[0] == 1 )  
		{
			for (j=0;j<=degree;j++)
			{
				ptr[j] = ptr[j] ^ gx[j];
			}
			
		}	

		latest_size--;
		for(n=0;n<(size_ptr_array - i);n++)
		{
			ptr[n]=ptr[n+1];
		}
		ptr[n+1]='\0';
	}

	/* Prepare p(x) containing both mx and ptr[] array */

	strcpy(px,mx);
	c=px;
	while( *c != '\0')
		c++;
	for(i=0;i<latest_size;i++)
	{
		if(ptr[i] == 0)
			c[i] = '0';
		else
			c[i] = '1';

	}
	c[i]='\0';

	printf("\n*********************************\n");
	printf("FINAL ARRAY TO SEND OUT P(X) = %s\n",px);

	strcpy(rx,px);

	printf("Do you want to insert any error ? Y/N : ");
	scanf(" %c", &ch);

	if(ch == 'Y' | ch == 'y')
	{
		printf("\nSo, you want to insert error\n");
		printf("Please enter the bit string you want to test\n");
		scanf("%s",rx);

		printf("Bit string you have entered is : %s\n",rx);
	}
	else
	{
		printf("\n Ok, so let's proceed with calculated bit string\n");
	}

	size_ptr_array = 0;
	latest_size = 0;
	ptr1 = (int *)malloc(50*sizeof(int));

	for(i=0;i<(strlen(rx));i++)
	{
		if(rx[i] == '1')
			ptr1[i] = 1;
		else
			ptr1[i] = 0;

		size_ptr_array++;
	}

	latest_size = size_ptr_array;

	/* Long division of output received */
	for(i=0;((i<size_ptr_array) && (latest_size > degree));i++)
	{
		if(ptr1[0] == 1)
		{
			for(j=0;j<=degree;j++)
			{
				ptr1[j] = ptr1[j] ^ gx[j];
			}
		}
		latest_size--;
		for(n=0;n<(size_ptr_array - i);n++)
		{
			ptr1[n]=ptr1[n+1];
		}
		ptr1[n+1]='\0';

	}

	printf("\n*********************************************\n");
	printf("\nAfter long division, the resultant array is ");
        for(i=0;i<latest_size;i++)
        {
                printf("%d",ptr1[i]);
        }

	printf("\n");

	printf("TESTING FOR ERROR\n");
	for(i=0;i<latest_size;i++)
	{
		if(ptr1[i] != 0)
		{
			printf("ERROR IN CRC DECODING\n");
			exit(1);
		}

	}
	printf("NO ERROR IN CRC DECODING\n");

	free(mx);
	free(px);
	free(m_x);
	free(ptr);
	
	return 0;
}
