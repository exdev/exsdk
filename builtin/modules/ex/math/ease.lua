-- ======================================================================================
-- File         : ease.lua
-- Author       : Wu Jie 
-- Last Change  : 11/02/2010 | 17:08:24 PM | Tuesday,November
-- Description  : 
-- ======================================================================================

local __M = {}
local pi, two_pi, half_pi = math.pi, ex.two_pi, ex.half_pi
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
local function quad_in (_t) return _t^2 end
__M.quad_in = quad_in

--
local function quad_out (_t) return -_t * (_t - 2) end
__M.quad_out = quad_out

--
local function quad_inout (_t) 
    _t = _t * 2
    if ( _t < 1 ) then 
        return _t^2 / 2
    else
        _t = _t - 1
        return -0.5 * (_t*(_t-2) - 1)
    end
end
__M.quad_inout = quad_inout

--
local function quad_outin (_t) 
    if (_t < 0.5) then return quad_out(_t*2)/2 end
    return quad_in(2*_t-1)/2 + 0.5
end
__M.quad_outin = quad_outin

-- ------------------------------------------------------------------ 
-- cubic 
--  Easing equation function for a cubic (_t^3)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function cubic_in (_t) return _t^3 end
__M.cubic_in = cubic_in

--
local function cubic_out (_t) _t = _t - 1; return _t^3 + 1 end 
__M.cubic_out = cubic_out

--
local function cubic_inout (_t) 
    _t = _t * 2
    if (_t < 1) then
        return _t^3 / 2
    else
        _t = _t - 2
        return (_t^3 + 2)/2
    end
end 
__M.cubic_inout = cubic_inout

--
local function cubic_outin (_t) 
    if ( _t < 0.5 ) then return cubic_out(2*_t)/2 end
    return cubic_in(2*_t-1)/2 + 0.5
end
__M.cubic_outin = cubic_outin

-- ------------------------------------------------------------------ 
-- quart 
--  Easing equation function for a quartic (_t^4)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function quart_in (_t) return _t^4 end
__M.quart_in = quart_in

--
local function quart_out (_t) _t = _t - 1; return -(_t^4 - 1) end
__M.quart_out = quart_out

--
local function quart_inout (_t) 
    _t = _t * 2
    if (_t < 1) then 
        return _t^4 * 0.5
    else
        _t = _t - 2
        return (_t^4 - 2)/-2
    end
end
__M.quart_inout = quart_inout

--
local function quart_outin (_t) 
    if (_t < 0.5) then return quart_out(2*_t)/2 end
    return quart_in(2*_t-1)/2 + 0.5
end
__M.quart_outin = quart_outin

-- ------------------------------------------------------------------ 
-- quint
--  Easing equation function for a quintic (_t^5)
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function quint_in (_t) return _t^5 end
__M.quint_in = quint_in

--
local function quint_out (_t) _t = _t - 1; return _t^5 + 1 end
__M.quint_out = quint_out

--
local function quint_inout (_t)
    _t = _t * 2
    if (_t < 1) then 
        return _t^5 / 2
    else
        _t = _t - 2
        return (_t^5 + 2)/2
    end
end
__M.quint_inout = quint_inout

--
local function quint_outin (_t)
    if (_t < 0.5) then return quint_out (2*_t)/2 end
    return quint_in(2*_t - 1)/2 + 0.5
end
__M.quint_outin = quint_outin

-- ------------------------------------------------------------------ 
-- sine
--  Easing equation function for a sinusoidal (sin(_t))
--  @param _t: Current time (in frames or seconds).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function sine_in (_t) return (_t == 1) and 1 or -cos(_t * half_pi) + 1 end
__M.sine_in = sine_in

--
local function sine_out (_t) return sin(_t * half_pi) end
__M.sine_out = sine_out

--
local function sine_inout (_t) return (cos(pi*_t)-1)/-2 end
__M.sine_inout = sine_inout

