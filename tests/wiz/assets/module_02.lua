-- ======================================================================================
-- File         : module_02.lua
-- Author       : Wu Jie 
-- Last Change  : 12/11/2013 | 15:01:21 PM | Wednesday,December
-- Description  : 
-- ======================================================================================

module_02 = module_02 or {} 

function module_02.test ()
    print ( "module 02: Hello World [original]" )
end

function module_02.say_hello ()
    module_02.test()
end

