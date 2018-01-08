#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{

	char *str1 = (char *)malloc(1000*sizeof(char));
	char ch1,ch2[2],prev='y';
	short i=0,j=0,c=0,bptr[8];
	int len1=0,len2=0,transition=0,length=0;
	FILE *p,*p1;
	char letter;
	char *file_name1 = "/home/dinesh/Downloads/Networking_Assignment_2/C_Programming/encoding/file1.txt";
	char *file_name2 = "/home/dinesh/Downloads/Networking_Assignment_2/C_Programming/encoding/file2.txt";

	p = fopen(file_name1,"r");
	if(p == NULL){
		printf("Unable to open the file1\n");
		return -1;
	}

	p1 = fopen(file_name2,"w+");
	if(p1 == NULL){
		printf("Unable to open the file\n");
		return -1;
	}

	while( (letter=fgetc(p)) != EOF) {
		c = letter;
		if(c != 10) {
			length++;
			for(c=7;c>=0;c--) {
				bptr[c] = letter & 1;
				letter = letter >> 1;
			}
			for(c=0;c<8;c++)
				fprintf(p1,"%d",bptr[c]);
		}

	}

	len1 = length;

	printf("**************\n");
	printf("NRZ Encoding\n");
	printf("**************\n");
	
	fseek(p1,0,SEEK_SET);
	while( (ch1=fgetc(p1)) != EOF )
	{
		switch(ch1)
		{
			case '1' : printf("---"); 
				   if(prev == '0')
					   transition++;

				   prev = '1';
			   	   break;

			case '0' : printf("___"); 
				   if(prev == '1')
					   transition++;
				   
				   prev = '0';
			       	   break;

			defeault : break;

		}
	}

	printf("\n\n\n\nTotal number of transitions in NRZ Encoding = %d",transition);

	printf("\n\n\n\n\n");

	printf("*******************\n");
	printf("Manchester Encoding\n");
	printf("*******************\n");

	fseek(p1,0,SEEK_SET);
	while( (ch1=fgetc(p1)) != EOF )
	{
		str1[i++] = ch1;
	}

	len2 = strlen(str1);
	transition = 0;
	prev = 'y';
	while(len2 != 0)
	{
		ch2[0] = str1[j];
		if(len2 > 1) {
			ch2[0] = str1[j];
			ch2[1] = str1[j+1];

			if( ch2[0] == '0' && ch2[1] == '0')
			{
				printf("-|_|-|_");
				if(prev == '0')
					transition += 4;
				else
					transition += 3;

				prev = '0';
		
			}
			else if(ch2[0] == '0' && ch2[1] == '1')
			{
				printf("-|__|-");
				if(prev == '0')
					transition += 3;
				else
					transition += 2;
				
				prev = '1';

			}
			else if(ch2[0] == '1' && ch2[1] == '0')
			{
				printf("_|--|_");
				if(prev == '1')
					transition += 3;
				else
					transition += 2;
				
				prev = '0';

			}
			else if(ch2[0] == '1' &&  ch2[1] == '1')
			{
				printf("_|-|_|-");
				if(prev == '1')
					transition += 4;
				else
					transition += 3;
				
				prev = '1';

			}
		}
		else
		{
			if(ch2[0] == '0')
			{
				printf("-|_");
				if(prev == '0')
					transition += 2;
				else
					transition += 1;
			}
			else
			{
				printf("_|-");
				if(prev == '1')
					transition += 2;
				else
					transition += 1;
			}
		}

		if(len2 >1)
		{
			len2--;
			len2--;
		}
		else
		{
			len2--;
		}

		if(len2 == 1)
		{
			j = j+1;
		}
		else
		{
			j=j+2;
		}

	} 
	printf("\n\n\n");
	printf("Total number of transitions in Manchester Encoding : %d\n\n\n",transition);

	return 0;	

}
