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
    attrs = nil, -- {}
    style = nil, -- {} css-parsed style

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    generateRenderNodes = function ( self, parentRenderNode ) 
        if self.style.display == "inline" then
            self.renderNode = wiz.renderInline(self)
        else
            self.renderNode = wiz.renderBlock(self)
        end

        if parentRenderNode ~= nil then
            parentRenderNode:addChild(self.renderNode)
        end

        for i=1,#self.children do
            local node = self.children[i]
            node:generateRenderNodes(self.renderNode)
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    applyStyle = function ( self )
        -- create default style
        self.style = self.style or wiz.style()

        -- apply display by tag
        if self.tag == "div" then 
            self.style.display = "block"
        end

        local parentTag = self.parent.tag
        if parentTag == "hbox" then
            self.style.display = "inline-block"
        elseif parentTag == "vbox" then 
            self.style.display = "block"
        end

        -- apply style
        local styleAttr = self.attrs.style
        if styleAttr ~= nil then
            self.style:css(styleAttr)
        end

        for i=1,#self.children do
            local node = self.children[i]
            node:applyStyle()
        end
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
    __init = function ( self, text, isWhiteSpace )
        self.text = text
        self.isWhiteSpace = isWhiteSpace
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    text = "",
    isWhiteSpace = false,
    style = nil, -- must reference parent style

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    generateRenderNodes = function ( self, parentRenderNode ) 
        self.renderNode = wiz.renderText( self, self.text )

        if parentRenderNode ~= nil then
            parentRenderNode:addChild(self.renderNode)
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    applyStyle = function ( self )
        self.style = self.parent.style
    end,
})
