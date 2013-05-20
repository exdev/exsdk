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

local inherit_style = function ( _style, _parent_computed_style )
    -- copy from parent
    local new_style = table.deepcopy( {}, _parent_computed_style )

    -- default those not inherit properties
    new_style.display = "block"
    new_style.width = "auto"
    new_style.height = "auto"
    new_style.min_width = "auto"
    new_style.min_height = "auto"
    new_style.max_width = "auto"
    new_style.max_height = "auto"

    -- copy from myself
    new_style = table.deepcopy( new_style, _style )

    return new_style
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local process_style = function ( _el )
    _el._computed_style = inherit_style( _el.style, (_el.parent ~= nil) and _el.parent._computed_style or ui.style.default )
    for i=1,#_el.children do
        ui.process_style (_el.children[i])
    end
end
__M.process_style = process_style

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local do_layout = nil
do_layout = function ( _el, _x, _y )
    local rect = { 0, 0, 0, 0 }
    local x,y = _x,_y
    local style = _el._computed_style

    if _el.parent == nil then
        rect = { 0, 0, ex.canvas.width, ex.canvas.height }
    else 
        local p_style = _el.parent._computed_style

        local margin_width   = style.margin[ui.style.left]  + style.margin[ui.style.right]
        local margin_height  = style.margin[ui.style.top]   + style.margin[ui.style.bottom]
        local border_width   = style.border[ui.style.left]  + style.border[ui.style.right]
        local border_height  = style.border[ui.style.top]   + style.border[ui.style.bottom]
        local padding_width  = style.padding[ui.style.left] + style.padding[ui.style.right]
        local padding_height = style.padding[ui.style.top]  + style.padding[ui.style.bottom]

        local height = ui.style.content_height( style, _el.content ) + padding_height + margin_height + border_height 
        local width = _el.parent._rect[3] 
                      - p_style.margin[ui.style.left] - p_style.margin[ui.style.right]
                      - p_style.border[ui.style.left] - p_style.border[ui.style.right]
                      - p_style.padding[ui.style.left] - p_style.padding[ui.style.right]

        rect = { x, y, width, height }
    end

    -- first time assign the rect, will be re-calculate after all children layout
    _el._rect = rect

    --
    x = x + style.margin[ui.style.left] + style.border[ui.style.left] + style.padding[ui.style.left]
    y = y + style.margin[ui.style.top] + style.border[ui.style.top] + style.padding[ui.style.top]

    --
    for i=1,#_el.children do
        local child_el = _el.children[i]
        local child_style = child_el._computed_style 
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
-- ------------------------------------------------------------------ 

local layout = function ( _el )
    ui.process_style (_el)
    do_layout ( _el, 0, 0 )
end
__M.layout = layout

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
