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

function path.isabsolute (_p)
    -- /foo/bar
    local i = _p:find("/", 0, true )
    if i == 1 then
        return true
    end

    -- d:/foo/bar
    local i = _p:find(":/", 0, true )
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

function path.dirname (_p)
    local i = _p:findlast("/", true)
    if i then
        if i > 1 then i = i - 1 end
        return _p:sub(1, i)
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

function path.extname (_p) 
    local i = _p:findlast(".", true)
    if i then
        return _p:sub(i)
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

function path.filename (_p)
    local i = _p:findlast("[/\\]")
    if i then
        return _p:sub(i + 1)
    else
        return _p
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

function path.basename (_p) 
    local name = path.filename(_p)
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

function path.translate (_p, _sep)
    if _sep == nil then
        if ex.platform == "windows" then
            _sep = "\\"
        else
            _sep = "/"
        end
    end
    return _p:gsub("[/\\]", _sep)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function path.join (_p1, _p2)
    _p1 = _p1 or ""

    if not _p2 then
        return _p1
    end

    local len = _p1:len()
    if len > 0 and not _p1:ncmp("/", len-1, 1) then
        _p1 = _p1 .. "/"
    end

    return _p1 .. _p2
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function path.is ( _fname, _ext_list )
    local ext = path.extname(_fname)
    if type(_ext_list) == "string" then 
        return ext == _ext_list
    else
        return table.contains(_ext_list,ext)
    end
end
