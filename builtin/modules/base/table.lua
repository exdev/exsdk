-- ======================================================================================
-- File         : table.lua
-- Author       : Wu Jie 
-- Last Change  : 02/18/2013 | 16:59:48 PM | Monday,February
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- base functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function table.contains ( t, val )
    for _,v in pairs(t) do
        if v == val then
            return true
        end
    end
    return false
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- copy will not create new table and copy table-refrence
-- ------------------------------------------------------------------ 

function table.copy ( t, from )
    for k,v in pairs(from) do
        t[k] = v
    end
    return t
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- deepcopy will create new table and copy the value in the table to the new table
-- ------------------------------------------------------------------ 

function table.deepcopy ( t, from )
    for k,v in pairs(from) do
        if type(v) == "table" then
            local tt = {}
            t[k] = table.deepcopy ( tt, v )
        else
            t[k] = v
        end
    end
    return t
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function table.add ( t, el )
    t[#t+1] = el
    return t
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function table.addlist ( t, list )
    assert ( type(list) == "table" and #list > 0, "Invalid list" )
    for i=1,#list do
        t[#t+1] = list[i]
    end

    return t
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function table.removeel ( t, el )
    for i=1,#t do
        if t[i] == el then
            table.remove(t,i)
            break
        end
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function table.fastremoveat ( t, idx )
    assert ( type(idx) == "number" )
    if idx > #t then return end

    t[idx] = t[#t]
    t[#t] = nil
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function table.fastremoveel ( t, el )
    for i=1,#t do
        if t[i] == el then
            table.fastremoveat(t,i)
            break
        end
    end
end

