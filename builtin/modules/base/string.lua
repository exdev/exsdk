-- ======================================================================================
-- File         : string.lua
-- Author       : Wu Jie 
-- Last Change  : 02/19/2013 | 18:49:51 PM | Tuesday,February
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- base functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function string.findlast ( s, pattern, plain )
    local curr = 0

    repeat
        local next = s:find(pattern, curr + 1, plain)
        if next then curr = next end
    until not next

    if curr > 0 then
        return curr
    end	
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function string.gsplit ( s, sep, plain )
	local start = 1
	local done = false
	local function pass(i, j, ...)
		if i then
			local seg = s:sub(start, i - 1)
			start = j + 1
			return seg, ...
		else
			done = true
			return s:sub(start)
		end
	end
	return function()
		if done then return end
		if sep == '' then done = true return s end
		return pass(s:find(sep, start, plain))
	end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function string.split ( s, sep, plain )
    local list = {}

    if plain then
        for w in s:gsplit( sep, plain ) do
            list[#list+1] = w
        end
    else
        for w in s:gmatch("[^"..sep.."]+") do
            list[#list+1] = w
        end
    end

    return list
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function string.trim ( s )
    return s:match( "^%s*(.-)%s*$" )
end
