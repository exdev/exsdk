-- ======================================================================================
-- File         : debug.lua
-- Author       : Wu Jie 
-- Last Change  : 09/13/2010 | 10:59:05 AM | Monday,September
-- Description  : 
-- ======================================================================================

debug = debug or {}

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

debug.dump(t, "t")   -- a typical use

Heavily based on "Saving tables with cycles", PIL2, p. 113.

Arguments:
t is the table.
name is the name of the table (optional)
indent is a first indentation (optional).
--]]
-- ------------------------------------------------------------------ 

function debug.dump(t, name, indent, showMeta)
    local cart     -- a container
    local autoref  -- for self references

    --[[ counts the number of elements in a table
    local function tablecount(t)
        local n = 0
        for _, _ in pairs(t) do n = n+1 end
        return n
    end
    ]]
    -- returns true if the table is empty
    local function isemptytable(t) 
        return next(t) == nil 
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

    local function addtocart (value, name, indent, saved, field, showMeta)
        local indent = indent or ""
        local saved = saved or {}
        local field = field or name
        if showMeta == nil then showMeta = true end

        cart = cart .. indent .. field

        if type(value) ~= "table" then
            cart = cart .. " = " .. basicSerialize(value) .. ";\n"
        else
            if saved[value] then
                cart = cart .. " = {}; -- " .. saved[value] 
                .. " (self reference)\n"
                autoref = autoref ..  name .. " = " .. saved[value] .. ";\n"
            else
                local mt = nil
                if showMeta then mt = getmetatable(value) end
                saved[value] = name

                -- if tablecount(value) == 0 then
                if isemptytable(value) and mt == nil then
                    cart = cart .. " = {};\n"
                else
                    cart = cart .. " = {\n"
                    -- saved mt
                    if mt then
                        addtocart(mt, "", indent .. "   ", {} --[[ FIXME: this may have bugs in self reference --]], "[metatable]", showMeta)
                    end

                    -- save table if it is not empty
                    if isemptytable(value) == false then
                        for k, v in pairs(value) do
                            local sk = basicSerialize(k)
                            local fname = string.format("%s[%s]", name, sk)
                            field = string.format("[%s]", k)
                            -- three spaces between levels
                            addtocart(v, fname, indent .. "   ", saved, field, showMeta)
                        end
                    end
                    cart = cart .. indent .. "};\n"
                end
            end
        end
    end

    name = name or "__unnamed__"
    if type(t) ~= "table" then
        print (name .. " = " .. basicSerialize(t))
        return
    end
    cart, autoref = "", ""
    addtocart(t, name, indent, {}, name, showMeta)
    print(cart .. autoref)
end
