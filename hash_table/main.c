#include <stdio.h>
#include <string.h>
#include "hash_table.h"
#define MAXLEN 255		//Hashtable actually supports arbitrarily long strings.

int main()
{
	printf("Operations:\n");
	printf("1. Insert a key, value pair. \ne.g. 1 abc\ndef\n");
	printf("2. Delete a key-value pair, by key.\ne.g. 2 abc\n");
	printf("3. Search a value for a key.\n");
	printf("0. To exit the program.\n");
	printf("Key and value cannot be more than 255 characters long.\n");
    hash_table* ht = new_hash_table();
    int choice=1;
	while(choice != 0) 
	{
		char key[MAXLEN+1];
		char value[MAXLEN+1];
	
		scanf("%d ", &choice);
		if(choice == 0)
			break;
			
		fgets(key, MAXLEN, stdin);
		key[MAXLEN]='\0';	//To truncate input after MAXLEN.
		key[strlen(key)-1]='\0';	//To truncate string after it's actual length.
				
		if(choice==1) 
		{
			fgets(value, MAXLEN, stdin);
			value[MAXLEN]='\0';
			value[strlen(value)-1]='\0';
			char *valForThisKey =ht_search(ht, key);
			if(valForThisKey)
			{	printf("%s, %s pair exists in the hashtable.\nDo you want to overwrite it? [Y/N]", key, valForThisKey);
				char c='a';
				while(c!='Y' && c!='N')
					scanf("%c",&c);
				if(c=='N')
					continue;
			}
			ht_insert(ht, key, value);
			printf("%s, %s is inserted into the hashtable.\n", key, value);
		}
		else if(choice == 2) 
		{
			if(ht_delete(ht, key) == 1) 
				printf("value corresponding to %s is deleted.\n", key);
			else
				printf("%s key doesn't exist in the hashtable.\n", key);
		}
		else if(choice == 3) 
		{
			char *val= ht_search(ht, key);
			if(val == NULL)
				printf("%s key doesn't exist in the hashtable.\n", key);
			else
				printf("%s, %s exists in the hashtable.\n", key, val);
		}
		else 
		{
			printf("enter choice properly.");
		}
	}
	del_hash_table(ht);
	return 0;
}
