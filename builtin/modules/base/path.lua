-- ======================================================================================
-- File         : path.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 18:26:39 PM | Sunday,February
-- Description  : 
-- ======================================================================================

path = path or {}

--/////////////////////////////////////////////////////////////////////////////
-- functions
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local sep = "/"
if os.platform == "windows" then
    sep = "\\"
end
path.sep = sep

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function path.isabsolute (p)
    -- /foo/bar
    local i = p:find("/", 0, true )
    if i == 1 then
        return true
    end

    -- d:/foo/bar
    local i = p:find(":/", 0, true )
    if i ~= nil then
        return true
    end

    return false
end

-- ------------------------------------------------------------------ 
-- Desc: 
--      "assets/foo/bar/foobar.txt" ==> "assets/foo/bar/" 
--      "assets/foo/bar/foobar" ==> "assets/foo/bar/" 
--      "assets/foo/bar/.foobar" ==> "assets/foo/bar/" 
--      "assets/foo/bar/.foobar/" ==> "assets/foo/bar/.foobar/" 
--      "foobar.txt" ==> "" 
--      "foobar" ==> "" 
--      "foobar/" ==> "foobar/" 
-- ------------------------------------------------------------------ 

function path.dirname (p)
    local i = p:findlast("/", true)
    if i then
        if i > 1 then i = i - 1 end
        return p:sub(1, i)
    else
        return "."
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
--      "assets/foo/bar/foobar.txt" ==> ".txt" 
--      "assets/foo/bar/foobar" ==> "" 
--      "assets/foo/bar/.foobar" ==> "" 
--      "foobar.txt" ==> ".txt" 
--      "foobar" ==> "" 
--      "foobar/" ==> "" 
-- ------------------------------------------------------------------ 

function path.extname (p) 
    local i = p:findlast(".", true)
    if i then
        return p:sub(i)
    else
        return ""
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
--      "assets/foo/bar/foobar.txt" ==> "foobar.txt" 
--      "assets/foo/bar/foobar" ==> "foobar" 
--      "assets/foo/bar/.foobar" ==> ".foobar" 
--      "foobar.txt" ==> "foobar.txt" 
--      "foobar" ==> "foobar" 
--      "foobar/" ==> "" 
-- ------------------------------------------------------------------ 

function path.filename (p)
    local i = p:findlast("[/\\]")
    if i then
        return p:sub(i + 1)
    else
        return p
    end
end

-- ------------------------------------------------------------------ 
-- Desc: filename without extension
--      "assets/foo/bar/foobar.txt" ==> "foobar" 
--      "assets/foo/bar/foobar" ==> "foobar" 
--      "assets/foo/bar/.foobar" ==> ".foobar" 
--      "foobar.txt" ==> "foobar" 
--      "foobar" ==> "foobar" 
--      "foobar/" ==> "" 
-- ------------------------------------------------------------------ 

function path.basename (p) 
    local name = path.filename(p)
    local i = name:findlast(".", true)
    if i then
        return name:sub(1,i-1)
    else
        return name
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
--      path.translate("assets/foo/bar/foobar.txt","\\") 
--          ==> "assets\\foo\\bar\\foobar.txt" 
-- ------------------------------------------------------------------ 

function path.translate (p, sep)
    sep = sep or path.sep
    return p:gsub("[/\\]", sep)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function path.join (p1, p2)
    p1 = p1 or ""

    if not p2 then
        return p1
    end

    local len = p1:len()
    if len > 0 and not p1:ncmp("/", len-1, 1) then
        p1 = p1 .. "/"
    end

    return p1 .. p2
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function path.is ( fname, extList )
    local ext = path.extname(fname)
    if type(extList) == "string" then 
        return ext == extList
    else
        return table.contains(extList,ext)
    end
end
