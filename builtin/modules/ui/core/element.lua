-- ======================================================================================
-- File         : element.lua
-- Author       : Wu Jie 
-- Last Change  : 05/03/2013 | 16:47:17 PM | Friday,May
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

local element = class ({
    __typename = "element",

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _dirty = false,
    _rect = { 0, 0, 0, 0 },

    id = "__unknown__",
    content = "", -- can be text, image, video, audio and ..., but only one of them can be set to content 
    style = ui.style.default,
    parent = nil, -- element
    children = {}, -- element list

    --/////////////////////////////////////////////////////////////////////////////
    -- functions
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    add = function ( _self, _id, _content, _style )
        local new_style = {}
        table.deepcopy( new_style, _self.style )
        table.deepcopy( new_style, _style )

        local new_element = ui.element( { parent = _self, id = _id, content = _content, style = new_style } )
        table.add ( _self.children, new_element )

        return _self
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    set_dirty = function ( _self )
        _self._dirty = true
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    debug_draw = function ( _self )
        -- draw margin + border
        local style = _self.style
        local x, y, w, h = _self._rect[1], _self._rect[2], _self._rect[3], _self._rect[4]
        local l, r, t, b = ui.style.left, ui.style.right, ui.style.top, ui.style.bottom
        local alpha = 200

        ex.canvas.color = ex.color4f.from_rgba_8888 ( { 249, 204, 157, alpha } )
        ex.canvas.draw_rect_4 ( x, y, w, h,
                                style.margin[1] + style.border[1], 
                                style.margin[2] + style.border[2], 
                                style.margin[3] + style.border[3], 
                                style.margin[4] + style.border[4] )

        -- draw padding 
        x, y, w, h = x + style.margin[l] + style.border[l], 
                     y + style.margin[t] + style.border[t],
                     w - ( style.margin[l] + style.margin[r] + style.border[l] + style.border[r] ), 
                     h - ( style.margin[t] + style.margin[b] + style.border[t] + style.border[b] )

        ex.canvas.color = ex.color4f.from_rgba_8888 ( { 195, 222, 183, alpha } )
        ex.canvas.draw_rect_4 ( x, y, w, h,
                                style.padding[1], style.padding[2], style.padding[3], style.padding[4] )

        -- draw content 
        x, y, w, h = x + style.padding[l],
                     y + style.padding[t],
                     w - ( style.padding[l] + style.padding[r] ), 
                     h - ( style.padding[t] + style.padding[b] )
        ex.canvas.color = ex.color4f.from_rgba_8888( { 155, 192, 227, alpha } )
        ex.canvas.draw_filled_rect ( x, y, w, h )

        for i=1,#_self.children do
            local child = _self.children[i]
            child:debug_draw()
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    draw = function ( _self ) 
        _self.style:draw( _self._rect, _self.content  )
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- events
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- TODO
    -- ------------------------------------------------------------------ 

    on_click = function ( _self )
    end,
}) 
__M.element = element

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
