-- ======================================================================================
-- File         : module_01.lua
-- Author       : Wu Jie 
-- Last Change  : 12/11/2013 | 14:58:46 PM | Wednesday,December
-- Description  : 
-- ======================================================================================

module_01 = module_01 or {} 

local function test ()
    print ( "module 01: Hello World [original]" )
end
module_01.test = test

local function say_hello ()
    test()
end
module_01.say_hello = say_hello

return module_01

