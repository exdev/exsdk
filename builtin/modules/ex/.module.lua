-- ======================================================================================
-- File         : .module.lua
-- Author       : Wu Jie 
-- Last Change  : 01/31/2013 | 13:31:01 PM | Thursday,January
-- Description  : 
-- ======================================================================================

local old_path = package.path
package.path = "./?.lua"

local _M = {
    class = require ("class"),
    vec2f = require ("math.vec2f"),
}

package.path = old_path

_G[ex] = _M
package.loaded[ex] = _M 

return _M
