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
    _computed_css = {}, -- computed css style

    id = "__unknown__",
    content = "", -- can be text, image, video, audio and ..., but only one of them can be set to content 
    css = ui.css.default, -- the css we define at the beginning
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
        local css = _self.css
        local x, y, w, h = _self._rect[1], _self._rect[2], _self._rect[3], _self._rect[4]
        local l, r, t, b = ui.css.left, ui.css.right, ui.css.top, ui.css.bottom
        local alpha = 200

        ex.canvas.color = ex.color4f.from_rgba_8888 ( { 249, 204, 157, alpha } )
        ex.canvas.draw_rect_4 ( x, y, w, h,
                                css.margin[1], css.margin[2], css.margin[3], css.margin[4] )

        -- draw border
        x, y, w, h = x + css.margin[l],
                     y + css.margin[t],
                     w - ( css.margin[l] + css.margin[r] ), 
                     h - ( css.margin[t] + css.margin[b] )

        ex.canvas.color = ex.color4f.from_rgba_8888 ( { 128, 128, 128, alpha } )
        ex.canvas.draw_rect_4 ( x, y, w, h,
                                css.border[1], css.border[2], css.border[3], css.border[4] )

        -- draw padding 
        x, y, w, h = x + css.border[l], 
                     y + css.border[t],
                     w - ( css.border[l] + css.border[r] ), 
                     h - ( css.border[t] + css.border[b] )

        ex.canvas.color = ex.color4f.from_rgba_8888 ( { 195, 222, 183, alpha } )
        ex.canvas.draw_rect_4 ( x, y, w, h,
                                css.padding[1], css.padding[2], css.padding[3], css.padding[4] )

        -- draw content 
        x, y, w, h = x + css.padding[l],
                     y + css.padding[t],
                     w - ( css.padding[l] + css.padding[r] ), 
                     h - ( css.padding[t] + css.padding[b] )
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

    add = function ( _self, _id, _content, _css )
        -- TODO { 
        -- local new_style = {}
        -- table.deepcopy( new_style, _self.css )
        -- table.deepcopy( new_style, _style )
        -- } TODO end 

        local new_element = ui.element( { 
            parent = _self, 
            id = _id or "__unknown__", 
            content = _content or "", 
            css = _css or {} 
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
        _self._computed_css:draw( _self._rect, _self.content  )

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
