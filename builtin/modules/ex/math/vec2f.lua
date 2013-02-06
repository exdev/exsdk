-- ======================================================================================
-- File         : vec2f.lua
-- Author       : Wu Jie 
-- Last Change  : 01/28/2013 | 10:46:10 AM | Monday,January
-- Description  : 
-- ======================================================================================

local __M = {}
local deepcopy, typeof, typename = ex.deepcopy, ex.typeof, ex.typename

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local vec2f = ex.class ({
    __typename = "vec2f",
    __isvalue = true,
    __metaclass = {
        __call = function ( _self, _x, _y )
            assert ( type(_x) == "number" )
            assert ( type(_y) == "number" )
            local table = {
                __isinstance = true,
                _handle = ex_c.vec2f_new(_x,_y),
            }
            return setmetatable( table, _self )
        end,
    },
    __gc = function (_self)
        ex_c.vec2f_delete(_self._handle)
    end,
    __index = function ( _self, _k )
        local mt = getmetatable(_self) 
        assert( mt, "can't find the metatable of _self" )

        local get_table = rawget(mt,"__get")
        assert ( get_table ~= nil and type(get_table) == "table", "can't find __get table" )

        local get_func = get_table[_k]
        assert ( get_func ~= nil and type(get_func) == "function", "can't find key " .. _k )

        return get_func(_self._handle)
    end,
    __newindex = function ( _self, _k, _v )
        local mt = getmetatable(_self) 
        assert( mt, "can't find the metatable of _self" )

        local set_table = rawget(mt,"__set")
        assert ( set_table ~= nil and type(set_table) == "table", "can't find __set table" )

        local set_func = set_table[_k]
        assert ( set_func ~= nil and type(set_func) == "function", "can't find key " .. _k )

        set_func(_self._handle,_v)
    end,

    --
    __get = {
        x = function (_self)
            return ex_c.vec2f_get_x ( _self._handle )
        end,
        y = function (_self)
            return ex_c.vec2f_get_y ( _self._handle )
        end,
    },
    __set = {
        x = function (_self,_v)
            return ex_c.vec2f_set_x ( _self._handle, _v )
        end,
        y = function (_self,_v)
            return ex_c.vec2f_set_y ( _self._handle, _v )
        end,
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- functions
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    copy = function ( _self )
        t = typeof (_self)
        assert ( typeof(_self) == ex.vec2f )

        return t( _self.x, _self.y )
    end
}) 
__M.vec2f = vec2f

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
