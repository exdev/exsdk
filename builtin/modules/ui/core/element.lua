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
    _enable_debug = false,
    _debug_level = 1,
    _computed_style = {}, -- computed style

    id = "__unknown__",
    content = "", -- can be text, image, video, audio and ..., but only one of them can be set to content 
    style = ui.style.default, -- the style we define at the beginning
    parent = nil, -- element
    children = {}, -- element list

    --/////////////////////////////////////////////////////////////////////////////
    -- private functions
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    _do_debug_draw = function ( _self, _level )
        local cur_level = _level
        if cur_level == nil then 
            cur_level = 1
        end
        if cur_level == 0 then 
            return
        end

        -- draw margin
        local style = _self.style
        local x, y, w, h = _self._rect[1], _self._rect[2], _self._rect[3], _self._rect[4]
        local l, r, t, b = ui.style.left, ui.style.right, ui.style.top, ui.style.bottom
        local alpha = 200

        ex.canvas.color = ex.color4f.from_rgba_8888 ( { 249, 204, 157, alpha } )
        ex.canvas.draw_rect_4 ( x, y, w, h,
                                style.margin[1], style.margin[2], style.margin[3], style.margin[4] )

        -- draw border
        x, y, w, h = x + style.margin[l],
                     y + style.margin[t],
                     w - ( style.margin[l] + style.margin[r] ), 
                     h - ( style.margin[t] + style.margin[b] )

        ex.canvas.color = ex.color4f.from_rgba_8888 ( { 128, 128, 128, alpha } )
        ex.canvas.draw_rect_4 ( x, y, w, h,
                                style.border[1], style.border[2], style.border[3], style.border[4] )

        -- draw padding 
        x, y, w, h = x + style.border[l], 
                     y + style.border[t],
                     w - ( style.border[l] + style.border[r] ), 
                     h - ( style.border[t] + style.border[b] )

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
            child:_do_debug_draw(cur_level-1)
        end
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- functions
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    add = function ( _self, _id, _content, _style )
        local new_element = ui.element( { 
            parent = _self, 
            id = _id or "__unknown__", 
            content = _content or "", 
            style = _style or {} 
        } )
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

    debug_draw = function ( _self, _enable, _level )
        _self._enable_debug = (_enable == nil) and true or _enable
        _self._debug_level = (_level == nil) and 1 or _level
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    draw = function ( _self ) 
        _self._dirty = false;
        _self._computed_style:draw( _self._rect, _self.content  )

        for i=1,#_self.children do
            local child_el = _self.children[i]
            child_el:draw ()
        end

        if _self._enable_debug then
            _self:_do_debug_draw(_self._debug_level)
        end
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
