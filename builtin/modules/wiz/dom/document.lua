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
    __init = function ( self, el, window )
        checkarg(el,"elementNode")

        self._rootEL = el
        self.window = window
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    _rootEL = nil,
    _rootRenderNode = nil,
    window = nil,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( self ) 
        self._rootEL.renderNode:repaint()
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    applyStyle = function ( self )
        self._rootEL:applyStyle()
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    generateRenderNodes = function ( self )
        self._rootEL:generateRenderNodes()
        self._rootRenderNode = self._rootEL.renderNode
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    layout = function ( self )
        local state = {
            offsetX = 0,
            offsetY = 0,
            contentW = self.window.width,
            contentH = self.window.height,
        }
        self._rootRenderNode:layout(state)
    end,
})
