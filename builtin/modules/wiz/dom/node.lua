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
    renderNode = nil,
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

    children = {},

    tag = "",
    id = "",
    attrs = {},
    style = {}, -- computed style

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    createRenderNodes = function ( self ) 
    end,

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
})
