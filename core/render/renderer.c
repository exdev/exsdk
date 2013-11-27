// ======================================================================================
// File         : renderer.c
// Author       : Wu Jie 
// Last Change  : 03/12/2013 | 16:21:54 PM | Tuesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "SDL_opengl.h"
#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// TEMP
///////////////////////////////////////////////////////////////////////////////

static void *__main_renderer = NULL;
void *ex_get_main_sdl_renderer() { return __main_renderer; }
void ex_set_main_sdl_renderer ( void *_r ) { __main_renderer = _r; }

///////////////////////////////////////////////////////////////////////////////
// static
///////////////////////////////////////////////////////////////////////////////

// you can use VAO, VBO or FIXED_PIEPLINE
#define VAO   1
#define VBO   2
#define FIXED 3
#define BUFFER_OP FIXED

#define USE_TRIANGLE_STRIP 1

#define MEMBLOCK_INIT( _block, _type, _size ) \
    ex_memblock_init ( &_block \
                      , sizeof(_type) \
                      , _size \
                      , ex_func_alloc \
                      , ex_func_realloc \
                      , ex_func_dealloc \
                    )

typedef struct __ui_vertex_t {
    ex_vec2f_t pos;
    ex_vec2f_t uv0;
    ex_vec4f_t color;
} __ui_vertex_t;

typedef struct __ui_node_t {
    // ex_material_t *mat;
    const char *text;
    void *texture;

    ex_mat33f_t transform;
    uint32 depth;

    ex_recti_t pos;
    ex_recti_t border;
    ex_recti_t rect;
    ex_vec4f_t color;
} __ui_node_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __ui_node_cmp ( const void *_a, const void *_b ) {
    int r;
    __ui_node_t *node_a, *node_b;
    
    node_a = (__ui_node_t *)_a;
    node_b = (__ui_node_t *)_b;

    r = node_a->depth - node_b->depth;
    if ( r != 0 ) return r;

    return (uint32)node_a->texture - (uint32)node_b->texture;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline __ui_node_t *__request_ui_node ( ex_renderer_t *_renderer ) {
    return ex_memblock_request( &_renderer->ui_node_block, 1 );
}

///////////////////////////////////////////////////////////////////////////////
// renderer op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_renderer_init ( ex_renderer_t *_renderer ) {
    ex_assert ( _renderer->initialized == false );

    if ( _renderer->initialized )
        return -1;

    // ======================================================== 
    // init ui 
    // ======================================================== 

    // create ui node pool
    MEMBLOCK_INIT ( _renderer->ui_node_block, __ui_node_t, 512 );
    MEMBLOCK_INIT ( _renderer->ui_vb, __ui_vertex_t, 4096 );
    MEMBLOCK_INIT ( _renderer->ui_ib, sizeof(uint16), 4096 );

    // init ui VBO
    glGenBuffers( 1, &_renderer->ui_vb_id );
    glGenBuffers( 1, &_renderer->ui_ib_id );

    // init ui USE_VAO
#if (BUFFER_OP == VAO)
    glGenVertexArrays(1, &_renderer->ui_vao_id);
    glBindVertexArray(_renderer->ui_vao_id);

        // send buffer data
        glBindBuffer ( GL_ARRAY_BUFFER, _renderer->ui_vb_id );
        glBufferData ( GL_ARRAY_BUFFER, sizeof(__ui_vertex_t) * _renderer->ui_vb.count, _renderer->ui_vb.data, GL_DYNAMIC_DRAW );

        glEnableVertexAttribArray( VAT_POSITION );
        glEnableVertexAttribArray( VAT_COLOR );
        glEnableVertexAttribArray( VAT_TEXCOORD );

        glVertexAttribPointer( VAT_POSITION, 2, GL_FLOAT        , GL_FALSE, sizeof(__ui_vertex_t), (GLvoid*)offsetof(__ui_vertex_t, pos)   );
        glVertexAttribPointer( VAT_COLOR   , 4, GL_UNSIGNED_BYTE, GL_TRUE , sizeof(__ui_vertex_t), (GLvoid*)offsetof(__ui_vertex_t, color) );
        glVertexAttribPointer( VAT_TEXCOORD, 2, GL_FLOAT        , GL_FALSE, sizeof(__ui_vertex_t), (GLvoid*)offsetof(__ui_vertex_t, uv0)   );

        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, _renderer->ui_ib_id );
        glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_UNSIGNED_SHORT) * _renderer->ui_ib.count, _renderer->ui_ib.data, GL_DYNAMIC_DRAW );

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif

    _renderer->initialized = true;
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_renderer_deinit ( ex_renderer_t *_renderer ) {
    ex_assert ( _renderer->initialized );

    if ( _renderer->initialized == false )
        return;

    glDeleteBuffers(1, &_renderer->ui_vb_id);
    glDeleteBuffers(1, &_renderer->ui_ib_id);

#if (BUFFER_OP == VAO)
    glDeleteVertexArrays(1, &_renderer->ui_vao_id);
#endif

    // destroy ui node pool
    ex_memblock_deinit ( &_renderer->ui_node_block );
    ex_memblock_deinit ( &_renderer->ui_vb );
    ex_memblock_deinit ( &_renderer->ui_ib );

    _renderer->initialized = false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __flush_ui_vertices_vao ( ex_renderer_t *_renderer ) {

    // ======================================================== 
    // send buffer data 
    // ======================================================== 

    // send vertex buffer data
    // TODO: in cocos2d-x they do this for sending data.
    // glBindBuffer ( GL_ARRAY_BUFFER, _renderer->ui_vb_id );
    // glBufferData ( GL_ARRAY_BUFFER, sizeof(__ui_vertex_t) * _renderer->ui_vb.count, NULL, GL_DYNAMIC_DRAW );
    // void *buf = glMapBuffer ( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    // memcpy ( buf, _renderer->ui_vb.data, sizeof(__ui_vertex_t) * _renderer->ui_vb.count );
    // glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer ( GL_ARRAY_BUFFER, _renderer->ui_vb_id );
    glBufferData ( GL_ARRAY_BUFFER, sizeof(__ui_vertex_t) * _renderer->ui_vb.count, _renderer->ui_vb.data, GL_DYNAMIC_DRAW );

    // define vertex attribute
    glBindVertexArray(_renderer->ui_vao_id);

    // send index buffer data
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, _renderer->ui_ib_id );
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_UNSIGNED_SHORT) * _renderer->ui_ib.count, _renderer->ui_ib.data, GL_DYNAMIC_DRAW );

    // ======================================================== 
    // draw elements 
    // ======================================================== 

    // TODO: the n here should be calculate by code because we have Nine-Scaled-Bitmap and Quad Bitmap shapes
