-- ======================================================================================
-- File         : document.lua
-- Author       : Wu Jie 
-- Last Change  : 12/17/2013 | 10:27:41 AM | Tuesday,December
-- Description  : 
-- ======================================================================================

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

wiz.document = class ({
    __typename = "document",

    -- constructor & destructor
    __init = function ( self, rootEL )
        checkarg(rootEL,"elementNode")

        self._root = rootEL
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    _root = nil,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( self ) 
        self._root:repaint()
    end,

    setSize = function ( self, w, h )
        local style = self._root.style
        style.width = w
        style.height = h

        self.root.layoutDirty = true
        self.root.repaintDirty = true
    end,
})
