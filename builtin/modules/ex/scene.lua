-- ======================================================================================
-- File         : scene.lua
-- Author       : Wu Jie 
-- Last Change  : 02/23/2013 | 16:03:34 PM | Saturday,February
-- Description  : 
-- ======================================================================================

local __M = {}
local typename = ex.typename

local entities = {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function update ()
    for _,ent in ipairs(entities) do
        ent:update()
    end
end
__M.update = update

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function new_entity ( _name )
    local ent = ex.entity(_name)
    entities[#entities+1] = ent
    return ent
end
__M.new_entity = new_entity

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
