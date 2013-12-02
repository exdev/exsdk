-- ======================================================================================
-- File         : painter.lua
-- Author       : Wu Jie 
-- Last Change  : 11/29/2013 | 16:04:28 PM | Friday,November
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- Reference 
-- http://www.w3.org/html/wg/drafts/2dcontext/html5_canvas/
-- http://www.w3schools.com/tags/ref_canvas.asp
-- http://qt-project.org/doc/qt-5.1/qtquick/qml-qtquick2-context2d.html
-- http://qt-project.org/doc/qt-5.1/qtpainter/qpainter.html
--/////////////////////////////////////////////////////////////////////////////

local painter = class ({
    __typename = "painter",

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        color = property { 
            set = function ( _self, _v ) 
                checkarg(_v,"color4f")
                ex_c.painter_set_color(_v.r, _v.g, _v.b, _v.a) 
            end
        },

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        rect = function ( _dx, _dy, _dw, _dh, _thickness )
            ex_c.painter_draw_rect ( _dx, _dy, _dw, _dh, _thickness or 1 )
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        rect4 = function ( _dx, _dy, _dw, _dh, _t, _r, _b, _l )
            ex_c.painter_draw_rect_4 ( _dx, _dy, _dw, _dh, _t, _r, _b, _l )
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        filled_rect = function ( _dx, _dy, _dw, _dh )
            ex_c.painter_draw_filled_rect ( _dx, _dy, _dw, _dh )
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        image = function ( _image, 
                           _dx, _dy, _dw, _dh,
                           _sx, _sy, _sw, _sh )
            checkarg(_image,"texture")
            checkarg(_dx,"number")
            checkarg(_dy,"number")

            _dw = _dw or _image.width
            _dh = _dh or _image.height
            _sx = _sx or 0
            _sy = _sy or 0
            _sw = _sw or _image.width
            _sh = _sh or _image.height

            ex_c.painter_set_texture(_image._cptr) 
            ex_c.painter_draw_texture( _dx, _dy, _dw, _dh, -- pos
                                       _sx, _sy, _sw, _sh -- rect
                                     )
            ex_c.painter_flush()
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        sliced_image = function ( _image, 
                                  _dx, _dy, _dw, _dh,
                                  _t, _r, _b, _l,
                                  _sx, _sy, _sw, _sh )
            checkarg(_image,"texture")
            checkarg(_dx,"number")
            checkarg(_dy,"number")
            checkarg(_dw,"number")
            checkarg(_dh,"number")
            checkarg(_t,"number")
            checkarg(_r,"number")
            checkarg(_b,"number")
            checkarg(_l,"number")

            _sx = _sx or 0
            _sy = _sy or 0
            _sw = _sw or _image.width
            _sh = _sh or _image.height

            ex_c.painter_set_texture(_image._cptr) 
            ex_c.painter_draw_sliced_texture( _dx, _dy, _dw, _dh,   -- pos
                                              _t, _r, _b, _l,       -- border
                                              _sx, _sy, _sw, _sh    -- rect
                                            )
            ex_c.painter_flush()
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        text = function ( _text, _font, _dx, _dy, _dw, _dh ) 
            checkarg(_text,"string")
            checkarg(_font,"font")
            checkarg(_dx,"number")
            checkarg(_dy,"number")
            _dw = _dw or -1
            _dh = _dh or -1

            ex_c.painter_draw_text( _text, _font._cptr, 
                                    _dx, _dy, _dw, _dh -- pos
                                  )
            ex_c.painter_flush()
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        outline_text = function ( _text, _font, _color, _outline_color, _outline_thickness, _dx, _dy, _dw, _dh ) 
            _font.outline_type = 1
            _font.outline_thickness = _outline_thickness

            ex.painter.color = _outline_color
            ex.painter.text( _text, _font, _dx, _dy, _dw, _dh ) 

            _font.outline_type = 0
            _font.outline_thickness = 0.0

            ex.painter.color = _color
            ex.painter.text( _text, _font, _dx, _dy, _dw, _dh ) 
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        shadow_text = function ( _text, _font, _color, _shadow_color, _offset, _dx, _dy, _dw, _dh ) 
            _font.outline_type = 0

            ex.painter.color = _shadow_color
            ex.painter.text( _text, _font, _dx + _offset.x, _dy + _offset.y, _dw, _dh ) 

            ex.painter.color = _color
            ex.painter.text( _text, _font, _dx, _dy, _dw, _dh ) 
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        bitmap_text = function ( _text, _font, _dx, _dy, _dw, _dh ) 
            checkarg(_text,"string")
            checkarg(_font,"bitmapfont")
            checkarg(_dx,"number")
            checkarg(_dy,"number")
            -- TODO: auto calc size
            -- checkarg(_dw,"number")
            -- checkarg(_dh,"number")

            local cur_x, cur_y = _dx, _dy

            local last_texture = ex.texture.null
            local last_id = -1
            local id = -1
            local id_list = ex_c.utf8_list(_text)

            for i=1,#id_list do
                local id = id_list[i]

                -- if this is \n(10) or \r(13)
                if id == 10 or id == 13 then
                    cur_y = cur_y + _font.lineHeight
                    cur_x = _dx
                else
                    local charInfo = _font.charInfos[id]
                    assert( charInfo, "Can't find char info by id " .. id )

                    -- adjust kerning
                    if i > 1 and _font.hasKerning then
                        cur_x = cur_x + _font:get_kerning( last_id, id )
                    end

                    -- if this is space(32)
                    if id == 32 then
                        cur_x = cur_x + charInfo.xadvance
                    else
                        local page_texture = _font.pageInfos[charInfo.page]

                        if last_texture ~= page_texture then
                            if last_texture ~= ex.texture.null then
                                ex_c.painter_flush()
                            end
                            ex_c.painter_set_texture(page_texture._cptr) 
                            last_texture = page_texture
                        end

                        -- draw
                        ex_c.painter_draw_texture( 
                            cur_x + charInfo.xoffset, cur_y + charInfo.yoffset, charInfo.width, charInfo.height, -- pos
                            charInfo.x, charInfo.y, charInfo.width, charInfo.height -- rect
                        )
                        cur_x = cur_x + charInfo.xadvance
                    end
                end

                last_id = id
            end

            ex_c.painter_flush()
        end,
    }
}) 
__M.painter = painter

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
