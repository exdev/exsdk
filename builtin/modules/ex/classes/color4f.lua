-- ======================================================================================
-- File         : color4f.lua
-- Author       : Wu Jie 
-- Last Change  : 02/26/2013 | 09:21:16 AM | Tuesday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local color4f = class ({
    __typename = "color4f",
    __isvalue = true,

    -- constructor & destructor
    __init = function ( _self, _r, _g, _b, _a )
        checkarg(_r,"number")
        checkarg(_g,"number")
        checkarg(_b,"number")
        checkarg(_a,"number")

        _self._handle = ex_c.vec4f_new(_r,_g,_b,_a)
    end,

    __gc = function (_self)
        ex_c.vec4f_delete(_self._handle)
    end,

    -- meta-methods
    __tostring = function (_op)
        return string.format ( "{ %.3f, %.3f }", _op.r, _op.g, _op.b, _op.a )
    end,
    __concat = function (_op1,_op2)
        return tostring(_op1)..tostring(_op2)
    end,
    __len = function (_op)
        return 2
    end,
    __add = function (_op1,_op2)
        checkarg(_op1,"color4f")
        checkarg(_op2,"color4f")

        r = ex.color4f.black
        ex_c.vec4f_add ( r._handle, _op1._handle, _op2._handle )
        return r
    end,
    __sub = function (_op1,_op2)
        checkarg(_op1,"color4f")
        checkarg(_op2,"color4f")

        r = ex.color4f.black
        ex_c.vec4f_sub ( r._handle, _op1._handle, _op2._handle )
        return r
    end,
    __mul = function (_op1,_op2)
        type1 = typename(_op1)
        type2 = typename(_op2)

        if type1 == "color4f" and type2 == "color4f" then
            r = ex.color4f.black
            ex_c.vec4f_mul ( r._handle, _op1._handle, _op2._handle )
            return r
        elseif type1 == "color4f" and type2 == "number" then
            r = ex.color4f.black
            ex_c.vec4f_mul_scalar ( r._handle, _op1._handle, _op2 )
            return r
        elseif type1 == "number" and type2 == "color4f" then
            r = ex.color4f.black
            ex_c.vec4f_mul_scalar ( r._handle, _op2._handle, _op1 )
            return r
        end

        error ( "Type error: _op1, _op2 must be color4f or number" )
        return nil
    end,
    __div = function (_op1,_op2)
        type1 = typename(_op1)
        type2 = typename(_op2)

        if type1 == "color4f" and type2 == "color4f" then
            r = ex.color4f.black
            ex_c.vec4f_div ( r._handle, _op1._handle, _op2._handle )
            return r
        elseif type1 == "color4f" and type2 == "number" then
            r = ex.color4f.black
            ex_c.vec4f_div_scalar ( r._handle, _op1._handle, _op2 )
            return r
        elseif type1 == "number" and type2 == "color4f" then
            r = ex.color4f.black
            ex_c.scalar_div_vec4f ( r._handle, _op1, _op2._handle )
            return r
        end

        error ( "Type error: _op1, _op2 must be color4f or number" )
        return nil
    end,
    __unm = function (_op)
        r = ex.color4f.black
        ex_c.vec4f_neg ( r._handle, _op )
        return r
    end,
    __eq = function (_op1,_op2)
        checkarg(_op1,"color4f")
        checkarg(_op2,"color4f")

        return ex_c.vec4f_eq ( _op1._handle, _op2._handle )
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {
        black   = property { get = function () return ex.color4f( 0.0, 0.0, 0.0, 1.0 ) end },
        white   = property { get = function () return ex.color4f( 1.0, 1.0, 1.0, 1.0 ) end },
        red     = property { get = function () return ex.color4f( 1.0, 0.0, 0.0, 1.0 ) end },
        green   = property { get = function () return ex.color4f( 0.0, 1.0, 0.0, 1.0 ) end },
        blue    = property { get = function () return ex.color4f( 0.0, 0.0, 1.0, 1.0 ) end },
        yellow  = property { get = function () return ex.color4f( 1.0, 1.0, 0.0, 1.0 ) end },
        cyan    = property { get = function () return ex.color4f( 0.0, 1.0, 1.0, 1.0 ) end },
        magenta = property { get = function () return ex.color4f( 1.0, 0.0, 1.0, 1.0 ) end },
        gray    = property { get = function () return ex.color4f( 0.5, 0.5, 0.5, 1.0 ) end },
        lerp  = function ( _from, _to, _t )
            local r = ex.color4f.black
            ex_c.vec4f_lerp( r._handle, _from._handle, _to._handle, _t )
            return r
        end
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _handle = ex_c.invalid_handle,
    r = property {
        get = function (_self) return ex_c.vec4f_get_x ( _self._handle ) end,
        set = function (_self,_v) return ex_c.vec4f_set_x ( _self._handle, _v ) end
    },
    g = property { 
        get = function (_self) return ex_c.vec4f_get_y ( _self._handle ) end,
        set = function (_self,_v) return ex_c.vec4f_set_y ( _self._handle, _v ) end
    },
    b = property { 
        get = function (_self) return ex_c.vec4f_get_z ( _self._handle ) end,
        set = function (_self,_v) return ex_c.vec4f_set_z ( _self._handle, _v ) end
    },
    a = property { 
        get = function (_self) return ex_c.vec4f_get_w ( _self._handle ) end,
        set = function (_self,_v) return ex_c.vec4f_set_w ( _self._handle, _v ) end
    },
    normalized = property { 
        get = function (_self) 
            r = ex.color4f.black
            ex_c.vec4f_get_normalize ( _self._handle, r._handle ) 
            return r
        end
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    copy = function ( _self )
        t = typeof (_self)
        return t( _self.r, _self.g, _self.b, _self.a )
    end,
}) 
__M.color4f = color4f

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
