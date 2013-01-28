-- ======================================================================================
-- File         : debug.lua
-- Author       : Wu Jie 
-- Last Change  : 09/13/2010 | 10:59:05 AM | Monday,September
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
-- require and module
--/////////////////////////////////////////////////////////////////////////////

local assert = assert
local type = type
local print = print
local pairs = pairs
local next = next
local tostring = tostring
local assert = assert
local type = type
local pairs = pairs
local next = next
local getmetatable = getmetatable
local debug = debug
local string, io = string, io

module (...)

--/////////////////////////////////////////////////////////////////////////////
-- functions defines
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: Modified by Wu Jie
--[[
Author: Julio Manuel Fernandez-Diaz
Date:   January 12, 2007
(For Lua 5.1)

Modified slightly by RiciLake to avoid the unnecessary table traversal in tablecount()

Formats tables with cycles recursively to any depth.
The output is returned as a string.
References to other tables are shown as values.
Self references are indicated.

The string returned is "Lua code", which can be procesed
(in the case in which indent is composed by spaces or "--").
Userdata and function keys and values are shown as strings,
which logically are exactly not equivalent to the original code.

This routine can serve for pretty formating tables with
proper indentations, apart from printing them:

dump(t, "t")   -- a typical use

Heavily based on "Saving tables with cycles", PIL2, p. 113.

Arguments:
t is the table.
name is the name of the table (optional)
indent is a first indentation (optional).
--]]
-- ------------------------------------------------------------------ 


function dump(_t, _name, _indent, _show_meta)
    local cart     -- a container
    local autoref  -- for self references

    --[[ counts the number of elements in a table
    local function tablecount(_t)
    local n = 0
    for _, _ in pairs(_t) do n = n+1 end
    return n
    end
    ]]
    -- (RiciLake) returns true if the table is empty
    local function isemptytable(_t) 
        return next(_t) == nil 
    end

    local function basicSerialize (o)
        local so = tostring(o)
        if type(o) == "function" then
            local info = debug.getinfo(o, "S")
            -- info.name is nil because o is not a calling level
            if info.what == "C" then
                return string.format("%q", so .. ", C function")
            else 
                -- the information is defined through lines
                return string.format("%q", so .. ", defined in (" ..
                info.linedefined .. "-" .. info.lastlinedefined ..
                ")" .. info.source)
            end
        elseif type(o) == "number" then
            return so
        else
            return string.format("%q", so)
        end
    end

    local function addtocart (_value, _name, _indent, _saved, _field, _show_meta)
        local _indent = _indent or ""
        local _saved = _saved or {}
        local _field = _field or _name
        if _show_meta == nil then
            _show_meta = true
        end

        cart = cart .. _indent .. _field

        if type(_value) ~= "table" then
            cart = cart .. " = " .. basicSerialize(_value) .. ";\n"
        else
            if _saved[_value] then
                cart = cart .. " = {}; -- " .. _saved[_value] 
                .. " (self reference)\n"
                autoref = autoref ..  _name .. " = " .. _saved[_value] .. ";\n"
            else
                local mt = nil
                if _show_meta then mt = getmetatable(_value) end
                _saved[_value] = _name

                -- if tablecount(_value) == 0 then
                if isemptytable(_value) and mt == nil then
                    cart = cart .. " = {};\n"
                else
                    cart = cart .. " = {\n"
                    -- _saved mt
                    if mt then
                        addtocart(mt, "", _indent .. "   ", {} --[[ FIXME: this may have bugs in self reference --]], "[metatable]", _show_meta)
                    end

                    -- save table if it is not empty
                    if isemptytable(_value) == false then
                        for k, v in pairs(_value) do
                            local sk = basicSerialize(k)
                            local fname = string.format("%s[%s]", _name, sk)
                            _field = string.format("[%s]", k)
                            -- three spaces between levels
                            addtocart(v, fname, _indent .. "   ", _saved, _field, _show_meta)
                        end
                    end
                    cart = cart .. _indent .. "};\n"
                end
            end
        end
    end

    _name = _name or "__unnamed__"
    if type(_t) ~= "table" then
        print (_name .. " = " .. basicSerialize(_t))
        return
    end
    cart, autoref = "", ""
    addtocart(_t, _name, _indent, {}, _name, _show_meta)
    print(cart .. autoref)
end
