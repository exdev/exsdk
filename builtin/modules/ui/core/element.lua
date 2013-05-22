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
    _computed_style = {}, -- computed style from element.css

    id = "__unknown__",
    content = "", -- can be text, image, video, audio and ..., but only one of them can be set to content 
    css = {}, -- the css table we parsed from ui.css.build()...done()
    parent = nil, -- element
    children = {}, -- element list

    --/////////////////////////////////////////////////////////////////////////////
    -- private functions
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    _do_draw () function ( _self )
        local style = _self._computed_style
        local rect = _self._rect

        local content = _self.content
        local x, y, w, h = rect[1], rect[2], rect[3], rect[4]

        local margin_R, margin_T, margin_B, margin_L 
            = style.margin_right, style.margin_top, style.margin_bottom, style.margin_left

        local border_R, border_T, border_B, border_L 
            = style.border_size_right, style.border_size_top, style.border_size_bottom, style.border_size_left

        local padding_R, padding_T, padding_B, padding_L 
            = style.padding_right, style.padding_top, style.padding_bottom, style.padding_left

        -- margin step in
        x = x + margin_L
        y = y + margin_T
        w = w - margin_L - margin_R
        h = h - margin_T - margin_B

        -- draw border
        local color = ex.color4f.from_rgba_8888(style.border_color)
        ex.canvas.color = color
        ex.canvas.draw_rect_4( x, y, w, h, border_T, border_R, border_B, border_L ) 

        -- border step in
        x = x + border_L
        y = y + border_T
        w = w - border_L - border_R
        h = h - border_T - border_B

        -- draw background rect
        if style.background_color[4] ~= 0 then
            local color = ex.color4f.from_rgba_8888(style.background_color)
            ex.canvas.color = color
            ex.canvas.draw_filled_rect( x, y, w, h ) 
        end

        -- padding step in
        x = x + padding_L
        y = y + padding_T
        w = w - padding_L - padding_R
        h = h - padding_T - padding_B

        -- draw content 
        local tname = typename (content)
        if tname == "string" then 
            if content == "" then 
                return
            end

            local color = ex.color4f.from_rgba_8888(style.color)
            ex.canvas.color = color

            local font = ui.style.setup_font(style)
            local text_done = false

            -- draw outline text
            if style.text_outline[1] > 0 then 
                local color2 = ex.color4f.from_rgba_8888( style.text_outline[2] )
                ex.canvas.draw_outline_text( content, font, color, color2, style.text_outline[1], x, y ) 
                text_done = true
            end

            -- draw shadow text
            local shadow_x, shadow_y = style.text_shadow[1][1], style.text_shadow[1][2] 
            if shadow_x > 0 or shadow_y > 0 then 
                local color2 = ex.color4f.from_rgba_8888( style.text_shadow[2] )
                ex.canvas.draw_shadow_text( content, font, color, color2, ex.vec2f(shadow_x, shadow_y), x, y ) 
                text_done = true
            end

            -- draw normal text
            if text_done == false then
                ex.canvas.draw_text( content, font, x, y ) 
            end
        end
    end,

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

    add = function ( _self, _id, _content, _css )
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
        _self._do_draw()

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
