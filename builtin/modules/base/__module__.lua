-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:30:40 PM | Sunday,February
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

-- global extension
module_add ( "global.lua" )
module_add ( "class.lua" )

-- lua internal extension
module_add ( "debug.lua", "debug" )
module_add ( "table.lua", "table" )
module_add ( "string.lua", "string" )
module_add ( "os.lua", "os" )
module_add ( "math/math.lua", "math" )
module_add ( "math/ease.lua", "math" )

-- ex internal extension
module_add ( "re.lua", "re" ) -- lpeg re module
module_add ( "app.lua", "app" )
module_add ( "project.lua", "project" )
module_add ( "path.lua", "path" )
module_add ( "keycode.lua", "keycode" )
