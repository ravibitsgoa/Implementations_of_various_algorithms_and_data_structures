#define HT_INITIAL_BASE_SIZE 50

typedef struct 
{
    char* key;
    char* value;
} ht_item;

typedef struct 
{
    int size, count;    //size= total space in hash_table. count= number of stored ht_item(s).
    ht_item** item;
} hash_table;

hash_table* new_hash_table();

void del_hash_table(hash_table* ht);
//This function takes a pointer to a hash table, and deletes it.

void ht_insert(hash_table*  ht, const char* key, const char* value);
/*
 * Inserts {key, value} pair to given hash_table ht.
 * Does nothing if any one of these pointers is NULL.
 * If hash_table is more than 70% full, increase its size, upto next prime after its size.
 */

char* ht_search(const hash_table* ht, const char* key);
/*
 * Searches for given key in hash_table ht. If such a key exists, returns corresponding value.
 * If key does not exist in the hash_table, it returns NULL.
 * If either of the ht or key is NULL, it returns NULL.
 * This function will never modify given hash_table.
 */
 
int ht_delete(hash_table*  ht, const char* key);
/*
 * Deletes key-value pair with given key from hash_table ht.
 * If ht or key is NULL, returns 0.
 * If hash_table is less than 10% full, decreases its size to biggest prime less than current size.
 * Returns 1 on successful deletion, and 0 if key does not exist in the hash_table ht.
 */
 
//These commented functions are private ones:

//ht_item* new_ht_item(const char* k, const char* v);

//A factory function to create new hash_table of a given size.
//hash_table* new_hash_table_sized(int size);

//A factory function to create new hash_table of the default size.
//hash_table* new_hash_table();

//This function takes a pointer to a hash item, and deletes it.
//void del_ht_item(ht_item* i);

//This finds a^k % MOD in time O(log N). Fast modular exponentiation.
//long long power(const long long a, const long long k, const long long MOD);

//This private function generates hash for given string key.
//int gen_hash(const char* key, const int prime, const int num_buckets);

//This is a wrapper function around gen_hash, to reduce collisions by open addressing.
//int get_hash(const char* key, const int num_buckets, const int attempt);

//void resize(hash_table* ht, const int new_size);

//void resize_up(hash_table* ht);

//void ht_resize_down(hash_table* ht);