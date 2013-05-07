-- ======================================================================================
-- File         : component.lua
-- Author       : Wu Jie 
-- Last Change  : 02/23/2013 | 16:09:11 PM | Saturday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local component = class ({
    __typename = "component",

    --/////////////////////////////////////////////////////////////////////////////
    -- properites
    --/////////////////////////////////////////////////////////////////////////////

    node = ex.node.null,
}) 
__M.component = component

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M