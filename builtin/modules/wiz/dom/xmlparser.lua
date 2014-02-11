-- ======================================================================================
-- File         : xmlparser.lua
-- Author       : Wu Jie 
-- Last Change  : 12/23/2013 | 16:09:55 PM | Monday,December
-- Description  : 
-- ======================================================================================

local rootElement = nil -- wiz.elementNode
local curElement = nil -- wiz.elementNode
local lastTextNode = nil -- wiz.textNode

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

wiz.xmlparser = {

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    onStartElement = function ( tag, attrs ) 
        local newElement = wiz.elementNode( tag, attrs )

        if rootElement == nil then
            rootElement = newElement
        else
            curElement:addChild(newElement)
        end

        curElement = newElement
        lastTextNode = nil
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    onEndElement = function ( tag ) 
        curElement = curElement.parent
        lastTextNode = nil
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    onAddText = function ( text, isWhiteSpace ) 
        if lastTextNode == nil then
            local newText = wiz.textNode( text, isWhiteSpace )
            curElement:addChild(newText)
            lastTextNode = newText

            return
        end

        lastTextNode.text = lastTextNode.text .. text
        lastTextNode.isWhiteSpace = lastTextNode.isWhiteSpace or isWhiteSpace
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    onFinish = function ()
        local windowEL = rootElement:getElementByTag("window")
        if windowEL == nil then
            error ( "Parse Error: Can't find the <window>" )
        end

        local w = windowEL.attrs.width and tonumber(windowEL.attrs.width) or 640
        local h = windowEL.attrs.height and tonumber(windowEL.attrs.height) or 480
        local window = wiz.window(w,h)

        window.document = wiz.document(windowEL,window)
        window.document:applyStyle()
        window.document:generateRenderNodes()
        window.document:layout()
    end,
}
