-- ======================================================================================
-- File         : math.lua
-- Author       : Wu Jie 
-- Last Change  : 02/25/2013 | 14:46:40 PM | Monday,February
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- properties
--/////////////////////////////////////////////////////////////////////////////

math.twoPI = math.pi*2 
math.halfPI = math.pi/2

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function math.clamp ( _val, _min, _max ) 
    if _val > _max then return _max end 
    if _val < _min then return _min end 
    return _val
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function math.lerp ( _src, _dest, _ratio )
    assert ( type(_ratio) == "number", "Type error: _ratio is not a number" )
    return _src * (1.0 - _ratio) + _dest * _ratio 
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- Usage: 
-- item = { "gold knife", "silver knife", "axe", "knife" }
-- gen_idx = probability( {0.12, 0.3, 0.3, 0.9 } )
-- drop_item = item[gen_idx()]
-- ------------------------------------------------------------------ 

function math.probability ( _weights )
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
