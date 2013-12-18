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
    children = {},

    -- position & size
    x = 0,
    y = 0,
    w = 0,
    h = 0,
    style = {},

    --
    layoutDirty = true,
    repaintDirty = true,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    addChild = function ( _self, _node )
        _node.parent = _self
        table.add( _self.children, _node )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    getElementByTag = function ( _self, _tag )
        for i=1,#_self.children do
            local node = _self.children[i]
            if node.tag == _tag then
                return node
            end
        end
        return nil
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    layout = function ( _self, _x, _y, _w, _h )
        if _self.layoutDirty then
            -- TODO:

            _self.layoutDirty = false
        end

        return _self.x, _self.y, _self.w, _self.h
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _self )
        -- recursively repaint the child 
        for i=1,#_self.children do
            local node = _self.children[i]
            node:repaint()
        end

        -- repaint myself
        if _self.repaintDirty then
            _self:_doRepaint()

            _self.repaintDirty = false
        end
    end,
})

--/////////////////////////////////////////////////////////////////////////////
-- class elementNode
--/////////////////////////////////////////////////////////////////////////////

wiz.elementNode = wiz.domNode.extend ({
    __typename = "elementNode",

    -- constructor & destructor
    __init = function ( _self, _tag, _attrs )
        _self.tag = _tag
        _self.attrs = _attrs

        if _attrs.id ~= nil then
            _self.id = _attrs.id
        end
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    tag = "",
    id = "",
    attrs = {},

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    _doRepaint = function ( _self ) 
    end,
})

--/////////////////////////////////////////////////////////////////////////////
-- class textNode
--/////////////////////////////////////////////////////////////////////////////

wiz.textNode = wiz.domNode.extend ({
    __typename = "textNode",

    -- constructor & destructor
    __init = function ( _self, _text, _isWhiteSpace )
        _self.text = _text
        _self.isWhiteSpace = _isWhiteSpace or false
    end,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    text = "",
    isWhiteSpace = false,

    --/////////////////////////////////////////////////////////////////////////////
    --
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    _doRepaint = function ( _self ) 
        -- TEMP
        local ttfFont = wiz.bundles["os.fonts"]:load("Arial.ttf")

        if _self.isWhiteSpace == false then
            ex.painter.color = ex.color4f.black 
            ex.painter.text( _self.text, ttfFont, _self.x, _self.y, 100, 100 )
        end
    end,
})
