-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 04/25/2013 | 15:03:12 PM | Thursday,April
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- NOTE: XCode add command: "../../../../../tests/wiz/main.lua"

print("arguments = " .. #wiz.arguments)
for i=1,#wiz.arguments do
    print(wiz.arguments[i])
end

local bundle = wiz.mount( "./", "tests" )
bundle:dofile( "test_graphics.lua" )
