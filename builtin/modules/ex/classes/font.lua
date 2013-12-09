-- ======================================================================================
-- File         : font.lua
-- Author       : Wu Jie 
-- Last Change  : 04/09/2013 | 13:34:44 PM | Tuesday,April
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local font = class ({
    __typename = "font",

    -- constructor & destructor
    __gc = function (_self)
        ex_c.font_destroy(_self._cptr)
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _cptr = ex_c.null, 

    size = property { 
        get = function (_self) return ex_c.font_get_size(_self._cptr) end, 
        set = function (_self,_v) ex_c.font_set_size(_self._cptr,_v) end
    },

    outlineType = property { 
        get = function (_self) return ex_c.font_get_outline_type(_self._cptr) end, 
        set = function (_self,_v) ex_c.font_set_outline_type(_self._cptr,_v) end
    },

    outlineThickness = property { 
        get = function (_self) return ex_c.font_get_outline_thickness(_self._cptr) end, 
        set = function (_self,_v) ex_c.font_set_outline_thickness(_self._cptr,_v) end
    },

    family = property {
        get = function (_self) return ex_c.font_get_family_name (_self._cptr) end,
    },

    style = property {
        get = function (_self) return ex_c.font_get_style_name (_self._cptr) end,
    },

    height = property {
        get = function (_self) return ex_c.font_get_height (_self._cptr) end,
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

}) 
__M.font = font

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
