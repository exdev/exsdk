-- ======================================================================================
-- File         : ease.lua
-- Author       : Wu Jie 
-- Last Change  : 11/02/2010 | 17:08:24 PM | Tuesday,November
-- Description  : 
-- ======================================================================================

local __M = {}

local pi = math.pi
local twoPI = math.twoPI
local halfPI = math.halfPI
local sqrt = math.sqrt

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- linear
-- ------------------------------------------------------------------ 

local function linear (_t) return _t end
__M.linear = linear

-- ------------------------------------------------------------------ 
-- quad
--  Easing equation function for a quadratic (_t^2)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function quadIn (_t) return _t^2 end
__M.quadIn = quadIn

--
local function quadOut (_t) return -_t * (_t - 2) end
__M.quadOut = quadOut

--
local function quadInOut (_t) 
    _t = _t * 2
    if ( _t < 1 ) then 
        return _t^2 / 2
    else
        _t = _t - 1
        return -0.5 * (_t*(_t-2) - 1)
    end
end
__M.quadInOut = quadInOut

--
local function quadOutIn (_t) 
    if (_t < 0.5) then return quadOut(_t*2)/2 end
    return quadIn(2*_t-1)/2 + 0.5
end
__M.quadOutIn = quadOutIn

-- ------------------------------------------------------------------ 
-- cubic 
--  Easing equation function for a cubic (_t^3)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function cubicIn (_t) return _t^3 end
__M.cubicIn = cubicIn

--
local function cubicOut (_t) _t = _t - 1; return _t^3 + 1 end 
__M.cubicOut = cubicOut

--
local function cubicInOut (_t) 
    _t = _t * 2
    if (_t < 1) then
        return _t^3 / 2
    else
        _t = _t - 2
        return (_t^3 + 2)/2
    end
end 
__M.cubicInOut = cubicInOut

--
local function cubicOutIn (_t) 
    if ( _t < 0.5 ) then return cubicOut(2*_t)/2 end
    return cubicIn(2*_t-1)/2 + 0.5
end
__M.cubicInOut = cubicInOut

-- ------------------------------------------------------------------ 
-- quart 
--  Easing equation function for a quartic (_t^4)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function quartIn (_t) return _t^4 end
__M.quartIn = quartIn

--
local function quartOut (_t) _t = _t - 1; return -(_t^4 - 1) end
__M.quartOut = quartOut

--
local function quartInOut (_t) 
    _t = _t * 2
    if (_t < 1) then 
        return _t^4 * 0.5
    else
        _t = _t - 2
        return (_t^4 - 2)/-2
    end
end
__M.quartInOut = quartInOut

--
local function quartOutIn (_t) 
    if (_t < 0.5) then return quartOut(2*_t)/2 end
    return quartIn(2*_t-1)/2 + 0.5
end
__M.quartOutIn = quartOutIn

-- ------------------------------------------------------------------ 
-- quint
--  Easing equation function for a quintic (_t^5)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function quintIn (_t) return _t^5 end
__M.quintIn = quintIn

--
local function quintOut (_t) _t = _t - 1; return _t^5 + 1 end
__M.quintOut = quintOut

--
local function quintInOut (_t)
    _t = _t * 2
    if (_t < 1) then 
        return _t^5 / 2
    else
        _t = _t - 2
        return (_t^5 + 2)/2
    end
end
__M.quintInOut = quintInOut

--
local function quintOutIn (_t)
    if (_t < 0.5) then return quintOut (2*_t)/2 end
    return quintIn(2*_t - 1)/2 + 0.5
end
__M.quintOutIn = quintOutIn

-- ------------------------------------------------------------------ 
-- sine
--  Easing equation function for a sinusoidal (sin(_t))
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function sineIn (_t) return (_t == 1) and 1 or -cos(_t * halfPI) + 1 end
__M.sineIn = sineIn

--
local function sineOut (_t) return sin(_t * halfPI) end
__M.sineOut = sineOut

--
local function sineInOut (_t) return (cos(pi*_t)-1)/-2 end
__M.sineInOut = sineInOut

--
local function sineOutIn (_t) 
    if (_t < 0.5) then return sineOut (2*_t)/2 end
    return sineIn(2*_t - 1)/2 + 0.5
end
__M.sineOutIn = sineOutIn

-- ------------------------------------------------------------------ 
-- class expo 
--  Easing equation function for an exponential (2^_t)
--  param _t: Current time (in frames or seconds).
--  return: The correct value.
-- ------------------------------------------------------------------ 

--
local function expoIn (_t) return (_t == 0 or _t == 1) and _t or 2^(10*(_t-1)) - 0.001 end
__M.expoIn = expoIn

--
local function expoOut (_t) return (_t == 1) and 1 or 1.001 * ( 1 - (2^(-10*_t)) ) end
__M.expoOut = expoOut

--
local function expoInOut (_t)
    if (_t==0) then return 0 end
    if (_t==1) then return 1 end
    _t = _t * 2
    if (_t < 1) then return 2^(10*(_t-1))/2 - 0.0005 end
    return 1.0005 * (2-2^(-10*(_t-1))) / 2
