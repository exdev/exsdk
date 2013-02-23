-- ======================================================================================
-- File         : entity.lua
-- Author       : Wu Jie 
-- Last Change  : 02/23/2013 | 16:05:59 PM | Saturday,February
-- Description  : 
-- ======================================================================================

local __M = {}
local property
    , typeof
    , typename
    , isclass
    , isclasstype
    , component
      = 
      ex.property
    , ex.typeof
    , ex.typename
    , ex.isclass
    , ex.isclasstype
    , ex.component

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local entity = ex.class ({
    __typename = "entity",

    -- constructor & destructor
    __init = function ( _self, _name )
        assert ( type(_name) == "string", "Type error: _name must be string" )
        _self.name = _name
    end,

    -- meta-methods
    __len = function (_op)
        local cnt = 0
        for _,v in pairs(op) do
            if isclass(v) and v:childof(component) then
                cnt = cnt+1
            end
        end
        return cnt
    end,
    __add = function (_op1,_op2)
        assert ( typename(_op1) == "entity", "Type error: _op1 must be vec2f" )
        assert ( isclasstype(_op2) or type(_op2) == "string", "Type error: _op2 must be class-type or string" )

        local inst = ex.instantiate(_op2)

        if type(_op2) == "string" then
            _op1[_op2] = inst
        else
            _op1[typename(_op2)] = inst
        end

        return _op1
    end,
    __sub = function (_op1,_op2)
        assert ( typename(_op1) == "entity", "Type error: _op1 must be vec2f" )
        assert ( isclasstype(_op2) or type(_op2) == "string", "Type error: _op2 must be class-type or string" )

        if type(_op2) == "string" then
            _op1[_op2] = nil
        else
            _op1[typename(_op2)] = nil
        end

        return _op1
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    name = "",
    position = ex.vec2f.zero, 
    angle = 0.0,
    scale = ex.vec2f.one,

    _cached_components = {},

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    update = function ( _self )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    get_component = function ( _self, _name )
        local comp = _self[_name]

        if comp ~= nil 
        and isclass(comp) 
        and comp:childof(component) 
        then
            return comp
        end

        return nil
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    add_component = function ( _self, _name )
    end,

}) 
__M.entity = entity

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
