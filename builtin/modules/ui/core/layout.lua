-- ======================================================================================
-- File         : layout.lua
-- Author       : Wu Jie 
-- Last Change  : 05/09/2013 | 01:29:00 AM | Thursday,May
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- public functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local calc_size = function ( _size, _parent_size, _default )
    local default = _default or _parent_size

    if _size == nil then 
        return default 
    elseif _size[1] == "auto" then
        return "auto"
    elseif _size[1] == "inherit" then
        return _parent_size
    elseif _size[1] == "none" then
        return "none"
    elseif _size[1] == "px" then
        return _size[2]
    elseif _size[1] == "%" then
        return _size[2] * _parent_size
    end

    return default
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local inherit_style = function ( _css, _parent_style )
    -- copy from parent
    local new_style = table.deepcopy( {}, _parent_style )

    -- copy from css
    new_style = table.deepcopy( new_style, _css )

    return new_style
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local do_layout = nil
do_layout = function ( _el, _block_x, _block_y, _block_w, _block_h )
    local p_style = (_el.parent ~= nil) and _el.parent._style or ui.style.default
    local rect = { 0, 0, 0, 0 }
    local style = inherit_style( _el.css, p_style )
    local x,y = _x,_y

    -- calculate current element's css to computed_style

    if _el.parent == nil then
        rect = { 0, 0, ex.canvas.width, ex.canvas.height }
    else 
        local margin_width   = style.margin_left  + style.margin_right
        local margin_height  = style.margin_top   + style.margin_bottom
        local border_width   = style.border_left  + style.border_right
        local border_height  = style.border_top   + style.border_bottom
        local padding_width  = style.padding_left + style.padding_right
        local padding_height = style.padding_top  + style.padding_bottom

        local height = ui.style.content_height( style, _el.content ) + padding_height + margin_height + border_height 
        local width = _el.parent._rect[3] 
                      - p_style.margin_left  - p_style.margin_right
                      - p_style.border_left  - p_style.border_right
                      - p_style.padding_left - p_style.padding_right

        rect = { x, y, width, height }
    end

    -- first time assign the rect, will be re-calculate after all children layout
    _el._rect = rect
    _el._style = style

    --
    x = x + style.margin_left + style.border_left + style.padding_left
    y = y + style.margin_top + style.border_top + style.padding_top

    --
    for i=1,#_el.children do
        local child_el = _el.children[i]
        local child_style = child_el._style 
        local last_rect = do_layout ( child_el, x, y )
        -- 
        if child_style.display == "block" then 
            y = y + last_rect[4]
        elseif child_style.display == "inline-block" then
            x = x + last_rect[3]
        elseif child_style.display == "inline" then 
            -- TODO
        end

    end

    return rect
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- http://www.w3.org/TR/CSS21/
-- ------------------------------------------------------------------ 

local layout = function ( _el )
    local block_x = 0
    local block_y = 0
    local block_w = ex.canvas.width
    local block_h = ex.canvas.height
    local css = _el.css
    local style = inherit_style( css, ui.style.default )

    style.width         = calc_size ( css.width,  block_w, "auto" )
    style.min_width     = calc_size ( css.min_width,  block_w, 0 )
    style.max_width     = calc_size ( css.max_width,  block_w, "none" )
    style.height        = calc_size ( css.height, block_h, "auto" )
    style.min_height    = calc_size ( css.min_height, block_h, 0 )
    style.max_height    = calc_size ( css.max_height, block_h, "none" )

    style.margin_left   = calc_size ( css.margin_left,   block_w, "auto" )
    style.margin_right  = calc_size ( css.margin_right,  block_w, "auto" )
    style.margin_top    = calc_size ( css.margin_top,    block_w, "auto" )
    style.margin_bottom = calc_size ( css.margin_bottom, block_w, "auto" )

    style.padding_left   = calc_size ( css.padding_left,   block_w, 0 )
    style.padding_right  = calc_size ( css.padding_right,  block_w, 0 )
    style.padding_top    = calc_size ( css.padding_top,    block_w, 0 )
    style.padding_bottom = calc_size ( css.padding_bottom, block_w, 0 )

    style.border_size_left   = calc_size ( css.border_size_left,   block_w, 0 )
    style.border_size_right  = calc_size ( css.border_size_right,  block_w, 0 )
    style.border_size_top    = calc_size ( css.border_size_top,    block_w, 0 )
    style.border_size_bottom = calc_size ( css.border_size_bottom, block_w, 0 )

    if style.display == "block" then
        if style.width == "auto" then
            if style.margin_left == "auto" then style.margin_left = 0 end
            if style.margin_right == "auto" then style.margin_right = 0 end
        else
            -- TODO
        end
    end

    local x = block_x + style.margin_left + style.border_left + style.padding_left
    local y = block_y + style.margin_top + style.border_top + style.padding_top

    do_layout ( _el, x, y, style.width, style.height )
end
__M.layout = layout

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
