-- ======================================================================================
-- File         : class.lua
-- Author       : Wu Jie 
-- Last Change  : 01/28/2013 | 10:46:22 AM | Monday,January
-- Description  : 
-- ======================================================================================

local __classes = {}

--/////////////////////////////////////////////////////////////////////////////
-- basic
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- {
--     get,            -- function (self) ... end
--     set,            -- function (self,val) ... end
--     range,          -- { min, max }
--     editor_only,    -- true/false
--     ...
-- }
-- ------------------------------------------------------------------ 

property = setmetatable( {}, {
    __call = function ( _, ... ) 
        local info = ... or {}
        info.__isproperty = true
        return info
    end
} )

--/////////////////////////////////////////////////////////////////////////////
-- type-op
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function typeof (obj)
    if type(obj) == "table" then
        -- this is an object
        if obj.__isinstance then 
            return getmetatable(obj)
        end
    end
    return nil
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function isclasstype (cls)
    local r = rawget(cls, "__isclass")
    if r == nil then 
        return false 
    end
    return r
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function isclass (obj)
    local tp = typeof(obj)
    if tp and type(tp) == "table" then 
        local r = rawget(tp, "__isclass")
        if r == nil then 
            return false 
        end
        return r
    end
    return false
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function isvalue (obj)
    local tp = typeof(obj)
    if tp and type(tp) == "table" then 
        local r = rawget(tp, "__isvalue")
        if r == nil then 
            return false 
        end
        return r
    end 
    return false
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function isproperty (val)
    if type(val) == "table" then 
        local r = rawget(val, "__isproperty")
        if r == nil then 
            return false 
        end
        return r
    end 
    return false 
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function __childof ( myclass,superclass )
    local super = rawget(myclass,"__super")
    while super ~= nil do
        if super == superclass then 
            return true 
        end
        super = rawget(super,"__super")
    end
    return false
end

--
function ischildof ( myclass, superclass )
    return __childof(myclass,superclass)
end

--
function issuperof ( myclass, subclass )
	return __childof(subclass,myclass)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function typename (obj)
    if isclass(obj) then 
        local name = rawget(typeof(obj), "__typename")
        assert ( name ~= nil, "Can't find __typename define in your class." )
        return name
    end
    return type(obj)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function super ( obj )
    local tp = typeof(obj)
    return rawget(tp,"__super")
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function __instantiate ( cls, ... )
    local obj = ... or {}
    obj.__isinstance = true
    return setmetatable( obj, cls )
end

--
function instantiate ( cls, ... )
    local class_type = cls

    -- if the argument is class type name
    if type(cls) == "string" then
        class_type = __classes[cls]
        assert ( class_type ~= nil, "Can't find class type " .. cls )
    end

    return __instantiate( class_type, ... )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function deepcopy ( val )
    local lookup_table = {}
    local function _copy ( val )
        if isvalue ( val ) then
            assert ( val.copy, "Please provide copy function for value type: " .. typename(val)  )
            return val:copy()
        elseif type(val) ~= "table" then
            return val
        elseif lookup_table[val] then
            return lookup_table[val]
        end

        local new_table = {}
        lookup_table[val] = new_table
        for index, value in pairs(val) do
            new_table[_copy(index)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(val))
    end
    return _copy(val)
end

