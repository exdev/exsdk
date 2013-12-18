-- ======================================================================================
-- File         : texture.lua
-- Author       : Wu Jie 
-- Last Change  : 02/19/2013 | 18:27:04 PM | Tuesday,February
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

ex.texture = class ({
    __typename = "texture",

    -- constructor & destructor
    __init = function ( self, w, h )
        checkarg(w,"number")
        checkarg(h,"number")

        self._cptr = ex_c.texture_new(w,h)
    end,

    __gc = function (self)
        ex_c.texture_destroy(self._cptr)
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _cptr = ex_c.null,
    _lockStartX = -1,
    _lockStartY = -1,

    width = property { 
        get = function (self) return ex_c.texture_get_width ( self._cptr ) end 
    },
    height = property { 
        get = function (self) return ex_c.texture_get_height ( self._cptr ) end 
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    lockRect = function ( self, rect )
        self._lockStartX = math.ceil(rect.x)
        self._lockStartY = math.ceil(rect.y)
        ex_c.texture_lock_rect ( self._cptr, 
                                 self._lockStartX, 
                                 self._lockStartY, 
                                 rect.width, 
                                 rect.height )
    end,

    lock = function ( self, x, y, w, h )
        self._lockStartX = math.ceil(x)
        self._lockStartY = math.ceil(y)
        ex_c.texture_lock_rect ( self._cptr, 
                                 self._lockStartX, 
                                 self._lockStartY, 
                                 w, 
                                 h )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    unlock = function ( self )
        ex_c.texture_unlock ( self._cptr )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    setPixel = function ( self, x, y, color )
        ex_c.texture_set_pixel ( self._cptr, 
                                 self._lockStartX + x, 
                                 self._lockStartY + y, 
                                 color.r, color.g, color.b, color.a )
    end,
}) 
