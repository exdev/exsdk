-- ======================================================================================
-- File         : css.lua
-- Author       : Wu Jie 
-- Last Change  : 12/25/2013 | 10:19:09 AM | Wednesday,December
-- Description  : 
-- ======================================================================================

local lookupTable = {}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function parseNumber ( propName, options )
    local hasPX = false

    for i=1,#options do
        local opt = options[i]

        if     opt == "px"      then hasPX      = true 
        end
    end

    return function ( style, text )
        local text = text:trim()
        local len = text:len()

        -- px
        if hasPX and text:ncmp( "px", len-2, 2 ) then 
            style[propName] = tonumber( text:sub( 1, len-2 ) )
            return
        end
        style[propName] = tonumber(text)
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function parseLength ( propName, options )
    local hasPX = false
    local hasPercent = false
    local hasAuto = false
    local hasNone = false
    local hasInherit = false

    for i=1,#options do
        local opt = options[i]

        if     opt == "px"      then hasPX      = true 
        elseif opt == "%"       then hasPercent = true
        elseif opt == "auto"    then hasAuto    = true
        elseif opt == "none"    then hasNone    = true
        elseif opt == "inherit" then hasInherit = true
        end
    end

    return function ( style, text )
        local text = text:trim()

        -- inherit
        if hasInherit and text == "inherit" then
            style[propName] = { type = "inherit", value = 0 } 
            return

        -- auto
        elseif hasAuto and text == "auto" then
            style[propName] = { type = "auto", value = 0 } 
            return

        -- none
        elseif hasNone and text == "none" then
            style[propName] = { type = "none", value = 0 } 
            return
        end

        local len = text:len()

        -- px
        if hasPX and text:ncmp( "px", len-2, 2 ) then 
            style[propName] = { type = "length", value = tonumber( text:sub( 1, len-2 ) ) } 
            return

        -- %
        elseif hasPercent and text:ncmp( "%", len-1, 1 ) then
            style[propName] = { type = "percent", value = tonumber( text:sub( 1, len-1 ) ) } 
            return

        end
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function parseColor ( propName )
    return function ( style, text )
        local text = text:trim()

        -- #f00, #ff0000
        if text:ncmp("#",0,1) then
            local v = text:sub(2)
            if #v == 3 then
                local r = text:sub(2,2)
                local g = text:sub(3,3)
                local b = text:sub(4,4)
                style[propName] = ex.color4f ( 
                    tonumber(r..r,16)/255,
                    tonumber(g..g,16)/255,
                    tonumber(b..b,16)/255,
                    1.0
                )
                return

            elseif #v == 6 then
                local r = text:sub(2,3)
                local g = text:sub(4,5)
                local b = text:sub(6,7)
                style[propName] = ex.color4f (
                    tonumber(r,16)/255,
                    tonumber(g,16)/255,
                    tonumber(b,16)/255,
                    1.0
                )
                return

            else

                error ( "invalid color value " .. text )
                return
            end

        -- rgb or rgba
        elseif text:ncmp("rgb",0,3) then
            local list = {}
            for w in string.gmatch(text, "%d+") do
                table.add ( list, w )
            end
            local r = list[1]/255 or 1.0
            local g = list[2]/255 or 1.0
            local b = list[3]/255 or 1.0
            local a = list[4]/255 or 1.0
            style[propName] = ex.color( r, g, b, a )
            return
        end
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function parseOption ( propName, options )
    return function ( style, text )
        local text = text:trim()
        local found = false

        for i=1,#options do
            if options[i] == text then 
                found = true
                break 
            end
        end

        assert ( found, "Can not find option: " .. text .. " for property: " .. propName )
        style[propName] = text
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function parseAsset ( propName )
    return function ( style, text )
        local text = text:trim()
        -- TODO: asset must have the bundle
        style[propName] = wiz.bundle:load(text)
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function parseBox ( top, right, bottom, left )
    return function ( style, text )
        local text = text:trim()
        local list = text:split(" ")

        local txtTop = list[1]
        local txtRight = list[2] or txtTop
        local txtBottom = list[3] or txtTop
        local txtLeft = list[4] or txtRight

        local parser = lookupTable[top]
        assert ( parser ~= nil, "can't not find parser for " .. top )
        parser( style, txtTop )

        parser = lookupTable[right]
        assert ( parser ~= nil, "can't not find parser for " .. right )
        parser( style, txtRight )

        parser = lookupTable[bottom]
        assert ( parser ~= nil, "can't not find parser for " .. bottom )
        parser( style, txtBottom )

        parser = lookupTable[left]
        assert ( parser ~= nil, "can't not find parser for " .. left )
        parser( style, txtLeft )
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

lookupTable["width"]        = parseLength ( "width",     { "px", "%", "auto" } ) 
lookupTable["height"]       = parseLength ( "height",    { "px", "%", "auto" } ) 
lookupTable["min-width"]    = parseLength ( "minWidth",  { "px", "%" } )
lookupTable["min-height"]   = parseLength ( "minHeight", { "px", "%" } ) 
lookupTable["max-width"]    = parseLength ( "maxWidth",  { "px", "%", "none" } )
lookupTable["max-height"]   = parseLength ( "maxHeight", { "px", "%", "none" } ) 
lookupTable["z-index"]      = parseNumber ( "zIndex",    {} ) 

