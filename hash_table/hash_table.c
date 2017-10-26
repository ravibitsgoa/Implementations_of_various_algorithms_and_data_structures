#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "hash_table.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};	//This is just a ghost item.

#ifndef HT_PRIME_1
	#include "prime.h"
#endif

//A factory function to create new ht_item.
ht_item* new_ht_item(const char* key, const char* value)
{
	if(key == NULL || value == NULL)
		return NULL;
		
    ht_item* i= malloc(sizeof(ht_item));
    i->key = malloc(sizeof(key));
    i->value = malloc(sizeof(value));
    strcpy(i->key, key);
    strcpy(i->value, value);
    return i;
}

//A factory function to create new hash_table of a given size.
hash_table* new_hash_table_sized(int size) 
{
	if(size<=0)
		return NULL;
		
	hash_table* ht = malloc(sizeof(hash_table));

	ht->size = next_prime(size);            
	ht->count = 0;              //Initially no elements are stored in hash_table.
	ht->item = calloc((size_t)ht->size, sizeof(ht_item*)); //To malloc + NULL in one go.
	return ht;
}

//A factory function to create new hash_table of the default size.
hash_table* new_hash_table() 
{
	return new_hash_table_sized(HT_INITIAL_BASE_SIZE); //Default size is 50.
}

//This function takes a pointer to a hash item, and deletes it.
void del_ht_item(ht_item* i) 
{
	if(i->key == NULL || i->value == NULL || i == NULL )
	{	//printf("hmm");	//Debugging statement to check for some bug.
	}
	else
	{
		free(i->key);
		free(i->value);
		free(i);		
	}
	i->key= NULL;
	i->value = NULL;
	i= NULL;
}

//This function takes a pointer to a hash table, and deletes it.
void del_hash_table(hash_table* ht)
{
	if(ht == NULL)	//If the hashtable is already deleted, return.
		return;
		
    for(int i=0; i<ht->size; i++)
	{
        if((ht->item)[i] != NULL)
		{
            del_ht_item((ht->item)[i]);
        }
    }
    free(ht->item);
    free(ht);
	ht->item = NULL;
	ht = NULL;
}

//This finds a^k % MOD in time O(log N). Fast modular exponentiation.
long long power(const long long a, const long long k, const long long MOD)
{
    if(k==0)	return 1;
    if(k==1)    return (a%MOD);
    if(k%2) 
	{
		long long x=power(a, (k-1)/2, MOD)%MOD; assert(x>=0);   x= (x*x)%MOD; return (a*x)%MOD;
	}
    else 
	{
		long long y=power(a, k/2, MOD)%MOD;     assert(y>=0);   y= (y*y)%MOD; return y;
	}
}

//This private function generates hash for given string key.
int gen_hash(const char* key, const int prime, const int num_buckets)
{
	assert(key!=NULL && prime>=5 && num_buckets>0);
	
	long long hash_val = 0;
	const int len = strlen(key);
	long long multiplier= power(prime, len-1, num_buckets);
	
	for(int i=0; i<len; i++)
	{
		hash_val += multiplier * (int)(key[i]);
		
		// multiplier = (a ** (string_len - (i+1)));
		multiplier /= prime;
		hash_val %= num_buckets;
	}
	
	hash_val %= num_buckets;
	return (int)hash_val;
}

//This is a wrapper function around gen_hash, to reduce collisions by open addressing.
int get_hash(const char* key, const int num_buckets, const int attempt)
{
	if(key==NULL || num_buckets<=0 || attempt<0)
		assert(0);
		
	const int hash_a = gen_hash(key, HT_PRIME_1, num_buckets);
	const int hash_b = gen_hash(key, HT_PRIME_2, num_buckets);
	return (hash_a + (attempt*(hash_b + 1))) % num_buckets;
}

