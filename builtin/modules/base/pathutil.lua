-- ======================================================================================
-- File         : pathutil.lua
-- Author       : Wu Jie 
-- Last Change  : 12/18/2013 | 17:36:52 PM | Wednesday,December
-- Description  : 
-- ======================================================================================

pathutil = pathutil or {}

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
pathutil.sep = sep

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function pathutil.isabsolute (p)
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

function pathutil.dirname (p)
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

function pathutil.extname (p) 
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

function pathutil.filename (p)
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

function pathutil.basename (p) 
    local name = pathutil.filename(p)
    local i = name:findlast(".", true)
    if i then
        return name:sub(1,i-1)
    else
        return name
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
--      pathutil.translate("assets/foo/bar/foobar.txt","\\") 
--          ==> "assets\\foo\\bar\\foobar.txt" 
-- ------------------------------------------------------------------ 

function pathutil.translate (p, sep)
    sep = sep or pathutil.sep
    return p:gsub("[/\\]", sep)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function pathutil.join (p1, p2)
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

function pathutil.is ( fname, extList )
    local ext = pathutil.extname(fname)
    if type(extList) == "string" then 
        return ext == extList
    else
        return table.contains(extList,ext)
    end
end
