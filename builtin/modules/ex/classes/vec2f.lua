-- ======================================================================================
-- File         : vec2f.lua
-- Author       : Wu Jie 
-- Last Change  : 01/28/2013 | 10:46:10 AM | Monday,January
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

ex.vec2f = class ({
    __typename = "vec2f",
    __isvalue = true,

    -- constructor & destructor
    __init = function ( self, x, y )
        checkarg(x,"number")
        checkarg(y,"number")

        self._handle = ex_c.vec2f_new(x,y)
    end,

    __gc = function (self)
        ex_c.vec2f_delete(self._handle)
    end,

    -- meta-methods
    __tostring = function (op)
        return string.format ( "{ %.3f, %.3f }", op.x, op.y )
    end,
    __concat = function (op1,op2)
        return tostring(op1)..tostring(op2)
    end,
    __len = function (op)
        return 2
    end,
    __add = function (op1,op2)
        checkarg(op1,"vec2f")
        checkarg(op2,"vec2f")

        local result = ex.vec2f.zero
        ex_c.vec2f_add ( result._handle, op1._handle, op2._handle )
        return result
    end,
    __sub = function (op1,op2)
        checkarg(op1,"vec2f")
        checkarg(op2,"vec2f")

        local result = ex.vec2f.zero
        ex_c.vec2f_sub ( result._handle, op1._handle, op2._handle )
        return result
    end,
    __mul = function (op1,op2)
        local type1 = typename(op1)
        local type2 = typename(op2)

        if type1 == "vec2f" and type2 == "vec2f" then
            local result = ex.vec2f.zero
            ex_c.vec2f_mul ( result._handle, op1._handle, op2._handle )
            return result
        elseif type1 == "vec2f" and type2 == "number" then
            local result = ex.vec2f.zero
            ex_c.vec2f_mul_scalar ( result._handle, op1._handle, op2 )
            return result
        elseif type1 == "number" and type2 == "vec2f" then
            local result = ex.vec2f.zero
            ex_c.vec2f_mul_scalar ( result._handle, op2._handle, op1 )
            return result
        end

        error ( "Type error: op1, op2 must be vec2f or number" )
        return nil
    end,
    __div = function (op1,op2)
        local type1 = typename(op1)
        local type2 = typename(op2)

        if type1 == "vec2f" and type2 == "vec2f" then
            local result = ex.vec2f.zero
            ex_c.vec2f_div ( result._handle, op1._handle, op2._handle )
            return result
        elseif type1 == "vec2f" and type2 == "number" then
            local result = ex.vec2f.zero
            ex_c.vec2f_div_scalar ( result._handle, op1._handle, op2 )
            return result
        elseif type1 == "number" and type2 == "vec2f" then
            local result = ex.vec2f.zero
            ex_c.scalar_div_vec2f ( result._handle, op1, op2._handle )
            return result
        end

        error ( "Type error: op1, op2 must be vec2f or number" )
        return nil
    end,
    __unm = function (op)
        local result = ex.vec2f.zero
        ex_c.vec2f_neg ( result._handle, op )
        return result
    end,
    __eq = function (op1,op2)
        checkarg(op1,"vec2f")
        checkarg(op2,"vec2f")

        return ex_c.vec2f_eq ( op1._handle, op2._handle )
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {
        zero  = property { get = function () return ex.vec2f( 0.0, 0.0 ) end },
        one   = property { get = function () return ex.vec2f( 1.0, 1.0 ) end },
        right = property { get = function () return ex.vec2f( 1.0, 0.0 ) end },
        up    = property { get = function () return ex.vec2f( 0.0, 1.0 ) end },
        lerp  = function ( from, to, t )
            -- local result = ex.vec2f.zero
            -- result.x = math.lerp ( from.x, to.x, t )
            -- result.y = math.lerp ( from.y, to.y, t )
            -- return result

            local result = ex.vec2f.zero
            ex_c.vec2f_lerp( result._handle, from._handle, to._handle, t )
            return result
        end
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _handle = ex_c.invalid_handle,
    x = property {
        get = function (self) return ex_c.vec2f_get_x ( self._handle ) end,
        set = function (self,v) ex_c.vec2f_set_x ( self._handle, v ) end
    },
    y = property { 
        get = function (self) return ex_c.vec2f_get_y ( self._handle ) end,
        set = function (self,v) ex_c.vec2f_set_y ( self._handle, v ) end
    },
    normalized = property { 
        get = function (self) 
            local result = ex.vec2f.zero
            ex_c.vec2f_get_normalize ( self._handle, result._handle ) 
            return result
        end
    },
    len = property {
        get = function (self) return ex_c.vec2f_len ( self._handle ) end
    },
    lenSQR = property {
        get = function (self) return ex_c.vec2f_lenSQR ( self._handle ) end
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    copy = function ( self )
        return ex.vec2f( self.x, self.y )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    normalize = function (self) 
        ex_c.vec2f_normalize ( self._handle ) 
    end,
}) 
