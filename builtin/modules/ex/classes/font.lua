-- ======================================================================================
-- File         : font.lua
-- Author       : Wu Jie 
-- Last Change  : 04/09/2013 | 13:34:44 PM | Tuesday,April
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

ex.font = class ({
    __typename = "font",

    -- constructor & destructor
    __gc = function (self)
        ex_c.font_destroy(self._cptr)
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _cptr = ex_c.null, 

    size = property { 
        get = function (self) return ex_c.font_get_size(self._cptr) end, 
        set = function (self,v) ex_c.font_set_size(self._cptr,v) end
    },

    outlineType = property { 
        get = function (self) return ex_c.font_get_outline_type(self._cptr) end, 
        set = function (self,v) ex_c.font_set_outline_type(self._cptr,v) end
    },

    outlineThickness = property { 
        get = function (self) return ex_c.font_get_outline_thickness(self._cptr) end, 
        set = function (self,v) ex_c.font_set_outline_thickness(self._cptr,v) end
    },

    family = property {
        get = function (self) return ex_c.font_get_family_name (self._cptr) end,
    },

    style = property {
        get = function (self) return ex_c.font_get_style_name (self._cptr) end,
    },

    height = property {
        get = function (self) return ex_c.font_get_height (self._cptr) end,
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

}) 
