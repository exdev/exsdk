-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:30:40 PM | Sunday,February
-- Description  : 
-- ======================================================================================

return {
    -- name = nil, NOTE: DO NOT define name for global module
    files = {
        -- global extension
        "global.lua",
        "class.lua",
        "defs.lua",

        -- lua internal extension
        "debug.lua",
        "table.lua",
        "string.lua",
        "os.lua",
        "math/math.lua",
        "math/ease.lua",

        -- ex internal extension
        "re.lua",
        "pathutil.lua",
    }
}