end
__M.expoInOut = expoInOut

--
local function expoOutIn (_t)
    if (_t < 0.5) then return expoOut(2*_t)/2 end
    return expoIn(2*_t-1)/2 + 0.5
end
__M.expoOutIn = expoOutIn

-- ------------------------------------------------------------------ 
-- circ 
--  Easing equation function for a circular (sqrt(1-_t^2))
--  @param _t: Current time (in frames or seconds).
--  @return:	The correct value.
-- ------------------------------------------------------------------ 

--
local function circIn (_t) return -(sqrt(1-_t^2) - 1) end
__M.circIn = circIn

--
local function circOut (_t) _t = _t - 1; return sqrt(1-_t^2) end
__M.circOut = circOut

--
local function circInOut (_t) 
    _t = _t * 2
    if ( _t < 1 ) then
        return -( sqrt(1-_t^2) - 1 )/2
    end
    _t = _t - 2
    return ( sqrt(1-_t^2) + 1 )/2
end
__M.circInOut = circInOut

--
local function circOutIn (_t)
    if (_t < 0.5) then 
        return circOut(2*_t)/2 
    end
    return circIn(2*_t - 1)/2 + 0.5
end
__M.circOutIn = circOutIn

-- ------------------------------------------------------------------ 
-- elastic 
--  Easing equation function for an elastic (exponentially decaying sine wave)
--  @param _t: Current time (in frames or seconds).
--  @param a: Amplitude.
--  @param p: Period.
--  @return: The correct value.
--  recommand value: elastic (t, 0.1, 0.05)
-- ------------------------------------------------------------------ 

local function elasticInHelper ( _t, _b, _c, _d, _a, _p )
    if (_t==0) then return _b end
    local t_adj = _t / _d
    if (t_adj==1) then return _b+_c end
    local s
    if ( _a < abs(_c) ) then 
        _a = _c
        s = _p / 4
    else
        s = _p / twoPI * asin(_c/_a)
    end
    t_adj = t_adj - 1
    return -(_a * 2^(10 * t_adj) * sin( twoPI * (t_adj*_d-s) / _p )) + _b
end
local function elasticOutHelper ( _t, _b --[[ dummy --]], _c, _d --[[ dummy --]], _a, _p )
    if (_t==0) then return 0 end
    if (_t==1) then return _c end
    local s
    if (_a < _c) then _a = _c; s = _p / 4
    else s = _p / twoPI * asin(_c/_a) end
    return _a * 2^(-10*_t) * sin( (_t-s) * twoPI / _p ) + _c
end

--
local function elasticIn ( _t, _a, _p ) return elasticInHelper ( _t, 0, 1, 1, _a, _p ) end
__M.elasticIn = elasticIn

--
local function elasticOut ( _t, _a, _p ) return elasticOutHelper ( _t, 0, 1, 1, _a, _p ) end
__M.elasticOut = elasticOut

--
local function elasticInOut ( _t, _a, _p ) 
    if (_t==0) then return 0 end
    _t = _t * 2
    if (_t==2) then return 1 end

    local s
    if (_a<1) then _a = 1; s = _p/4
    else s = _p / twoPI * asin(1/_a) end

    if (_t < 1) then
        return (_a * 2^(10*(_t-1)) * sin( (_t-1-s) * twoPI / _p ))/-2
    end
    return _a * 2^(-10*(_t-1)) * sin( (_t-1-s) * twoPI / _p ) / 2 + 1
end
__M.elasticInOut = elasticInOut

--
local function elasticOutIn ( _t, _a, _p ) 
    if ( _t < 0.5 ) then return elasticOutHelper ( 2*_t, 0, 0.5, 1, _a, _p ) end
    return elasticInHelper ( 2*_t - 1, 0.5, 0.5, 1, _a, _p )
end
__M.elasticOutIn = elasticOutIn

-- ------------------------------------------------------------------ 
-- back 
--  Easing equation function for a back (overshooting cubic easing: (s+1)*_t^3 - s*_t^2)
--  @param _t: Current time (in frames or seconds).
--  @param s: Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function backIn ( _t, _s ) return _t * _t * ( (_s+1) * _t - _s ) end
__M.backIn = backIn

--
local function backOut ( _t, _s ) _t = _t - 1; return _t * _t * ( (_s+1) * _t + _s ) + 1 end
__M.backOut = backOut

--
local function backInOut ( _t, _s ) 
    _t = _t * 2
    if ( _t < 1 ) then
        _s = _s * 1.525
        return 0.5 * ( _t * _t * ( (_s+1) * _t - _s ) )
    else
        _t = _t - 2
        _s = _s * 1.525
        return 0.5 * ( _t * _t * ( (_s+1) * _t + _s ) + 2 )
    end
end
__M.backInOut = backInOut

--
local function backOutIn ( _t, _s ) 
    if ( _t < 0.5 ) then return backOut(2*_t,_s) / 2 end
    return backIn(2*_t - 1, _s)/2 + 0.5
