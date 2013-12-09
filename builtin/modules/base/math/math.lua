-- ======================================================================================
-- File         : math.lua
-- Author       : Wu Jie 
-- Last Change  : 02/25/2013 | 14:46:40 PM | Monday,February
-- Description  : 
-- ======================================================================================

local __M = {}

local pi = math.pi

--/////////////////////////////////////////////////////////////////////////////
-- constants
--/////////////////////////////////////////////////////////////////////////////

local twoPI = pi*2 
__M.twoPI = twoPI

local halfPI = pi/2
__M.halfPI = halfPI

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local clamp = function ( _val, _min, _max ) 
    if _val > _max then return _max end 
    if _val < _min then return _min end 
    return _val
end
__M.clamp = clamp

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local lerp = function ( _src, _dest, _ratio )
    assert ( type(_ratio) == "number", "Type error: _ratio is not a number" )
    return _src * (1.0 - _ratio) + _dest * _ratio 
end
__M.lerp = lerp

-- ------------------------------------------------------------------ 
-- Desc: 
-- Usage: 
-- item = { "gold knife", "silver knife", "axe", "knife" }
-- gen_idx = probability( {0.12, 0.3, 0.3, 0.9 } )
-- drop_item = item[gen_idx()]
-- ------------------------------------------------------------------ 

local probability = function ( _weights )
    local sum = 0.0
    local cdf = {}

    for i=1,#_weights do 
        sum = sum + _weights[i] 
    end

    cdf[1] = _weights[1]/sum
    for i=2,#_weights-1 do
        cdf[i] = _weights[i]/sum
        cdf[i] = cdf[i] + cdf[i-1]
    end
    cdf[#_weights] = 1.0

    return function ()
        local y = math.random()
        for i=1,#cdf do
            if ( y < cdf[i] ) then 
                return i
            end
        end
        return -1
    end
end
__M.probability = probability

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
