-- ======================================================================================
-- File         : style.lua
-- Author       : Wu Jie 
-- Last Change  : 12/20/2013 | 12:01:33 PM | Friday,December
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

-- type: auto, relative, percent, length, none
-- value: float, double, int
local function length ( type, value ) 
    return { 
        type = type, 
        value = value or 0
    } 
end

-- ------------------------------------------------------------------ 
-- Desc: default style 
-- ------------------------------------------------------------------ 

function wiz.style () 
    return {
        -- box
        width       = length("auto"),
        height      = length("auto"),
        minWidth    = length("length",0),
        minHeight   = length("length",0),
        maxWidth    = length("none"),
        maxHeight   = length("none"),
        zIndex      = 0,

        -- surround (offset)
        left            = length("length",0),
        right           = length("length",0),
        top             = length("length",0),
        bottom          = length("length",0),

        -- surround (margin)
        marginLeft      = length("length",0),
        marginRight     = length("length",0),
        marginTop       = length("length",0),
        marginBottom    = length("length",0),

        -- surround (padding)
        paddingLeft     = length("length",0),
        paddingRight    = length("length",0),
        paddingTop      = length("length",0),
        paddingBottom   = length("length",0),

        -- surround (border)
        borderStyle     = "none", -- none, solid, image
        borderImage     = ex.texture.null, 
        borderLeft      = 0,
        borderRight     = 0,
        borderTop       = 0,
        borderBottom    = 0,
        borderLeftColor   = ex.color4f.white,
        borderRightColor  = ex.color4f.white,
        borderTopColor    = ex.color4f.white,
        borderBottomColor = ex.color4f.white,

        -- background
        backgroundColor = ex.color4f.white,
        backgroundImage = ex.texture.null,

        -- inherited (the value can set to "inherit")
        fontFamily = "VeraMono",
        wordSpacing = 0,
        letterSpacing = 0,
        lineHeight = length("auto"),
        visible = "visible", -- visible, hidden, collapse
        textAlign = "left", -- left, right, center 
        textTransform = "none", -- capitalize, uppercase, lowercase, none
        textDecorations = "none", -- none, underline, overline, line-through
        textDirection = "ltr", -- ltr, rtl
        whiteSpace = "normal", -- normal, pre, pre-wrap, pre-line, nowrap

        -- non-inherited
        display = "inline", -- inline, block, inline-block, flex, inline-flex, grid, inline-grid, none,  
        overflowX = "visible", -- visible, hidden, scroll, auto, overlay, marquee, pagedx, pagedy
        overflowY = "visible", -- visible, hidden, scroll, auto, overlay, marquee, pagedx, pagedy
        verticalAlign = "baseline", -- baseline, middle, sub, super, text_top, text_bottom, top, bottom, baseline_middle, length
        -- clear = "none", -- none, left, right, both
        position = "static", -- static, relative, absolute, sticky, fixed
        -- floating = "none", -- none, left, right
    }
end