void resize(hash_table* ht, const int new_size)
{
	if(ht == NULL || new_size<=0)
		return;
	
	if(ht->size <= HT_INITIAL_BASE_SIZE ) //Hash table is already smaller than default size.
		return;
	hash_table * new_ht = new_hash_table_sized(new_size); //made a new hash_table of given size.
	for(int i=0; i<ht->size; i++)
	{
		ht_item* item = ht->item[i];	//We insert all non-null items to the new hashtable.
		if(item != NULL && item!= &HT_DELETED_ITEM)
		{
			ht_insert(new_ht, item->key, item->value);
		}
	}
	ht->count = new_ht->count;
		
	// To delete new_ht, we give its ht's size and items with those of new_ht.
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->item;
    ht->item = new_ht->item;
    new_ht->item = tmp_items;

    del_hash_table(new_ht);
}

void resize_up(hash_table* ht) 
{
	if(ht == NULL)
		return;
    const int new_size = ht->size * 2;
    resize(ht, new_size);
}


void ht_resize_down(hash_table* ht) 
{
	if(ht == NULL)
		return;
    const int new_size = ht->size / 2;
    resize(ht, new_size);
}

void ht_insert(hash_table* ht, const char* key, const char* value)
{
	if(ht== NULL || key==NULL || value == NULL)
		return;
		
	//If hash_table is more than 70% full, increase its size.
	const int load = (ht->count * 100) / ht->size;
	if(load >= 70) 
	{
		resize_up(ht);
	}
	
	ht_item* this_item = new_ht_item(key, value);
	for(int i=0; 1; i++)
	{	printf("%d", i);		//debugging statements.
		int hash_val = get_hash(key, ht->size, i);
		ht_item* cur_item = (ht->item)[hash_val];
		if(cur_item == NULL || cur_item == &HT_DELETED_ITEM)
		{
			(ht->item)[hash_val] = this_item;
			break;
		}
		//printf("%s %s ", cur_item->key, cur_item->value);
		if(strcmp(cur_item->key, key) == 0)	//If a given key already exists, and we're overwriting it.
		{	cur_item->value = malloc(sizeof(value));
			strcpy(cur_item->value, value);
			break;
		}
	}
	(ht->count) ++;
}

char* ht_search(const hash_table* ht, const char* key)
{	
	if(ht == NULL || key == NULL)
		return NULL;
		
	for(int i=0; 1; i++)
	{
		//printf("%d", i);		//debugging statements.
		int hash_val = get_hash(key, ht->size, i);
		//printf("%d", hash_val);
		//fflush(stdout);
		
		ht_item* this_item = (ht->item)[hash_val];
		
		if( this_item == NULL || this_item == &HT_DELETED_ITEM)
			return NULL;
		
		else if( strcmp(this_item->key, key) ==0 )
			return this_item->value;
	}
	//assert(0);	//control should never reach here.
}

int ht_delete(hash_table* ht, const char* key)
{
	if(ht==NULL || key==NULL)
		return 0;
		
	//If hash_table is less than 10% full, decrease its size.
	const int load = (ht->count * 100) / ht->size;
	if(load <= 10) 
		ht_resize_down(ht);
	
	for(int i=0; 1; i++)
	{
		int hash_val = get_hash(key, ht->size, i);
		//printf("%d %d", i, hash_val);
		//fflush(stdout);
		//return 0;
		
		ht_item* this_item = (ht->item)[hash_val];
		if( this_item == NULL || this_item == &HT_DELETED_ITEM)	//No such key is found in hash table.
			return 0;
		
		else //if( this_item != &HT_DELETED_ITEM)
		{	if( strcmp(this_item->key, key) ==0 )
			{
				//printf("%s %s",key, this_item->value);
				del_ht_item(this_item);
				(ht->item)[hash_val]= &HT_DELETED_ITEM;
				(ht->count)--;
				return 1;
			}
		}
	}
	//assert(0);	//control should never reach here. If it does, there is some bug.
}