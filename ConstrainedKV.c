#include "kv.h" 
#include <string.h> 
#include <stdint.h> 
#include <stdlib.h>

int FNV1A(char* data, int len){ //Algorithm for hash function

	int hash = FNV_OFFSET_BASIS; 
	int i; 

	for(i = 0; i<len; i++){
		hash = (hash ^ data[i]) * FNV_PRIME; // XOR each byte of data by FNV_OFFSET_BASIS then multiply by the FNV_PRIME value 
		hash = hash & 0xFFFFFFFF;
	} 
	
	return hash; 
	
}
int HT_HASH(char* key){
	
	uint32_t hash = FNV1A(key,strlen(key)); 
	return hash % HTSIZE; // To return the convert the hash into an index, use the modulus operator coupled with the number of bytes in the table

}
void HT_INIT(HT* ht){	
	ht -> count = 0; // Initializes the hashtable count to 0 
	int i;
	for(i = 0; i<HTSIZE; i++){
		ht->items[i].occupied = 0;  // Initializes each hashtable item as unoccupied 
	} 
} 
int HT_INSERT_KV(HT* ht, char* k, char* v){
	int index = HT_HASH(k);  // Hash to get index
	for (int i = 0; i < HTSIZE; i++) {
        	int try = (index + i) % HTSIZE; // Linear probing to avoid collisions 
		if (!ht->items[try].occupied || strncmp(ht->items[try].key, k, KEYSIZE) == 0) { // "If item is not occupied or key matches parameter" 
			
			memcpy(ht->items[try].key, k, KEYSIZE-1); // Copy key and value into hashtable item as raw bytes
			memcpy(ht->items[try].value, v, VALSIZE-1); 

            		ht->items[try].occupied = 1; // Set the item as occupied
					
            		return 0;	// NOTE: This same scheme exists across all write operations
        	}
    	}
	return -1; 
}
int HT_OVERWRITE_K(HT* ht, char* k, char* nk){
	int index = HT_HASH(k); 
	for(int i = 0; i<HTSIZE; i++){
		int try = (index+i) % HTSIZE; 
		if(ht->items[try].occupied && strncmp(ht->items[try].key, k, KEYSIZE-1) == 0){
			memset(&ht->items[try].key, 0, KEYSIZE-1); // Clear the key buffer in hashtable item 
			memcpy(ht->items[try].key, nk, KEYSIZE-1); // Copy new key as raw bytes
		} 
	}
	return 0;	// NOTE: This scheme exists across both overwrite operations
} 
int HT_OVERWRITE_V(HT* ht, char* v, char* nv){
	int index = HT_HASH(v); 
	for(int i = 0; i<HTSIZE; i++){
		int try = (index+i) % HTSIZE; 
		if(ht->items[try].occupied && strncmp(ht->items[try].value, v, VALSIZE-1) == 0){
			memset(&ht->items[try].key, 0, VALSIZE-1); 
			memcpy(ht->items[try].key, nv, VALSIZE-1); 
		} 
	}
	return 0;
}
int HT_POP_ITEM(HT* ht, int i){
	ht->items[i].occupied = 0; // Set the item as unoccupied 
	memset(&ht->items[i], 0, sizeof(ht->items[i])); // Clear the item
	ht->count -= 1; // Decrement count 
	return 0; 
} 
char* HT_GET_V(HT* ht, char* k){
	int index = HT_HASH(k); 
	
	for(int i = 0; i<HTSIZE; i++){
		int try = (index + i) % HTSIZE;
		if(ht->items[try].occupied && strncmp(ht->items[try].key, k, KEYSIZE-1) == 0){ // "if item is occupied and key matches parameter" 
			return ht->items[try].value; 
		} 
	} 

	return 0;
} 
int HT_GET_V_ASINT(HT* ht, char* k){
	int index = HT_HASH(k); 
	
	for(int i = 0; i<HTSIZE; i++){
		int try = (index + i) % HTSIZE;
		if(ht->items[try].occupied && strncmp(ht->items[try].key, k, KEYSIZE-1) == 0){
			return strtol(ht->items[try].value, NULL, VALSIZE); // Same scheme as HT_GET_V(), only with conversion for a long integer instead of char* 
		} 
	} 

	return 0;
} 
int HT_GET_V_ASFLOAT(HT* ht, char* k){
	int index = HT_HASH(k); 
	
	for(int i = 0; i<HTSIZE; i++){
		int try = (index + i) % HTSIZE;
		if(ht->items[try].occupied && strncmp(ht->items[try].key, k, KEYSIZE-1) == 0){
			return strtof(ht->items[try].value, NULL); // Same scheme as HT_GET_V(), only with conversion for a float instead of char* 
		} 
	} 

	return -1;
} 
int HT_SBK(HT* ht, char* k){
	int i; 
	for(i=0; i<HTSIZE; i++){ 
		if(ht->items[i].occupied && strncmp(ht->items[i].key, k, KEYSIZE-1)==0){ // "If item is occupied and key matches parameter"
			return i; // Return index of key
		} 
	} 
	return -1;
} 
int HT_SBV(HT* ht, char* v){
	int i; 
	for(i=0; i<HTSIZE; i++){ 
		if(ht->items[i].occupied && strncmp(ht->items[i].value, v, VALSIZE-1)==0){ // "If item is occupied and value matches parameter" 
			return i; // Return index of value 
		} 
	} 
	return -1;
} 
int main(){ 
	
	HT ht; 
	HT_INIT(&ht);
} 
