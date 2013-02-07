-- ======================================================================================
-- File         : class.lua
-- Author       : Wu Jie 
-- Last Change  : 01/28/2013 | 10:46:22 AM | Monday,January
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
-- basic
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- {
--     get,            -- function (_self) ... end
--     set,            -- function (_self,_v) ... end
--     range,          -- { min, max }
--     editor_only,    -- true/false
--     ...
-- }
-- ------------------------------------------------------------------ 

local property = setmetatable( {}, {
    __call = function ( _t, ... ) 
        local info = ... or {}
        info.__isproperty = true
        return info
    end
} )
__M.property = property

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function deepcopy ( _v )
    local lookup_table = {}
    local function _copy ( _v )
        if isvalue ( _v ) then
            assert ( _v.copy, "Please provide copy function for value type: " .. typename(_v)  )
            return _v:copy()
        elseif type(_v) ~= "table" then
            return _v
        elseif lookup_table[_v] then
            return lookup_table[_v]
        end

        local new_table = {}
        lookup_table[_v] = new_table
        for index, value in pairs(_v) do
            new_table[_copy(index)] = _copy(value)
        end
        return setmetatable(new_table, getmetatable(_v))
    end
    return _copy(_v)
end
__M.deepcopy = deepcopy

--/////////////////////////////////////////////////////////////////////////////
-- type-op
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function typeof (_object)
    if type(_object) == "table" then
        -- this is an object
        if _object.__isinstance then 
            return getmetatable(_object)
        end
    end
    return nil
end
__M.typeof = typeof

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function isclass (_object)
    local tp = typeof(_object)
    if tp and type(tp) == "table" then 
        local r = rawget(tp, "__isclass")
        if r == nil then 
            return false 
        end
        return r
    end
    return false
end
__M.isclass = isclass

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function isvalue (_object)
    local tp = typeof(_object)
    if tp and type(tp) == "table" then 
        local r = rawget(tp, "__isvalue")
        if r == nil then 
            return false 
        end
        return r
    end 
    return false
end
__M.isvalue = isvalue

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function isproperty (_v)
    if type(_v) == "table" then 
        local r = rawget(_v, "__isproperty")
        if r == nil then 
            return false 
        end
        return r
    end 
    return false 
end
__M.isproperty = isproperty

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function typename(_object)
    if isclass(_object) then 
        local name = rawget(typeof(_object), "__typename")
        assert ( name ~= nil, "Can't find __typename define in your class." )
        return name
    end
    return type(_object)
end
__M.typename = typename

--/////////////////////////////////////////////////////////////////////////////
-- classes functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function instantiate ( _class, ... )
    local object = ... or {}
    object.__isinstance = true
    return setmetatable( object, _class )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function instanceof (_object, _class)
    return typeof(_object) == _class
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function __childof ( _myclass,_superclass )
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
local function childof ( _object, _superclass )
    return __childof(typeof(_object),_superclass)
end

--
local function superof ( _object, _subclass )
	return __childof(_subclass,typeof(_object))
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function isa (_object, _class)
    local cls = typeof(_object)
    return cls == _class or __childof(cls,_class)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function member_readonly ( _t, _k, _v )
    error( string.format( "the key %s is readonly", _k ) )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function member_readonly_get ( _t, _k )
    return rawget(_t,_k)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function class_newindex ( _t, _k, _v )
    -- NOTE: the _t is an object instance

    -- make sure only get __readonly in table _t, not invoke __index method.
    local readonly = rawget(_t,"__readonly")
    if readonly then -- this equals to (is_readonly ~= nil and is_readonly == true)
        error ( "The table is readonly" )
        return
    end

    -- check if the metatable have the key
    local mt = getmetatable(_t) 
    assert( mt, "Can't find the metatable of _t" )

    local v = rawget(mt,_k)
    if v ~= nil then 
        -- if this is a property
        if isproperty (v) then
            assert ( v.set, string.format("Can't find set function in property %s", _k) )
            v.set(_t,_v)
            return
        end

        --
        assert ( type(v) == type(_v), string.format("Invalid type of [%s]: %s, should be %s", _k, type(_v), type(v)) )
        rawset(_t,_k,_v)
        return
    end

    -- check if the super have the key
    local super = rawget(mt,"__super")
    while super ~= nil do
        -- get key from super's metatable
        v = rawget(super,_k)

        --
        if v ~= nil then 
            -- if this is a property
            if isproperty (v) then
                assert ( v.set, string.format("Can't find set function in property %s", _k) )
                v.set(_t,_v)
                return
            end

            --
            assert ( type(v) == type(_v), string.format("Invalid type of [%s]: %s, should be %s", _k, type(_v), type(v)) )
            rawset(_t,_k,_v)
            return
        end

        -- get super's super from super's metatable
        super = rawget(super,"__super")
    end

    -- 
    error( "Can't find the key " .. _k )
    return
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function class_index ( _t, _k )
    -- NOTE: the _t is an object instance

    -- check if the metatable have the key
    local mt = getmetatable(_t) 
    assert( mt, "Can't find the metatable of _t" )

    local v = rawget(mt,_k)
    if v ~= nil then 
        local vv = v
        if type(vv) == "table" and getmetatable(vv) == nil then
            -- if this is a property. NOTE: we don't use isproperty() because we've do table test above
            if rawget(vv, "__isproperty") then
                assert ( vv.get, string.format("Can't find get function in property %s", _k) )
                return vv.get(_t)
            end

            --
            vv = deepcopy(v)
        end
        rawset(_t,_k,vv)
        return vv
    end

    -- check if the super have the key
    local super = rawget(mt,"__super")
    while super ~= nil do
        -- get key from super's metatable
        v = rawget(super,_k)
        if v ~= nil then 
            local vv = v
            if type(vv) == "table" and getmetatable(vv) == nil then
                -- if this is a property. NOTE: we don't use isproperty() because we've do table test above
                if rawget(vv, "__isproperty") then
                    assert ( vv.get, string.format("Can't find get function in property %s", _k) )
                    return vv.get(_t)
                end

                --
                vv = deepcopy(v)
            end
            rawset(_t,_k,vv)
            return vv
        end

        -- get super's super from super's metatable
        super = rawget(super,"__super")
    end

    -- return
    error( "Can't find the key " .. _k )
    return nil
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function class(...)
    local base,super = ...
    assert( type(base) == "table", "The first parameter must be a table" )
    assert( base.__typename ~= nil, "Please define __typename for your class" )

    -- set super class
    if super == nil then
        rawset(base, "__super", nil)
    else
        assert( type(super) == "table", "The super parameter must be a table" )
        assert( rawget(super,"__isclass"), "The super parameter must be a class" )
        rawset( base, "__super", super )
    end

    -- set basic functions
    rawset( base, "__isclass", true )
    if rawget ( base, "__index" ) == nil then
        rawset( base, "__index", class_index )
    end
    if rawget ( base, "__newindex" ) == nil then
        rawset( base, "__newindex", class_newindex )
    end
    rawset( base, "instanceof", instanceof )
    rawset( base, "superof", superof )
    rawset( base, "childof", childof )
    rawset( base, "isa", isa )
    rawset( base, "extend", function (_t)
        return class( _t, base )
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
        metaclass = { __call = instantiate }
    else
        metaclass = { 
            __call = function ( _class, ... ) 
                local object = instantiate (_class)
                init ( object, ... )
                return object
            end
        }
    end
    return setmetatable( base, metaclass )
end
__M.class = class

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

return __M
