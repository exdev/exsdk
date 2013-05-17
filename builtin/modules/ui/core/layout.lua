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

local inherit_css = function ( _css, _parent_computed_css )
    -- copy from parent
    local new_css = table.deepcopy( {}, _parent_computed_css )

    -- default those not inherit properties
    new_css.display = "block"
    new_css.width = "auto"
    new_css.height = "auto"
    new_css.min_width = "auto"
    new_css.min_height = "auto"
    new_css.max_width = "auto"
    new_css.max_height = "auto"

    -- copy from myself
    new_css = table.deepcopy( new_css, _css )

    return new_css
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local process_css = function ( _el )
    _el._computed_css = inherit_css( _el.css, (_el.parent ~= nil) and _el.parent._computed_css or ui.css.default )
    for i=1,#_el.children do
        ui.process_css (_el.children[i])
    end
end
__M.process_css = process_css

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local do_layout = function ( _el, _x, _y )
    local rect = { 0, 0, 0, 0 }
    local x,y = _x,_y

    if _el.parent == nil then
        rect = { 0, 0, ex.canvas.width, ex.canvas.height }
    else 
        -- local next_child_el = _el.children[i+1] -- TODO?
        local css = _el._computed_css

        local padding_width  = css.padding[ui.css.left] + css.padding[ui.css.right]
        local padding_height = css.padding[ui.css.top]  + css.padding[ui.css.bottom]
        local margin_width   = css.margin[ui.css.left]  + css.margin[ui.css.right]
        local margin_height  = css.margin[ui.css.top]   + css.margin[ui.css.bottom]
        local border_width   = css.border[ui.css.left]  + css.border[ui.css.right]
        local border_height  = css.border[ui.css.top]   + css.border[ui.css.bottom]

        local height = css:content_height( _el.content ) + padding_height + margin_height + border_height 
        local width = p_width

        rect = { x, y, width, height }
    end

    --
    for i=1,#_el.children do
        local child_el = _el.children[i]
        local child_css = child_el._computed_css 
        local last_rect = do_layout ( child_el, x, y )
        -- 
        if child_css.display == "block" then 
            y = y + height
        elseif child_css.display == "inline-block" then
            x = x + width
        elseif child_css.display == "inline" then 
            -- TODO
        end

    end

    _el.rect = rect
    return rect

    -- local p_css = _el._computed_css

    -- local p_padding_width  = p_css.padding[ui.css.left] + p_css.padding[ui.css.right]
    -- local p_padding_height = p_css.padding[ui.css.top]  + p_css.padding[ui.css.bottom]
    -- local p_margin_width   = p_css.margin[ui.css.left]  + p_css.margin[ui.css.right]
    -- local p_margin_height  = p_css.margin[ui.css.top]   + p_css.margin[ui.css.bottom]
    -- local p_border_width   = p_css.border[ui.css.left]  + p_css.border[ui.css.right]
    -- local p_border_height  = p_css.border[ui.css.top]   + p_css.border[ui.css.bottom]

    -- local p_x = _el._rect[1] + p_css.margin[ui.css.left] + p_css.border[ui.css.left] + p_css.padding[ui.css.left]
    -- local p_y = _el._rect[2] + p_css.margin[ui.css.top] + p_css.border[ui.css.top] + p_css.padding[ui.css.top]
    -- local p_width = _el._rect[3] - p_padding_width - p_margin_width - p_border_width
    -- local p_height = _el._rect[4] - p_padding_height - p_margin_height - p_border_height

    -- local cur_x, cur_y = p_x, p_y

    -- for i=1,#_el.children do
    --     local child_el = _el.children[i]
    --     -- local next_child_el = _el.children[i+1] -- TODO?
    --     local css = child_el._computed_css

    --     local padding_width  = css.padding[ui.css.left] + css.padding[ui.css.right]
    --     local padding_height = css.padding[ui.css.top]  + css.padding[ui.css.bottom]
    --     local margin_width   = css.margin[ui.css.left]  + css.margin[ui.css.right]
    --     local margin_height  = css.margin[ui.css.top]   + css.margin[ui.css.bottom]
    --     local border_width   = css.border[ui.css.left]  + css.border[ui.css.right]
    --     local border_height  = css.border[ui.css.top]   + css.border[ui.css.bottom]

    --     local height = css:content_height( child_el.content ) + padding_height + margin_height + border_height 
    --     local width = p_width
    --     child_el._rect = { cur_x, cur_y, width, height }

    --     -- 
    --     if css.display == "block" then 
    --         cur_y = cur_y + height
    --     elseif css.display == "inline-block" then
    --         cur_x = cur_x + width
    --     elseif css.display == "inline" then 
    --         -- TODO
    --     end
    -- end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local layout = function ( _el )
    ui.process_css (_el)
    do_layout ( _el, 0, 0 )
end
__M.layout = layout

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
