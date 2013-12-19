-- ======================================================================================
-- File         : node.lua
-- Author       : Wu Jie 
-- Last Change  : 12/17/2013 | 15:16:32 PM | Tuesday,December
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- class domNode
--/////////////////////////////////////////////////////////////////////////////

wiz.domNode = class ({
    __typename = "domNode",

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    -- relation
    parent = nil,
    children = {},

    -- position & size
    x = 0,
    y = 0,
    w = 0,
    h = 0,
    style = {}, -- computed style

    --
    layoutDirty = true,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    addChild = function ( self, node )
        node.parent = self
        table.add( self.children, node )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    getElementByTag = function ( self, tag )
        for i=1,#self.children do
            local node = self.children[i]
            if node.tag == tag then
                return node
            end
        end
        return nil
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    layout = function ( self, x, y, w, h )
        if self.layoutDirty then
            if self:isa(wiz.textNode) then
                -- TODO:
            end

            self.layoutDirty = false
        end

        return self.x, self.y, self.w, self.h
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( self )
        -- recursively repaint the child 
        for i=1,#self.children do
            local node = self.children[i]
            node:repaint()
        end

        self:_doRepaint()
    end,
})

--/////////////////////////////////////////////////////////////////////////////
-- class elementNode
--/////////////////////////////////////////////////////////////////////////////

wiz.elementNode = wiz.domNode.extend ({
    __typename = "elementNode",

    -- constructor & destructor
    __init = function ( self, tag, attrs )
        self.tag = tag
        self.attrs = attrs

        if attrs.id ~= nil then
            self.id = attrs.id
        end
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    tag = "",
    id = "",
    attrs = {},

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    _doRepaint = function ( self ) 
    end,
})

--/////////////////////////////////////////////////////////////////////////////
-- class textNode
--/////////////////////////////////////////////////////////////////////////////

wiz.textNode = wiz.domNode.extend ({
    __typename = "textNode",

    -- constructor & destructor
    __init = function ( self, text, textType )
        self.text = text
        self.textType = textType
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    text = "",
    textType = 2, -- 0: white-space, 1: end-of-line, 2: plain-text

    isWhiteSpace = property { get = function (self) return self.textType == 0 end },
    isEndOfLine = property { get = function (self) return self.textType == 1 end },
    isPlainText = property { get = function (self) return self.textType == 2 end },

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    _doRepaint = function ( self ) 
        -- TEMP
        local ttfFont = wiz.bundles["os.fonts"]:load("Arial.ttf")

        if self.isWhiteSpace == false then
            ex.painter.color = ex.color4f.black 
            ex.painter.text( self.text, ttfFont, self.x, self.y )
        end
    end,
})
