-- ======================================================================================
-- File         : canvas.lua
-- Author       : Wu Jie 
-- Last Change  : 02/22/2013 | 16:18:16 PM | Friday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

local canvas = class ({
    __typename = "canvas",

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        width = property { get = function () return ex_c.canvas_width() end },
        height = property { get = function () return ex_c.canvas_height() end },
        color = property { 
            set = function ( _self, _v ) 
                checkarg(_v,"color4f")
                ex_c.gui_set_color(_v.r, _v.g, _v.b, _v.a) 
            end
        },

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        draw_image = function ( _image, 
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

            ex_c.gui_set_texture(_image._cptr) 
            ex_c.gui_draw_texture( _dx, _dy, _dw, _dh, -- pos
                                   _sx, _sy, _sw, _sh -- rect
                                 )
            ex_c.gui_flush()
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        draw_image_border = function ( _image, 
                                       _dx, _dy, _dw, _dh,
                                       _l, _r, _t, _b,
                                       _sx, _sy, _sw, _sh )
            checkarg(_image,"texture")
            checkarg(_dx,"number")
            checkarg(_dy,"number")
            checkarg(_dw,"number")
            checkarg(_dh,"number")
            checkarg(_l,"number")
            checkarg(_r,"number")
            checkarg(_t,"number")
            checkarg(_b,"number")

            _sx = _sx or 0
            _sy = _sy or 0
            _sw = _sw or _image.width
            _sh = _sh or _image.height

            ex_c.gui_set_texture(_image._cptr) 
            ex_c.gui_draw_border_texture( _dx, _dy, _dw, _dh, -- pos
                                          _l, _r, _t, _b, -- border
                                          _sx, _sy, _sw, _sh -- rect
                                         )
            ex_c.gui_flush()
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        draw_bitmap_text = function ( _text, _font, _dx, _dy, _dw, _dh ) 
            checkarg(_text,"string")
            checkarg(_font,"bitmapfont")
            checkarg(_dx,"number")
            checkarg(_dy,"number")
            -- TODO: auto calc size
            -- checkarg(_dw,"number")
            -- checkarg(_dh,"number")

            local cur_x, cur_y = _dx, _dy
            local ustr_ptr = ex_c.ustr_new(_text)
            local count = ex_c.ustr_length(ustr_ptr)-1

            local last_texture = ex.texture.null

            for i=0,count do
                local id = ex_c.ustr_get(ustr_ptr,i)
                local charInfo = _font.charInfos[id]
                assert( charInfo, "Can't find char info by id " .. id )
                local page_texture = _font.pageInfos[charInfo.page]

                if last_texture ~= page_texture then
                    if last_texture ~= ex.texture.null then
                        ex_c.gui_flush()
                    end
                    ex_c.gui_set_texture(page_texture._cptr) 
                    last_texture = page_texture
                end

                ex_c.gui_draw_texture( cur_x, cur_y + charInfo.yoffset, charInfo.width, charInfo.height, -- pos
                                       charInfo.x, charInfo.y, charInfo.width, charInfo.height -- rect
                                     )
                cur_x = cur_x + charInfo.xadvance

                -- TODO { 
                -- if _font.hasKerning then
                --     cur_x = cur_x
                -- end
                -- } TODO end 
            end

            ex_c.gui_flush()
            ex_c.ustr_delete(ustr_ptr)
        end,
    }
}) 
__M.canvas = canvas

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
