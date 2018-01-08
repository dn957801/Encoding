#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct linked_list
{
	int data;
	struct linked_list *next;
}list;

list *head=NULL, *ptr=NULL, *prev = NULL;

void insert( int value)
{
	ptr = (list *)malloc(sizeof(list));
	ptr->data = value;
	ptr->next = NULL;
	
	if(head == NULL)
	{
		head  = ptr;
		return;
	}
	else
	{
		prev = head;
		while(prev->next != NULL)
			prev = prev->next;

		prev->next = ptr;
	}
}

list* insert_in_middle (list *prev)
{
	list *ptr;

	ptr = (list *)malloc(sizeof(list));
	ptr->data = 0;
	ptr->next = prev->next;
	prev->next = ptr;

	return ptr;

}

void display_list()
{
	list *ptr;
	printf("DISPLAYING CURRENT LIST : \n");
	for(ptr = head; ptr != NULL; ptr=ptr->next)
	{
		printf(" %d",ptr->data);
	}
	printf("\n");
}

list* delete_zeroth_node( list *prev)
{
	list *ptr;
	if(head == NULL)
	{
		printf("Can't delete, as list is empty\n");
		return NULL;
	}

	if(prev != NULL && prev->next != NULL)
	{
		ptr = prev->next;
		prev->next = prev->next->next;	
		free(ptr);
		return (prev->next);
	}
	else
	{
		printf("PREV PTR is NULL. Can't delete anything\n");
		return NULL;
	}

}


int main()
{
	short bit = 0;
	int c=0, ch1=0, bptr[8], i=0;
	char ch, cptr[8],ch2,letter[8],letter1;
	FILE *ptr1,*ptr2,*ptr3,*ptr4;
	list *ptr, *new_node, *temp;
	int *digit;
	char *file_name1 = "/home/dinesh/Downloads/Networking_Assignment_2/C_Programming/bit_stuffing/file11.txt";
	char *file_name2 = "/home/dinesh/Downloads/Networking_Assignment_2/C_Programming/bit_stuffing/file21.txt";
	char *file_name3 = "/home/dinesh/Downloads/Networking_Assignment_2/C_Programming/bit_stuffing/file31.txt";
	char *file_name4 = "/home/dinesh/Downloads/Networking_Assignment_2/C_Programming/bit_stuffing/file41.txt";
	
	ptr1 = fopen(file_name1,"r");
	if(ptr1 == NULL){
		printf("unable to open file1\n");
		return -1;
	}

	
	if( (ptr2=fopen(file_name2, "w")) == NULL ) {
		printf("Cannot open file2.txt\n");
		return -1;
	}

	if( (ptr3=fopen(file_name3, "w")) == NULL ) {
		printf("Cannot open file3.txt\n");
		return -1;
	}

	if( (ptr4=fopen(file_name4, "w")) == NULL ) {
		printf("Cannot open file4.txt\n");
		return -1;
	}
	
	while((ch=fgetc(ptr1)) != EOF) {
		ch1=ch; 
		for(c=7;c>=0;c--) {
			bptr[c] = ch1 & 1;
			bit = ch1 & 1;
			ch1 = ch1 >> 1;
		}

		for(c=0;c<=7;c++)
		{
			insert(bptr[c]);	
		}	
		for(i=0;i<8;i++) 
			fprintf(ptr3,"%d",bptr[i]);

		fputc(ch,ptr2);
	}

	/* Done with inserting all characters into list */
	/* Now start traversing through the list */
	printf("Firstly displaying the list contents\n");
	display_list();

	for(ptr=head;ptr!=NULL && ptr->next !=NULL;)
	{
		if ((ptr->next->next != NULL) &&
		    (ptr->next->next->next != NULL) &&
		    (ptr->next->next->next->next != NULL) )
		{
			if( (ptr->data == 1) &&
			    (ptr->next->data == 1) &&
			    (ptr->next->next->data == 1) &&
			    (ptr->next->next->next->data == 1) &&
			    (ptr->next->next->next->next->data == 1) )
			{
				/* we hit the case , 5 consecutive ones */
				new_node = insert_in_middle (ptr->next->next->next->next);
				ptr = new_node->next;
				continue;
			}
		}

		ptr = ptr->next;	

	}


	printf("\n******************\n");
	printf("PRINTING LIST AFTER INSERTING ZERO\n");
	for(ptr = head; ptr!=NULL; ptr=ptr->next)
		printf(" %d", ptr->data);

	printf("\n");

	
	/* decoding and removing zeros */
	for(ptr=head;ptr!=NULL && ptr->next!=NULL;)
	{
		if ((ptr->next->next != NULL) &&
		    (ptr->next->next->next != NULL) &&
		    (ptr->next->next->next->next != NULL) &&
		    (ptr->next->next->next->next->next != NULL) ) 
		{

			if( (ptr->data == 1) &&
		    	    (ptr->next->data == 1) &&
	    	    	    (ptr->next->next->data == 1) &&
		    	    (ptr->next->next->next->data == 1) &&
		    	    (ptr->next->next->next->next->data == 1) && 
		    	    (ptr->next->next->next->next->next->data == 0) )
	        	{
				/* we hit the case, 5 consecutive ones and then a zero */
				ptr = delete_zeroth_node (ptr->next->next->next->next);
				continue;
			}
		}
		ptr = ptr->next;
	}	

	printf("\n*************************\n");
 	printf("PRINTING LIST AFTER REMOVING ZERO\n");
	for(ptr = head; ptr!=NULL;ptr=ptr->next)
		printf(" %d",ptr->data);
	printf("\nDONE WITH PRINTING\n");

	/* Converting bits into letters */
	c = 0;
	for(ptr=head;ptr!=NULL;)
	{
		c = 0;
	        for(i=7;i>=0;i--)
	        {       
	                cptr[i]=(char)ptr->data;
			c += (ptr->data) * (pow(2, i));
			ch = (char)c;
			ptr=ptr->next;
	        } 
	        fputc(c,ptr4);	

	}
	printf("\n");

	/* free remaining nodes of list */
	for(ptr = head; ptr != NULL; )
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}

	fclose(ptr1);
	fclose(ptr2);
	fclose(ptr3);
	fclose(ptr4);

	return 1;
}