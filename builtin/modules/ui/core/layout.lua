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

local calc_size = function ( _size, _parent_size, _container_size, _default )
    if _size == nil then 
        return _default 
    elseif _size[1] == "auto" then
        return "auto"
    elseif _size[1] == "inherit" then
        return _parent_size
    elseif _size[1] == "none" then
        return "none"
    elseif _size[1] == "px" then
        return _size[2]
    elseif _size[1] == "%" then
        return _size[2] * _container_size
    end

    return _default
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- http://www.w3.org/TR/CSS21/
-- ------------------------------------------------------------------ 

local finalize_style = function ( _el, _block_w, _block_h )
    local css = _el.css
    local p_style = (_el.parent ~= nil) and _el.parent._style or ui.style.default
    local style = table.deepcopy( {}, p_style ) -- copy from parent
    style = table.deepcopy( style, css ) -- copy from css

    style.font_size              = calc_size ( css.font_size, p_style.font_size, nil, 16 )
    style.text_outline_thickness = calc_size ( css.text_outline_thickness, p_style.text_outline_thickness, nil, 0 )
    style.text_shadow_offset_x   = calc_size ( css.text_shadow_offset_x, p_style.text_shadow_offset_x, nil, 0 )
    style.text_shadow_offset_y   = calc_size ( css.text_shadow_offset_y, p_style.text_shadow_offset_y, nil, 0 )

    style.width         = calc_size ( css.width,      p_style.width,      _block_w, "auto" )
    style.min_width     = calc_size ( css.min_width,  p_style.min_width,  _block_w, 0      )
    style.max_width     = calc_size ( css.max_width,  p_style.max_width,  _block_w, "none" )
    style.height        = calc_size ( css.height,     p_style.height,     _block_h, "auto" )
    style.min_height    = calc_size ( css.min_height, p_style.min_height, _block_h, 0      )
    style.max_height    = calc_size ( css.max_height, p_style.max_height, _block_h, "none" )

    style.margin_left   = calc_size ( css.margin_left,   p_style.margin_left,   _block_w, "auto" )
    style.margin_right  = calc_size ( css.margin_right,  p_style.margin_right,  _block_w, "auto" )
    style.margin_top    = calc_size ( css.margin_top,    p_style.margin_top,    _block_w, "auto" )
    style.margin_bottom = calc_size ( css.margin_bottom, p_style.margin_bottom, _block_w, "auto" )

    style.padding_left   = calc_size ( css.padding_left,   p_style.padding_left,   _block_w, 0 )
    style.padding_right  = calc_size ( css.padding_right,  p_style.padding_right,  _block_w, 0 )
    style.padding_top    = calc_size ( css.padding_top,    p_style.padding_top,    _block_w, 0 )
    style.padding_bottom = calc_size ( css.padding_bottom, p_style.padding_bottom, _block_w, 0 )

    style.border_size_left   = calc_size ( css.border_size_left,   p_style.border_size_left,   _block_w, 0 )
    style.border_size_right  = calc_size ( css.border_size_right,  p_style.border_size_right,  _block_w, 0 )
    style.border_size_top    = calc_size ( css.border_size_top,    p_style.border_size_top,    _block_w, 0 )
    style.border_size_bottom = calc_size ( css.border_size_bottom, p_style.border_size_bottom, _block_w, 0 )

    -- based on http://www.w3.org/TR/CSS21/visudet.html#the-width-property  
    if style.display == "block" then
        -- process width
        if style.width == "auto" then
            if style.margin_left == "auto" then style.margin_left = 0 end
            if style.margin_right == "auto" then style.margin_right = 0 end
            style.width = _block_w 
                        - style.margin_left - style.margin_right 
                        - style.padding_left - style.padding_right
                        - style.border_size_left - style.border_size_right
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

        -- process height
        if style.margin_top == "auto" then style.margin_top = 0 end
        if style.margin_bottom == "auto" then style.margin_bottom = 0 end

    -- TODO { 
    -- elseif style.display == "inline-block" then
    -- } TODO end 

    end

    return style
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- the _height can be px or auto
-- the _x, _y are offsets of parent-contain-block
-- ------------------------------------------------------------------ 

local layout = function ( _el, _x, _y, _width, _height )
    -- layout current element
    local style = finalize_style(_el, _width, _height )  
    _el._style = style

    -- confirm the cx, cy
    local cx,cy = 0,0

    if style.display == "block" then
        cx,cy = 0,_y

        -- confirm the _pos here
        _el._pos = (_el.parent == nil) and { 0, 0 } or { _el.parent._pos[1] + cx, _el.parent._pos[2] + cy }

        -- block item x start from 0
        cx = style.margin_left + style.border_size_left + style.padding_left
        cy = cy + style.margin_top + style.border_size_top + style.padding_top

        -- calculate content height
        local _,content_height = ui.style.calc_content_size( style, _el.content, 0, 0, style.width )
        cy = cy + content_height 

    elseif style.display == "inline-block" then
        -- TODO:
    end

    -- layout the child
    for i=1,#_el.children do
        local child_el = _el.children[i]
        cx,cy = ui.layout ( child_el, cx, cy, style.width, style.height )
    end

    cy = cy + style.margin_bottom + style.border_size_bottom + style.padding_bottom

    -- NOTE: if the style.width and style.height is "auto", it can only be decided here after all children layouted
    local h = cy - _y
    local w = style.width 
            + style.margin_left + style.margin_right
            + style.border_size_left + style.border_size_right
            + style.padding_left + style.padding_right
    if style.height == "auto" then
        style.height = h
    end

    _el._size = { w, h }

    --
    return cx,cy
end
__M.layout = layout

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
