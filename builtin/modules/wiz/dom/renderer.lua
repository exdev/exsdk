-- ======================================================================================
-- File         : renderer.lua
-- Author       : Wu Jie 
-- Last Change  : 12/19/2013 | 17:09:51 PM | Thursday,December
-- Description  : 
-- ======================================================================================

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

    -- computed style (style computed during layout phase)
    minWidth = 0,
    maxWidth = 0,
    minHeight = 0,
    maxHeight = 0,

    marginLeft = 0,
    marginRight = 0,
    marginTop = 0,
    marginBottom = 0,

    paddingLeft = 0,
    paddingRight = 0,
    paddingTop = 0,
    paddingBottom = 0,

    borderSizeLeft = 0,
    borderSizeRight = 0,
    borderSizeTop = 0,
    borderSizeBottom = 0,

    font = ex.font.null,
    wordSpacing = 0,
    letterSpacing = 0,
    lineHeight = 0,
    visible = "visible",
    textAlign = "left",
    textTransform = "none",
    textDecorations = "none",
    textDirection = "ltr",
    whiteSpace = "normal",

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

    _computeStyle = function ( self, style, state )
        local val = -1

        -- minWidth
        val = style.minWidth.value
        if style.minWidth.type == "percent" then 
            val = val/100 * state.contentW
        end
        self.minWidth = val

        -- minHeight
        val = style.minHeight.value
        if style.minHeight.type == "percent" then 
            val = val/100 * state.contentH
        end
        self.minHeight = val

        -- maxWidth
        val = style.maxWidth.value
        if style.maxWidth.type == "percent" then
            val = val/100 * style.contentW
        elseif style.maxWidth.type == "none" then
            val = 9999
        end
        self.maxWidth = val

        -- maxHeight
        val = style.maxHeight.value
        if style.maxHeight.type == "percent" then
            val = val/100 * style.contentH
        elseif style.maxHeight.type == "none" then
            val = 9999
        end
        self.maxHeight = val

        -- marginLeft
        val = style.marginLeft.value
        if style.marginLeft.type == "percent" then
            val = val/100 * style.contentW
        end
        self.marginLeft = val

        -- marginRight
        val = style.marginRight.value
        if style.marginRight.type == "percent" then
            val = val/100 * style.contentW
        end
        self.marginRight = val

        -- marginTop
        val = style.marginTop.value
        if style.marginTop.type == "percent" then
            val = val/100 * style.contentH
        end
        self.marginTop = val

        -- marginBottom
        val = style.marginBottom.value
        if style.marginBottom.type == "percent" then
            val = val/100 * style.contentH
        end
        self.marginBottom = val

        -- paddingLeft
        val = style.paddingLeft.value
        if style.paddingLeft.type == "percent" then
            val = val/100 * style.contentW
        end
        self.paddingLeft = val

        -- paddingRight
        val = style.paddingRight.value
        if style.paddingRight.type == "percent" then
            val = val/100 * style.contentW
        end
        self.paddingRight = val

        -- paddingTop
        val = style.paddingTop.value
        if style.paddingTop.type == "percent" then
            val = val/100 * style.contentH
        end
        self.paddingTop = val

        -- paddingBottom
        val = style.paddingBottom.value
        if style.paddingBottom.type == "percent" then
            val = val/100 * style.contentH
        end
        self.paddingBottom = val

        -- borderSize
        self.borderLeft = style.borderLeft
        self.borderRight = style.borderRight
        self.borderTop = style.borderTop
        self.borderBottom = style.borderBottom

        -- TODO: inherit properties
        -- font = ex.font.null,
        -- wordSpacing = 0,
        -- letterSpacing = 0,
        -- lineHeight = 0,
        -- visible = "visible",
        -- textAlign = "left",
        -- textTransform = "none",
        -- textDecorations = "none",
        -- textDirection = "ltr",
        -- whiteSpace = "normal",
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

    layout = function ( self, state )
        local style = self.domNode.style
        self:_computeStyle( style, state )

        -- TODO:
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

