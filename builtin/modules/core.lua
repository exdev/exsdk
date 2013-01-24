-- ======================================================================================
-- File         : core.lua
-- Author       : Wu Jie 
-- Last Change  : 01/24/2013 | 19:06:45 PM | Thursday,January
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- require and module
--/////////////////////////////////////////////////////////////////////////////

local assert = assert
local type = type
local getmetatable = getmetatable
local setmetatable = setmetatable
local pairs = pairs
local rawget = rawget
local rawset = rawset

module("ex")

--/////////////////////////////////////////////////////////////////////////////
-- base functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function deepcopy (_obj)
    local lookup_table = {}
    local function _copy(_obj)
        if isbuiltin( _obj ) then
            assert(_obj.copy, "please provide copy function for builtin type: " .. typename(_obj) )
            return _obj:copy()
        elseif type(_obj) ~= "table" then
            return _obj
        elseif lookup_table[_obj] then
            return lookup_table[_obj]
        end
        local new_table = {}
        lookup_table[_obj] = new_table
        for index, value in pairs(_obj) do
            new_table[_copy(index)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(_obj))
    end
    return _copy(_obj)
end

--/////////////////////////////////////////////////////////////////////////////
-- type-op
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function typeof (_object)
    local obj = _object
    while obj.__isinstance == false do 
        obj = getmetatable(obj)
    end
    if obj.__isinstance then
        return getmetatable(obj)
    end
    return nil
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

metaclass = {
    __call = function ( _self, ... )
        local table = ... or {}
        table.__isinstance = true
        return setmetatable( table, _self )
    end
}

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function isclass (_object)
    local tp = typeof(_object)
    if type(tp) ~= "table" then 
        return false
    end

    local r = rawget(tp, "__isclass")
    if r == nil then 
        return false 
    end
    return r
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function isbuiltin (_object)
    local tp = typeof(_object)
    if type(tp) ~= "table" then 
        return false 
    end 

    local r = rawget(tp, "__isbuiltin")
    if r == nil then 
        return false 
    end
    return r
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function typename(_object)
    if isbuiltin(_object) or isclass(_object) then 
        local name = rawget(typeof(_object), "__typename")
        assert ( name ~= nil, "can't find __typename define in your class." )
        return name
    end
    return type(_object)
end

--/////////////////////////////////////////////////////////////////////////////
-- classes functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function instanceof(_object, _class)
    return typeof(_object) == _class
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function __childof(_myclass,_superclass)
    local super = rawget(_myclass,"__super")
    while super ~= nil do
        if super == _superclass then 
            return true 
        end
        super = rawget(super,"__super")
    end
    return false
end

--

local function childof(_object, _superclass)
    return __childof(typeof(_object),_superclass)
end

--

