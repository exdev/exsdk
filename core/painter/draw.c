// ======================================================================================
// File         : draw.c
// Author       : Wu Jie 
// Last Change  : 11/29/2013 | 16:43:14 PM | Friday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include "SDL_opengl.h"

#include "exsdk.h"
// #include "gl/gl_inc.h"

#include "utf8proc.h"

#include <ft2build.h>
#include FT_FREETYPE_H

///////////////////////////////////////////////////////////////////////////////
// TEMP HACK
///////////////////////////////////////////////////////////////////////////////

// TEMP HACK: copy from SDL, if SDL structure changed, we need to change this block { 

typedef struct
{
    GLuint texture;
    GLenum type;
    GLfloat texw;
    GLfloat texh;
    GLenum format;
    GLenum formattype;
    void *pixels;
    int pitch;
    SDL_Rect locked_rect;

    /* YV12 texture support */
    SDL_bool yuv;
    GLuint utexture;
    GLuint vtexture;

    void *fbo; // GL_FBOList *fbo;
} GL_TextureData;

struct SDL_Texture
{
    const void *magic;
    Uint32 format;              /**< The pixel format of the texture */
    int access;                 /**< SDL_TextureAccess */
    int w;                      /**< The width of the texture */
    int h;                      /**< The height of the texture */
    int modMode;                /**< The texture modulation mode */
    SDL_BlendMode blendMode;    /**< The texture blend mode */
    Uint8 r, g, b, a;           /**< Texture modulation values */

    SDL_Renderer *renderer;

    /* Support for formats not supported directly by the renderer */
    SDL_Texture *native;
    void *yun; // SDL_SW_YUVTexture *yuv;
    void *pixels;
    int pitch;
    SDL_Rect locked_rect;

    void *driverdata;           /**< Driver specific texture representation */

