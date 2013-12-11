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

function math.linear (_t) return _t end

-- ------------------------------------------------------------------ 
-- quad
--  Easing equation function for a quadratic (_t^2)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.quadIn (_t) return _t^2 end

--
function math.quadOut (_t) return -_t * (_t - 2) end

--
function math.quadInOut (_t) 
    _t = _t * 2
    if ( _t < 1 ) then 
        return _t^2 / 2
    else
        _t = _t - 1
        return -0.5 * (_t*(_t-2) - 1)
    end
end

--
function math.quadOutIn (_t) 
    if (_t < 0.5) then return math.quadOut(_t*2)/2 end
    return math.quadIn(2*_t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- cubic 
--  Easing equation function for a cubic (_t^3)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.cubicIn (_t) return _t^3 end

--
function math.cubicOut (_t) _t = _t - 1; return _t^3 + 1 end 

--
function math.cubicInOut (_t) 
    _t = _t * 2
    if (_t < 1) then
        return _t^3 / 2
    else
        _t = _t - 2
        return (_t^3 + 2)/2
    end
end 

--
function math.cubicOutIn (_t) 
    if ( _t < 0.5 ) then return math.cubicOut(2*_t)/2 end
    return math.cubicIn(2*_t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- quart 
--  Easing equation function for a quartic (_t^4)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.quartIn (_t) return _t^4 end

--
function math.quartOut (_t) _t = _t - 1; return -(_t^4 - 1) end

--
function math.quartInOut (_t) 
    _t = _t * 2
    if (_t < 1) then 
        return _t^4 * 0.5
    else
        _t = _t - 2
        return (_t^4 - 2)/-2
    end
end

--
function math.quartOutIn (_t) 
    if (_t < 0.5) then return math.quartOut(2*_t)/2 end
    return math.quartIn(2*_t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- quint
--  Easing equation function for a quintic (_t^5)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.quintIn (_t) return _t^5 end

--
function math.quintOut (_t) _t = _t - 1; return _t^5 + 1 end

--
function math.quintInOut (_t)
    _t = _t * 2
    if (_t < 1) then 
        return _t^5 / 2
    else
        _t = _t - 2
        return (_t^5 + 2)/2
    end
end

--
function math.quintOutIn (_t)
    if (_t < 0.5) then return math.quintOut (2*_t)/2 end
    return math.quintIn(2*_t - 1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- sine
--  Easing equation function for a sinusoidal (sin(_t))
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.sineIn (_t) return (_t == 1) and 1 or -cos(_t * halfPI) + 1 end

--
function math.sineOut (_t) return sin(_t * halfPI) end

--
function math.sineInOut (_t) return (cos(pi*_t)-1)/-2 end

--
function math.sineOutIn (_t) 
    if (_t < 0.5) then return math.sineOut (2*_t)/2 end
    return math.sineIn(2*_t - 1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- class expo 
--  Easing equation function for an exponential (2^_t)
--  param _t: Current time (in frames or seconds).
--  return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.expoIn (_t) return (_t == 0 or _t == 1) and _t or 2^(10*(_t-1)) - 0.001 end

--
function math.expoOut (_t) return (_t == 1) and 1 or 1.001 * ( 1 - (2^(-10*_t)) ) end

--
function math.expoInOut (_t)
    if (_t==0) then return 0 end
    if (_t==1) then return 1 end
    _t = _t * 2
    if (_t < 1) then return 2^(10*(_t-1))/2 - 0.0005 end
    return 1.0005 * (2-2^(-10*(_t-1))) / 2
end

--
function math.expoOutIn (_t)
    if (_t < 0.5) then return math.expoOut(2*_t)/2 end
    return math.expoIn(2*_t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- circ 
--  Easing equation function for a circular (sqrt(1-_t^2))
--  @param _t: Current time (in frames or seconds).
--  @return:	The correct value.
-- ------------------------------------------------------------------ 

--
function math.circIn (_t) return -(sqrt(1-_t^2) - 1) end

--
function math.circOut (_t) _t = _t - 1; return sqrt(1-_t^2) end

--
function math.circInOut (_t) 
    _t = _t * 2
    if ( _t < 1 ) then
        return -( sqrt(1-_t^2) - 1 )/2
    end
    _t = _t - 2
    return ( sqrt(1-_t^2) + 1 )/2
end

--
function math.circOutIn (_t)
    if (_t < 0.5) then 
        return math.circOut(2*_t)/2 
    end
    return math.circIn(2*_t - 1)/2 + 0.5
end

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
function math.elasticIn ( _t, _a, _p ) return elasticInHelper ( _t, 0, 1, 1, _a, _p ) end

--
function math.elasticOut ( _t, _a, _p ) return elasticOutHelper ( _t, 0, 1, 1, _a, _p ) end

--
function math.elasticInOut ( _t, _a, _p ) 
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

--
function math.elasticOutIn ( _t, _a, _p ) 
    if ( _t < 0.5 ) then return elasticOutHelper ( 2*_t, 0, 0.5, 1, _a, _p ) end
    return elasticInHelper ( 2*_t - 1, 0.5, 0.5, 1, _a, _p )
end

-- ------------------------------------------------------------------ 
-- back 
--  Easing equation function for a back (overshooting cubic easing: (s+1)*_t^3 - s*_t^2)
--  @param _t: Current time (in frames or seconds).
--  @param s: Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
function math.backIn ( _t, _s ) return _t * _t * ( (_s+1) * _t - _s ) end

--
function math.backOut ( _t, _s ) _t = _t - 1; return _t * _t * ( (_s+1) * _t + _s ) + 1 end

--
function math.backInOut ( _t, _s ) 
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

--
function math.backOutIn ( _t, _s ) 
    if ( _t < 0.5 ) then return math.backOut(2*_t,_s) / 2 end
    return math.backIn(2*_t - 1, _s)/2 + 0.5
end

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
function math.bounceOut ( _t, _a ) return bounceOutHelper(_t, 1, _a) end

--
function math.bounceIn ( _t, _a ) return 1 - bounceOutHelper(1-_t, 1, _a) end

--
function math.bounceInOut ( _t, _a ) 
    if (_t < 0.5) then return math.bounceIn(2*_t,_a)/2; end
    return (_t == 1) and 1 or math.bounceOut(2*_t-1, _a)/2 + 0.5
end

--
function math.bounceOutIn ( _t, _a ) 
    if (_t < 0.5) then return bounceOutHelper(_t*2, 0.5, _a) end
    return 1 - bounceOutHelper(2-2*_t, 0.5, _a)
end

-- ------------------------------------------------------------------ 
-- smooth 
-- _t<=0: 0 | 0<_t<1: 3*_t^2 - 2*t^3 | _t>=1: 1
-- ------------------------------------------------------------------ 

function math.smooth (_t)
    if ( _t <= 0 ) then return 0 end
    if ( _t >= 1 ) then return 1 end
    return _t*_t*(3 - 2*_t)
end

-- ------------------------------------------------------------------ 
-- fade 
-- _t<=0: 0 | 0<_t<1: 6*_t^5 - 15*_t^4 + 10*_t^3 | _t>=1: 1
-- ------------------------------------------------------------------ 

function math.fade (_t)
    if ( _t <= 0 ) then return 0 end
    if ( _t >= 1 ) then return 1 end
    return _t*_t*_t*(_t*(_t*6-15)+10)
end

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
function math.curveIn (_t)
    local r = sinProgress(_t)
    local mix = smoothBeginEndMixFactor(_t)
    return r * mix + _t * (1 - mix)
end

-- Easing function that starts growing steadily, then ends slowly. The speed will be constant at the beginning of the curve.
function math.curveOut (_t)
    local r = sinProgress(_t)
    local mix = smoothBeginEndMixFactor(1 - _t)
    return r * mix + _t * (1 - mix)
end

-- Easing function where the value grows sinusoidally. Note that the calculated  end value will be 0 rather than 1.
function math.curveSine (_t) 
    return (sin(((_t * twoPI)) - halfPI) + 1) / 2 
end

-- Easing function where the value grows cosinusoidally. Note that the calculated start value will be 0.5 and the end value will be 0.5
-- contrary to the usual 0 to 1 easing curve.
function math.curveCosine (_t) 
    return (cos(((_t * twoPI)) - halfPI) + 1) / 2 
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function math.makecurve ( _from, _to, _duration, _curve )
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

