-- ======================================================================================
-- File         : layout.lua
-- Author       : Wu Jie 
-- Last Change  : 05/09/2013 | 01:29:00 AM | Thursday,May
-- Description  : 
-- ======================================================================================

local __M = {}

local cur_x, cur_y = 0, 0

--/////////////////////////////////////////////////////////////////////////////
-- public functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local do_layout = function ( _root )
    _root._rect = { cur_x, cur_y, _root.style.width, _root.style.height }

    for i=1,#_root.children do
        local el = _root.children[i]
        local next_el = _root.children[i+1]
        local style = el.style

        local padding_width  = style.padding[ui.style.left] + style.padding[ui.style.right]
        local padding_height = style.padding[ui.style.top]  + style.padding[ui.style.bottom]
        local margin_width   = style.margin[ui.style.left]  + style.margin[ui.style.right]
        local margin_height  = style.margin[ui.style.top]   + style.margin[ui.style.bottom]
        local border_width   = style.border[ui.style.left]  + style.border[ui.style.right]
        local border_height  = style.border[ui.style.top]   + style.border[ui.style.bottom]

        -- TODO: you can't doing it like this { 
        local height = style:content_height( el.content ) + padding_height + margin_height + border_height 
        local width = style.width
        el._rect = { cur_x, cur_y, width, height }
        -- } TODO end 

        -- TODO: should recursively get parent style { 
        -- margin_bottom = style.margin[3]
        -- next_margin_top = next_el ? 0 : next_el.style.margin[3]
        -- } TODO end 
        cur_y = cur_y + height
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local layout = function ( _root )
    cur_x, cur_y = 0, 0
    do_layout (_root)
end
__M.layout = layout

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
