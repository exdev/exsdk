-- ======================================================================================
-- File         : font_importer.lua
-- Author       : Wu Jie 
-- Last Change  : 04/03/2013 | 11:53:08 AM | Wednesday,April
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

local font_importer = editor.importer.extend ({
    __typename = "font_importer",

    -- constructor & destructor
    __init = function ( _self, _path )
        checkarg(_path,"string")

        _self.path = _path
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    size = 16,

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    exec = function (_self)
        local fnt = ex.font.new()
        local cptr = ex_c.font_load ( project.fsys_path(_self.path), _self.size )
        fnt._cptr = cptr

        return fnt
    end,
})
__M.font_importer = font_importer

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
