// ======================================================================================
// File         : hashmap.c
// Author       : Wu Jie 
// Last Change  : 06/28/2010 | 08:54:19 AM | Monday,June
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// fwd-decls
///////////////////////////////////////////////////////////////////////////////

//
typedef struct __node_t {
    size_t prev; // prev index of nodes
    size_t next; // next index of nodes
    uint32 hash; // cached hash index, this will help us skip calculate hashkey again when remove object from hash-table
    // in memory, a node has:
    //   | prev index
    //   | next index
    //   | key_data
    //   | value_data
} __node_t;

static inline uint32 __hash_index ( const ex_hashmap_t *_hashmap, const void *_key ) {
    return _hashmap->hashkey(_key) & ( _hashmap->hashsize - 1 );
}

static inline __node_t *__getnode ( const ex_hashmap_t *_hashmap, size_t _idx ) {
    return (__node_t *)( (char *)_hashmap->nodes + _idx * _hashmap->node_bytes );
}

static inline void *__getkey ( const __node_t *_node ) {
    return (char *)_node + sizeof(__node_t);
}

static inline void *__getvalue ( const __node_t *_node, size_t _key_bytes ) {
    return (char *)_node + sizeof(__node_t) + _key_bytes;
}

static inline uint32 __ceilpow2u ( uint32 _value ) {
    uint32 result = 1;
    while ( result < _value ) {
        result <<= 1; 
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// managed
ex_hashmap_t *ex_hashmap_alloc ( size_t _key_bytes, 
                                 size_t _value_bytes, 
                                 size_t _hashsize, 
                                 hashkey_t _hashkey, 
                                 keycmp_t _keycmp )
{
    ex_hashmap_t *hashmap = ex_malloc( sizeof(ex_hashmap_t) );
    ex_hashmap_init ( hashmap, 
                      _key_bytes, _value_bytes, 
                      _hashsize,
                      _hashkey, _keycmp,
                      ex_func_alloc,
                      ex_func_realloc,
                      ex_func_dealloc
                      );
    return hashmap;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_hashmap_init ( ex_hashmap_t *_hashmap, 
                       size_t _key_bytes, 
                       size_t _value_bytes, 
                       size_t _hashsize, 
                       hashkey_t _hashkey, 
                       keycmp_t _keycmp, 
                       void *(*_alloc) ( size_t ),
                       void *(*_realloc) ( void *, size_t ),
                       void  (*_dealloc) ( void * )
                     ) 
{
    // check if the count is pow of 2, if not, calc the nearest pow of 2 of the count.
    if ( ex_is_pow_of_2(_hashsize) == false ) {
        _hashsize = ex_ceilpow2u(_hashsize);
    }

    _hashmap->alloc = _alloc;
    _hashmap->realloc = _realloc;
    _hashmap->dealloc = _dealloc;

    // init length, _capacity, element bytes, hash and keycmp callbacks.
    _hashmap->count = 0;
    _hashmap->capacity = _hashsize;
    _hashmap->hashsize = _hashsize;
    _hashmap->key_bytes = _key_bytes;
    _hashmap->value_bytes = _value_bytes;
    _hashmap->hashkey = _hashkey;
    _hashmap->keycmp = _keycmp;

    _hashmap->node_bytes = sizeof(__node_t) + _key_bytes + _value_bytes;

    // init nodes
    _hashmap->nodes = _hashmap->alloc ( _hashsize * _hashmap->node_bytes );
    ex_memzero ( _hashmap->nodes, _hashsize * _hashmap->node_bytes );

    // init hash indices
    _hashmap->indices = _hashmap->alloc ( _hashsize * sizeof(size_t) );
    memset ( _hashmap->indices, -1, _hashsize * sizeof(size_t) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_hashmap_deinit ( ex_hashmap_t *_hashmap ) {
    _hashmap->dealloc (_hashmap->nodes);
    _hashmap->nodes = NULL;
    _hashmap->dealloc (_hashmap->indices);
    _hashmap->indices = NULL;

    _hashmap->key_bytes = 0;
    _hashmap->value_bytes = 0;
    _hashmap->count = 0;
    _hashmap->capacity = 0;
    _hashmap->hashsize = 0;
    _hashmap->hashkey = NULL;
    _hashmap->keycmp = NULL;

    _hashmap->alloc = NULL;
    _hashmap->realloc = NULL;
    _hashmap->dealloc = NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_hashmap_free ( ex_hashmap_t *_hashmap ) {
    ex_assert( _hashmap != NULL );

    ex_hashmap_deinit (_hashmap);
    ex_free(_hashmap);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t ex_hashmap_add_new ( ex_hashmap_t *_hashmap, 
                            const void *_key, 
                            const void *_val, 
                            size_t _hash_idx ) {
    size_t cur_idx, next_idx;
    uint8 *dptr;
    __node_t *new_node;
    
    if ( _hashmap->count >= _hashmap->capacity ) {
        _hashmap->capacity *= 2;
        _hashmap->nodes = _hashmap->realloc ( _hashmap->nodes, 
                                              _hashmap->capacity * _hashmap->node_bytes  );
    }
    cur_idx = _hashmap->count;
    _hashmap->count += 1;

    next_idx = _hashmap->indices[_hash_idx];

    new_node = (__node_t *)( (char *)_hashmap->nodes + cur_idx * _hashmap->node_bytes );
    new_node->next = next_idx;
    new_node->prev = -1;
    new_node->hash = _hash_idx;
    _hashmap->indices[_hash_idx] = cur_idx;

    //
    if ( next_idx != -1 )
        __getnode(_hashmap,next_idx)->prev = cur_idx;

    // set key and value
    dptr = (char *)new_node + sizeof(__node_t);
    memcpy ( (char *)dptr,  _key, _hashmap->key_bytes );

    dptr += _hashmap->key_bytes;
    if ( _val != NULL )
        memcpy ( (char *)dptr, _val, _hashmap->value_bytes );

    return cur_idx;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_hashmap_find ( const ex_hashmap_t *_hashmap, const void *_key ) {
    size_t hash_next;
    uint32 hash_idx = __hash_index ( _hashmap, _key ); 
    __node_t *node;

    // check if the key exists. if yes, don't do any thing.
    hash_next = _hashmap->indices[hash_idx];
    while ( hash_next != -1 ) {
        node = __getnode(_hashmap,hash_next);

        // compare the key
        if ( _hashmap->keycmp(_key, __getkey( node ) ) == 0 ) {
            return hash_next;
        }

        hash_next = node->next;
    }

    //
    return -1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_hashmap_get ( const ex_hashmap_t *_hashmap, const void *_key ) {
    size_t hash_next;
    uint32 hash_idx = __hash_index ( _hashmap, _key ); 
    __node_t *node;

    // check if the key exists. if yes, don't do any thing.
    hash_next = _hashmap->indices[hash_idx];
    while ( hash_next != -1 ) {
        node = __getnode(_hashmap,hash_next);

        // compare the key
        if ( _hashmap->keycmp(_key, __getkey( node ) ) == 0 ) {
            return __getvalue(node, _hashmap->key_bytes);
        }

        hash_next = node->next;
    }

    //
    return NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_hashmap_get_or_new ( ex_hashmap_t *_hashmap, const void *_key ) {
    size_t idx, hash_next;
    uint32 hash_idx = __hash_index ( _hashmap, _key ); 
    __node_t *node;

    // check if the key exists. if yes, don't do any thing.
    hash_next = _hashmap->indices[hash_idx];
    while ( hash_next != -1 ) {
        node = __getnode(_hashmap,hash_next);

        // compare the key
        if ( _hashmap->keycmp(_key, __getkey( node ) ) == 0 ) {
            return __getvalue(node, _hashmap->key_bytes);
        }

        hash_next = node->next;
    }

    idx = ex_hashmap_add_new ( _hashmap, _key, NULL, hash_idx ); 
    return ex_hashmap_get_by_idx ( _hashmap, idx );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_hashmap_get_by_idx ( const ex_hashmap_t *_hashmap, size_t _idx ) {
    return __getvalue ( __getnode ( _hashmap, _idx ), _hashmap->key_bytes );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t ex_hashmap_set_or_new ( ex_hashmap_t *_hashmap, 
                               const void *_key, 
                               const void *_val )
{
    size_t hash_next;
    uint32 hash_idx = __hash_index ( _hashmap, _key ); 
    __node_t *node;

    // check if the key exists. if yes, don't do any thing.
    hash_next = _hashmap->indices[hash_idx];
    while ( hash_next != -1 ) {
        node = __getnode(_hashmap,hash_next);

        // compare the key
        if ( _hashmap->keycmp(_key, __getkey( node ) ) == 0 ) {
            memcpy ( __getvalue(node, _hashmap->key_bytes), _val, _hashmap->value_bytes );
            return hash_next;
        }

        hash_next = node->next;
    }

    return ex_hashmap_add_new ( _hashmap, _key, _val, hash_idx ); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t ex_hashmap_add_unique ( ex_hashmap_t *_hashmap, 
                               const void *_key, 
                               const void *_val )
{
    size_t hash_next;
    uint32 hash_idx = __hash_index ( _hashmap, _key ); 
    __node_t *node;

    // check if the key exists. if yes, don't do any thing.
    hash_next = _hashmap->indices[hash_idx];
    while ( hash_next != -1 ) {
        node = __getnode(_hashmap,hash_next);

        // compare the key
        if ( _hashmap->keycmp(_key, __getkey( node ) ) == 0 ) {
            return hash_next;
        }

        hash_next = node->next;
    }

    return ex_hashmap_add_new ( _hashmap, _key, _val, hash_idx ); 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_hashmap_cpy ( ex_hashmap_t *_to, const ex_hashmap_t *_from ) {
    ex_assert ( _to->key_bytes == _from->key_bytes );
    ex_assert ( _to->value_bytes == _from->value_bytes );
    ex_assert ( _to->node_bytes == _from->node_bytes );
    ex_assert ( _to->hashkey == _from->hashkey && _to->keycmp == _from->keycmp );

    //
    if ( _to->capacity < _from->capacity ) {
        _to->capacity = _from->capacity;
        _to->nodes = _to->realloc ( _to->nodes, _to->capacity * _to->node_bytes  );
    }

    _to->count = _from->count;
    _to->hashsize = _from->hashsize;
    _to->indices = _to->realloc ( _to->indices, _to->hashsize * _to->node_bytes  );

    memcpy( _to->nodes, _from->nodes, _to->capacity * _to->node_bytes );
    memcpy( _to->indices, _from->indices, _to->hashsize * sizeof(size_t) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_hashmap_remove_at ( ex_hashmap_t *_hashmap, const void *_key ) {
    size_t hash_next;
    uint32 hash_idx = __hash_index ( _hashmap, _key ); 
    __node_t *node;

    // check if the key exists. if yes, don't do any thing.
    hash_next = _hashmap->indices[hash_idx];
    while ( hash_next != -1 ) {
        node = __getnode(_hashmap,hash_next);

        // compare the key
        if ( _hashmap->keycmp(_key, __getkey( node ) ) == 0 ) {
            break;
        }

        hash_next = node->next;
    }

    // the key is not found!
    if ( hash_next == -1 ) {
        return false;
    }

    ex_hashmap_remove_by_idx( _hashmap, hash_next );
    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_hashmap_remove_by_idx ( ex_hashmap_t *_hashmap, size_t _idx ) {
    size_t prev_idx, next_idx;
    uint32 hash_idx;
    __node_t *node, *last_node;

    node = __getnode(_hashmap,_idx);
    hash_idx = node->hash;
    prev_idx = node->prev;
    next_idx = node->next;

    // if the erase node is not the tail
    if ( next_idx != -1 ) {
        __getnode (_hashmap,next_idx)->prev = prev_idx;
    }

    // if the erase node is the header, change the index
    if ( prev_idx == -1 )
        _hashmap->indices[hash_idx] = next_idx;
    // if not header
    else 
        __getnode(_hashmap,prev_idx)->next = next_idx;

    // now use fast remove technique, replace the erased node by last node in the nodes
    if ( _idx == _hashmap->count-1 ) {
        last_node = __getnode(_hashmap,_hashmap->count-1);
        last_node->next = -1;
        last_node->prev = -1;
        last_node->hash = -1;

        _hashmap->count -= 1;
    }
    else {
        last_node = __getnode(_hashmap,_hashmap->count-1);
        memcpy ( node, last_node, _hashmap->node_bytes );
        last_node->next = -1;
        last_node->prev = -1;
        last_node->hash = -1;

        // adjust hash table
        if ( node->prev == -1 ) 
            _hashmap->indices[node->hash] = _idx;
        else
            __getnode(_hashmap,node->prev)->next = _idx;

        //
        _hashmap->count -= 1;
    }
}
