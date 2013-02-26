-- ======================================================================================
-- File         : entity.lua
-- Author       : Wu Jie 
-- Last Change  : 02/23/2013 | 16:05:59 PM | Saturday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local entity = class ({
    __typename = "entity",

    -- constructor & destructor
    __init = function ( _self, _name )
        checkarg(_name,"string")

        _self.name = _name
    end,

    -- meta-methods
    __len = function (_op)
        local cnt = 0
        for _,v in pairs(op) do
            if isclass(v) and v:childof(ex.component) then
                cnt = cnt+1
            end
        end
        return cnt
    end,
    __add = function (_op1,_op2)
        checkarg(_op1,"entity")
        assert ( ischildof(_op2,ex.component) or type(_op2) == "string", "Type error: must be component or string" )

        _op1:add_component (_op2)
        return _op1
    end,
    __sub = function (_op1,_op2)
        checkarg(_op1,"entity")
        assert ( ischildof(_op2,ex.component) or type(_op2) == "string", "Type error: must be component or string" )

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

    get_component = function ( _self, _comp )
        local comp_name = _comp
        if type(_comp) ~= "string" then
            comp_name = typename(_comp)
        end

        local comp_inst = _self[comp_name]

        if comp_inst ~= nil 
        and isclass(comp_inst) 
        and comp_inst:childof(ex.component) 
        then
            return comp_inst
        end

        return nil
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    add_component = function ( _self, _comp )
        local inst = ex.instantiate(_comp)
        inst.entity = _self

        if type(_comp) == "string" then
            _self[_comp] = inst
        else
            _self[typename(_comp)] = inst
        end

        return inst
    end,

}) 
__M.entity = entity

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
