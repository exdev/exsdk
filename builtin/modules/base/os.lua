-- ======================================================================================
-- File         : os.lua
-- Author       : Wu Jie 
-- Last Change  : 02/18/2013 | 11:23:53 AM | Monday,February
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- base functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function os.executef (cmd, ...)
    return os.execute( string.format(cmd, ...) )
end

