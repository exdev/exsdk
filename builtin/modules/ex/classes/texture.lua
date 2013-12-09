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
        checkarg(_w,"number")
        checkarg(_h,"number")

        _self._cptr = ex_c.texture_new(_w,_h)
    end,

    __gc = function (_self)
        ex_c.texture_destroy(_self._cptr)
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _cptr = ex_c.null,
    _lock_start_x = -1,
    _lock_start_y = -1,

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

    lockRect = function ( _self, _rect )
        _self._lock_start_x = math.ceil(_rect.x)
        _self._lock_start_y = math.ceil(_rect.y)
        ex_c.texture_lock_rect ( _self._cptr, 
                                 _self._lock_start_x, 
                                 _self._lock_start_y, 
                                 _rect.width, 
                                 _rect.height )
    end,

    lock = function ( _self, _x, _y, _w, _h )
        _self._lock_start_x = math.ceil(_x)
        _self._lock_start_y = math.ceil(_y)
        ex_c.texture_lock_rect ( _self._cptr, 
                                 _self._lock_start_x, 
                                 _self._lock_start_y, 
                                 _w, 
                                 _h )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    unlock = function ( _self )
        ex_c.texture_unlock ( _self._cptr )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    setPixel = function ( _self, _x, _y, _color )
        ex_c.texture_set_pixel ( _self._cptr, 
                                 _self._lock_start_x + _x, 
                                 _self._lock_start_y + _y, 
                                 _color.r, _color.g, _color.b, _color.a )
    end,
}) 
__M.texture = texture

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
