-- ======================================================================================
-- File         : color4f.lua
-- Author       : Wu Jie 
-- Last Change  : 02/26/2013 | 09:21:16 AM | Tuesday,February
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

ex.color4f = class ({
    __typename = "color4f",
    __isvalue = true,

    -- constructor & destructor
    __init = function ( self, r, g, b, a )
        checkarg(r,"number")
        checkarg(g,"number")
        checkarg(b,"number")
        checkarg(a,"number")

        self._handle = ex_c.vec4f_new(r,g,b,a)
    end,

    __gc = function (self)
        ex_c.vec4f_delete(self._handle)
    end,

    -- meta-methods
    __tostring = function (op)
        return string.format ( "{ %.3f, %.3f }", op.r, op.g, op.b, op.a )
    end,
    __concat = function (op1,op2)
        return tostring(op1)..tostring(op2)
    end,
    __len = function (op)
        return 4
    end,
    __add = function (op1,op2)
        checkarg(op1,"color4f")
        checkarg(op2,"color4f")

        local result = ex.color4f.black
        ex_c.vec4f_add ( result._handle, op1._handle, op2._handle )
        return result
    end,
    __sub = function (op1,op2)
        checkarg(op1,"color4f")
        checkarg(op2,"color4f")

        local result = ex.color4f.black
        ex_c.vec4f_sub ( result._handle, op1._handle, op2._handle )
        return result
    end,
    __mul = function (op1,op2)
        local type1 = typename(op1)
        local type2 = typename(op2)

        if type1 == "color4f" and type2 == "color4f" then
            local result = ex.color4f.black
            ex_c.vec4f_mul ( result._handle, op1._handle, op2._handle )
            return result
        elseif type1 == "color4f" and type2 == "number" then
            local result = ex.color4f.black
            ex_c.vec4f_mul_scalar ( result._handle, op1._handle, op2 )
            return result
        elseif type1 == "number" and type2 == "color4f" then
            local result = ex.color4f.black
            ex_c.vec4f_mul_scalar ( result._handle, op2._handle, op1 )
            return result
        end

        error ( "Type error: op1, op2 must be color4f or number" )
        return nil
    end,
    __div = function (op1,op2)
        local type1 = typename(op1)
        local type2 = typename(op2)

        if type1 == "color4f" and type2 == "color4f" then
            local result = ex.color4f.black
            ex_c.vec4f_div ( result._handle, op1._handle, op2._handle )
            return result
        elseif type1 == "color4f" and type2 == "number" then
            local result = ex.color4f.black
            ex_c.vec4f_div_scalar ( result._handle, op1._handle, op2 )
            return result
        elseif type1 == "number" and type2 == "color4f" then
            local result = ex.color4f.black
            ex_c.scalar_div_vec4f ( result._handle, op1, op2._handle )
            return result
        end

        error ( "Type error: op1, op2 must be color4f or number" )
        return nil
    end,
    __unm = function (op)
        local result = ex.color4f.black
        ex_c.vec4f_neg ( result._handle, op )
        return result
    end,
    __eq = function (op1,op2)
        checkarg(op1,"color4f")
        checkarg(op2,"color4f")

        return ex_c.vec4f_eq ( op1._handle, op2._handle )
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
        lerp = function ( from, to, t )
            local result = ex.color4f.black
            ex_c.vec4f_lerp( result._handle, from._handle, to._handle, t )
            return result
        end,
        from_rgba_8888 = function ( list )
            return ex.color4f( list[1]/255, 
                               list[2]/255, 
                               list[3]/255, 
                               (list[4] or 255)/255 )
        end,
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _handle = ex_c.invalid_handle,
    r = property {
        get = function (self) return ex_c.vec4f_get_x ( self._handle ) end,
        set = function (self,v) ex_c.vec4f_set_x ( self._handle, v ) end
    },
    g = property { 
        get = function (self) return ex_c.vec4f_get_y ( self._handle ) end,
        set = function (self,v) ex_c.vec4f_set_y ( self._handle, v ) end
    },
    b = property { 
        get = function (self) return ex_c.vec4f_get_z ( self._handle ) end,
        set = function (self,v) ex_c.vec4f_set_z ( self._handle, v ) end
    },
    a = property { 
        get = function (self) return ex_c.vec4f_get_w ( self._handle ) end,
        set = function (self,v) ex_c.vec4f_set_w ( self._handle, v ) end
    },
    normalized = property { 
        get = function (self) 
            local result = ex.color4f.black
            ex_c.vec4f_get_normalize ( self._handle, result._handle ) 
            return result
        end
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    copy = function ( self )
        return ex.color4f ( self.r, self.g, self.b, self.a )
    end,
}) 
