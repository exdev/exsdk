-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 04/25/2013 | 15:03:12 PM | Thursday,April
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

local function parseArgs ( _arguments, _options ) 
end

--/////////////////////////////////////////////////////////////////////////////
-- execute
--/////////////////////////////////////////////////////////////////////////////

parseArgs ( wiz.arguments, {
    -- { "app" },
} )

-- test_app
local appName = "test_graphics"
local appPath = ""

-- if wiz.platform == "windows" then
--     appPath = string.format( "d:/dev/exdev/exsdk/examples/%s/", appName ) 
-- elseif wiz.platform == "macosx" then
--     appPath = string.format( "/Users/Johnny/exdev/exsdk/examples/%s/", appName ) 
-- end
appPath = string.format( "../../../../../examples/%s/", appName ) 

wiz:openApp(appPath)
