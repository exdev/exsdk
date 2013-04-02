-- ======================================================================================
-- File         : rect.lua
-- Author       : Wu Jie 
-- Last Change  : 04/01/2013 | 20:02:19 PM | Monday,April
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local rect = class ({
    __typename = "rect",
    __isvalue = true,

    -- constructor & destructor
    __init = function ( _self, _x, _y, _w, _h )
        checkarg(_x,"number")
        checkarg(_y,"number")
        checkarg(_w,"number")
        checkarg(_h,"number")

        _self.x = _x
        _self.y = _y
        _self.width = _w
        _self.height = _h
    end,

    -- meta-methods
    __tostring = function (_op)
        return string.format ( "{ %.3f, %.3f, %.3f, %.3f }", _op.x, _op.y, _op.width, _op.height )
    end,
    __concat = function (_op1,_op2)
        return tostring(_op1)..tostring(_op2)
    end,
    __len = function (_op)
        return 4
    end,
    __eq = function (_op1,_op2)
        checkarg(_op1,"rect")
        checkarg(_op2,"rect")

        if _op1.x == _op2.x and
           _op1.y == _op2.y and
           _op1.width == _op2.width and
           _op1.height == _op2.height then
           return true
        end

        return false
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    x = 0,
    y = 0,
    width = 1,
    height = 1,

    center = property {
        get = function (_self) 
            return ex.vec2f( _self.x + _self.width * 0.5,  
                             _self.y + _self.height * 0.5 )  
        end,
    },

    min_x = property {
        get = function (_self) return _self.x end,
    },
    min_y = property {
        get = function (_self) return _self.y end,
    },
    max_x = property {
        get = function (_self) return _self.x + _self.width end,
    },
    max_y = property {
        get = function (_self) return _self.y + _self.height end,
    },

    left = property {
        get = function (_self) return _self.x end,
        set = function (_self,_v) _self.x = _v end
    },
    right = property {
        get = function (_self) return _self.y end,
        set = function (_self,_v) _self.y = _v end
    },
    top = property {
        get = function (_self) return _self.width end,
        set = function (_self,_v) _self.width = _v end
    },
    bottom = property {
        get = function (_self) return _self.height end,
        set = function (_self,_v) _self.height = _v end
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    copy = function ( _self )
        t = typeof (_self)
        return t( _self.x, _self.y, _self.width, _self.height )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    contains = function ( _self, _point )
        if _point.x >= _self.min_x and
           _point.x < _self.max_x and
           _ponit.y >= _self.min_x and
           _point.y < _self.max_x then
           return true
       end
       return false
    end,
}) 
__M.rect = rect

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
