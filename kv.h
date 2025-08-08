#pragma once 

#define KEYSIZE 32
#define VALSIZE 64
#define HTSIZE 128 

#define FNV_OFFSET_BASIS 0x811c9dc5
#define FNV_PRIME 0x01000193

typedef struct HT_ITEM { // Hashtable Item struct
	char key[KEYSIZE]; 
	char value[VALSIZE]; 
	int occupied; 
} HT_ITEM; 

typedef struct HT { // Hashtable struct
		
	HT_ITEM items[HTSIZE];
	int count; 

} HT; 

void HT_INIT(HT* ht);
int HT_INSERT_KV(HT* ht, char* k, char* v);
int HT_OVERWRITE_K(HT* ht, char* k, char* nk);
int HT_OVERWRITE_V(HT* ht, char* v, char* nv);
int HT_POP_ITEM(HT* ht, int i);
char* HT_GET_V(HT* ht, char* k);
int HT_GET_V_ASINT(HT* ht, char* k);
int HT_GET_V_ASFLOAT(HT* ht, char* k);
int HT_SBK(HT* ht, char* k);
int HT_SBV(HT* ht, char* v);
