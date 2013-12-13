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

function string.findlast ( _s, _pattern, _plain )
    local curr = 0

    repeat
        local next = _s:find(_pattern, curr + 1, _plain)
        if next then curr = next end
    until not next

    if curr > 0 then
        return curr
    end	
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function string.gsplit ( _s, _sep, _plain )
	local start = 1
	local done = false
	local function pass(i, j, ...)
		if i then
			local seg = _s:sub(start, i - 1)
			start = j + 1
			return seg, ...
		else
			done = true
			return _s:sub(start)
		end
	end
	return function()
		if done then return end
		if _sep == '' then done = true return _s end
		return pass(_s:find(_sep, start, _plain))
	end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function string.split ( _s, _sep, _plain )
    local list = {}

    if _plain then
        for w in _s:gsplit( _sep, _plain ) do
            list[#list+1] = w
        end
    else
        for w in _s:gmatch("[^".._sep.."]+") do
            list[#list+1] = w
        end
    end

    return list
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function string.trim ( _s )
    return _s:match( "^%s*(.-)%s*$" )
end
