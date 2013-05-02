-- ======================================================================================
-- File         : window.lua
-- Author       : Wu Jie 
-- Last Change  : 04/26/2013 | 09:35:05 AM | Friday,April
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

local window = class ({
    __typename = "window",

    -- constructor & destructor
    __init = function ( _self, _w, _h )
        checkarg(_w,"number")
        checkarg(_h,"number")

        _self._cptr = ex_c.create_window (_w,_h)

        table.add( editor.window.window_list, _self )
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _cptr = ex_c.null,

    dirty = true,
    elements = {}, -- root gui elements

    --/////////////////////////////////////////////////////////////////////////////
    -- functions
    --/////////////////////////////////////////////////////////////////////////////

    dispatch_event = function ( _self, _sys_event )
        local event = ex.event

        if _sys_event.type == event_type.key_down then
            -- print( "key down " .. _sys_event.keycode )
            event.type = _sys_event.type 
            event.keycode = _sys_event.keycode 
        elseif _sys_event.type == event_type.key_up then
            -- print( "key up " .. _sys_event.keycode )
            event.type = _sys_event.type 
            event.keycode = _sys_event.keycode 
        end

        -- TODO: dispatch on_event on active element 
    end,

    draw = function ( _self )
        -- repaint the window if it is dirty
        if dirty then
            dirty = false
            for i=1,#elements do
                local el = elements[i]
                if el.on_draw ~= nil then
                    elements[i]:on_draw()
                end
            end
        end
    end,

    update = function ( _self )
        for i=1,#elements do
            local el = elements[i]
            if el.on_update ~= nil then
                elements[i]:on_update()
            end
        end
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {
        window_list = {},

        on_event = function ( _sys_event )
            for i=1,#editor.window.window_list do
                local win = editor.window.window_list[i]
                if win._cptr == _sys_event.display then
                    win:dispatch_event (_sys_event)
                    break
                end
            end
        end,

        on_draw = function ( _sys_event )
            for i=1,#editor.window.window_list do
                local win = editor.window.window_list[i]
                win:draw()
            end
        end,

        on_update = function ( _sys_event )
            for i=1,#editor.window.window_list do
                local win = editor.window.window_list[i]
                win:update()
            end
        end,

        on_destroy = function ( _cptr )
            for i=1,#editor.window.window_list do
                local win = editor.window.window_list[i]
                if win._cptr == _cptr then
                    table.fast_remove_at( editor.window.window_list, i )
                    break
                end
            end
        end,
    },
}) 
__M.window = window

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
