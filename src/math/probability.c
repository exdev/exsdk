// ======================================================================================
// File         : probability.c
// Author       : Wu Jie 
// Last Change  : 02/09/2011 | 19:45:20 PM | Wednesday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// http://explodecomputer.com/page.php?id=154
// http://code.activestate.com/recipes/576564-walkers-alias-method-for-random-objects-with-diffe/
// ------------------------------------------------------------------ 

void ex_walkers_alias( const float *_weights, 
                       int _num_weights,
                       int *_samples, 
                       int _num_samples ) 
{
    int *a;
    float *q, *p, rU;
    int i,j,k;
    int *HL,*H,*L;
    float sum;

    a = calloc(_num_weights,sizeof(int));
    HL = calloc(_num_weights,sizeof(int));
    q = calloc(_num_weights,sizeof(float));
    p = calloc(_num_weights,sizeof(float));
    H = HL - 1; 
    L = HL + _num_weights;
    sum = 0;

    for ( i = 0; i < _num_weights; ++i )
        sum += _weights[i];

    for ( i = 0; i < _num_weights; ++i )
        p[i] = _weights[i]/sum;

    for ( i = 0; i < _num_weights; ++i ) {
        q[i] = p[i] * _num_weights;
        if(q[i] < 1.0f) *++H = i; else *--L = i;
    }

    if ( H >= HL && L < HL +_num_weights ) {
        for ( k = 0; k < _num_weights-1; ++k ) {
            i = HL[k];
            j = *L;
            a[i] = j;
            q[j] += q[i] - 1;
            if ( q[j] < 1.0f ) 
                L++;
            if ( L >= HL + _num_weights ) 
                break;
        }
    }

    for(i = 0; i < _num_weights; i++) 
        q[i] += i;

    for(i = 0; i < _num_samples; i++) {
        rU = (float) rand() / RAND_MAX * _num_weights;
        k = (int) rU;
        _samples[i] = (rU < q[k]) ? k : a[k];
    }

    free(a);
    free(HL);
    free(q);
    free(p);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_weights_to_cdf ( float *_cdf, 
                         const float *_weights, 
                         int _num_weights ) 
{
    int i;
    float sum;

    for ( i = 0; i < _num_weights; ++i )
        sum += _weights[i];

    _cdf[0] = _weights[0]/sum; 
    for ( i = 1; i < _num_weights - 1; ++i ) {
        _cdf[i] = _weights[i]/sum;
        _cdf[i] += _cdf[i-1]; 
    }
    _cdf[_num_weights-1] = 1.0f;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_cdf_gen_index ( float *_cdf, int _num_cdf ) {
    int i;
    float y = ex_range_randf(0.0f,1.0f);

    for ( i = 0; i < _num_cdf; ++i ) {
        if ( y < _cdf[i] )
            return i;
    }
    ex_assert( false, "can't find valid result from incoming cdf." );
    return -1;
}
