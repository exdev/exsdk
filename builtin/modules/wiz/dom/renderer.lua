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

    font = nil,
    wordSpacing = 0,
    letterSpacing = 0,
    lineHeight = 0,
    visible = "visible",
    textAlign = "left",
    textTransform = "none",
    textDecorations = "none",
    textDirection = "ltr",
    whiteSpace = "normal",

    display = "inline",

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

        self.display = style.display

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

        -- TODO: TEMP 
        -- fontFamily
        for i=1,#style.fontFamily do
            local fontName = style.fontFamily[i]
            local ttfFont = wiz.bundles["os.fonts"]:load(fontName)
            if ttfFont ~= nil then
                self.font = ttfFont
                break
            end
        end
        if self.font == nil then
            self.font = wiz.bundles["os.fonts"]:load("Arial.ttf")
        end

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
            if self.font ~= nil then
                local fontType = typename(self.font)

                if fontType == "bitmapfont" then
                    val = self.font.lineHeight 
                elseif fontType == "font" then
                    val = self.font.height
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
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( self )
        local parent = self.parent
        local x = self.x
        local y = self.y
        while parent ~= nil do
            x = x + parent.x
            y = y + parent.y
        end

        self:paint(x,y)
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    paint = function ( self, x, y )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    totalWidth = function ( self )
        return self.width
        + self.marginLeft + self.marginRight 
        + self.borderLeft + self.borderRight 
        + self.paddingLeft + self.paddingRight
    end,

    totalHeight = function ( self )
        return self.height 
        + self.marginTop + self.marginBottom 
        + self.borderTop + self.borderBottom 
        + self.paddingTop + self.paddingBottom
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

    layout = function ( self, parentState )
        local style = self.domNode.style
        self:_computeStyle( style, parentState )
        self.x = parentState.offsetX + self.marginLeft + self.borderLeft + self.paddingLeft
        self.y = parentState.offsetY + self.marginTop + self.borderTop + self.paddingTop

        local contentW = parentState.contentW 
        - self.marginLeft - self.marginRight 
        - self.borderLeft - self.borderRight 
        - self.paddingLeft - self.paddingRight 
        -- DISABLE: - parentState.offsetX
        contentW = contentW > 0 and contentW or 0

        local contentH = parentState.contentH 
        - self.marginTop - self.marginBottom 
        - self.borderTop - self.borderBottom 
        - self.paddingTop - self.paddingBottom
        -- DISABLE: - parentState.offsetY
        contentH = contentH > 0 and contentH or 0

        -- add to parent's line-box
        parentState.next = nil
        if self.display == "block" then
            if #parentState.line.nodes > 0 then 
                parentState.newline = true
                parentState.next = self
                return
            else
                parentState.newline = true -- always new-line
            end

        elseif self.display == "inline-block" then
            local totalWidth = self:totalWidth()

            if #parentState.line.nodes > 0 and 
                parentState.offsetX + totalWidth > parentState.contentW then
                parentState.newline = true
                parentState.next = self
                return
            else
                parentState.offsetX = parentState.offsetX + totalWidth
                parentState.line.w = parentState.offsetX
            end

        end

        -- layout children
        local state = {
            offsetX = 0,
            offsetY = 0,
            contentW = contentW,
            contentH = contentH,
            newline = false,
            next = nil,
            line = { w = 0, h = 0, nodes = {} },
        }

        -- clear the lines
        self._lines = {}

        -- recursively layout the child 
        for i=1,#self.children do

            --
            local child = self.children[i]
            child:layout(state)

            --
            if state.newline then
                state.newline = false
                state.offsetX = 0
                state.offsetY = state.offsetY + state.line.h
                table.add( self._lines, state.line )
                state.line = { w = 0, h = 0, nodes = {} }
            end

            --
            while state.next ~= nil do
                state.next:layout(state)
                if state.newline then
                    state.newline = false
                    state.offsetX = 0
                    state.offsetY = state.offsetY + state.line.h
                    table.add( self._lines, state.line )
                    state.line = { w = 0, h = 0, nodes = {} }
                end
            end
        end
        if #state.line.nodes > 0 then
            table.add( self._lines, state.line )
        end

        -- calculate the height
        if style.height.type == "auto" then 
            local height = 0 
            for i=1,#self._lines do
                height = height + self._lines[i].h
            end
            self.height = math.clamp( height, self.minHeight, self.maxHeight )
        end

        -- add node to parent's line-box
        local totalHeight = self:totalHeight()
        if parentState.line.h < totalHeight then
            parentState.line.h = totalHeight
        end
        table.add( parentState.line.nodes, self ) 
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    paint = function ( self, x, y )
        -- recursively paint the child 
        for i=1,#self._lines do
            local line = self._lines[i]

            for j=1,#line.nodes do
                local node = line.nodes[j]
                node:paint( x + node.x, y + node.y )
            end
        end

        -- TODO: paint self
        local style = self.domNode.style
        local x = x - self.paddingLeft - self.borderLeft
        local y = y - self.paddingTop - self.borderTop
        local w = self.width + self.paddingLeft + self.paddingRight + self.borderLeft + self.borderRight
        local h = self.height + self.paddingTop + self.paddingBottom + self.borderTop + self.borderBottom
        if style.borderStyle == "solid" then
            ex.painter.color = style.borderLeftColor -- TODO
            ex.painter.rect4( x, y, w, h,
                              self.borderTop,
                              self.borderRight,
                              self.borderBottom,
                              self.borderLeft )
        end
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

    layout = function ( self, parentState )
        local style = self.domNode.style
        self:_computeStyle( style, parentState )
        self.x = parentState.offsetX + self.marginLeft + self.borderLeft + self.paddingLeft
        self.y = parentState.offsetY

        local contentW = parentState.contentW 
        - self.marginLeft - self.marginRight 
        - self.borderLeft - self.borderRight 
        - self.paddingLeft - self.paddingRight 
        - parentState.offsetX
        contentW = contentW > 0 and contentW or 0

        local contentH = parentState.contentH 
        - self.marginTop - self.marginBottom 
        - self.borderTop - self.borderBottom 
        - self.paddingTop - self.paddingBottom
        - parentState.offsetY
        contentH = contentH > 0 and contentH or 0

        -- layout children
        local state = {
            offsetX = 0,
            offsetY = 0,
            contentW = contentW,
            contentH = contentH,
            newline = false,
            next = nil,
            line = { w = 0, h = 0, nodes = {} },
        }

        -- clear the lines
        self._lines = {}

        -- recursively layout the child 
        for i=1,#self.children do

            --
            local child = self.children[i]
            child:layout(state)

            -- TODO:
            -- if state.newline then
            --     state.newline = false
            --     state.offsetX = 0
            --     state.offsetY = state.offsetY + state.line.h
            --     table.add( self._lines, state.line )

            --     break
            -- end
        end
        if #state.line.nodes > 0 then
            table.add( self._lines, state.line )
        end

        -- TODO
        parentState.offsetX = parentState.offsetX + state.line.w
        parentState.line.w = parentState.offsetX
        table.add( parentState.line.nodes, self ) 

    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    paint = function ( self, x, y )
        -- recursively paint the child 
        for i=1,#self._lines do
            local line = self._lines[i]

            for j=1,#line.nodes do
                local node = line.nodes[j]
                node:paint( x + node.x, y + node.y )
            end
        end

        -- TODO: paint self
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
    font = nil,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    layout = function ( self, parentState )
        local parent = self.parent
        local font = parent.font
        local whiteSpace = parent.whiteSpace

        local lineElementCount = #parentState.line.nodes
        if lineElementCount == 0 
        and whiteSpace ~= "pre"
        and self.domNode.isWhiteSpace 
        then
            return
        end

        local contentW = parentState.contentW - parentState.offsetX 
        local text1, text2, width, linebreak = ex_c.font_wrap_text ( self.text, font._cptr, whiteSpace, contentW )
        print( string.format( "text = %s, text1 = %s, text2 = %s, width = %d, display = %s", self.text, text1, text2, width, parent.display ) )

        local renderText1 = wiz.renderText( self.domNode, text1 )
        renderText1.x = parentState.offsetX
        renderText1.y = parentState.offsetY
        renderText1.width = width
        renderText1.height = self.parent.lineHeight
        renderText1.font = font

        -- add node to parent's line-box
        local totalHeight = renderText1:totalHeight()
        if parentState.line.h < totalHeight then
            parentState.line.h = totalHeight
        end
        parentState.offsetX = parentState.offsetX + width
        parentState.line.w = parentState.offsetX
        table.add( parentState.line.nodes, renderText1 ) 

        -- check if break to new-line
        if linebreak then
            parentState.newline = true
            if text2 ~= nil then
                local renderText2 = wiz.renderText( self.domNode, text2 )
                renderText2.font = font
                parentState.next = renderText2
            end
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    paint = function ( self, x, y )
        local font = self.font

        ex.painter.color = ex.color4f.black 
        ex.painter.text( self.text, font, x, y )
    end,
})