local function superof(_object, _subclass)
	return __childof(_subclass,typeof(_object))
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function isa(_object, _class)
    local cls = typeof(_object)
    return cls == _class or __childof(cls,_class)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function member_readonly ( _t, _k, _v )
    assert( false, "keys are readonly" )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function member_readonly_get ( _t, _k )
    print( "get value " .. _k )
    return rawget(_t,_k)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function class_newindex ( _t, _k, _v )
    -- NOTE: the _t can only be object instance, 
    --       we can garantee this, case if it is a class, 
    --       it never use class_index as __index method. 
    --       it use metaclass.__index

    -- make sure only get __readonly in table _t, not invoke __index method.
    local is_readonly = rawget(_t,"__readonly")
    if is_readonly then -- this equals to (is_readonly ~= nil and is_readonly == true)
        assert ( false, "the table is readonly" )
        return
    end

    -- check if the metatable have the key
    local mt = getmetatable(_t) 
    assert( mt, "can't find the metatable of _t" )
    local v = rawget(mt,_k)
    if v ~= nil then 
        -- DISABLE: the new index can only garantee 'new' value, but old one still not protected. { 
        -- if type(v) ~= type(_v) then
        --     assert( false, "can't set the key ".._k..", the type is not the same" )
        --     return
        -- end
        -- } DISABLE end 
        rawset(_t,_k,_v)
        return
    end

    -- DISABLE { 
    -- -- check if the super have the key
    -- local super = rawget(mt,"__super")
    -- while super ~= nil do
    --     -- get key from super's metatable
    --     v = rawget(super,_k)

    --     --
    --     if v ~= nil then 
    --         -- DISABLE: the new index can only garantee 'new' value, but old one still not protected. { 
    --         -- if type(v) ~= type(_v) then
    --         --     assert( false, "can't set the key ".._k..", the type is not the same" )
    --         --     return
    --         -- end
    --         -- } DISABLE end 
    --         rawset(_t,_k,_v)
    --         return
    --     end

    --     -- get super's super from super's metatable
    --     super = rawget(super,"__super")
    -- end
    -- } DISABLE end 

    -- 
    assert( false, "can't find the key " .. _k )
    return
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function class_index ( _t, _k )
    -- DISABLE { 
    -- -- NOTE: the _t can only be object instance, 
    -- --       we can garantee this, case if it is a class, 
    -- --       it never use class_index as __index method. 
    -- --       it use metaclass.__index

    -- -- speical case
    -- if _k == "super" then
    --     local mt = getmetatable(_t) 
    --     assert( mt, "can't find the metatable of _t" )
    --     local super = rawget(mt,"__super")

    --     if super and rawget(super, "__isbuiltin") then
    --         return rawget(_t, "__cobject")
    --     else
    --         -- NOTE: in class_newindex, it will check if table have __readonly, and prevent setting things.
    --         return setmetatable( { __readonly = true }, super )
    --     end
    -- end
    -- } DISABLE end 

    -- check if the metatable have the key
    local mt = getmetatable(_t) 
    assert( mt, "can't find the metatable of _t" )
    local v = rawget(mt,_k)
    if v ~= nil then 
        local vv = v
        if type(vv) == "table" and getmetatable(vv) == nil then
            vv = deepcopy(v)
        end
        rawset(_t,_k,vv)
        return vv
    end

    -- DISABLE { 
    -- -- check if the super have the key
    -- local super = rawget(mt,"__super")
    -- while super ~= nil do
    --     -- get key from super's metatable
    --     v = rawget(super,_k)

    --     --
    --     if v ~= nil then 
    --         local vv = v
    --         if type(vv) == "table" and getmetatable(vv) == nil then
    --             vv = deepcopy(v)
    --         end
    --         rawset(_t,_k,vv)
    --         return vv
    --     end

    --     -- get super's super from super's metatable
    --     super = rawget(super,"__super")
    -- end
    -- } DISABLE end 

    -- return
    return nil
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function class(...)
    local base,super = ...
    assert( type(base) == "table", "the first parameter must be a table" )
    assert( base.__typename ~= nil, "please define __typename for your class" )

    if super == nil then
        rawset(base, "__super", nil)
    else
        assert( type(super) == "table", "the super parameter must be a table" )
        assert( rawget(super,"__isclass"), "the super parameter must be a class" )
        rawset(base, "__super", super)
    end

    base.__isclass = true
    base.__index = class_index
    base.__newindex = class_newindex
    base.instanceof = instanceof
    base.superof = superof
    base.childof = childof
    base.isa = isa
    base.derive = function (_t)
        return class( _t, base )
    end

    -- check if we derived from builtin class
    local derived_from_builtin = false
    local builtin_class = nil
    while super ~= nil do 
        derived_from_builtin = rawget(super, "__isbuiltin")
        if derived_from_builtin then 
            builtin_class = super
            break 
        end
        super = rawget(super, "__super")
    end

    -- 
    if derived_from_builtin then
        return setmetatable(base,builtin_class.__metaclass)
    else
        return setmetatable(base,metaclass)
    end
end
