-- ======================================================================================
-- File         : ease.lua
-- Author       : Wu Jie 
-- Last Change  : 11/02/2010 | 17:08:24 PM | Tuesday,November
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- modules
--/////////////////////////////////////////////////////////////////////////////

require("ex.math") 

local math = math
local ex_math = ex.math
local assert,type = assert,type
local pi,two_pi,half_pi = math.pi,ex.math.two_pi,ex.math.half_pi
local sin,cos,asin,acos,sqrt,min,max,abs = math.sin,math.cos,math.asin,math.acos,math.sqrt,math.min,math.max,math.abs
local os = os
local ex_time = ex.time

module(...)

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- linear
-- ------------------------------------------------------------------ 

function linear (_t) return _t end

-- ------------------------------------------------------------------ 
-- quad
--  Easing equation function for a quadratic (_t^2)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

function in_quad (_t) return _t^2 end
function out_quad (_t) return -_t * (_t - 2) end
function inout_quad (_t) 
    _t = _t * 2
    if ( _t < 1 ) then 
        return _t^2 / 2
    else
        _t = _t - 1
        return -0.5 * (_t*(_t-2) - 1)
    end
end
function outin_quad (_t) 
    if (_t < 0.5) then return out_quad(_t*2)/2 end
    return in_quad(2*_t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- cubic 
--  Easing equation function for a cubic (_t^3)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

function in_cubic (_t) return _t^3 end
function out_cubic (_t) _t = _t - 1; return _t^3 + 1 end 
function inout_cubic (_t) 
    _t = _t * 2
    if (_t < 1) then
        return _t^3 / 2
    else
        _t = _t - 2
        return (_t^3 + 2)/2
    end
end 
function outin_cubic (_t) 
    if ( _t < 0.5 ) then return out_cubic(2*_t)/2 end
    return in_cubic(2*_t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- quart 
--  Easing equation function for a quartic (_t^4)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

function in_quart (_t) return _t^4 end
function out_quart (_t) _t = _t - 1; return -(_t^4 - 1) end
function inout_quart (_t) 
    _t = _t * 2
    if (_t < 1) then 
        return _t^4 * 0.5
    else
        _t = _t - 2
        return (_t^4 - 2)/-2
    end
end
function outin_quart (_t) 
    if (_t < 0.5) then return out_quart(2*_t)/2 end
    return in_quart(2*_t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- quint
--  Easing equation function for a quintic (_t^5)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

function in_quint (_t) return _t^5 end
function out_quint (_t) _t = _t - 1; return _t^5 + 1 end
function inout_quint (_t)
    _t = _t * 2
    if (_t < 1) then 
        return _t^5 / 2
    else
        _t = _t - 2
        return (_t^5 + 2)/2
    end
end
function outin_quint (_t)
    if (_t < 0.5) then return out_quint (2*_t)/2 end
    return in_quint(2*_t - 1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- sine
--  Easing equation function for a sinusoidal (sin(_t))
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

function in_sine (_t) return (_t == 1) and 1 or -cos(_t * half_pi) + 1 end
function out_sine (_t) return sin(_t * half_pi) end
function inout_sine (_t) return (cos(pi*_t)-1)/-2 end
function outin_sine (_t) 
    if (_t < 0.5) then return out_sine (2*_t)/2 end
    return in_sine(2*_t - 1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- class expo 
--  Easing equation function for an exponential (2^_t)
--  param _t: Current time (in frames or seconds).
--  return: The correct value.
-- ------------------------------------------------------------------ 

function in_expo (_t) return (_t == 0 or _t == 1) and _t or 2^(10*(_t-1)) - 0.001 end
function out_expo (_t) return (_t == 1) and 1 or 1.001 * ( 1 - (2^(-10*_t)) ) end
function inout_expo (_t)
    if (_t==0) then return 0 end
    if (_t==1) then return 1 end
    _t = _t * 2
    if (_t < 1) then return 2^(10*(_t-1))/2 - 0.0005 end
    return 1.0005 * (2-2^(-10*(_t-1))) / 2
end
function outin_expo (_t)
    if (_t < 0.5) then return out_expo(2*_t)/2 end
    return in_expo(2*_t-1)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- circ 
--  Easing equation function for a circular (sqrt(1-_t^2))
--  @param _t: Current time (in frames or seconds).
--  @return:	The correct value.
-- ------------------------------------------------------------------ 

function in_circ (_t) return -(sqrt(1-_t^2) - 1) end
function out_circ (_t) _t = _t - 1; return sqrt(1-_t^2) end
function inout_circ (_t) 
    _t = _t * 2
    if ( _t < 1 ) then
        return -( sqrt(1-_t^2) - 1 )/2
    end
    _t = _t - 2
    return ( sqrt(1-_t^2) + 1 )/2
end
function outin_circ (_t)
    if (_t < 0.5) then 
        return out_circ(2*_t)/2 
    end
    return in_circ(2*_t - 1)/2 + 0.5
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

local function in_elastic_helper ( _t, _b, _c, _d, _a, _p )
    if (_t==0) then return _b end
    local t_adj = _t / _d
    if (t_adj==1) then return _b+_c end
    local s
    if ( _a < abs(_c) ) then 
        _a = _c
        s = _p / 4
    else
        s = _p / two_pi * asin(_c/_a)
    end
    t_adj = t_adj - 1
    return -(_a * 2^(10 * t_adj) * sin( two_pi * (t_adj*_d-s) / _p )) + _b
end
local function out_elastic_helper ( _t, _b --[[ dummy --]], _c, _d --[[ dummy --]], _a, _p )
    if (_t==0) then return 0 end
    if (_t==1) then return _c end
    local s
    if (_a < _c) then _a = _c; s = _p / 4
    else s = _p / two_pi * asin(_c/_a) end
    return _a * 2^(-10*_t) * sin( (_t-s) * two_pi / _p ) + _c
end

function in_elastic ( _t, _a, _p ) return in_elastic_helper ( _t, 0, 1, 1, _a, _p ) end
function out_elastic ( _t, _a, _p ) return out_elastic_helper ( _t, 0, 1, 1, _a, _p ) end
function inout_elastic ( _t, _a, _p ) 
    if (_t==0) then return 0 end
    _t = _t * 2
    if (_t==2) then return 1 end

    local s
    if (_a<1) then _a = 1; s = _p/4
    else s = _p / two_pi * asin(1/_a) end

    if (_t < 1) then
        return (_a * 2^(10*(_t-1)) * sin( (_t-1-s) * two_pi / _p ))/-2
    end
    return _a * 2^(-10*(_t-1)) * sin( (_t-1-s) * two_pi / _p ) / 2 + 1
end
function outin_elastic ( _t, _a, _p ) 
    if ( _t < 0.5 ) then return out_elastic_helper ( 2*_t, 0, 0.5, 1, _a, _p ) end
    return in_elastic_helper ( 2*_t - 1, 0.5, 0.5, 1, _a, _p )
end


-- ------------------------------------------------------------------ 
-- back 
--  Easing equation function for a back (overshooting cubic easing: (s+1)*_t^3 - s*_t^2)
--  @param _t: Current time (in frames or seconds).
--  @param s: Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

function in_back ( _t, _s ) return _t * _t * ( (_s+1) * _t - _s ) end
function out_back ( _t, _s ) _t = _t - 1; return _t * _t * ( (_s+1) * _t + _s ) + 1 end
function inout_back ( _t, _s ) 
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
function outin_back ( _t, _s ) 
    if ( _t < 0.5 ) then return out_back(2*_t,_s) / 2 end
    return in_back(2*_t - 1, _s)/2 + 0.5
end

-- ------------------------------------------------------------------ 
-- bounce 
--  Easing equation function for a bounce (exponentially decaying parabolic bounce)
--  @param _t: Current time (in frames or seconds).
--  @param a: Amplitude.
--  @return: The correct value.
-- ------------------------------------------------------------------ 

local function out_bounce_helper ( _t, _c, _a )
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

function out_bounce ( _t, _a ) return out_bounce_helper(_t, 1, _a) end
function in_bounce ( _t, _a ) return 1 - out_bounce_helper(1-_t, 1, _a) end
function inout_bounce ( _t, _a ) 
    if (_t < 0.5) then return in_bounce(2*_t,_a)/2; end
    return (_t == 1) and 1 or out_bounce(2*_t-1, _a)/2 + 0.5
end
function outin_bounce ( _t, _a ) 
    if (_t < 0.5) then return out_bounce_helper(_t*2, 0.5, _a) end
    return 1 - out_bounce_helper(2-2*_t, 0.5, _a)
end

-- ------------------------------------------------------------------ 
-- smooth 
-- _t<=0: 0 | 0<_t<1: 3*_t^2 - 2*t^3 | _t>=1: 1
-- ------------------------------------------------------------------ 

function smooth (_t)
    if ( _t <= 0 ) then return 0 end
    if ( _t >= 1 ) then return 1 end
    return _t*_t*(3 - 2*_t)
end

-- ------------------------------------------------------------------ 
-- fade 
-- _t<=0: 0 | 0<_t<1: 6*_t^5 - 15*_t^4 + 10*_t^3 | _t>=1: 1
-- ------------------------------------------------------------------ 

function fade (_t)
    if ( _t <= 0 ) then return 0 end
    if ( _t >= 1 ) then return 1 end
    return _t*_t*_t*(_t*(_t*6-15)+10)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function sin_progress (_v) return sin((_v * pi) - half_pi) / 2 + 0.5 end
local function smooth_begin_end_mix_factor (_v) return min(max(1 - _v * 2 + 0.3, 0), 1) end

-- SmoothBegin blends Smooth and Linear Interpolation.
-- Progress 0 - 0.3      : Smooth only
-- Progress 0.3 - ~ 0.5  : Mix of Smooth and Linear
-- Progress ~ 0.5  - 1   : Linear only

-- Easing function that starts growing slowly, then increases in speed. At the end of the curve the speed will be constant.
function in_curve (_t)
    local sinProgress = sin_progress(_t)
    local mix = smooth_begin_end_mix_factor(_t)
    return sinProgress * mix + _t * (1 - mix)
end

-- Easing function that starts growing steadily, then ends slowly. The speed will be constant at the beginning of the curve.
function out_curve (_t)
    local sinProgress = sin_progress(_t)
    local mix = smooth_begin_end_mix_factor(1 - _t)
    return sinProgress * mix + _t * (1 - mix)
end

-- Easing function where the value grows sinusoidally. Note that the calculated  end value will be 0 rather than 1.
function curve_sine (_t) 
    return (sin(((_t * two_pi)) - half_pi) + 1) / 2 
end

-- Easing function where the value grows cosinusoidally. Note that the calculated start value will be 0.5 and the end value will be 0.5
-- contrary to the usual 0 to 1 easing curve.
function curve_cosine (_t) 
    return (cos(((_t * two_pi)) - half_pi) + 1) / 2 
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function make_curve ( _from, _to, _duration, _curve )
    -- assert ( type(_from) == "number", "_from is not a number" )
    -- assert ( type(_to) == "number", "_to is not a number" )

    -- init startTime and curve
    local startTime = ex_time.time
    local curve = _curve or ex_ease.linear  

    -- create tick closure
    return function ()
        local curTime = ex_time.time
        local t = math.min( 1.0, (curTime - startTime) / _duration )
        local ratio = curve(t)
        return ex_math.lerp( _from, _to, ratio ), (t == 1.0) -- current value, finished
    end
end