    SDL_Texture *prev;
    SDL_Texture *next;
};
// } TEMP end 

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_painter_draw_texture ( int _dx, int _dy, int _dw, int _dh,
                               int _sx, int _sy, int _sw, int _sh )
{
    ex_painter_state_t *state;

    size_t index_start;
    ex_painter_vertex_t *verts;
    uint16 *indices;

    SDL_Texture *texture;
    GL_TextureData *texture_data;
    float tex_l, tex_t, tex_r, tex_b, w, h;
    int sx, sy, sw, sh;
    float dx, dy, dw, dh;

    //
    state = ex_painter_state();
    texture = (SDL_Texture *)state->texture;
    texture_data = (GL_TextureData *)texture->driverdata;

    // create vertex and indices
    tex_l = 0.0f;
    tex_r = 1.0f; // texture_data->texw;
    tex_t = 0.0f;
    tex_b = 1.0f; // texture_data->texh;

    dx = (float)_dx;
    dy = (float)_dy;
    dw = (float)_dw;
    dh = (float)_dh;

    sx = _sx;
    sy = _sy;
    sw = _sw;
    sh = _sh;

    w = texture->w;
    h = texture->h;

    tex_l += sx / w;
    tex_t -= sy / h;
    tex_r -= (w - sx - sw) / w;
    tex_b += (h - sy - sh) / h;

    // NOTE: texture_data->texw in GL_TEXTURE_2D is texture->w/power_of_2(texture->w)
    //                          in GL_TEXTURE_RECTANGLE_ARB is texture->w  
    tex_l *= texture_data->texw;
    tex_t *= texture_data->texh;
    tex_r *= texture_data->texw;
    tex_b *= texture_data->texh;

    // ui_vb
    index_start = state->vb.count;
    verts = (ex_painter_vertex_t *)ex_memblock_request ( &state->vb, 4 );

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

void ex_painter_draw_sliced_texture ( int _dx, int _dy, int _dw, int _dh,
                                      int _t, int _r, int _b, int _l, 
                                      int _sx, int _sy, int _sw, int _sh )
{
#if 0
    ex_painter_state_t *state;

    size_t index_start;
    ex_painter_vertex_t *verts;
    uint16 *indices;
    uint16 index_preset[] = {
        4, 0, 5, 5, 0, 1, 5, 1, 6, 6, 1, 2, 6, 2, 7, 7, 2, 3,
        8, 4, 9, 9, 4, 5, 9, 5, 10, 10, 5, 6, 10, 6, 11, 11, 6, 7,
        12, 8, 13, 13, 8, 9, 13, 9, 14, 14, 9, 10, 14, 10, 15, 15, 10, 11
    };
    int i;

    ALLEGRO_BITMAP *texture;
    ALLEGRO_BITMAP_OGL *texture_data;
    float tex_l, tex_t, tex_r, tex_b, w, h, true_w, true_h;
    float x0, x1, x2, x3, y0, y1, y2, y3;
    float s0, s1, s2, s3, t0, t1, t2, t3;

    //
    state = ex_painter_state();
    texture = (ALLEGRO_BITMAP *)state->texture;
    texture_data = (ALLEGRO_BITMAP_OGL *)state->texture;

    // create vertex and indices
    tex_l = texture_data->left;
    tex_r = texture_data->right;
    tex_t = texture_data->top;
    tex_b = texture_data->bottom;

    x0 = (float)_dx;
    x1 = (float)_dx + (float)_l;
    x2 = (float)_dx + (float)_dw - (float)_r;
    x3 = (float)_dx + (float)_dw;

    y0 = (float)_dy;
    y1 = (float)_dy + (float)_t;
    y2 = (float)_dy + (float)_dh - (float)_b;
    y3 = (float)_dy + (float)_dh;

    w = texture->w;
    h = texture->h;
    true_w = texture_data->true_w;
    true_h = texture_data->true_h;

    s0 = tex_l + _sx / true_w;
    s1 = tex_l + (_sx + _l) / true_w;
    s2 = tex_r - (w - _sx - _sw + _r) / true_w;
    s3 = tex_r - (w - _sx - _sw) / true_w;

    t0 = tex_t - _sy / true_h;
    t1 = tex_t - (_sy + _t) / true_h;
    t2 = tex_b + (h - _sy - _sh + _b) / true_h;
    t3 = tex_b + (h - _sy - _sh) / true_h;

    // ui_vb
    index_start = state->vb.count;
    verts = (ex_painter_vertex_t *)ex_memblock_request ( &state->vb, 16 );

    // row 1
    verts[0].pos.x = x0; verts[0].pos.y = y0;
    verts[0].uv0.x = s0; verts[0].uv0.y = t0;
    verts[0].color = state->color;

    verts[1].pos.x = x1; verts[1].pos.y = y0;
    verts[1].uv0.x = s1; verts[1].uv0.y = t0;
    verts[1].color = state->color;

    verts[2].pos.x = x2; verts[2].pos.y = y0;
    verts[2].uv0.x = s2; verts[2].uv0.y = t0;
    verts[2].color = state->color;

    verts[3].pos.x = x3; verts[3].pos.y = y0;
    verts[3].uv0.x = s3; verts[3].uv0.y = t0;
    verts[3].color = state->color;

    // row 2
    verts[4].pos.x = x0; verts[4].pos.y = y1;
    verts[4].uv0.x = s0; verts[4].uv0.y = t1;
    verts[4].color = state->color;

    verts[5].pos.x = x1; verts[5].pos.y = y1;
    verts[5].uv0.x = s1; verts[5].uv0.y = t1;
    verts[5].color = state->color;

    verts[6].pos.x = x2; verts[6].pos.y = y1;
    verts[6].uv0.x = s2; verts[6].uv0.y = t1;
    verts[6].color = state->color;

    verts[7].pos.x = x3; verts[7].pos.y = y1;
    verts[7].uv0.x = s3; verts[7].uv0.y = t1;
    verts[7].color = state->color;

    // row 3
    verts[8].pos.x = x0; verts[8].pos.y = y2;
    verts[8].uv0.x = s0; verts[8].uv0.y = t2;
    verts[8].color = state->color;

    verts[9].pos.x = x1; verts[9].pos.y = y2;
    verts[9].uv0.x = s1; verts[9].uv0.y = t2;
    verts[9].color = state->color;

    verts[10].pos.x = x2; verts[10].pos.y = y2;
    verts[10].uv0.x = s2; verts[10].uv0.y = t2;
    verts[10].color = state->color;

    verts[11].pos.x = x3; verts[11].pos.y = y2;
    verts[11].uv0.x = s3; verts[11].uv0.y = t2;
    verts[11].color = state->color;

    // row 4
    verts[12].pos.x = x0; verts[12].pos.y = y3;
    verts[12].uv0.x = s0; verts[12].uv0.y = t3;
    verts[12].color = state->color;

    verts[13].pos.x = x1; verts[13].pos.y = y3;
    verts[13].uv0.x = s1; verts[13].uv0.y = t3;
    verts[13].color = state->color;

    verts[14].pos.x = x2; verts[14].pos.y = y3;
    verts[14].uv0.x = s2; verts[14].uv0.y = t3;
    verts[14].color = state->color;

    verts[15].pos.x = x3; verts[15].pos.y = y3;
    verts[15].uv0.x = s3; verts[15].uv0.y = t3;
    verts[15].color = state->color;

    ex_vec2f_mul_mat33f ( &verts[0 ].pos, &verts[0 ].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[1 ].pos, &verts[1 ].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[2 ].pos, &verts[2 ].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[3 ].pos, &verts[3 ].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[4 ].pos, &verts[4 ].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[5 ].pos, &verts[5 ].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[6 ].pos, &verts[6 ].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[7 ].pos, &verts[7 ].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[8 ].pos, &verts[8 ].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[9 ].pos, &verts[9 ].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[10].pos, &verts[10].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[11].pos, &verts[11].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[12].pos, &verts[12].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[13].pos, &verts[13].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[14].pos, &verts[14].pos, &state->matrix );
    ex_vec2f_mul_mat33f ( &verts[15].pos, &verts[15].pos, &state->matrix );

    // ui_ib
    indices = (uint16 *)ex_memblock_request ( &state->ib, 54 );
    for ( i = 0; i < EX_ARRAY_COUNT(index_preset); ++i ) {
        indices[i] = index_preset[i];
    }

    ++state->primitive_count;
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __draw_glyph ( ex_font_t *_font, uint _prev_ft_index, uint _ft_index, int _dx, int _dy ) {
   ex_glyph_t *glyph;
   int advance = 0;

   //
   glyph = ex_font_get_glyph ( _font, _ft_index );

   //
   advance += ex_font_get_kerning( _font, _prev_ft_index, _ft_index );
   if ( glyph->page ) {
       ex_painter_set_texture ( glyph->page );
       ex_painter_draw_texture ( _dx + advance + glyph->offset_x, _dy + glyph->offset_y, glyph->w, glyph->h,
                                 glyph->x, glyph->y, glyph->w, glyph->h );
   }
   advance += glyph->advance_x;

   return advance;
} 

void ex_painter_draw_text ( const char *_text, 
                            ex_font_t *_font,
                            int _dx, int _dy, int _dw, int _dh ) 
{
    const char *str;
    int ch;
    uint ft_index, prev_ft_index;
    int cur_x, cur_y;
    int advance = 0;

    FT_Face face;
    FT_Size_Metrics metrics;
    int height, line_gap;

    str = _text;
    prev_ft_index = -1;
    cur_x = _dx;
    cur_y = _dy;

    face = _font->face;
    metrics = face->size->metrics;
    height = metrics.height >> 6;
    line_gap = (metrics.ascender >> 6) - (metrics.descender >> 6) - height;

    while ( *str ) {
        str += utf8proc_iterate ((const uint8_t *)str, -1, &ch);
        advance = 0;
        ft_index = FT_Get_Char_Index ( face, ch );

        // if this is \n(10) or \r(13)
        if ( ch == 10 || ch == 13 ) {
            cur_x = _dx;
            prev_ft_index = -1;
            cur_y = cur_y + height + line_gap;
        }
        else {
            advance = __draw_glyph ( _font, prev_ft_index, ft_index, cur_x, cur_y );
            cur_x += advance;
            prev_ft_index = ft_index;
        }
    }
}

//------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------ 

void ex_painter_draw_rect ( int _dx, int _dy, int _dw, int _dh, int _thickness ) {
    ex_painter_draw_rect_4 ( _dx, _dy, _dx + _dw, _dy + _dh, 
                             _thickness, _thickness, _thickness, _thickness );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_painter_draw_rect_4 ( int _dx, int _dy, int _dw, int _dh, 
                              int _t, int _r, int _b, int _l ) {
#if 0
    ex_painter_state_t *state;
    ALLEGRO_COLOR al_color;

    state = ex_painter_state();
    al_color = al_map_rgba_f ( state->color.r, state->color.g, state->color.b, state->color.a );

    al_draw_rectangle_4 ( _dx, _dy, _dx + _dw, _dy + _dh, al_color, 
                          _t, _r, _b, _l );
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_painter_draw_filled_rect ( int _dx, int _dy, int _dw, int _dh ) {
#if 0
    ex_painter_state_t *state;
    ALLEGRO_COLOR al_color;

    state = ex_painter_state();
    al_color = al_map_rgba_f ( state->color.r, state->color.g, state->color.b, state->color.a );

    al_draw_filled_rectangle ( _dx, _dy, _dx + _dw, _dy + _dh, al_color );
#endif
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_painter_flush () {
    ex_painter_state_t *state;
    SDL_Texture *texture;
    GL_TextureData *texture_data;

    state = ex_painter_state();
    // nothing to draw
    if ( state->vb.count == 0 )
        return;

    texture = (SDL_Texture *)state->texture;
    texture_data = (GL_TextureData *)texture->driverdata;

    // bind texture
    // glEnable(GL_TEXTURE_2D);
    // glBindTexture ( GL_TEXTURE_2D, texture_data->texture );
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glEnable (texture_data->type);
    glBindTexture ( texture_data->type, texture_data->texture );

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

        glVertexPointer  ( 2, GL_FLOAT, sizeof(ex_painter_vertex_t), state->vb.data );
        glColorPointer   ( 4, GL_FLOAT, sizeof(ex_painter_vertex_t), (char*)(state->vb.data) + offsetof(ex_painter_vertex_t, color) );
        glTexCoordPointer( 2, GL_FLOAT, sizeof(ex_painter_vertex_t), (char*)(state->vb.data) + offsetof(ex_painter_vertex_t, uv0) );

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
    // glDisable(GL_TEXTURE_2D);
    glDisable (texture_data->type);

    // clear buf
    ex_memblock_clear ( &state->vb );
    ex_memblock_clear ( &state->ib );
    state->primitive_count = 0;
}
