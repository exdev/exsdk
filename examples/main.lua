-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 04/25/2013 | 15:03:12 PM | Thursday,April
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

local function parse_args ( _arguments, _options ) 
end

--/////////////////////////////////////////////////////////////////////////////
-- execute
--/////////////////////////////////////////////////////////////////////////////

parse_args ( wiz.arguments, {
    -- { "app" },
} )

if wiz.platform == "windows" then
    wiz:open_app( "d:/dev/exdev/exsdk/examples/test_project/" )
elseif wiz.platform == "macosx" then
    wiz:open_app( "/Users/Johnny/exdev/exsdk/examples/test_project/" )
end
