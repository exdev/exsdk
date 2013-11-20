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

-- test_app
local app_name = "test_graphics"
local app_path = ""

-- if wiz.platform == "windows" then
--     app_path = string.format( "d:/dev/exdev/exsdk/examples/%s/", app_name ) 
-- elseif wiz.platform == "macosx" then
--     app_path = string.format( "/Users/Johnny/exdev/exsdk/examples/%s/", app_name ) 
-- end
app_path = string.format( "../../../../../examples/%s/", app_name ) 

wiz:open_app(app_path)
