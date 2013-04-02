// ======================================================================================
// File         : renderer.c
// Author       : Wu Jie 
// Last Change  : 03/12/2013 | 16:21:54 PM | Tuesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"
#include "allegro5/allegro_opengl.h"
#include "allegro5/internal/aintern_opengl.h"

#include "exsdk.h"
// #include "gl/gl_inc.h"

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_ui_draw_texture ( int _dx, int _dy, int _dw, int _dh,
                          int _sx, int _sy, int _sw, int _sh )
{
    ex_ui_state_t *state;

    size_t index_start;
    ex_ui_vertex_t *verts;
    uint16 *indices;

    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_BITMAP_OGL *ogl_bitmap;
    float tex_l, tex_t, tex_r, tex_b, w, h, true_w, true_h;
    int sx, sy, sw, sh;
    float dx, dy, dw, dh;

    //
    state = ex_ui_state();
    bitmap = (ALLEGRO_BITMAP *)state->texture;
    ogl_bitmap = (ALLEGRO_BITMAP_OGL *)state->texture;

    // create vertex and indices
    tex_l = ogl_bitmap->left;
    tex_r = ogl_bitmap->right;
    tex_t = ogl_bitmap->top;
    tex_b = ogl_bitmap->bottom;

    dx = (float)_dx;
    dy = (float)_dy;
    dw = (float)_dw;
    dh = (float)_dh;

    sx = _sx;
    sy = _sy;
    sw = _sw;
    sh = _sh;

    w = bitmap->w;
    h = bitmap->h;
    true_w = ogl_bitmap->true_w;
    true_h = ogl_bitmap->true_h;

    tex_l += sx / true_w;
    tex_t -= sy / true_h;
    tex_r -= (w - sx - sw) / true_w;
    tex_b += (h - sy - sh) / true_h;

    // ui_vb
    index_start = state->vb.count;
    verts = (ex_ui_vertex_t *)ex_memblock_request ( &state->vb, 4 );

    verts[0].pos.x = dx;
    verts[0].pos.y = dy + dh;
    verts[0].uv0.x = tex_l;
    verts[0].uv0.y = tex_b;
    verts[0].color = state->color;

    verts[1].pos.x = dx;
    verts[1].pos.y = dy;
    verts[1].uv0.x = tex_l;
    verts[1].uv0.y = tex_t;
    verts[1].color = state->color;

    verts[2].pos.x = dx + dw;
    verts[2].pos.y = dy + dh;
    verts[2].uv0.x = tex_r;
    verts[2].uv0.y = tex_b;
    verts[2].color = state->color;

    verts[3].pos.x = dx + dw;
    verts[3].pos.y = dy;
    verts[3].uv0.x = tex_r;
    verts[3].uv0.y = tex_t;
    verts[3].color = state->color;

    ex_vec2f_mul_mat33f ( &verts[0].pos, &verts[0].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[1].pos, &verts[1].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[2].pos, &verts[2].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[3].pos, &verts[3].pos, &state->matrix );

    // DISABLE: since we use integer here { 
    // verts[0].pos.x = ceilf(verts[0].pos.x); verts[0].pos.y = ceilf(verts[0].pos.y);
    // verts[1].pos.x = ceilf(verts[1].pos.x); verts[1].pos.y = ceilf(verts[1].pos.y);
    // verts[2].pos.x = ceilf(verts[2].pos.x); verts[2].pos.y = ceilf(verts[2].pos.y);
    // verts[3].pos.x = ceilf(verts[3].pos.x); verts[3].pos.y = ceilf(verts[3].pos.y);
    // } DISABLE end 

    // ui_ib
    indices = (uint16 *)ex_memblock_request ( &state->ib, 6 );
    indices[0] = index_start;
    indices[1] = index_start + 1;
    indices[2] = index_start + 2;
    indices[3] = index_start + 2;
    indices[4] = index_start + 1;
    indices[5] = index_start + 3;

    ++state->primitive_count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_ui_draw_border_texture ( int _dx, int _dy, int _dw, int _dh,
                                 int _sx, int _sy, int _sw, int _sh,
                                 int _l, int _r, int _t, int _b )
{
    // ++state->primitive_count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_ui_flush () {
    ex_ui_state_t *state;
    ALLEGRO_BITMAP_OGL *ogl_bitmap;

    state = ex_ui_state();
    // nothing to draw
    if ( state->vb.count == 0 )
        return;

    ogl_bitmap = (ALLEGRO_BITMAP_OGL *)state->texture;

    // bind texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture ( GL_TEXTURE_2D, ogl_bitmap->texture );

    // setup blending 
    glEnable ( GL_BLEND );
    glBlendFuncSeparate ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
                          GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBlendEquationSeparate ( GL_FUNC_ADD, 
                              GL_FUNC_ADD );

    // send buffer data 
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer  ( 2, GL_FLOAT, sizeof(ex_ui_vertex_t), state->vb.data );
        glColorPointer   ( 4, GL_FLOAT, sizeof(ex_ui_vertex_t), (char*)(state->vb.data) + offsetof(ex_ui_vertex_t, color) );
        glTexCoordPointer( 2, GL_FLOAT, sizeof(ex_ui_vertex_t), (char*)(state->vb.data) + offsetof(ex_ui_vertex_t, uv0) );

        // draw elements 
        glDrawElements( GL_TRIANGLES, /* also can use GL_TRIANGLES */ 
                        (GLsizei)(state->ib.count),
                        GL_UNSIGNED_SHORT, 
                        state->ib.data );

    // unbind buffers
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    // disable texture
    glDisable(GL_TEXTURE_2D);

    // clear buf
    ex_memblock_clear ( &state->vb );
    ex_memblock_clear ( &state->ib );
    state->primitive_count = 0;
}
