-- ======================================================================================
-- File         : window.lua
-- Author       : Wu Jie 
-- Last Change  : 05/07/2013 | 18:02:22 PM | Tuesday,May
-- Description  : 
-- ======================================================================================

local __M = {}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local event = {
    type = event_type.none,
    display = ex_c.null,
    keycode = -1, -- we use in keycode table
    mouse_pos_x = -1,
    mouse_pos_y = -1,
    mouse_button = -1, -- -1:None, 0:left, 1:right, 2:middle
}
__M.event = event


-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local window = class ({
    __typename = "window",

    -- constructor & destructor
    __init = function ( _self, _w, _h )
        checkarg(_w,"number")
        checkarg(_h,"number")

        _self._cptr = wiz_c.create_window (_w,_h)

        table.add( wiz.window.window_list, _self )
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _cptr = ex_c.null,
    _view = ui.element.null,

    background = { 1, 1, 1 },
    need_repaint = true,
    need_layout = true,
    width = property {
        get = function ( _self ) return wiz_c.get_window_width(_self._cptr) end
    },
    height = property {
        get = function ( _self ) return wiz_c.get_window_height(_self._cptr) end
    },
    view = property {
        get = function ( _self ) return _self._view end,
        set = function ( _self, _v )
            checkarg ( _v, "element" )
            _self._view = _v
            _self._view.style.width = _self.width
            _self._view.style.height = _self.height
            _self.need_repaint = true
            _self.need_layout = true
        end,
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- functions
    --/////////////////////////////////////////////////////////////////////////////

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
            ex_c.canvas_set_blending ( ex.blend_op.add, ex.blend_mode.alpha, ex.blend_mode.inverse_alpha )
            if typename(_self.background) == "texture" then
                ex_c.canvas_clear( 1, 1, 1 )

                local size = math.max( ex.canvas.width, ex.canvas.height )
                ex.canvas.color = ex.color4f.white
                ex.canvas.draw_image( _self.background, 
                                      0, 0, size, size,
                                      0, 0, size, size )
            else
                ex_c.canvas_clear( _self.background[1], _self.background[2], _self.background[3] )
            end

                _self._view.style.min_width = _self.width
                _self._view.style.min_height = _self.height
                _self:_do_draw(_self.view) 
                _self.need_repaint = false

            ex_c.canvas_flush()
            return
        end

        _self:_draw_recursively (_self.view)
    end,

    _draw_recursively = function ( _self, _el )
        if _el._dirty then
            _self:_do_draw(_el) 
            return
        end

        for i=1,#_el.children do
            local child_el = _el.children[i]
            if child_el._dirty then 
                _self:_do_draw(child_el) 
            else
                _self:_draw_recursively(child_el)
            end
        end
    end,

    _do_draw = function ( _self, _el )
        -- repaint by parent first
        _el:draw()
        _el._dirty = false

        for i=1,#_el.children do
            local child_el = _el.children[i]
            _self:_do_draw (child_el)
        end
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {
        window_list = {},

        on_event = function ( _os_event )
            for i=1,#wiz.window.window_list do
                local win = wiz.window.window_list[i]
                if win._cptr == _os_event.display then
                    win:dispatch_event (_os_event)
                    break
                end
            end
        end,
        
        on_repaint = function ( _os_event )
            for i=1,#wiz.window.window_list do
                local win = wiz.window.window_list[i]
                win.need_repaint = true
            end
        end,

        on_draw = function ( _os_event )
            for i=1,#wiz.window.window_list do
                local win = wiz.window.window_list[i]
                win:draw()
            end
        end,

        on_update = function ( _os_event )
            for i=1,#wiz.window.window_list do
                local win = wiz.window.window_list[i]
                win:update()
            end
        end,

        on_destroy = function ( _cptr )
            for i=1,#wiz.window.window_list do
                local win = wiz.window.window_list[i]
                if win._cptr == _cptr then
                    table.fast_remove_at( wiz.window.window_list, i )
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
