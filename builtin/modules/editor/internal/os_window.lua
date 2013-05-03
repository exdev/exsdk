-- ======================================================================================
-- File         : os_window.lua
-- Author       : Wu Jie 
-- Last Change  : 05/03/2013 | 09:20:29 AM | Friday,May
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

local os_window = class ({
    __typename = "os_window",

    -- constructor & destructor
    __init = function ( _self, _w, _h )
        checkarg(_w,"number")
        checkarg(_h,"number")

        _self._cptr = ex_c.create_window (_w,_h)

        table.add( editor.os_window.window_list, _self )
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _cptr = ex_c.null,
    element = ui.element.null,
    need_repaint = true,

    --/////////////////////////////////////////////////////////////////////////////
    -- functions
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    dispatch_event = function ( _self, _os_event )
        local event = ui.event

        if _os_event.type == event_type.key_down then
            -- print( "key down " .. _os_event.keycode )
            event.type = _os_event.type 
            event.keycode = _os_event.keycode 
        elseif _os_event.type == event_type.key_up then
            -- print( "key up " .. _os_event.keycode )
            event.type = _os_event.type 
            event.keycode = _os_event.keycode 
        end

        -- TODO: dispatch on_event on active element 
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    draw = function ( _self )
        if _self.need_repaint then
            _self:_repaint_all(_self.element) 
            _self.need_repaint = false
            return
        end

        _self:_draw_recursively (_self.element)
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    update = function ( _self )
        -- TODO: I think a time event will be better
        -- for i=1,#elements do
        --     local el = elements[i]
        --     if el.on_update ~= nil then
        --         elements[i]:on_update()
        --     end
        -- end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    _draw_recursively = function ( _self, _el )
        if _el._dirty then
            _self:_repaint_all(_el) 
            return
        end

        for i=1,#_el.children do
            local child_el = _el.children[i]
            if child_el._dirty then 
                _self:_repaint_all(child_el) 
            else
                _self:_draw_recursively(child_el)
            end
        end
    end,

    _repaint_all = function ( _self, _el )
        -- repaint by parent first
        _el:on_repaint()
        _el._dirty = false

        for i=1,#_el.children do
            local child_el = _el.children[i]
            child_el:on_repaint()
            child_el._dirty = false
        end
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {
        window_list = {},

        on_event = function ( _os_event )
            for i=1,#editor.os_window.window_list do
                local win = editor.os_window.window_list[i]
                if win._cptr == _os_event.display then
                    win:dispatch_event (_os_event)
                    break
                end
            end
        end,
        
        on_repaint = function ( _os_event )
            for i=1,#editor.os_window.window_list do
                local win = editor.os_window.window_list[i]
                win.need_repaint = true
            end
        end,

        on_draw = function ( _os_event )
            for i=1,#editor.os_window.window_list do
                local win = editor.os_window.window_list[i]
                win:draw()
            end
        end,

        on_update = function ( _os_event )
            for i=1,#editor.os_window.window_list do
                local win = editor.os_window.window_list[i]
                win:update()
            end
        end,

        on_destroy = function ( _cptr )
            for i=1,#editor.os_window.window_list do
                local win = editor.os_window.window_list[i]
                if win._cptr == _cptr then
                    table.fast_remove_at( editor.os_window.window_list, i )
                    break
                end
            end
        end,
    },
}) 
__M.os_window = os_window

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
