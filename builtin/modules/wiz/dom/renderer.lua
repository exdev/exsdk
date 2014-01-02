-- ======================================================================================
-- File         : renderer.lua
-- Author       : Wu Jie 
-- Last Change  : 12/19/2013 | 17:09:51 PM | Thursday,December
-- Description  : 
-- ======================================================================================

-- TODO { 
-- local layoutState = {
-- }
-- } TODO end 

--/////////////////////////////////////////////////////////////////////////////
-- class renderNode
--/////////////////////////////////////////////////////////////////////////////

wiz.renderNode = class ({
    __typename = "renderNode",

    -- relation
    parent = nil,
    children = {},

    -- position & size
    x = 0, -- left, relate with parent
    y = 0, -- top, relate with parent
    w = 0,
    h = 0,

    --
    domNode = nil,

    --
    -- lineBox = {
    --     w = 0, -- max-width of the line-box
    --     h = 0, -- max-height of the line-box
    --     nodes = {}, -- render nodes
    -- }
    _lines = {}, -- lineBox list

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

    layout = function ( self )
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

        self:paint()
    end,
})

--/////////////////////////////////////////////////////////////////////////////
-- class renderBlock
--/////////////////////////////////////////////////////////////////////////////

wiz.renderBlock = wiz.renderNode.extend ({
    __typename = "renderBlock",

    __init = function ( self, domNode )
        self.domNode = domNode
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    paint = function ( self )
        -- local style = self.domNode.style
        -- TODO: 
    end,
})

--/////////////////////////////////////////////////////////////////////////////
-- class renderInline
--/////////////////////////////////////////////////////////////////////////////

wiz.renderInline = wiz.renderNode.extend ({
    __typename = "renderInline",

    __init = function ( self, domNode )
        self.domNode = domNode
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    paint = function ( self )
    end,
})

--/////////////////////////////////////////////////////////////////////////////
-- class renderText
--/////////////////////////////////////////////////////////////////////////////

wiz.renderText = wiz.renderNode.extend ({
    __typename = "renderText",

    __init = function ( self, domNode, text )
        self.domNode = domNode
        self.text = text
    end,

    text = "",

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    paint = function ( self )
        -- TEMP: self.parent.style
        local ttfFont = wiz.bundles["os.fonts"]:load("Arial.ttf")

        ex.painter.color = ex.color4f.black 
        ex.painter.text( self.text, ttfFont, self.x, self.y )
    end,
})

