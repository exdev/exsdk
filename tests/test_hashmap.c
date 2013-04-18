// ======================================================================================
// File         : test_hashmap.c
// Author       : Wu Jie 
// Last Change  : 04/18/2013 | 10:22:50 AM | Thursday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

int main (void) {
    ex_hashmap_t *hashmap1, *hashmap2;
    int i = 0;

    ex_sdk_init ();

    hashmap1 = ex_hashmap_alloc ( sizeof(int), sizeof(float),
                                  4096,
                                  ex_hashkey_int, ex_keycmp_int );
    hashmap2 = ex_hashmap_alloc ( sizeof(int), sizeof(float),
                                  4096,
                                  ex_hashkey_int, ex_keycmp_int );

    i = 0;
    while ( i < 2000 ) {
        int k;
        float v;

        k = rand();
        v = ex_range_randf( -1000.0f, 1000.0f );
        ex_hashmap_set_or_new ( hashmap1, &k, &v );

        k = rand();
        v = ex_range_randf( -1000.0f, 1000.0f );
        ex_hashmap_set_or_new ( hashmap2, &k, &v );
        ++i;
    }

    i = 0;
    while ( i < 2000 ) {
        int k;
        int idx;

        k = rand();
        if ( ex_hashmap_remove_at ( hashmap1, &k ) ) {
            ex_log("remove key %d in hashmap1", k);
        }

        k = rand();
        idx = ex_hashmap_find ( hashmap2, &k );
        if ( idx != -1 ) {
            ex_hashmap_remove_by_idx ( hashmap2, idx );
            ex_log("remove key %d in hashmap2", k);
        }

        ++i;
    }

    ex_hashmap_free (hashmap1);
    ex_hashmap_free (hashmap2);

    ex_sdk_deinit ();
    return 0;
}
