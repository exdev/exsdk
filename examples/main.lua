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

parse_args ( app.arguments, {
    -- { "project" },
} )

if app.platform == "windows" then
    app:open_project( "d:/dev/exdev/exsdk/examples/test_project/" )
elseif app.platform == "macosx" then
    app:open_project( "/Users/Johnny/exdev/exsdk/examples/test_project/" )
end
