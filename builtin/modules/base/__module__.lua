-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 16:30:40 PM | Sunday,February
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

-- lua internal extension
module_add ( "global.lua" )
module_add ( "debug.lua", "debug" )
module_add ( "table.lua", "table" )
module_add ( "string.lua", "string" )

-- ex internal extension
module_add ( "os.lua", "os" )
module_add ( "app.lua", "app" )
module_add ( "path.lua", "path" )