#if USE_TRIANGLE_STRIP
    glDrawElements( GL_TRIANGLE_STRIP, 
                    (GLsizei)_renderer->ui_ib.count, 
                    GL_UNSIGNED_SHORT, 
                    NULL );
#else
    glDrawElements( GL_TRIANGLES, 
                    (GLsizei)_renderer->ui_ib.count, 
                    GL_UNSIGNED_SHORT, 
                    NULL );
#endif // USE_TRIANGLE_STRIP

    // ======================================================== 
    // unbind buffers
    // ======================================================== 

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // ======================================================== 
    // reset memory
    // ======================================================== 

    ex_memblock_clear(&_renderer->ui_vb);
    ex_memblock_clear(&_renderer->ui_ib);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __flush_ui_vertices_vbo ( ex_renderer_t *_renderer ) {
    // ======================================================== 
    // send buffer data 
    // ======================================================== 

    // send vertex buffer data
    glBindBuffer ( GL_ARRAY_BUFFER, _renderer->ui_vb_id );
    glBufferData ( GL_ARRAY_BUFFER, sizeof(__ui_vertex_t) * _renderer->ui_vb.count, _renderer->ui_vb.data, GL_DYNAMIC_DRAW );

    // define vertex attribute
    glEnableVertexAttribArray( VAT_POSITION );
    glEnableVertexAttribArray( VAT_COLOR );
    glEnableVertexAttribArray( VAT_TEXCOORD );

    glVertexAttribPointer( VAT_POSITION, 2, GL_FLOAT        , GL_FALSE, sizeof(__ui_vertex_t), (GLvoid*)offsetof(__ui_vertex_t, pos)   );
    glVertexAttribPointer( VAT_COLOR   , 4, GL_UNSIGNED_BYTE, GL_TRUE , sizeof(__ui_vertex_t), (GLvoid*)offsetof(__ui_vertex_t, color) );
    glVertexAttribPointer( VAT_TEXCOORD, 2, GL_FLOAT        , GL_FALSE, sizeof(__ui_vertex_t), (GLvoid*)offsetof(__ui_vertex_t, uv0)   );

    // send index buffer data
    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, _renderer->ui_ib_id );
    glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_UNSIGNED_SHORT) * _renderer->ui_ib.count, _renderer->ui_ib.data, GL_DYNAMIC_DRAW );

    // ======================================================== 
    // draw elements 
    // ======================================================== 

    // TODO: the n here should be calculate by code because we have Nine-Scaled-Bitmap and Quad Bitmap shapes
#if USE_TRIANGLE_STRIP
    glDrawElements( GL_TRIANGLE_STRIP, 
                    (GLsizei)_renderer->ui_ib.count, 
                    GL_UNSIGNED_SHORT, 
                    NULL );
