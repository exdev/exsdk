-- ======================================================================================
-- File         : .module.lua
-- Author       : Wu Jie 
-- Last Change  : 01/31/2013 | 13:31:01 PM | Thursday,January
-- Description  : 
-- ======================================================================================

local _M = {}

_ENV = _M

    dofile("core.lua")
    dofile("class.lua")
    dofile("debug.lua")
    dofile("math/math.lua")
    dofile("math/ease.lua")
    dofile("math/vec2f.lua")

_ENV = _G

_G[ex] = _M
package.loaded[ex] = _M 

return _M
