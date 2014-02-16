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
            val = val/100 * state.contentW
        elseif style.width.type == "auto" then
            val = state.contentW
                - self.marginLeft - self.marginRight 
                - self.borderLeft - self.borderRight 
                - self.paddingLeft - self.paddingRight 
        end
        self.width = math.clamp( val, self.minWidth, self.maxWidth )

        -- height
        val = style.height.value
        if style.height.type == "percent" then 
            val = val/100 * state.contentH
        elseif style.height.type == "auto" then
            val = state.contentH
                - self.marginTop - self.marginBottom 
                - self.borderTop - self.borderBottom 
                - self.paddingTop - self.paddingBottom
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

    -- lineBox = {
    --     w = 0, -- max-width of the line-box
    --     h = 0, -- max-height of the line-box
    --     nodes = {}, -- render nodes
    -- }
    _lines = {}, -- lineBox list

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    layout = function ( self, parentState )
        local style = self.domNode.style
        self:_computeStyle( style, parentState )
        self.x = parentState.offsetX + self.marginLeft + self.borderLeft + self.paddingLeft
        self.y = parentState.offsetY + self.marginTop + self.borderTop + self.paddingTop

        local contentW = self.width
        contentW = contentW > 0 and contentW or 0

        local contentH = self.height
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

        end

        -- layout children
        local state = {
            offsetX = 0,
            offsetY = 0,
            contentW = contentW,
            contentH = contentH,
            newline = false,
            node = self,
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
                child = state.next
                state.next = nil

                child:layout(state)
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
            state.line = { w = 0, h = 0, nodes = {} }
        end

        -- calculate the width
        if style.width.type == "auto" then 
            if self.display == "block" then
                self.width = contentW
            elseif self.display == "inline-block" then
                local width = 0 
                for i=1,#self._lines do
                    if width < self._lines[i].w then
                        width = self._lines[i].w
                    end
                end
                self.width = math.clamp( width, self.minWidth, self.maxWidth )
            end
        end

        -- calculate the height
        if style.height.type == "auto" then 
            local height = 0 
            for i=1,#self._lines do
                height = height + self._lines[i].h
            end
            self.height = math.clamp( height, self.minHeight, self.maxHeight )
        end

        --
        local totalWidth = self:totalWidth()
        if self.display == "inline-block" then
            if #parentState.line.nodes > 0 and 
                parentState.offsetX + totalWidth > parentState.contentW then
                parentState.newline = true
                parentState.next = self
                return
            end
        end

        -- add node to parent's line-box
        local totalHeight = self:totalHeight()
        if parentState.line.h < totalHeight then
            parentState.line.h = totalHeight
        end
        parentState.offsetX = parentState.offsetX + totalWidth
        parentState.line.w = parentState.offsetX
        table.add( parentState.line.nodes, self ) 
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    paint = function ( self, x, y )
        -- TODO: paint self
        local style = self.domNode.style
        local border_x = x - self.paddingLeft - self.borderLeft
        local border_y = y - self.paddingTop - self.borderTop
        local border_w = self.width + self.paddingLeft + self.paddingRight + self.borderLeft + self.borderRight
        local border_h = self.height + self.paddingTop + self.paddingBottom + self.borderTop + self.borderBottom
        if style.borderStyle == "solid" then
            ex.painter.color = style.borderLeftColor -- TODO
            ex.painter.rect4( border_x, border_y, border_w, border_h,
                              self.borderTop,
                              self.borderRight,
                              self.borderBottom,
                              self.borderLeft )
        end

        -- recursively paint the child 
        for i=1,#self._lines do
            local line = self._lines[i]
            for j=1,#line.nodes do
                local node = line.nodes[j]
                node:paint( x + node.x, y + node.y )
            end
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

    _flows = {},

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    layout = function ( self, parentState )
        local style = self.domNode.style
        self:_computeStyle( style, parentState )
        self.x = parentState.offsetX + self.marginLeft + self.borderLeft + self.paddingLeft
        self.y = parentState.offsetY

        local contentW = self.width - parentState.offsetX
        contentW = contentW > 0 and contentW or 0

        local contentH = self.height - parentState.offsetY
        contentH = contentH > 0 and contentH or 0

        -- layout flows (children)
        local state = {
            offsetX = 0,
            offsetY = 0,
            contentW = contentW,
            contentH = contentH,
            newline = false,
            node = self,
            next = nil,
            line = { w = 0, h = 0, nodes = {} },
        }

        -- if we are layout renderNode create in generateRenderNodes
        -- NOTE: the renderNode create in generateRenderNodes will have children
        if #self.children > 0 then
            self._flows = {}
            for i=1,#self.children do
                table.add(self._flows, self.children[i])
            end
        end

        -- recursively layout the child 
        for i=1,#self._flows do

            --
            local child = self._flows[i]
            child:layout(state)

            -- create new node renderInline1 for current line, 
            -- and store rest of child in the renderInline2
            if state.newline then
                state.newline = false
                parentState.newline = true

                local renderInline1 = wiz.renderInline(self.domNode)
                renderInline1.x = self.x
                renderInline1.y = self.y
                renderInline1.width = state.line.w -- TODO
                renderInline1.height = state.line.h -- TODO
                renderInline1._flows = state.line.nodes

                if parentState.line.h < renderInline1.height then
                    parentState.line.h = renderInline1.height
                end
                parentState.offsetX = parentState.offsetX + renderInline1.width
                parentState.line.w = parentState.offsetX
                table.add( parentState.line.nodes, renderInline1 ) 

                --
                if state.next ~= nil then
                    local renderInline2 = wiz.renderInline(self.domNode)

                    table.add( renderInline2._flows, state.next )
                    state.next = nil

                    for j=i+1,#self._flows do
                        table.add( renderInline2._flows, self._flows[j] )
                    end

                    parentState.next = renderInline2
                end

                return
            end
        end
        if #state.line.nodes > 0 then
            self._flows = state.line.nodes
        end
        self.width = state.line.w -- TODO
        self.height = state.line.h -- TODO

        --
        if parentState.line.h < self.height then
            parentState.line.h = self.height
        end
        parentState.offsetX = parentState.offsetX + self.width
        parentState.line.w = parentState.offsetX
        table.add( parentState.line.nodes, self ) 

    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    paint = function ( self, x, y )
        -- TODO: paint self

        -- recursively paint the child 
        for i=1,#self._flows do
            local node = self._flows[i]
            node:paint( x + node.x, y + node.y )
        end
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
        local parentNode = parentState.node -- NOTE: parentNode may not be self.parent since line-break will create temp new renderNode
        local font = parentNode.font
        local whiteSpace = parentNode.whiteSpace
        local beginningOfLine = #parentState.line.nodes == 0 and 1 or 0

        local contentW = parentState.contentW - parentState.offsetX 
        local text1, text2, width, linebreak = ex_c.font_wrap_text ( self.text, font._cptr, whiteSpace, contentW, beginningOfLine )
        -- DEBUG { 
        -- print( string.format( "text = \"%s\"\n - text1 = \"%s\"\n - text2 = \"%s\"\n - width = %d, display = %s, whitespace = %s", 
        --                       self.text, 
        --                       text1, 
        --                       text2, 
        --                       width, 
        --                       parentNode.display,
        --                       whiteSpace ) )
        -- } DEBUG

        -- process text split
        if text1 ~= nil then
            local renderText1 = wiz.renderText( self.domNode, text1 )
            renderText1.x = parentState.offsetX
            renderText1.y = parentState.offsetY
            renderText1.width = width
            renderText1.height = parentNode.lineHeight
            renderText1.font = font

            -- add node to parent's line-box
            local totalHeight = renderText1:totalHeight()
            if parentState.line.h < totalHeight then
                parentState.line.h = totalHeight
            end
            parentState.offsetX = parentState.offsetX + renderText1.width
            parentState.line.w = parentState.offsetX
            table.add( parentState.line.nodes, renderText1 ) 
        end

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