--
local function sine_outin (_t) 
    if (_t < 0.5) then return sine_out (2*_t)/2 end
    return sine_in(2*_t - 1)/2 + 0.5
end
__M.sine_outin = sine_outin

-- ------------------------------------------------------------------ 
-- class expo 
--  Easing equation function for an exponential (2^_t)
--  param _t: Current time (in frames or seconds).
--  return: The correct value.
-- ------------------------------------------------------------------ 

--
local function expo_in (_t) return (_t == 0 or _t == 1) and _t or 2^(10*(_t-1)) - 0.001 end
__M.expo_in = expo_in

--
local function expo_out (_t) return (_t == 1) and 1 or 1.001 * ( 1 - (2^(-10*_t)) ) end
__M.expo_out = expo_out

--
local function expo_inout (_t)
    if (_t==0) then return 0 end
    if (_t==1) then return 1 end
    _t = _t * 2
    if (_t < 1) then return 2^(10*(_t-1))/2 - 0.0005 end
    return 1.0005 * (2-2^(-10*(_t-1))) / 2
end
__M.expo_inout = expo_inout

--
local function expo_outin (_t)
    if (_t < 0.5) then return expo_out(2*_t)/2 end
    return expo_in(2*_t-1)/2 + 0.5
end
__M.expo_outin = expo_outin

-- ------------------------------------------------------------------ 
-- circ 
--  Easing equation function for a circular (sqrt(1-_t^2))
--  @param _t: Current time (in frames or seconds).
--  @return:	The correct value.
-- ------------------------------------------------------------------ 

--
local function circ_in (_t) return -(sqrt(1-_t^2) - 1) end
__M.circ_in = circ_in

--
local function circ_out (_t) _t = _t - 1; return sqrt(1-_t^2) end
__M.circ_out = circ_out

--
local function circ_inout (_t) 
    _t = _t * 2
    if ( _t < 1 ) then
        return -( sqrt(1-_t^2) - 1 )/2
    end
    _t = _t - 2
    return ( sqrt(1-_t^2) + 1 )/2
end
__M.circ_inout = circ_inout

--
local function circ_outin (_t)
    if (_t < 0.5) then 
        return circ_out(2*_t)/2 
    end
    return circ_in(2*_t - 1)/2 + 0.5
end
__M.circ_outin = circ_outin

-- ------------------------------------------------------------------ 
-- elastic 
--  Easing equation function for an elastic (exponentially decaying sine wave)
--  @param _t: Current time (in frames or seconds).
--  @param a: Amplitude.
--  @param p: Period.
--  @return: The correct value.
--  recommand value: elastic (t, 0.1, 0.05)
-- ------------------------------------------------------------------ 

local function elastic_in_helper ( _t, _b, _c, _d, _a, _p )
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
local function elastic_out_helper ( _t, _b --[[ dummy --]], _c, _d --[[ dummy --]], _a, _p )
    if (_t==0) then return 0 end
    if (_t==1) then return _c end
    local s
    if (_a < _c) then _a = _c; s = _p / 4
    else s = _p / two_pi * asin(_c/_a) end
    return _a * 2^(-10*_t) * sin( (_t-s) * two_pi / _p ) + _c
end

--
local function elastic_in ( _t, _a, _p ) return elastic_in_helper ( _t, 0, 1, 1, _a, _p ) end
__M.elastic_in = elastic_in

--
local function elastic_out ( _t, _a, _p ) return elastic_out_helper ( _t, 0, 1, 1, _a, _p ) end
__M.elastic_out = elastic_out

--
local function elastic_inout ( _t, _a, _p ) 
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
__M.elastic_inout = elastic_inout

--
local function elastic_outin ( _t, _a, _p ) 
    if ( _t < 0.5 ) then return elastic_out_helper ( 2*_t, 0, 0.5, 1, _a, _p ) end
    return elastic_in_helper ( 2*_t - 1, 0.5, 0.5, 1, _a, _p )
end
__M.elastic_outin = elastic_outin

