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
    width = 0,
    height = 0,
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

    borderLeft = 0,
    borderRight = 0,
    borderTop = 0,
    borderBottom = 0,

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
            val = val/100 * state.contentW
        elseif style.maxWidth.type == "none" then
            val = 9999
        end
        self.maxWidth = val

        -- maxHeight
        val = style.maxHeight.value
        if style.maxHeight.type == "percent" then
            val = val/100 * state.contentH
        elseif style.maxHeight.type == "none" then
            val = 9999
        end
        self.maxHeight = val

        -- marginLeft
        val = style.marginLeft.value
        if style.marginLeft.type == "percent" then
            val = val/100 * state.contentW
        end
        self.marginLeft = val

        -- marginRight
        val = style.marginRight.value
        if style.marginRight.type == "percent" then
            val = val/100 * state.contentW
        end
        self.marginRight = val

        -- marginTop
        val = style.marginTop.value
        if style.marginTop.type == "percent" then
            val = val/100 * state.contentH
        end
        self.marginTop = val

        -- marginBottom
        val = style.marginBottom.value
        if style.marginBottom.type == "percent" then
            val = val/100 * state.contentH
        end
        self.marginBottom = val

        -- paddingLeft
        val = style.paddingLeft.value
        if style.paddingLeft.type == "percent" then
            val = val/100 * state.contentW
        end
        self.paddingLeft = val

        -- paddingRight
        val = style.paddingRight.value
        if style.paddingRight.type == "percent" then
            val = val/100 * state.contentW
        end
        self.paddingRight = val

        -- paddingTop
        val = style.paddingTop.value
        if style.paddingTop.type == "percent" then
            val = val/100 * state.contentH
        end
        self.paddingTop = val

        -- paddingBottom
        val = style.paddingBottom.value
        if style.paddingBottom.type == "percent" then
            val = val/100 * state.contentH
        end
        self.paddingBottom = val

        -- borderSize
        self.borderLeft = style.borderLeft
        self.borderRight = style.borderRight
        self.borderTop = style.borderTop
        self.borderBottom = style.borderBottom

        -- TODO: 
        -- font = ex.font.null,

        -- wordSpacing
        val = style.wordSpacing
        if val == "inherit" then
            val = self.parent and self.parent.wordSpacing or 0
        end
        self.wordSpacing = val

        -- letterSpacing
        val = style.letterSpacing
        if val == "inherit" then
            val = self.parent and self.parent.letterSpacing or 0
        end
        self.letterSpacing = val

        -- lineHeight
        val = style.lineHeight.value
        if style.lineHeight.type == "inherit" then
            val = self.parent and self.parent.lineHeight or 0
        elseif style.lineHeight.type == "percent" then
            val = self.parent and self.parent * val/100 or 0
        elseif style.lineHeight.type == "auto" then
            if font ~= nil then
                local fontType = typename(font)

                if fontType == "bitmapfont" then
                    val = font.lineHeight 
                elseif fontType == "font" then
                    val = font.height
                end
            end
        end
        self.lineHeight = val

        -- visible
        val = style.visible
        if val == "inherit" then
            val = self.parent and self.parent.visible or "visible"
        end
        self.visible = val

        -- textAlign
        val = style.textAlign
        if val == "inherit" then
            val = self.parent and self.parent.textAlign or "left"
        end
        self.textAlign = val

        -- textTransform
        val = style.textTransform
        if val == "inherit" then
            val = self.parent and self.parent.textTransform or "none"
        end
        self.textTransform = val

        -- textDecorations
        val = style.textDecorations
        if val == "inherit" then
            val = self.parent and self.parent.textDecorations or "none"
        end
        self.textDecorations = val

        -- textDirection
        val = style.textDirection
        if val == "inherit" then
            val = self.parent and self.parent.textDirection or "ltr"
        end
        self.textDirection = val

        -- whiteSpace
        val = style.whiteSpace
        if val == "inherit" then
            val = self.parent and self.parent.whiteSpace or "normal"
        end
        self.whiteSpace = val

        -- width
        val = style.width.value
        if style.width.type == "percent" then 
            val = val/100 * self.contentW
        end
        self.width = math.clamp( val, self.minWidth, self.maxWidth )

        -- height
        val = style.height.value
        if style.height.type == "percent" then 
            val = val/100 * self.contentH
        end
        self.height = math.clamp( val, self.minHeight, self.maxHeight )
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

