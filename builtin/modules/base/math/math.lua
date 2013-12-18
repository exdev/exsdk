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

function math.clamp ( val, min, max ) 
    if val > max then return max end 
    if val < min then return min end 
    return val
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function math.lerp ( src, dest, ratio )
    assert ( type(ratio) == "number", "Type error: ratio is not a number" )
    return src * (1.0 - ratio) + dest * ratio 
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- Usage: 
-- item = { "gold knife", "silver knife", "axe", "knife" }
-- gen_idx = probability( {0.12, 0.3, 0.3, 0.9 } )
-- drop_item = item[gen_idx()]
-- ------------------------------------------------------------------ 

function math.probability ( weights )
    local sum = 0.0
    local cdf = {}

    for i=1,#weights do 
        sum = sum + weights[i] 
    end

    cdf[1] = weights[1]/sum
    for i=2,#weights-1 do
        cdf[i] = weights[i]/sum
        cdf[i] = cdf[i] + cdf[i-1]
    end
    cdf[#weights] = 1.0

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
