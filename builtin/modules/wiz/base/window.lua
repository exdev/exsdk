-- ======================================================================================
-- File         : window.lua
-- Author       : Wu Jie 
-- Last Change  : 12/09/2013 | 11:31:32 AM | Monday,December
-- Description  : 
-- ======================================================================================

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

wiz.window = class ({
    __typename = "window",

    -- constructor & destructor
    __init = function ( _self, _w, _h )
        checkarg(_w,"number")
        checkarg(_h,"number")

        _self.id = wiz_c.create_window (_self,_w,_h)
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    id = -1,
    background = property {
        set = function ( _self, _v ) wiz_c.set_window_background(_self.id,_v[1],_v[2],_v[3]) end
    },
    width = property {
        get = function ( _self ) return wiz_c.get_window_width(_self.id) end
    },
    height = property {
        get = function ( _self ) return wiz_c.get_window_height(_self.id) end
    },
    document = wiz.document.null,

    --/////////////////////////////////////////////////////////////////////////////
    -- functions
    --/////////////////////////////////////////////////////////////////////////////

    repaint = function ( _self )
        wiz_c.repaint_window(_self)
    end,

    onRepaint = function ( _self )
        _self.document:repaint()
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- system events
    --/////////////////////////////////////////////////////////////////////////////

    -- onDestroy ( _self )
    -- onUpdate ( _self )
    -- onRepaint ( _self )
    -- onResize ( _self, _w, _h )
    -- onFocus ( _self )
    -- onUnfocus ( _self )
    -- onDestroy ( _self )
}) 
