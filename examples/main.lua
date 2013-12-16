-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 04/25/2013 | 15:03:12 PM | Thursday,April
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

print("arguments = " .. #wiz.arguments)
for i=1,#wiz.arguments do
    print(wiz.arguments[i])
end

-- test_app
local appPath = "../../../../../examples/"

local bundle = wiz.mount( "./test_graphics/", "test_graphics" )
bundle:dofile( "init.lua" )
