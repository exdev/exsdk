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

    --/////////////////////////////////////////////////////////////////////////////
    -- functions
    --/////////////////////////////////////////////////////////////////////////////

    process_event = function ( _event )
        -- TODO
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {
        window_list = {},

        dispatch_events  = function ( _event )
            for i=1,#editor.window.window_list do
                local win = editor.window.window_list[i]

                if win._cptr == _event.window_cptr then
                    win:process_event (_event)
                end
            end
        end,

        on_destroy  = function ( _cptr )
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
