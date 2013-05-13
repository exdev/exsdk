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
        table.copy( new_style, _self.style )
        table.copy( new_style, _style )

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
        ex.canvas.color = ex.color4f ( 0.0, 0.5, 1.0, 0.2 )
        ex.canvas.draw_filled_rect ( _self._rect[1], _self._rect[2], _self._rect[3], _self._rect[4] )

        ex.canvas.color = ex.color4f.black
        ex.canvas.draw_rect ( _self._rect[1], _self._rect[2], _self._rect[3], _self._rect[4], 1 )

        for i=1,#_self.children do
            local child = _self.children[i]
            child:debug_draw()
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    draw = function ( _self ) 
        ui.style.draw( _self.style,  _self._rect, _self.content  )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    content_height = function ( _self )
        local tname = typename (_self.content)
        if tname == "string" then 

            local font = nil
            for i=1,#_self.style.font_family do
                font = ui.style.fonts[_self.style.font_family[i]]
                if font ~= nil then 
                    break 
                end
            end
            assert ( font ~= nil )

            font.size = _self.style.font_size
            return font.height
        elseif tname == "texture" then
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
