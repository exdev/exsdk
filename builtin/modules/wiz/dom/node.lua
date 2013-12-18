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
    style = {},

    --
    layoutDirty = true,
    repaintDirty = true,

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
            -- TODO:

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

        -- repaint myself
        if self.repaintDirty then
            self:_doRepaint()

            self.repaintDirty = false
        end
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
    __init = function ( self, text, isWhiteSpace )
        self.text = text
        self.isWhiteSpace = isWhiteSpace or false
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    text = "",
    isWhiteSpace = false,

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
            ex.painter.text( self.text, ttfFont, self.x, self.y, 100, 100 )
        end
    end,
})
