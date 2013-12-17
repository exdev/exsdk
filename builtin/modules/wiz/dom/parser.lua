-- ======================================================================================
-- File         : parser.lua
-- Author       : Wu Jie 
-- Last Change  : 12/17/2013 | 10:52:42 AM | Tuesday,December
-- Description  : 
-- ======================================================================================

local rootElement = nil -- wiz.element
local curElement = nil -- wiz.element

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

wiz.parser = {

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    onStartElement = function ( _tag, _attrs ) 
        local newElement = wiz.elementNode( _tag, _attrs )

        if rootElement == nil then
            rootElement = newElement
        else
            curElement:addChild(newElement)
        end

        curElement = newElement
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    onEndElement = function ( _tag ) 
        curElement = curElement.parent
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    onAddText = function ( _text, _isWhiteSpace ) 
        local newText = wiz.textNode( _text, _isWhiteSpace )
        curElement:addChild(newText)
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    onFinish = function ()
        local window = wiz.window( 640, 480 )
        window.document = wiz.document(rootElement)
    end,
}
