-- ======================================================================================
-- File         : ease.lua
-- Author       : Wu Jie 
-- Last Change  : 11/02/2010 | 17:08:24 PM | Tuesday,November
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- properties
--/////////////////////////////////////////////////////////////////////////////

local pi = math.pi
local twoPI = math.twoPI
local halfPI = math.halfPI
local sqrt = math.sqrt
local sin = math.sin
local cos = math.cos
local asin = math.asin
local acos = math.acos

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- linear
-- ------------------------------------------------------------------ 

function math.linear (t) return t end

-- ------------------------------------------------------------------ 
-- quad
--  Easing equation function for a quadratic (t^2)
--  @param t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.quadIn (t) return t^2 end

--
function math.quadOut (t) return -t * (t - 2) end

--
function math.quadInOut (t) 
    t = t * 2
    if ( t < 1 ) then 
        return t^2 / 2
    else
        t = t - 1
        return -0.5 * (t*(t-2) - 1)
    end
end

--
function math.quadOutIn (t) 
    if (t < 0.5) then return math.quadOut(t*2)/2 end
    return math.quadIn(2*t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- cubic 
--  Easing equation function for a cubic (t^3)
--  @param t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.cubicIn (t) return t^3 end

--
function math.cubicOut (t) t = t - 1; return t^3 + 1 end 

--
function math.cubicInOut (t) 
    t = t * 2
    if (t < 1) then
        return t^3 / 2
    else
        t = t - 2
        return (t^3 + 2)/2
    end
end 

--
function math.cubicOutIn (t) 
    if ( t < 0.5 ) then return math.cubicOut(2*t)/2 end
    return math.cubicIn(2*t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- quart 
--  Easing equation function for a quartic (t^4)
--  @param t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.quartIn (t) return t^4 end

--
function math.quartOut (t) t = t - 1; return -(t^4 - 1) end

--
function math.quartInOut (t) 
    t = t * 2
    if (t < 1) then 
        return t^4 * 0.5
    else
        t = t - 2
        return (t^4 - 2)/-2
    end
end

--
function math.quartOutIn (t) 
    if (t < 0.5) then return math.quartOut(2*t)/2 end
    return math.quartIn(2*t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- quint
--  Easing equation function for a quintic (t^5)
--  @param t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.quintIn (t) return t^5 end

--
function math.quintOut (t) t = t - 1; return t^5 + 1 end

--
function math.quintInOut (t)
    t = t * 2
    if (t < 1) then 
        return t^5 / 2
    else
        t = t - 2
        return (t^5 + 2)/2
    end
end

--
function math.quintOutIn (t)
    if (t < 0.5) then return math.quintOut (2*t)/2 end
    return math.quintIn(2*t - 1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- sine
--  Easing equation function for a sinusoidal (sin(t))
--  @param t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.sineIn (t) return (t == 1) and 1 or -cos(t * halfPI) + 1 end

--
function math.sineOut (t) return sin(t * halfPI) end

--
function math.sineInOut (t) return (cos(pi*t)-1)/-2 end

--
function math.sineOutIn (t) 
    if (t < 0.5) then return math.sineOut (2*t)/2 end
    return math.sineIn(2*t - 1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- class expo 
--  Easing equation function for an exponential (2^t)
--  param t: Current time (in frames or seconds).
--  return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.expoIn (t) return (t == 0 or t == 1) and t or 2^(10*(t-1)) - 0.001 end

--
function math.expoOut (t) return (t == 1) and 1 or 1.001 * ( 1 - (2^(-10*t)) ) end

--
function math.expoInOut (t)
    if (t==0) then return 0 end
    if (t==1) then return 1 end
    t = t * 2
    if (t < 1) then return 2^(10*(t-1))/2 - 0.0005 end
    return 1.0005 * (2-2^(-10*(t-1))) / 2
end

--
function math.expoOutIn (t)
    if (t < 0.5) then return math.expoOut(2*t)/2 end
    return math.expoIn(2*t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- circ 
--  Easing equation function for a circular (sqrt(1-t^2))
--  @param t: Current time (in frames or seconds).
--  @return:	The correct value.
-- ------------------------------------------------------------------ 

--
function math.circIn (t) return -(sqrt(1-t^2) - 1) end

--
function math.circOut (t) t = t - 1; return sqrt(1-t^2) end

--
function math.circInOut (t) 
    t = t * 2
    if ( t < 1 ) then
        return -( sqrt(1-t^2) - 1 )/2
    end
    t = t - 2
    return ( sqrt(1-t^2) + 1 )/2
end

--
function math.circOutIn (t)
    if (t < 0.5) then 
        return math.circOut(2*t)/2 
    end
    return math.circIn(2*t - 1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- elastic 
--  Easing equation function for an elastic (exponentially decaying sine wave)
--  @param t: Current time (in frames or seconds).
--  @param a: Amplitude.
--  @param p: Period.
--  @return: The correct value.
--  recommand value: elastic (t, 0.1, 0.05)
-- ------------------------------------------------------------------ 

local function elasticInHelper ( t, b, c, d, a, p )
    if (t==0) then return b end
    local t_adj = t / d
    if (t_adj==1) then return b+c end
    local s
    if ( a < abs(c) ) then 
        a = c
        s = p / 4
    else
        s = p / twoPI * asin(c/a)
    end
    t_adj = t_adj - 1
    return -(a * 2^(10 * t_adj) * sin( twoPI * (t_adj*d-s) / p )) + b
end
local function elasticOutHelper ( t, b --[[ dummy --]], c, d --[[ dummy --]], a, p )
    if (t==0) then return 0 end
    if (t==1) then return c end
    local s
    if (a < c) then a = c; s = p / 4
    else s = p / twoPI * asin(c/a) end
    return a * 2^(-10*t) * sin( (t-s) * twoPI / p ) + c
end

--
function math.elasticIn ( t, a, p ) return elasticInHelper ( t, 0, 1, 1, a, p ) end

--
function math.elasticOut ( t, a, p ) return elasticOutHelper ( t, 0, 1, 1, a, p ) end

--
function math.elasticInOut ( t, a, p ) 
    if (t==0) then return 0 end
    t = t * 2
    if (t==2) then return 1 end

    local s
    if (a<1) then a = 1; s = p/4
    else s = p / twoPI * asin(1/a) end

    if (t < 1) then
        return (a * 2^(10*(t-1)) * sin( (t-1-s) * twoPI / p ))/-2
    end
    return a * 2^(-10*(t-1)) * sin( (t-1-s) * twoPI / p ) / 2 + 1
end

--
function math.elasticOutIn ( t, a, p ) 
    if ( t < 0.5 ) then return elasticOutHelper ( 2*t, 0, 0.5, 1, a, p ) end
    return elasticInHelper ( 2*t - 1, 0.5, 0.5, 1, a, p )
end

-- ------------------------------------------------------------------ 
-- back 
--  Easing equation function for a back (overshooting cubic easing: (s+1)*t^3 - s*t^2)
--  @param t: Current time (in frames or seconds).
--  @param s: Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.backIn ( t, s ) return t * t * ( (s+1) * t - s ) end

--
function math.backOut ( t, s ) t = t - 1; return t * t * ( (s+1) * t + s ) + 1 end

--
function math.backInOut ( t, s ) 
    t = t * 2
    if ( t < 1 ) then
        s = s * 1.525
        return 0.5 * ( t * t * ( (s+1) * t - s ) )
    else
        t = t - 2
        s = s * 1.525
        return 0.5 * ( t * t * ( (s+1) * t + s ) + 2 )
    end
end

--
function math.backOutIn ( t, s ) 
    if ( t < 0.5 ) then return math.backOut(2*t,s) / 2 end
    return math.backIn(2*t - 1, s)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- bounce 
--  Easing equation function for a bounce (exponentially decaying parabolic bounce)
--  @param t: Current time (in frames or seconds).
--  @param a: Amplitude.
--  @return: The correct value.
-- ------------------------------------------------------------------ 

local function bounceOutHelper ( t, c, a )
    if (t == 1) then return c end
    if ( t < (4/11) ) then
        return c * ( 7.5625 * t * t )
    elseif ( t < 8/11 ) then
        t = t - (6/11)
        return -a * (1 - (7.5625*t*t + 0.75)) + c
    elseif (t < 10/11) then
        t = t - 9/11
        return -a * (1 - (7.5625*t*t + 0.9375)) + c
    else
        t = t - 21/22
        return -a * (1 - (7.5625*t*t + 0.984375)) + c
    end
end

--
function math.bounceOut ( t, a ) return bounceOutHelper(t, 1, a) end

--
function math.bounceIn ( t, a ) return 1 - bounceOutHelper(1-t, 1, a) end

--
function math.bounceInOut ( t, a ) 
    if (t < 0.5) then return math.bounceIn(2*t,a)/2; end
    return (t == 1) and 1 or math.bounceOut(2*t-1, a)/2 + 0.5
end

--
function math.bounceOutIn ( t, a ) 
    if (t < 0.5) then return bounceOutHelper(t*2, 0.5, a) end
    return 1 - bounceOutHelper(2-2*t, 0.5, a)
end

-- ------------------------------------------------------------------ 
-- smooth 
-- t<=0: 0 | 0<t<1: 3*t^2 - 2*t^3 | t>=1: 1
-- ------------------------------------------------------------------ 

function math.smooth (t)
    if ( t <= 0 ) then return 0 end
    if ( t >= 1 ) then return 1 end
    return t*t*(3 - 2*t)
end

-- ------------------------------------------------------------------ 
-- fade 
-- t<=0: 0 | 0<t<1: 6*t^5 - 15*t^4 + 10*t^3 | t>=1: 1
-- ------------------------------------------------------------------ 

function math.fade (t)
    if ( t <= 0 ) then return 0 end
    if ( t >= 1 ) then return 1 end
    return t*t*t*(t*(t*6-15)+10)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function sinProgress (v) return sin((v * pi) - halfPI) / 2 + 0.5 end
local function smoothBeginEndMixFactor (v) return min(max(1 - v * 2 + 0.3, 0), 1) end

-- SmoothBegin blends Smooth and Linear Interpolation.
-- Progress 0 - 0.3      : Smooth only
-- Progress 0.3 - ~ 0.5  : Mix of Smooth and Linear
-- Progress ~ 0.5  - 1   : Linear only

-- Easing function that starts growing slowly, then increases in speed. At the end of the curve the speed will be constant.
function math.curveIn (t)
    local r = sinProgress(t)
    local mix = smoothBeginEndMixFactor(t)
    return r * mix + t * (1 - mix)
end

-- Easing function that starts growing steadily, then ends slowly. The speed will be constant at the beginning of the curve.
function math.curveOut (t)
    local r = sinProgress(t)
    local mix = smoothBeginEndMixFactor(1 - t)
    return r * mix + t * (1 - mix)
end

-- Easing function where the value grows sinusoidally. Note that the calculated  end value will be 0 rather than 1.
function math.curveSine (t) 
    return (sin(((t * twoPI)) - halfPI) + 1) / 2 
end

-- Easing function where the value grows cosinusoidally. Note that the calculated start value will be 0.5 and the end value will be 0.5
-- contrary to the usual 0 to 1 easing curve.
function math.curveCosine (t) 
    return (cos(((t * twoPI)) - halfPI) + 1) / 2 
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function math.makecurve ( from, to, duration, curve )
    -- assert ( type(from) == "number", "from is not a number" )
    -- assert ( type(to) == "number", "to is not a number" )

    -- init startTime and curve
    local startTime = ex_c.time.time
    local curve = curve or ex_ease.linear  

    -- create tick closure
    return function ()
        local curTime = ex_c.time.time
        local t = math.min( 1.0, (curTime - startTime) / duration )
        local ratio = curve(t)
        return lerp( from, to, ratio ), (t == 1.0) -- current value, finished
    end
end