lookupTable["left"]         = parseLength ( "left",     { "px", "%", "auto" } )
lookupTable["right"]        = parseLength ( "right",    { "px", "%", "auto" } ) 
lookupTable["top"]          = parseLength ( "top",      { "px", "%", "auto" } ) 
lookupTable["bottom"]       = parseLength ( "bottom",   { "px", "%", "auto" } ) 

lookupTable["margin"] = parseBox ( "margin-top", "margin-right", "margin-bottom", "margin-left" ) 
lookupTable["margin-left"]   = parseLength ( "marginLeft",   { "px", "%", "auto" } ) 
lookupTable["margin-right"]  = parseLength ( "marginRight",  { "px", "%", "auto" } ) 
lookupTable["margin-top"]    = parseLength ( "marginTop",    { "px", "%", "auto" } ) 
lookupTable["margin-bottom"] = parseLength ( "marginBottom", { "px", "%", "auto" } ) 

lookupTable["padding"] = parseBox ( "padding-top", "padding-right", "padding-bottom", "padding-left" ) 
lookupTable["padding-left"]   = parseLength ( "paddingLeft",   { "px", "%" } ) 
lookupTable["padding-right"]  = parseLength ( "paddingRight",  { "px", "%" } ) 
lookupTable["padding-top"]    = parseLength ( "paddingTop",    { "px", "%" } ) 
lookupTable["padding-bottom"] = parseLength ( "paddingBottom", { "px", "%" } ) 

-- lookupTable["border"] = parseBorder () -- TODO 
lookupTable["border-style"]         = parseOption ( "borderStyle", { "none", "solid", "image" } ) 
lookupTable["border-image"]         = parseAsset  ( "borderImage" ) 
lookupTable["border-left"]          = parseNumber ( "borderLeft", { "px" } ) 
lookupTable["border-right"]         = parseNumber ( "borderRight", { "px" } ) 
lookupTable["border-top"]           = parseNumber ( "borderTop", { "px" } ) 
lookupTable["border-bottom"]        = parseNumber ( "borderBottom", { "px" } ) 
lookupTable["border-left-color"]    = parseColor ( "borderLeftColor" ) 
lookupTable["border-right-color"]   = parseColor ( "borderRightColor" )
lookupTable["border-top-color"]     = parseColor ( "borderTopColor" )
lookupTable["border-bottom-color"]  = parseColor ( "borderBottomColor" )

lookupTable["background-color"] = parseColor ( "backgroundColor" )
lookupTable["background-image"] = parseAsset ( "backgroundImage" )

-- lookupTable["font-family"]      = parseFontFamily ( "fontFamily" ) -- TODO
lookupTable["word-spacing"]     = parseNumber ( "wordSpacing", { "px" } ) 
lookupTable["letter-spacing"]   = parseNumber ( "letterSpacing", { "px" } ) 
lookupTable["line-height"]      = parseLength ( "lineHeight", { "px", "%", "auto" } ) 
lookupTable["visible"]          = parseOption ( "visible", { "visible", "hidden", "collapse" } ) 
lookupTable["text-align"]       = parseOption ( "textAlign", { "left", "right", "center" } ) 
lookupTable["text-transform"]   = parseOption ( "textTransform", { "capitalize", "uppercase", "lowercase", "none" } ) 
lookupTable["text-decorations"] = parseOption ( "textDecorations", { "none", "underline", "overline", "line-through" } ) 
lookupTable["text-direction"]   = parseOption ( "textDirection", { "ltr", "rtl" } ) 
lookupTable["white-space"]      = parseOption ( "whiteSpace", { "normal", "pre", "pre-wrap", "pre-line", "nowrap" } ) 

lookupTable["display"] = parseOption ( "display", { "inline", "block", "inline-block", 
                                                    "flex", "inline-flex", "grid", "inline-grid", 
                                                    "none" } ) 
lookupTable["overflow-x"] = parseOption ( "overflowX", { "visible", "hidden", "scroll", "auto", 
                                                         "overlay", "marquee", "pagedx", "pagedy" } ) 
lookupTable["overflow-y"] = parseOption ( "overflowY", { "visible", "hidden", "scroll", "auto", 
                                                         "overlay", "marquee", "pagedx", "pagedy" } ) 
lookupTable["vertical-align"] = parseOption ( "verticalAlign", { "baseline", "middle", "sub", "super", "text-top", 
                                                                 "text-bottom", "top", "bottom", "baseline-middle", "length" } ) 
lookupTable["position"] = parseOption ( "position", { "static", "relative", "absolute", "sticky", "fixed" } ) 

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

wiz.css = {

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    parse = function ( style, text )
        local decls = text:split ( ";", true )

        for i=1,#decls do
        end

        for i=1,#decls do
            local decl = decls[i]

            if decl:isblank() == false then
                local result = decl:split ( ":", true )
                assert ( #result == 2, "Invalid declaration " .. decl )

                -- DEBUG: print( string.format( "decl[%d] = %s, prop = %s, value = %s", i, decl, result[1], result[2] ) )

                local prop = result[1]:trim()
                local value = result[2]
                local parser = lookupTable[prop]
                assert ( parser ~= nil, "Can not find parser for " .. prop )

                parser( style, value )
            end
        end
    end,
}