-- ------------------------------------------------------------------ 
-- back 
--  Easing equation function for a back (overshooting cubic easing: (s+1)*_t^3 - s*_t^2)
--  @param _t: Current time (in frames or seconds).
--  @param s: Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
--  @return: The correct value.
-- ------------------------------------------------------------------ 

--
local function back_in ( _t, _s ) return _t * _t * ( (_s+1) * _t - _s ) end
__M.back_in = back_in

--
local function back_out ( _t, _s ) _t = _t - 1; return _t * _t * ( (_s+1) * _t + _s ) + 1 end
__M.back_out = back_out

--
local function back_inout ( _t, _s ) 
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
__M.back_inout = back_inout

--
local function back_outin ( _t, _s ) 
    if ( _t < 0.5 ) then return back_out(2*_t,_s) / 2 end
    return back_in(2*_t - 1, _s)/2 + 0.5
end
__M.back_outin = back_outin

-- ------------------------------------------------------------------ 
-- bounce 
--  Easing equation function for a bounce (exponentially decaying parabolic bounce)
--  @param _t: Current time (in frames or seconds).
--  @param a: Amplitude.
--  @return: The correct value.
-- ------------------------------------------------------------------ 

local function bounce_out_helper ( _t, _c, _a )
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
local function bounce_out ( _t, _a ) return bounce_out_helper(_t, 1, _a) end
__M.bounce_out = bounce_out

--
local function bounce_in ( _t, _a ) return 1 - bounce_out_helper(1-_t, 1, _a) end
__M.bounce_in = bounce_in

--
local function bounce_inout ( _t, _a ) 
    if (_t < 0.5) then return bounce_in(2*_t,_a)/2; end
    return (_t == 1) and 1 or bounce_out(2*_t-1, _a)/2 + 0.5
end
__M.bounce_inout = bounce_inout

--
local function bounce_outin ( _t, _a ) 
    if (_t < 0.5) then return bounce_out_helper(_t*2, 0.5, _a) end
    return 1 - bounce_out_helper(2-2*_t, 0.5, _a)
end
__M.bounce_outin = bounce_outin

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

local function sin_progress (_v) return sin((_v * pi) - half_pi) / 2 + 0.5 end
local function smooth_begin_end_mix_factor (_v) return min(max(1 - _v * 2 + 0.3, 0), 1) end

-- SmoothBegin blends Smooth and Linear Interpolation.
-- Progress 0 - 0.3      : Smooth only
-- Progress 0.3 - ~ 0.5  : Mix of Smooth and Linear
-- Progress ~ 0.5  - 1   : Linear only

-- Easing function that starts growing slowly, then increases in speed. At the end of the curve the speed will be constant.
local function curve_in (_t)
    local sinProgress = sin_progress(_t)
    local mix = smooth_begin_end_mix_factor(_t)
    return sinProgress * mix + _t * (1 - mix)
end
__M.curve_in = curve_in

-- Easing function that starts growing steadily, then ends slowly. The speed will be constant at the beginning of the curve.
local function curve_out (_t)
    local sinProgress = sin_progress(_t)
    local mix = smooth_begin_end_mix_factor(1 - _t)
    return sinProgress * mix + _t * (1 - mix)
end
__M.curve_out = curve_out

-- Easing function where the value grows sinusoidally. Note that the calculated  end value will be 0 rather than 1.
local function curve_sine (_t) 
    return (sin(((_t * two_pi)) - half_pi) + 1) / 2 
end
__M.curve_sine = curve_sine

-- Easing function where the value grows cosinusoidally. Note that the calculated start value will be 0.5 and the end value will be 0.5
-- contrary to the usual 0 to 1 easing curve.
local function curve_cosine (_t) 
    return (cos(((_t * two_pi)) - half_pi) + 1) / 2 
end
__M.curve_cosine = curve_cosine

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function make_curve ( _from, _to, _duration, _curve )
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
        return lerp( _from, _to, ratio ), (t == 1.0) -- current value, finished
    end
end
__M.make_curve = make_curve

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
