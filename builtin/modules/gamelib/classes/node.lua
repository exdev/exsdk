-- ======================================================================================
-- File         : node.lua
-- Author       : Wu Jie 
-- Last Change  : 03/05/2013 | 14:51:35 PM | Tuesday,March
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

ex.node = class ({
    __typename = "node",

    -- constructor & destructor
    __init = function ( self, name )
        checkarg(name,"string")

        self.name = name
    end,

    -- meta-methods
    __len = function (op)
        local cnt = 0
        for _,v in pairs(op) do
            if isclass(v) and v:childof(ex.component) then
                cnt = cnt+1
            end
        end
        return cnt
    end,
    __add = function (op1,op2)
        checkarg(op1,"node")
        assert ( ischildof(op2,ex.component) or type(op2) == "string", "Type error: must be component or string" )

        op1:add_component (op2)
        return op1
    end,
    __sub = function (op1,op2)
        checkarg(op1,"node")
        assert ( ischildof(op2,ex.component) or type(op2) == "string", "Type error: must be component or string" )

        if type(op2) == "string" then
            op1[op2] = nil
        else
            op1[typename(op2)] = nil
        end

        return op1
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    _isdead = false,
    isvalid = property {
        get = function (self) return self._isdead == false end,
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

    destroy = function ( self )
        _isdead = true
        -- TODO: destroy each component
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    update = function ( self )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    getComponent = function ( self, comp )
        local comp_name = comp
        if type(comp) ~= "string" then
            comp_name = typename(comp)
        end

        local comp_inst = self[comp_name]

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

    addComponent = function ( self, comp )
        local inst = ex.instantiate(comp)
        inst.node = self

        if type(comp) == "string" then
            self[comp] = inst
        else
            self[typename(comp)] = inst
        end

        return inst
    end,

}) 
