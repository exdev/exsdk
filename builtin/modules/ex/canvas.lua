-- ======================================================================================
-- File         : canvas.lua
-- Author       : Wu Jie 
-- Last Change  : 02/22/2013 | 16:18:16 PM | Friday,February
-- Description  : 
-- ======================================================================================

local __M = {}

local __cached_font_pages = {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function init ()
    print ( "Init canvas" )
    table.add( __cached_font_pages, ex.texture( 1024, 1024 ) )
end
__M.init = init

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function draw_texture ( _pos, _anchor, _scale, _degrees, _color, _texture )
    checkarg(_pos,"vec2f")
    checkarg(_color,"color4f")
    checkarg(_scale,"vec2f")
    checkarg(_degrees,"number")
    checkarg(_texture,"texture")

    -- local last_t = ex_c.transform_current()
    -- local t = ex_c.transform_identity()
    -- ex_c.transform_shear( t, _shear.x, _shear.y )
    -- ex_c.transform_scale( t, _scale.x, _scale.y )
    -- ex_c.transform_rotate( t, math.toradians(_degrees) )
    -- ex_c.transform_compose( t, last_t )
    -- ex_c.transform_apply( t )

    ex_c.canvas_draw_texture( _texture._cptr, 
                              _color.r, _color.g, _color.b, _color.a,
                              _pos.x, _pos.y
                              )
    -- ex_c.transform_apply( last_t )
end
__M.draw_texture = draw_texture

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function draw_text ( _pos, _color, _scale, _degrees, _font, _content ) 
    checkarg(_pos,"vec2f")
    checkarg(_color,"color4f")
    checkarg(_scale,"vec2f")
    checkarg(_degrees,"number")
    checkarg(_font,"bitmapfont")
    checkarg(_content,"string")

    local cur_x, cur_y = _pos.x, _pos.y
    local ustr_ptr = ex_c.ustr_new(_content)
    local count = ex_c.ustr_length(ustr_ptr)-1

    ex_c.canvas_hold_bitmap_drawing(true)

    for i=0,count do
        local id = ex_c.ustr_get(ustr_ptr,i)
        local charInfo = _font.charInfos[id]
        assert( charInfo, "Can't find char info by id " .. id )
        local page_texture = _font.pageInfos[charInfo.page]

        ex_c.canvas_draw_texture_region( page_texture._cptr, 
                                         _color.r, _color.g, _color.b, _color.a,
                                         charInfo.x, charInfo.y, charInfo.width, charInfo.height,
                                         cur_x, cur_y + charInfo.yoffset
                                         )
        cur_x = cur_x + charInfo.xadvance

        -- TODO { 
        -- if _font.hasKerning then
        --     cur_x = cur_x
        -- end
        -- } TODO end 
    end

    ex_c.canvas_hold_bitmap_drawing(false)
    ex_c.ustr_delete(ustr_ptr)
end
__M.draw_text = draw_text

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