#else
    glDrawElements( GL_TRIANGLES, 
                    (GLsizei)_renderer->ui_ib.count, 
                    GL_UNSIGNED_SHORT, 
                    NULL );
#endif // USE_TRIANGLE_STRIP

    // ======================================================== 
    // unbind buffers
    // ======================================================== 

    glDisableVertexAttribArray( VAT_POSITION );
    glDisableVertexAttribArray( VAT_COLOR );
    glDisableVertexAttribArray( VAT_TEXCOORD );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // ======================================================== 
    // reset memory
    // ======================================================== 

    ex_memblock_clear(&_renderer->ui_vb);
    ex_memblock_clear(&_renderer->ui_ib);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __flush_ui_vertices_fixed ( ex_renderer_t *_renderer ) {
    // ======================================================== 
    // send buffer data 
    // ======================================================== 

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer  ( 2, GL_FLOAT, sizeof(__ui_vertex_t), _renderer->ui_vb.data );
    glColorPointer   ( 4, GL_FLOAT, sizeof(__ui_vertex_t), (char*)(_renderer->ui_vb.data) + offsetof(__ui_vertex_t, color) );
    glTexCoordPointer( 2, GL_FLOAT, sizeof(__ui_vertex_t), (char*)(_renderer->ui_vb.data) + offsetof(__ui_vertex_t, uv0) );

    // ======================================================== 
    // draw elements 
    // ======================================================== 

    // TODO: the n here should be calculate by code because we have Nine-Scaled-Bitmap and Quad Bitmap shapes
#if USE_TRIANGLE_STRIP
    glDrawElements( GL_TRIANGLE_STRIP, 
                    (GLsizei)_renderer->ui_ib.count, 
                    GL_UNSIGNED_SHORT, 
                    _renderer->ui_ib.data );
#else
    glDrawElements( GL_TRIANGLES, 
                    (GLsizei)_renderer->ui_ib.count, 
                    GL_UNSIGNED_SHORT, 
                    _renderer->ui_ib.data );
#endif // USE_TRIANGLE_STRIP

    // ======================================================== 
    // unbind buffers
    // ======================================================== 

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    // ======================================================== 
    // reset memory
    // ======================================================== 

    ex_memblock_clear(&_renderer->ui_vb);
    ex_memblock_clear(&_renderer->ui_ib);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __setup_blending ( ex_renderer_t *_renderer ) {
    glEnable ( GL_BLEND );
    glBlendFuncSeparate ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                          GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBlendEquationSeparate ( GL_FUNC_ADD, 
                              GL_FUNC_ADD );
}

// ------------------------------------------------------------------ 
// Desc: 
#if ( BUFFER_OP == VAO )
    #define __flush_ui_vertices __flush_ui_vertices_vao
#elif ( BUFFER_OP == VBO )
    #define __flush_ui_vertices __flush_ui_vertices_vbo
#else
    #define __flush_ui_vertices __flush_ui_vertices_fixed
#endif
// ------------------------------------------------------------------ 

void __draw_ui_nodes ( ex_renderer_t *_renderer ) {
    // __ui_node_t *node;
    // size_t i, index_start;
    // void *last_texture;
    // __ui_vertex_t *verts;
    // uint16 *indices;
    // ALLEGRO_BITMAP *bitmap;
    // ALLEGRO_BITMAP_OGL *ogl_bitmap;
    // float tex_l, tex_t, tex_r, tex_b, w, h, true_w, true_h;
    // int sx, sy, sw, sh;
    // float dx, dy, dw, dh;

    // // process ui nodes
    // qsort ( _renderer->ui_node_block.data, 
    //         _renderer->ui_node_block.count,
    //         sizeof(__ui_node_t),
    //         __ui_node_cmp );

    // glEnable(GL_TEXTURE_2D);

    // // loop all ui node and draw
    // last_texture = NULL;
    // for ( i = 0; i < _renderer->ui_node_block.count; ++i ) {
    //     node = (__ui_node_t *)ex_memblock_get ( &_renderer->ui_node_block, i );

    //     // if this is not the first node,
    //     if ( i != 0 && node->texture != last_texture ) {
    //         glBindTexture ( GL_TEXTURE_2D, ogl_bitmap->texture );
    //         __setup_blending ( _renderer );
    //         __flush_ui_vertices ( _renderer );
    //     }

    //     bitmap = (ALLEGRO_BITMAP *)node->texture;
    //     ogl_bitmap = (ALLEGRO_BITMAP_OGL *)node->texture;

    //     // draw as pure sprite
    //     if ( node->border.l == 0 
    //       && node->border.r == 0 
    //       && node->border.t == 0 
    //       && node->border.b == 0 ) {

    //         tex_l = ogl_bitmap->left;
    //         tex_r = ogl_bitmap->right;
    //         tex_t = ogl_bitmap->top;
    //         tex_b = ogl_bitmap->bottom;

    //         dx = (float)node->pos.x;
    //         dy = (float)node->pos.y;
    //         dw = (float)node->pos.w;
    //         dh = (float)node->pos.h;

    //         sx = node->rect.x;
    //         sy = node->rect.y;
    //         sw = node->rect.w;
    //         sh = node->rect.h;

    //         w = bitmap->w;
    //         h = bitmap->h;
    //         true_w = ogl_bitmap->true_w;
    //         true_h = ogl_bitmap->true_h;

    //         tex_l += sx / true_w;
    //         tex_t -= sy / true_h;
    //         tex_r -= (w - sx - sw) / true_w;
    //         tex_b += (h - sy - sh) / true_h;

    //         // ui_vb
    //         verts = (__ui_vertex_t *)ex_memblock_request ( &_renderer->ui_vb, 4 );

    //         verts[0].pos.x = dx;
    //         verts[0].pos.y = dy + dh;
    //         verts[0].uv0.x = tex_l;
    //         verts[0].uv0.y = tex_b;
    //         verts[0].color = node->color;

    //         verts[1].pos.x = dx;
    //         verts[1].pos.y = dy;
    //         verts[1].uv0.x = tex_l;
    //         verts[1].uv0.y = tex_t;
    //         verts[1].color = node->color;

    //         verts[2].pos.x = dx + dw;
    //         verts[2].pos.y = dy + dh;
    //         verts[2].uv0.x = tex_r;
    //         verts[2].uv0.y = tex_b;
    //         verts[2].color = node->color;

    //         verts[3].pos.x = dx + dw;
    //         verts[3].pos.y = dy;
    //         verts[3].uv0.x = tex_r;
    //         verts[3].uv0.y = tex_t;
    //         verts[3].color = node->color;

    //         ex_vec2f_mul_mat33f ( &verts[0].pos, &verts[0].pos, &node->transform );
    //         ex_vec2f_mul_mat33f ( &verts[1].pos, &verts[1].pos, &node->transform );
    //         ex_vec2f_mul_mat33f ( &verts[2].pos, &verts[2].pos, &node->transform );
    //         ex_vec2f_mul_mat33f ( &verts[3].pos, &verts[3].pos, &node->transform );

    //         // DISABLE: since we use integer here { 
    //         // verts[0].pos.x = ceilf(verts[0].pos.x); verts[0].pos.y = ceilf(verts[0].pos.y);
    //         // verts[1].pos.x = ceilf(verts[1].pos.x); verts[1].pos.y = ceilf(verts[1].pos.y);
    //         // verts[2].pos.x = ceilf(verts[2].pos.x); verts[2].pos.y = ceilf(verts[2].pos.y);
    //         // verts[3].pos.x = ceilf(verts[3].pos.x); verts[3].pos.y = ceilf(verts[3].pos.y);
    //         // } DISABLE end 

    //         // ui_ib
    //         index_start = _renderer->ui_ib.count;
    //         indices = (uint16 *)ex_memblock_request ( &_renderer->ui_ib, 6 );
    //         indices[0] = index_start;
    //         indices[1] = index_start + 1;
    //         indices[2] = index_start + 2;
    //         indices[3] = index_start + 2;
    //         indices[4] = index_start + 1;
    //         indices[5] = index_start + 3;
    //     }

    //     // draw as border sprite
    //     else {
    //     }

    //     last_texture = node->texture;
    // }

    // // if we still have verices remain, flush it at the end
    // if ( ex_memblock_count (&_renderer->ui_vb) > 0 ) {
    //     glBindTexture ( GL_TEXTURE_2D, ogl_bitmap->texture );
    //     __setup_blending ( _renderer );
    //     __flush_ui_vertices ( _renderer );
    // }

    // glDisable(GL_TEXTURE_2D);

    // //
    // ex_memblock_clear( &_renderer->ui_node_block );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_renderer_draw_nodes ( ex_renderer_t *_renderer ) {
    // TODO: process 2d nodes
    // __draw_2d_nodes ();
    __draw_ui_nodes (_renderer);
}

///////////////////////////////////////////////////////////////////////////////
// node op
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ui op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __ui_draw_texture ( ex_renderer_t *_renderer,
                          void *_texture,
                          ex_recti_t _pos,
                          ex_recti_t _border,
                          ex_recti_t _rect,
                          ex_vec4f_t _color ) 
{
    __ui_node_t *node;

    node = __request_ui_node(_renderer);

    node->text = NULL;
    node->texture = _texture;

    ex_mat33f_identity(&node->transform);
    node->depth = 0;

    node->pos = _pos;
    node->border = _border;
    node->rect = _rect;
    node->color = _color;
}
