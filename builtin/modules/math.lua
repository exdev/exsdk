-- ======================================================================================
-- File         : math.lua
-- Author       : Wu Jie 
-- Last Change  : 11/02/2010 | 16:40:09 PM | Tuesday,November
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- module
--/////////////////////////////////////////////////////////////////////////////

local assert, type = assert, type
local math = math

module(...)

--/////////////////////////////////////////////////////////////////////////////
-- constants
--/////////////////////////////////////////////////////////////////////////////

two_pi = math.pi*2 
half_pi = math.pi/2

deg_to_rad = math.pi/180.0
rad_to_deg = 180.0/math.pi

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function lerp ( _src, _dest, _ratio )
    -- assert ( type(_src) == "number", "_src is not a number" )
    -- assert ( type(_dest) == "number", "_dest is not a number" )
    assert ( type(_ratio) == "number", "_ratio is not a number" )
    return _src * (1.0 - _ratio) + _dest * _ratio 
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- Usage: 
-- item = { "gold knife", "silver knife", "axe", "knife" }
-- gen_idx = probability( {0.12, 0.3, 0.3, 0.9 } )
-- drop_item = item[gen_idx()]
-- ------------------------------------------------------------------ 

function probability( _weights )
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