end
__M.backOutIn = backOutIn

-- ------------------------------------------------------------------ 
-- bounce 
--  Easing equation function for a bounce (exponentially decaying parabolic bounce)
--  @param _t: Current time (in frames or seconds).
--  @param a: Amplitude.
--  @return: The correct value.
-- ------------------------------------------------------------------ 

local function bounceOutHelper ( _t, _c, _a )
    if (_t == 1) then return _c end
    if ( _t < (4/11) ) then
        return _c * ( 7.5625 * _t * _t )
    elseif ( _t < 8/11 ) then
        _t = _t - (6/11)
        return -_a * (1 - (7.5625*_t*_t + 0.75)) + _c
    elseif (_t < 10/11) then
        _t = _t - 9/11
        return -_a * (1 - (7.5625*_t*_t + 0.9375)) + _c
    else
        _t = _t - 21/22
        return -_a * (1 - (7.5625*_t*_t + 0.984375)) + _c
    end
end

--
local function bounceOut ( _t, _a ) return bounceOutHelper(_t, 1, _a) end
__M.bounceOut = bounceOut

--
local function bounceIn ( _t, _a ) return 1 - bounceOutHelper(1-_t, 1, _a) end
__M.bounceIn = bounceIn

--
local function bounceInOut ( _t, _a ) 
    if (_t < 0.5) then return bounceIn(2*_t,_a)/2; end
    return (_t == 1) and 1 or bounceOut(2*_t-1, _a)/2 + 0.5
end
__M.bounceInOut = bounceInOut

--
local function bounceOutIn ( _t, _a ) 
    if (_t < 0.5) then return bounceOutHelper(_t*2, 0.5, _a) end
    return 1 - bounceOutHelper(2-2*_t, 0.5, _a)
end
__M.bounceOutIn = bounceOutIn

-- ------------------------------------------------------------------ 
-- smooth 
-- _t<=0: 0 | 0<_t<1: 3*_t^2 - 2*t^3 | _t>=1: 1
-- ------------------------------------------------------------------ 

local function smooth (_t)
    if ( _t <= 0 ) then return 0 end
    if ( _t >= 1 ) then return 1 end
    return _t*_t*(3 - 2*_t)
end
__M.smooth = smooth

-- ------------------------------------------------------------------ 
-- fade 
-- _t<=0: 0 | 0<_t<1: 6*_t^5 - 15*_t^4 + 10*_t^3 | _t>=1: 1
-- ------------------------------------------------------------------ 

local function fade (_t)
    if ( _t <= 0 ) then return 0 end
    if ( _t >= 1 ) then return 1 end
    return _t*_t*_t*(_t*(_t*6-15)+10)
end
__M.fade = fade

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function sinProgress (_v) return sin((_v * pi) - halfPI) / 2 + 0.5 end
local function smoothBeginEndMixFactor (_v) return min(max(1 - _v * 2 + 0.3, 0), 1) end

-- SmoothBegin blends Smooth and Linear Interpolation.
-- Progress 0 - 0.3      : Smooth only
-- Progress 0.3 - ~ 0.5  : Mix of Smooth and Linear
-- Progress ~ 0.5  - 1   : Linear only

-- Easing function that starts growing slowly, then increases in speed. At the end of the curve the speed will be constant.
local function curveIn (_t)
    local r = sinProgress(_t)
    local mix = smoothBeginEndMixFactor(_t)
    return r * mix + _t * (1 - mix)
end
__M.curveIn = curveIn

-- Easing function that starts growing steadily, then ends slowly. The speed will be constant at the beginning of the curve.
local function curveOut (_t)
    local r = sinProgress(_t)
    local mix = smoothBeginEndMixFactor(1 - _t)
    return r * mix + _t * (1 - mix)
end
__M.curveOut = curveOut

-- Easing function where the value grows sinusoidally. Note that the calculated  end value will be 0 rather than 1.
local function curveSine (_t) 
    return (sin(((_t * twoPI)) - halfPI) + 1) / 2 
end
__M.curveSine = curveSine

-- Easing function where the value grows cosinusoidally. Note that the calculated start value will be 0.5 and the end value will be 0.5
-- contrary to the usual 0 to 1 easing curve.
local function curveCosine (_t) 
    return (cos(((_t * twoPI)) - halfPI) + 1) / 2 
end
__M.curveCosine = curveCosine

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function makecurve ( _from, _to, _duration, _curve )
    -- assert ( type(_from) == "number", "_from is not a number" )
    -- assert ( type(_to) == "number", "_to is not a number" )

    -- init startTime and curve
    local startTime = ex_c.time.time
    local curve = _curve or ex_ease.linear  

    -- create tick closure
    return function ()
        local curTime = ex_c.time.time
        local t = math.min( 1.0, (curTime - startTime) / _duration )
        local ratio = curve(t)
        return lerp( _from, _to, ratio ), (t == 1.0) -- current value, finished
    end
end
__M.makecurve = makecurve

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
