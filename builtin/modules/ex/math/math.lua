-- ======================================================================================
-- File         : math.lua
-- Author       : Wu Jie 
-- Last Change  : 11/02/2010 | 16:40:09 PM | Tuesday,November
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- constants
--/////////////////////////////////////////////////////////////////////////////

local two_pi = math.pi*2 
__M.two_pi = two_pi

local half_pi = math.pi/2
__M.half_pi = half_pi

local deg_to_rad = math.pi/180.0
__M.deg_to_rad = deg_to_rad

local rad_to_deg = 180.0/math.pi
__M.rad_to_deg = rad_to_deg


--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function lerp ( _src, _dest, _ratio )
    -- assert ( type(_src) == "number", "_src is not a number" )
    -- assert ( type(_dest) == "number", "_dest is not a number" )
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

local function probability( _weights )
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
