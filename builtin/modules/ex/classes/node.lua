-- ======================================================================================
-- File         : node.lua
-- Author       : Wu Jie 
-- Last Change  : 03/05/2013 | 14:51:35 PM | Tuesday,March
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

local node = class ({
    __typename = "node",

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
        checkarg(_op1,"node")
        assert ( ischildof(_op2,ex.component) or type(_op2) == "string", "Type error: must be component or string" )

        _op1:add_component (_op2)
        return _op1
    end,
    __sub = function (_op1,_op2)
        checkarg(_op1,"node")
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

    _isdead = false,
    isvalid = property {
        get = function (_self) return _self._isdead == false end,
    },

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

    destroy = function ( _self )
        _isdead = true
        -- TODO: destroy each component
    end,

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
        inst.node = _self

        if type(_comp) == "string" then
            _self[_comp] = inst
        else
            _self[typename(_comp)] = inst
        end

        return inst
    end,

}) 
__M.node = node

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
