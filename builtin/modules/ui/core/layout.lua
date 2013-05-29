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
-- http://www.w3.org/TR/CSS21/
-- ------------------------------------------------------------------ 

local finalize_style = function ( _el, _block_x, _block_y, _block_w, _block_h )
    local css = _el.css
    local p_style = (_el.parent ~= nil) and _el.parent._style or ui.style.default
    local style = table.deepcopy( {}, p_style ) -- copy from parent
    style = table.deepcopy( new_style, _css ) -- copy from css

    style.width         = calc_size ( css.width,      _block_w, "auto" )
    style.min_width     = calc_size ( css.min_width,  _block_w, 0      )
    style.max_width     = calc_size ( css.max_width,  _block_w, "none" )
    style.height        = calc_size ( css.height,     _block_h, "auto" )
    style.min_height    = calc_size ( css.min_height, _block_h, 0      )
    style.max_height    = calc_size ( css.max_height, _block_h, "none" )

    style.margin_left   = calc_size ( css.margin_left,   _block_w, "auto" )
    style.margin_right  = calc_size ( css.margin_right,  _block_w, "auto" )
    style.margin_top    = calc_size ( css.margin_top,    _block_w, "auto" )
    style.margin_bottom = calc_size ( css.margin_bottom, _block_w, "auto" )

    style.padding_left   = calc_size ( css.padding_left,   _block_w, 0 )
    style.padding_right  = calc_size ( css.padding_right,  _block_w, 0 )
    style.padding_top    = calc_size ( css.padding_top,    _block_w, 0 )
    style.padding_bottom = calc_size ( css.padding_bottom, _block_w, 0 )

    style.border_size_left   = calc_size ( css.border_size_left,   _block_w, 0 )
    style.border_size_right  = calc_size ( css.border_size_right,  _block_w, 0 )
    style.border_size_top    = calc_size ( css.border_size_top,    _block_w, 0 )
    style.border_size_bottom = calc_size ( css.border_size_bottom, _block_w, 0 )

    -- based on http://www.w3.org/TR/CSS21/visudet.html#the-width-property  
    if style.display == "block" then
        if style.width == "auto" then
            if style.margin_left == "auto" then style.margin_left = 0 end
            if style.margin_right == "auto" then style.margin_right = 0 end
        else
            local w = style.width 
                    + style.padding_left + style.padding_right 
                    + style.border_size_left + style.border_size_right

            if w >= _block_w then
                if style.margin_left == "auto" then style.margin_left = 0 end
                if style.margin_right == "auto" then style.margin_right = 0 end
            else
                local remain = _block_w - w

                if style.margin_left == "auto" then 
                    style.margin_left = remain/2
                    style.margin_right = remain/2
                elseif style.margin_left >= remain then 
                    style.margin_right = 0 
                end
            end

            -- TODO, max_width can be "none"
            -- style.width = math.clamp( style.width, style.min_width, style.max_width )
        end
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local layout = function ( _el, _block_x, _block_y, _block_w, _block_h )
    -- layout current element
    local style = finalize_style(_el, _block_x, _block_y, _block_w, _block_h )  
    _el._style = style
    _el._rect = { _block_x, _block_y, _block_w, _block_h }

    -- layout the child
    local x = _block_x + style.margin_left + style.border_left + style.padding_left
    local y = _block_y + style.margin_top + style.border_top + style.padding_top

    for i=1,#_el.children do
        local child_el = _el.children[i]
        ui.layout ( child_el, x, y, style.width, style.height )

        -- 
        if child_style.display == "block" then 
            y = y + last_rect[4]
        elseif child_style.display == "inline-block" then
            x = x + last_rect[3]
        elseif child_style.display == "inline" then 
            -- TODO
        end

    end
end
__M.layout = layout

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
