-- ======================================================================================
-- File         : texture.lua
-- Author       : Wu Jie 
-- Last Change  : 02/19/2013 | 18:27:04 PM | Tuesday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local texture = class ({
    __typename = "texture",

    -- constructor & destructor
    __init = function ( _self, _w, _h )
        assert ( type(_w) == "number", "Type error: _x must be number" )
        assert ( type(_h) == "number", "Type error: _y must be number" )
        _self._cptr = ex_c.texture_new(_w,_h)
    end,

    __gc = function (_self)
        ex_c.texture_destroy(_self._cptr)
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _cptr = ex_c.null,

    width = property { 
        get = function (_self) return ex_c.texture_get_width ( _self._cptr ) end 
    },
    height = property { 
        get = function (_self) return ex_c.texture_get_height ( _self._cptr ) end 
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    _setptr = function ( _self, _ptr )
        _self._cptr = _ptr
    end,
}) 
__M.texture = texture

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