--/////////////////////////////////////////////////////////////////////////////
-- classes functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function instance_newindex ( t, key, val )
    -- NOTE: the t is an object instance

    -- DISABLE { 
    -- -- make sure only get __readonly in table t, not invoke __index method.
    -- local readonly = rawget(t,"__readonly")
    -- if readonly then -- this equals to (is_readonly ~= nil and is_readonly == true)
    --     error ( "The table is readonly" )
    --     return
    -- end
    -- } DISABLE end 

    -- check if the metatable have the key
    local mt = getmetatable(t) 
    assert( mt, "Can't find the metatable of t" )

    local v = rawget(mt,key)
    if v ~= nil then 
        -- if this is a property
        if isproperty (v) then
            assert ( v.set, string.format("Can't find set function in property %s", key) )
            v.set(t,val)
            return
        end

        --
        assert ( type(v) == type(val), string.format("Invalid type of [%s]: %s, should be %s", key, type(val), type(v)) )
        rawset(t,key,val)
        return
    end

    -- check if the super have the key
    local super = rawget(mt,"__super")
    while super ~= nil do
        -- get key from super's metatable
        v = rawget(super,key)

        --
        if v ~= nil then 
            -- if this is a property
            if isproperty (v) then
                assert ( v.set, string.format("Can't find set function in property %s", key) )
                v.set(t,val)
                return
            end

            --
            assert ( type(v) == type(val), string.format("Invalid type of [%s]: %s, should be %s", key, type(val), type(v)) )
            rawset(t,key,val)
            return
        end

        -- get super's super from super's metatable
        super = rawget(super,"__super")
    end

    -- 
    -- error( "Can't find the key " .. key )
    rawset(t,key,val)
    return
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function instance_index ( t, key )
    -- NOTE: the t is an object instance

    -- check if the metatable have the key
    local mt = getmetatable(t) 
    assert( mt, "Can't find the metatable of t" )

    local v = rawget(mt,key)
    if v ~= nil then 
        local vv = v
        if type(vv) == "table" and getmetatable(vv) == nil then
            -- if this is a property. NOTE: we don't use isproperty() because we've do table test above
            if rawget(vv, "__isproperty") then
                assert ( vv.get, string.format("Can't find get function in property %s", key) )
                return vv.get(t)
            end

            --
            vv = deepcopy(v)
        end
        rawset(t,key,vv)
        return vv
    end

    -- check if the super have the key
    local super = rawget(mt,"__super")
    while super ~= nil do
        -- get key from super's metatable
        v = rawget(super,key)
        if v ~= nil then 
            local vv = v
            if type(vv) == "table" and getmetatable(vv) == nil then
                -- if this is a property. NOTE: we don't use isproperty() because we've do table test above
                if rawget(vv, "__isproperty") then
                    assert ( vv.get, string.format("Can't find get function in property %s", key) )
                    return vv.get(t)
                end

                --
                vv = deepcopy(v)
            end
            rawset(t,key,vv)
            return vv
        end

        -- get super's super from super's metatable
        super = rawget(super,"__super")
    end

    -- return
    -- error( "Can't find the key " .. key )
    return nil
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function class_newindex ( t, key, val )
    -- NOTE: the t is a class table

    -- check if the metatable have the key
    local mt = getmetatable(t) 
    assert( mt, "Can't find the metatable of t" )

    --
    local v = rawget(mt,key)
    if v ~= nil then
        if isproperty(v) then 
            assert ( v.set, string.format("Can't find set function in property %s", key) )
            v.set(t,val)
            return
        end
    end

    -- return
    error ( "The table is readonly" )
    return
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function class_index ( t, key )
    -- NOTE: the t is a class table

    -- check if the metatable have the key
    local mt = getmetatable(t) 
    assert( mt, "Can't find the metatable of t" )

    --
    local v = rawget(mt,key)
    if v ~= nil then
        if isproperty(v) then 
            assert ( v.get, string.format("Can't find get function in property %s", key) )
            return v.get() -- NOTE: we don't need to send any argument compare to instance property 
        end
        return v
    end

    -- return
    error( "Can't find the key " .. key )
    return nil
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function class(...)
    local base,super = ...
    assert( type(base) == "table", "The first parameter must be a table" )
    assert( base.__typename ~= nil, "Please define __typename for your class" )
    assert( __classes[base.__typename] == nil, string.format("The class %s already defined!", base.__typename) )

    -- register name to class
    __classes[base.__typename] = base

    -- set super class
    if super == nil then
        rawset(base, "__super", nil)
    else
        assert( type(super) == "table", "The super parameter must be a table" )
        assert( rawget(super,"__isclass"), "The super parameter must be a class" )
        rawset( base, "__super", super )
    end

    -- set basic functions
    rawset ( base, "__isclass", true )
    if rawget ( base, "__index" ) == nil then
        rawset ( base, "__index", instance_index )
    end
    if rawget ( base, "__newindex" ) == nil then
        rawset ( base, "__newindex", instance_newindex )
    end
    rawset ( base, "instanceof", function (obj, cls)
        return typeof(obj) == cls
    end )
    rawset ( base, "superof", function (obj, subclass)
        return __childof(subclass,typeof(obj))
    end )
    rawset ( base, "childof", function (obj, superclass)
        return __childof(typeof(obj),superclass)
    end )
    rawset ( base, "isa", function (obj, cls)
        local objcls = typeof(obj)
        return objcls == cls or __childof(obj,cls)
    end )
    rawset ( base, "extend", function (t)
        return class( t, base )
    end )

    -- check if we derived from value type
    local isvalue = rawget( base, "__isvalue" )
    if isvalue == nil then
        while super ~= nil do 
            isvalue = rawget(super, "__isvalue")
            if isvalue ~= nil then 
                break 
            end
            super = rawget(super, "__super")
        end
        rawset ( base, "__isvalue", isvalue )
    end

    -- set metaclass
    local metaclass = {}
    local init = rawget ( base, "__init" )
    if init == nil then
        metaclass = { 
            __call = __instantiate,
        }
    else
        metaclass = { 
            __call = function ( cls, ... ) 
                local obj = __instantiate (cls)
                init ( obj, ... )
                return obj
            end,
        }
    end
    rawset ( metaclass, "__newindex", class_newindex )
    rawset ( metaclass, "__index", class_index )
    rawset ( metaclass, "null", property { get = function () return __instantiate(base) end } )
    rawset ( metaclass, "new", function (...) return __instantiate(base,...) end )

    -- copy __static properties to class-metatable
    -- NOTE: we don't do deepcopy to save memory
    local static = rawget( base, "__static" )
    if static ~= nil then
        for index, value in pairs(static) do
            metaclass[index] = value
        end
    end
    return setmetatable( base, metaclass )
end

