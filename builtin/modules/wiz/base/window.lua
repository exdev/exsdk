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
    __init = function ( self, w, h )
        checkarg(w,"number")
        checkarg(h,"number")

        self.id = wiz_c.create_window (self,w,h)
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    id = -1,
    background = property {
        set = function ( self, _v ) wiz_c.set_window_background(self.id,_v[1],_v[2],_v[3]) end
    },
    width = property {
        get = function ( self ) return wiz_c.get_window_width(self.id) end
    },
    height = property {
        get = function ( self ) return wiz_c.get_window_height(self.id) end
    },
    document = wiz.document.null,

    --/////////////////////////////////////////////////////////////////////////////
    -- functions
    --/////////////////////////////////////////////////////////////////////////////

    repaint = function ( self )
        wiz_c.repaint_window(self)
    end,

    onRepaint = function ( self )
        self.document:repaint()
    end,

    onResize = function ( self, w, h )
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- system events
    --/////////////////////////////////////////////////////////////////////////////

    -- onDestroy ( self )
    -- onUpdate ( self )
    -- onRepaint ( self )
    -- onResize ( self, w, h )
    -- onFocus ( self )
    -- onUnfocus ( self )
    -- onDestroy ( self )
}) 
