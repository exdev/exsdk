-- ======================================================================================
-- File         : bitmapfont.lua
-- Author       : Wu Jie 
-- Last Change  : 02/21/2013 | 14:09:11 PM | Thursday,February
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

ex.bitmapfont = class ({
    __typename = "bitmapfont",

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    -- basic information
    faceName = "",
    size = 0,
    lineHeight = 0,
    pages = 0,
    pageWidth = 0,
    pageHeight = 0,

    isBold = false,
    isItalic = false,  
    isUnicode = false,
    isSmooth = false,
    isAA = false,
    hasKerning = false,

    -- for details, please read the parse code in bitmapfont_importer.lua
    charInfos = {},
    pageInfos = {},
    kerningInfos = {},

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    getKerning = function ( _self, _first, _second )
        for i=1,#_self.kerningInfos do
            local kerningInfo = _self.kerningInfos[i]
            if kerningInfo.first == _first and 
               kerningInfo.second == _second then 
               return kerningInfo.amount
            end
        end

        return 0
    end,
}) 
