-- ======================================================================================
-- File         : init.lua
-- Author       : Wu Jie 
-- Last Change  : 12/11/2013 | 14:58:08 PM | Wednesday,December
-- Description  : 
-- ======================================================================================

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function test () 
    print ( "Hello World [override]" )
end

wiz.onInit = function () 
    print("runtime update test")

    wiz.dofile ("module_01.lua")
    wiz.dofile ("module_02.lua")

    module_01.say_hello();
    module_02.say_hello();

    print("override test")

    module_01.test = test;
    module_02.test = test;


    module_01.say_hello();
    module_02.say_hello();
end
