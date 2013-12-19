-- ======================================================================================
-- File         : parser.lua
-- Author       : Wu Jie 
-- Last Change  : 12/17/2013 | 10:52:42 AM | Tuesday,December
-- Description  : 
-- ======================================================================================

local rootElement = nil -- wiz.elementNode
local curElement = nil -- wiz.elementNode
local lastTextNode = nil -- wiz.textNode

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

wiz.parser = {

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
        local body = rootElement:getElementByTag("body")
        if body == nil then
            error ( "Parse Error: Can't find the <body>" )
        end

        local w = body.attrs.width or 640
        local h = body.attrs.height or 480
        local window = wiz.window( tonumber(w), tonumber(h) )

        window.document = wiz.document(rootElement)

        if os.platform == "macosx" then
            wiz.mount( "/Library/Fonts/", "os.fonts" )
        end
    end,
}
