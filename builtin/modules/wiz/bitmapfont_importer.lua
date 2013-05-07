-- ======================================================================================
-- File         : bitmapfont_importer.lua
-- Author       : Wu Jie 
-- Last Change  : 02/20/2013 | 13:48:36 PM | Wednesday,February
-- Description  : 
-- ======================================================================================

local __M = {}

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function create_pattern () 
    local space = lpeg.space^0
    local name = lpeg.C(lpeg.alpha^1) * space
    local range = lpeg.graph - lpeg.S("\"")
    local value = lpeg.S("\"")^0 * lpeg.C(range^1) * lpeg.S("\"")^0 * space
    local sep = lpeg.S(",;") * space
    local value_pair = lpeg.Cg(name * "=" * space * value) * sep^-1
    local command_pair = lpeg.Cg(lpeg.Cc("command") * name) * sep^-1
    return lpeg.Cf(lpeg.Ct("") * command_pair^-1 * value_pair^0, rawset)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function convert ( _from, _keys, _func ) 
    local to = {}
    for i=1,#_keys do
        local k = _keys[i]
        to[k] = _func( k, _from[k] )
    end
    return to
end

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

local bitmapfont_importer = wiz.importer.extend ({
    __typename = "bitmapfont_importer",

    -- constructor & destructor
    __init = function ( _self, _path )
        checkarg(_path,"string")

        _self.path = _path
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {
        _pattern = create_pattern(),
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    exec = function (_self)
        local asset_db = wiz.asset_db
        local files = asset_db.files_in(_self.path)
        local file = nil

        -- get the first txt/fnt file
        for i=1,#files do
            local filename = files[i]
            if path.is( filename, {".txt",".fnt"} ) then
                file = io.open( asset_db.fullpath(path.join(_self.path,filename)), "r" )
                break
            end
        end
        assert ( file, string.format("Can't find .txt/.fnt file at %s", _self.path) )

        -- instantiate a bitmapfont for parsing
        local btfont = ex.bitmapfont.new()

        -- parse the bitmapfont txt file
        local pattern = wiz.bitmapfont_importer._pattern
        for line in file:lines() do 
            local t = pattern:match(line)

            -- parse the basic info
            if t.command == "info" then
                local info = convert ( 
                                 t, 
                                 { "face", "size", "bold", "italic", "unicode", "smooth", "aa" },
                                 function (_k,_text)
                                     if _k == "size" then
                                         return tonumber(_text) 
                                     elseif _k == "bold" 
                                         or _k == "italic" 
                                         or _k == "unicode" 
                                         or _k == "smooth" 
                                         or _k == "aa" then
                                         return tonumber(_text) == 1 
                                     end
                                     return _text
                                 end 
                             )
                 btfont.faceName = info.face
                 btfont.size = info.size
                 btfont.isBold = info.bold
                 btfont.isItalic = info.italic
                 btfont.isUnicode = info.unicode
                 btfont.isSmooth = info.smooth
                 btfont.isAA = info.aa

            -- parse the common
            elseif t.command == "common" then
                local info = convert ( 
                                 t, 
                                 { "lineHeight", "pages", "scaleW", "scaleH" },
                                 function (_k,_text)
                                     return tonumber(_text) 
                                 end 
                             )
                 btfont.lineHeight = info.lineHeight
                 btfont.pages = info.pages
                 btfont.pageWidth = info.scaleW
                 btfont.pageHeight = info.scaleH

            -- parse the page
            elseif t.command == "page" then
                local pageinfo = convert ( 
                                     t, 
                                     { "id", "file" },
                                     function (_k,_text) 
                                         if _k == "id" then 
                                             return tonumber(_text) 
                                         end
                                         return _text
                                     end 
                                 )
                assert ( pageinfo.file ~= nil and
                         pageinfo.file ~= "", 
                         "Can't find image file in pageinfo" )
                imagefile = path.join(_self.path,pageinfo.file)
                if asset_db.exists( imagefile ) then
                    btfont.pageInfos[pageinfo.id] = asset_db.load(imagefile)
                end

            -- parse the char info
            elseif t.command == "char" then
                local charinfo = convert ( 
                                     t, 
                                     { "id", "x", "y", "width", "height", "xoffset", "yoffset", "xadvance", "page" },
                                     function (_k,_text) 
                                         return tonumber(_text) 
                                     end 
                                 )
                btfont.charInfos[charinfo.id] = charinfo

            -- parse the kernings
            elseif t.command == "kernings" then
                if tonumber(t.count) ~= 0 then 
                    btfont.hasKerning = true
                end

            -- parse the kerning info
            elseif t.command == "kerning" then
                local kerningInfo = convert ( 
                                     t, 
                                     { "first", "second", "amount" },
                                     function (_k,_text) 
                                         return tonumber(_text) 
                                     end 
                                 )
                table.add( btfont.kerningInfos, kerningInfo )
            end
        end

        file:close()

        --
        return btfont
    end,
})
__M.bitmapfont_importer = bitmapfont_importer

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
