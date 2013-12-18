-- ======================================================================================
-- File         : painter.lua
-- Author       : Wu Jie 
-- Last Change  : 11/29/2013 | 16:04:28 PM | Friday,November
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- Reference 
-- http://www.w3.org/html/wg/drafts/2dcontext/html5_canvas/
-- http://www.w3schools.com/tags/ref_canvas.asp
-- http://qt-project.org/doc/qt-5.1/qtquick/qml-qtquick2-context2d.html
-- http://qt-project.org/doc/qt-5.1/qtpainter/qpainter.html
--/////////////////////////////////////////////////////////////////////////////

ex.painter = class ({
    __typename = "painter",

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        color = property { 
            set = function ( self, v ) 
                checkarg(v,"color4f")
                ex_c.painter_set_color(v.r, v.g, v.b, v.a) 
            end
        },

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        rect = function ( dx, dy, dw, dh, thickness )
            ex_c.painter_draw_rect ( dx, dy, dw, dh, thickness or 1 )
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        rect4 = function ( dx, dy, dw, dh, t, r, b, l )
            ex_c.painter_draw_rect_4 ( dx, dy, dw, dh, t, r, b, l )
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        filledRect = function ( dx, dy, dw, dh )
            ex_c.painter_draw_filled_rect ( dx, dy, dw, dh )
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        image = function ( img, 
                           dx, dy, dw, dh,
                           sx, sy, sw, sh )
            checkarg(img,"texture")
            checkarg(dx,"number")
            checkarg(dy,"number")

            dw = dw or img.width
            dh = dh or img.height
            sx = sx or 0
            sy = sy or 0
            sw = sw or img.width
            sh = sh or img.height

            ex_c.painter_set_texture(img._cptr) 
            ex_c.painter_draw_texture( dx, dy, dw, dh, -- pos
                                       sx, sy, sw, sh -- rect
                                     )
            ex_c.painter_flush()
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        slicedImage = function ( img, 
                                 dx, dy, dw, dh,
                                 t, r, b, l,
                                 sx, sy, sw, sh )
            checkarg(img,"texture")
            checkarg(dx,"number")
            checkarg(dy,"number")
            checkarg(dw,"number")
            checkarg(dh,"number")
            checkarg(t,"number")
            checkarg(r,"number")
            checkarg(b,"number")
            checkarg(l,"number")

            sx = sx or 0
            sy = sy or 0
            sw = sw or img.width
            sh = sh or img.height

            ex_c.painter_set_texture(img._cptr) 
            ex_c.painter_draw_sliced_texture( dx, dy, dw, dh,   -- pos
                                              t, r, b, l,       -- border
                                              sx, sy, sw, sh    -- rect
                                            )
            ex_c.painter_flush()
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        text = function ( txt, fnt, dx, dy, dw, dh ) 
            checkarg(txt,"string")
            checkarg(fnt,"font")
            checkarg(dx,"number")
            checkarg(dy,"number")
            dw = dw or -1
            dh = dh or -1

            ex_c.painter_draw_text( txt, fnt._cptr, 
                                    dx, dy, dw, dh -- pos
                                  )
            ex_c.painter_flush()
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        outlineText = function ( txt, fnt, color, outlineColor, outlineThickness, dx, dy, dw, dh ) 
            fnt.outlineType = 1
            fnt.outlineThickness = outlineThickness

            ex.painter.color = outlineColor
            ex.painter.text( txt, fnt, dx, dy, dw, dh ) 

            fnt.outlineType = 0
            fnt.outlineThickness = 0.0

            ex.painter.color = color
            ex.painter.text( txt, fnt, dx, dy, dw, dh ) 
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        shadowText = function ( txt, fnt, color, shadowColor, offset, dx, dy, dw, dh ) 
            fnt.outlineType = 0

            ex.painter.color = shadowColor
            ex.painter.text( txt, fnt, dx + offset.x, dy + offset.y, dw, dh ) 

            ex.painter.color = color
            ex.painter.text( txt, fnt, dx, dy, dw, dh ) 
        end,

        -- ------------------------------------------------------------------ 
        -- Desc: 
        -- ------------------------------------------------------------------ 

        bitmapText = function ( txt, fnt, dx, dy, dw, dh ) 
            checkarg(txt,"string")
            checkarg(fnt,"bitmapfont")
            checkarg(dx,"number")
            checkarg(dy,"number")
            -- TODO: auto calc size
            -- checkarg(dw,"number")
            -- checkarg(dh,"number")

            local cur_x, cur_y = dx, dy

            local last_texture = ex.texture.null
            local last_id = -1
            local id = -1
            local id_list = ex_c.utf8_list(txt)

            for i=1,#id_list do
                local id = id_list[i]

                -- if this is \n(10) or \r(13)
                if id == 10 or id == 13 then
                    cur_y = cur_y + fnt.lineHeight
                    cur_x = dx
                else
                    local charInfo = fnt.charInfos[id]
                    assert( charInfo, "Can't find char info by id " .. id )

                    -- adjust kerning
                    if i > 1 and fnt.hasKerning then
                        cur_x = cur_x + fnt:getKerning( last_id, id )
                    end

                    -- if this is space(32)
                    if id == 32 then
                        cur_x = cur_x + charInfo.xadvance
                    else
                        local page_texture = fnt.pageInfos[charInfo.page]

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
