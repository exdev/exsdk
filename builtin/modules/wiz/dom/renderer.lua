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
    width = 0,
    height = 0,

    --
    domNode = nil,

    -- computed style (style computed during layout phase)
    style = {
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
    },

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    _computeStyle = function ( self, domStyle, state )
        local val = -1
        local renderStyle = self.style

        renderStyle.display = domStyle.display

        -- minWidth
        val = domStyle.minWidth.value
        if domStyle.minWidth.type == "percent" then 
            val = val/100 * state.contentW
        end
        renderStyle.minWidth = val

        -- minHeight
        val = domStyle.minHeight.value
        if domStyle.minHeight.type == "percent" then 
            val = val/100 * state.contentH
        end
        renderStyle.minHeight = val

        -- maxWidth
        val = domStyle.maxWidth.value
        if domStyle.maxWidth.type == "percent" then
            val = val/100 * state.contentW
        elseif domStyle.maxWidth.type == "none" then
            val = 9999
        end
        renderStyle.maxWidth = val

        -- maxHeight
        val = domStyle.maxHeight.value
        if domStyle.maxHeight.type == "percent" then
            val = val/100 * state.contentH
        elseif domStyle.maxHeight.type == "none" then
            val = 9999
        end
        renderStyle.maxHeight = val

        -- marginLeft
        val = domStyle.marginLeft.value
        if domStyle.marginLeft.type == "percent" then
            val = val/100 * state.contentW
        end
        renderStyle.marginLeft = val

        -- marginRight
        val = domStyle.marginRight.value
        if domStyle.marginRight.type == "percent" then
            val = val/100 * state.contentW
        end
        renderStyle.marginRight = val

        -- marginTop
        val = domStyle.marginTop.value
        if domStyle.marginTop.type == "percent" then
            val = val/100 * state.contentH
        end
        renderStyle.marginTop = val

        -- marginBottom
        val = domStyle.marginBottom.value
        if domStyle.marginBottom.type == "percent" then
            val = val/100 * state.contentH
        end
        renderStyle.marginBottom = val

        -- paddingLeft
        val = domStyle.paddingLeft.value
        if domStyle.paddingLeft.type == "percent" then
            val = val/100 * state.contentW
        end
        renderStyle.paddingLeft = val

        -- paddingRight
        val = domStyle.paddingRight.value
        if domStyle.paddingRight.type == "percent" then
            val = val/100 * state.contentW
        end
        renderStyle.paddingRight = val

        -- paddingTop
        val = domStyle.paddingTop.value
        if domStyle.paddingTop.type == "percent" then
            val = val/100 * state.contentH
        end
        renderStyle.paddingTop = val

        -- paddingBottom
        val = domStyle.paddingBottom.value
        if domStyle.paddingBottom.type == "percent" then
            val = val/100 * state.contentH
        end
        renderStyle.paddingBottom = val

        -- borderSize
        renderStyle.borderLeft = domStyle.borderLeft
        renderStyle.borderRight = domStyle.borderRight
        renderStyle.borderTop = domStyle.borderTop
        renderStyle.borderBottom = domStyle.borderBottom

        -- TODO: TEMP 
        -- fontFamily
        for i=1,#domStyle.fontFamily do
            local fontName = domStyle.fontFamily[i]
            local ttfFont = wiz.bundles["os.fonts"]:load(fontName)
            if ttfFont ~= nil then
                renderStyle.font = ttfFont
                break
            end
        end
        if renderStyle.font == nil then
            renderStyle.font = wiz.bundles["os.fonts"]:load("Arial.ttf")
        end

        -- wordSpacing
        val = domStyle.wordSpacing
        if val == "inherit" then
            val = renderStyle.parent and renderStyle.parent.wordSpacing or 0
        end
        renderStyle.wordSpacing = val

        -- letterSpacing
        val = domStyle.letterSpacing
        if val == "inherit" then
            val = renderStyle.parent and renderStyle.parent.letterSpacing or 0
        end
        renderStyle.letterSpacing = val

        -- lineHeight
        val = domStyle.lineHeight.value
        if domStyle.lineHeight.type == "inherit" then
            val = renderStyle.parent and renderStyle.parent.lineHeight or 0
        elseif domStyle.lineHeight.type == "percent" then
            val = renderStyle.parent and renderStyle.parent * val/100 or 0
        elseif domStyle.lineHeight.type == "auto" then
            if renderStyle.font ~= nil then
                local fontType = typename(renderStyle.font)

                if fontType == "bitmapfont" then
                    val = renderStyle.font.lineHeight 
                elseif fontType == "font" then
                    val = renderStyle.font.height
                end
            end
        end
        renderStyle.lineHeight = val

        -- visible
        val = domStyle.visible
        if val == "inherit" then
            val = renderStyle.parent and renderStyle.parent.visible or "visible"
        end
        renderStyle.visible = val

        -- textAlign
        val = domStyle.textAlign
        if val == "inherit" then
            val = renderStyle.parent and renderStyle.parent.textAlign or "left"
        end
        renderStyle.textAlign = val

        -- textTransform
        val = domStyle.textTransform
        if val == "inherit" then
            val = renderStyle.parent and renderStyle.parent.textTransform or "none"
        end
        renderStyle.textTransform = val

        -- textDecorations
        val = domStyle.textDecorations
        if val == "inherit" then
            val = renderStyle.parent and renderStyle.parent.textDecorations or "none"
        end
        renderStyle.textDecorations = val

        -- textDirection
        val = domStyle.textDirection
        if val == "inherit" then
            val = renderStyle.parent and renderStyle.parent.textDirection or "ltr"
        end
        renderStyle.textDirection = val

        -- whiteSpace
        val = domStyle.whiteSpace
        if val == "inherit" then
            val = renderStyle.parent and renderStyle.parent.whiteSpace or "normal"
        end
        renderStyle.whiteSpace = val

        -- width
        val = domStyle.width.value
        if domStyle.width.type == "percent" then 
            val = val/100 * state.contentW
        elseif domStyle.width.type == "auto" then
            val = state.contentW
                - renderStyle.marginLeft - renderStyle.marginRight 
                - renderStyle.borderLeft - renderStyle.borderRight 
                - renderStyle.paddingLeft - renderStyle.paddingRight 
        end
        self.width = math.clamp( val, renderStyle.minWidth, renderStyle.maxWidth )

        -- height
        val = domStyle.height.value
        if domStyle.height.type == "percent" then 
            val = val/100 * state.contentH
        elseif domStyle.height.type == "auto" then
            val = state.contentH
                - renderStyle.marginTop - renderStyle.marginBottom 
                - renderStyle.borderTop - renderStyle.borderBottom 
                - renderStyle.paddingTop - renderStyle.paddingBottom
        end
        self.height = math.clamp( val, renderStyle.minHeight, renderStyle.maxHeight )
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
        local renderStyle = self.style 
        return self.width
        + renderStyle.marginLeft + renderStyle.marginRight 
        + renderStyle.borderLeft + renderStyle.borderRight 
        + renderStyle.paddingLeft + renderStyle.paddingRight
    end,

    totalHeight = function ( self )
        local renderStyle = self.style 
        return self.height 
        + renderStyle.marginTop + renderStyle.marginBottom 
        + renderStyle.borderTop + renderStyle.borderBottom 
        + renderStyle.paddingTop + renderStyle.paddingBottom
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
        local domStyle = self.domNode.style
        local renderStyle = self.style
        self:_computeStyle( domStyle, parentState )

        self.x = parentState.offsetX + renderStyle.marginLeft + renderStyle.borderLeft + renderStyle.paddingLeft
        self.y = parentState.offsetY + renderStyle.marginTop + renderStyle.borderTop + renderStyle.paddingTop

        local contentW = self.width
        contentW = contentW > 0 and contentW or 0

        local contentH = self.height
        contentH = contentH > 0 and contentH or 0

        -- add to parent's line-box
        parentState.next = nil
        if renderStyle.display == "block" then
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
        if domStyle.width.type == "auto" then 
            if renderStyle.display == "block" then
                self.width = contentW
            elseif renderStyle.display == "inline-block" then
                local width = 0 
                for i=1,#self._lines do
                    if width < self._lines[i].w then
                        width = self._lines[i].w
                    end
                end
                self.width = math.clamp( width, renderStyle.minWidth, renderStyle.maxWidth )
            end
        end

        -- calculate the height
        if domStyle.height.type == "auto" then 
            local height = 0 
            for i=1,#self._lines do
                height = height + self._lines[i].h
            end
            self.height = math.clamp( height, renderStyle.minHeight, renderStyle.maxHeight )
        end

        --
        local totalWidth = self:totalWidth()
        if renderStyle.display == "inline-block" then
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
        local domStyle = self.domNode.style
        local renderStyle = self.style

        local border_x = x - renderStyle.paddingLeft - renderStyle.borderLeft
        local border_y = y - renderStyle.paddingTop - renderStyle.borderTop
        local border_w = self.width + renderStyle.paddingLeft + renderStyle.paddingRight + renderStyle.borderLeft + renderStyle.borderRight
        local border_h = self.height + renderStyle.paddingTop + renderStyle.paddingBottom + renderStyle.borderTop + renderStyle.borderBottom
        if domStyle.borderStyle == "solid" then
            ex.painter.color = domStyle.borderLeftColor -- TODO
            ex.painter.rect4( border_x, border_y, border_w, border_h,
                              renderStyle.borderTop,
                              renderStyle.borderRight,
                              renderStyle.borderBottom,
                              renderStyle.borderLeft )
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

    _split = false,
    _flows = {},

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    layout = function ( self, parentState )
        local domStyle = self.domNode.style
        local renderStyle = self.style

        self:_computeStyle( domStyle, parentState )
        if self._split then
            renderStyle.marginLeft = 0
            renderStyle.paddingLeft = 0
            renderStyle.borderLeft = 0
        end

        self.x = parentState.offsetX + renderStyle.marginLeft + renderStyle.borderLeft + renderStyle.paddingLeft
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
                local renderStyle1 = {} 
                table.copy(renderStyle1, renderStyle)
                renderStyle1.marginRight = 0
                renderStyle1.paddingRight = 0
                renderStyle1.borderRight = 0
                renderInline1.style = renderStyle1

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

                    local renderStyle2 = {} 
                    table.copy(renderStyle2, renderStyle)
                    renderInline2.style = renderStyle2
                    renderInline2._split = true

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
        local totalWidth = self:totalWidth()

        --
        if parentState.line.h < self.height then
            parentState.line.h = self.height
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
        local domStyle = self.domNode.style
        local renderStyle = self.style

        local border_x = x - renderStyle.paddingLeft - renderStyle.borderLeft
        local border_y = y - renderStyle.paddingTop - renderStyle.borderTop
        local border_w = self.width + renderStyle.paddingLeft + renderStyle.paddingRight + renderStyle.borderLeft + renderStyle.borderRight
        local border_h = self.height + renderStyle.paddingTop + renderStyle.paddingBottom + renderStyle.borderTop + renderStyle.borderBottom
        if domStyle.borderStyle == "solid" then
            ex.painter.color = domStyle.borderLeftColor -- TODO
            ex.painter.rect4( border_x, border_y, border_w, border_h,
                              renderStyle.borderTop,
                              renderStyle.borderRight,
                              renderStyle.borderBottom,
                              renderStyle.borderLeft )
        end

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

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    layout = function ( self, parentState )
        local parentNode = parentState.node -- NOTE: parentNode may not be self.parent since line-break will create temp new renderNode
        self.style = parentNode.style

        local renderStyle = self.style
        local beginningOfLine = #parentState.line.nodes == 0 and 1 or 0

        local contentW = parentState.contentW - parentState.offsetX 
        local text1, text2, width, linebreak = ex_c.font_wrap_text ( self.text, 
                                                                     renderStyle.font._cptr, 
                                                                     renderStyle.whiteSpace, 
                                                                     contentW, 
                                                                     beginningOfLine )
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
            renderText1.style = renderStyle
            renderText1.x = parentState.offsetX
            renderText1.y = parentState.offsetY
            renderText1.width = width
            renderText1.height = renderStyle.lineHeight

            -- add node to parent's line-box
            local totalHeight = renderText1.height
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
                renderText2.style = renderStyle
                parentState.next = renderText2
            end
        end
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    paint = function ( self, x, y )
        local renderStyle = self.style

        ex.painter.color = ex.color4f.black 
        ex.painter.text( self.text, renderStyle.font, x, y )
    end,
})

