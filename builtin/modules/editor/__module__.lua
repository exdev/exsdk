-- ======================================================================================
-- File         : __module__.lua
-- Author       : Wu Jie 
-- Last Change  : 02/05/2013 | 14:43:22 PM | Tuesday,February
-- Description  : 
-- ======================================================================================

local __M = {}
_G["editor"] = __M
package.loaded["editor"] = __M 

-- basic module
__M.asset_db = {}
module_add( __M.asset_db, "editor", "asset_db" )
module_add( __M, "editor", "importer" )

return __M
