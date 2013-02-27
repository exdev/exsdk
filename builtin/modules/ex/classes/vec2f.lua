-- ======================================================================================
-- File         : vec2f.lua
-- Author       : Wu Jie 
-- Last Change  : 01/28/2013 | 10:46:10 AM | Monday,January
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local vec2f = class ({
    __typename = "vec2f",
    __isvalue = true,

    -- constructor & destructor
    __init = function ( _self, _x, _y )
        checkarg(_x,"number")
        checkarg(_y,"number")

        _self._handle = ex_c.vec2f_new(_x,_y)
    end,

    __gc = function (_self)
        ex_c.vec2f_delete(_self._handle)
    end,

    -- meta-methods
    __tostring = function (_op)
        return string.format ( "{ %.3f, %.3f }", _op.x, _op.y )
    end,
    __concat = function (_op1,_op2)
        return tostring(_op1)..tostring(_op2)
    end,
    __len = function (_op)
        return 2
    end,
    __add = function (_op1,_op2)
        checkarg(_op1,"vec2f")
        checkarg(_op2,"vec2f")

        r = ex.vec2f.zero
        ex_c.vec2f_add ( r._handle, _op1._handle, _op2._handle )
        return r
    end,
    __sub = function (_op1,_op2)
        checkarg(_op1,"vec2f")
        checkarg(_op2,"vec2f")

        r = ex.vec2f.zero
        ex_c.vec2f_sub ( r._handle, _op1._handle, _op2._handle )
        return r
    end,
    __mul = function (_op1,_op2)
        type1 = typename(_op1)
        type2 = typename(_op2)

        if type1 == "vec2f" and type2 == "vec2f" then
            r = ex.vec2f.zero
            ex_c.vec2f_mul ( r._handle, _op1._handle, _op2._handle )
            return r
        elseif type1 == "vec2f" and type2 == "number" then
            r = ex.vec2f.zero
            ex_c.vec2f_mul_scalar ( r._handle, _op1._handle, _op2 )
            return r
        elseif type1 == "number" and type2 == "vec2f" then
            r = ex.vec2f.zero
            ex_c.vec2f_mul_scalar ( r._handle, _op2._handle, _op1 )
            return r
        end

        error ( "Type error: _op1, _op2 must be vec2f or number" )
        return nil
    end,
    __div = function (_op1,_op2)
        type1 = typename(_op1)
        type2 = typename(_op2)

        if type1 == "vec2f" and type2 == "vec2f" then
            r = ex.vec2f.zero
            ex_c.vec2f_div ( r._handle, _op1._handle, _op2._handle )
            return r
        elseif type1 == "vec2f" and type2 == "number" then
            r = ex.vec2f.zero
            ex_c.vec2f_div_scalar ( r._handle, _op1._handle, _op2 )
            return r
        elseif type1 == "number" and type2 == "vec2f" then
            r = ex.vec2f.zero
            ex_c.scalar_div_vec2f ( r._handle, _op1, _op2._handle )
            return r
        end

        error ( "Type error: _op1, _op2 must be vec2f or number" )
        return nil
    end,
    __unm = function (_op)
        r = ex.vec2f.zero
        ex_c.vec2f_neg ( r._handle, _op )
        return r
    end,
    __eq = function (_op1,_op2)
        checkarg(_op1,"vec2f")
        checkarg(_op2,"vec2f")

        return ex_c.vec2f_eq ( _op1._handle, _op2._handle )
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {
        zero  = property { get = function () return ex.vec2f( 0.0, 0.0 ) end },
        one   = property { get = function () return ex.vec2f( 1.0, 1.0 ) end },
        right = property { get = function () return ex.vec2f( 1.0, 0.0 ) end },
        up    = property { get = function () return ex.vec2f( 0.0, 1.0 ) end },
        lerp  = function ( _from, _to, _t )
            -- local r = ex.vec2f.zero
            -- r.x = math.lerp ( _from.x, _to.x, _t )
            -- r.y = math.lerp ( _from.y, _to.y, _t )
            -- return r

            local r = ex.vec2f.zero
            ex_c.vec2f_lerp( r._handle, _from._handle, _to._handle, _t )
            return r
        end
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _handle = ex_c.invalid_handle,
    x = property {
        get = function (_self) return ex_c.vec2f_get_x ( _self._handle ) end,
        set = function (_self,_v) return ex_c.vec2f_set_x ( _self._handle, _v ) end
    },
    y = property { 
        get = function (_self) return ex_c.vec2f_get_y ( _self._handle ) end,
        set = function (_self,_v) return ex_c.vec2f_set_y ( _self._handle, _v ) end
    },
    normalized = property { 
        get = function (_self) 
            r = ex.vec2f.zero
            ex_c.vec2f_get_normalize ( _self._handle, r._handle ) 
            return r
        end
    },
    len = property {
        get = function (_self) return ex_c.vec2f_len ( _self._handle ) end
    },
    lenSQR = property {
        get = function (_self) return ex_c.vec2f_lenSQR ( _self._handle ) end
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    copy = function ( _self )
        t = typeof (_self)
        return t( _self.x, _self.y )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    normalize = function (_self) 
        ex_c.vec2f_normalize ( _self._handle ) 
    end,
}) 
__M.vec2f = vec2f

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
