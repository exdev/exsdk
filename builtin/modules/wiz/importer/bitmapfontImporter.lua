-- ======================================================================================
-- File         : bitmapfontImporter.lua
-- Author       : Wu Jie 
-- Last Change  : 12/09/2013 | 11:27:18 AM | Monday,December
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local function createPattern () 
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

wiz.bitmapfontImporter = wiz.importer.extend ({
    __typename = "bitmapfontImporter",

    -- constructor & destructor
    __init = function ( _self, _bundle, _path )
        super(_self).__init( _self, _bundle, _path )
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- static 
    --/////////////////////////////////////////////////////////////////////////////

    __static = {
        _pattern = createPattern(),
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
        local files = _self.bundle:filesIn(_self.path)
        local file = nil

        -- get the first txt/fnt file
        for i=1,#files do
            local filename = files[i]
            if path.is( filename, {".txt",".fnt"} ) then
                file = io.open( _self.bundle:osPath(path.join(_self.path,filename)), "r" )
                break
            end
        end
        assert ( file, string.format("Can't find .txt/.fnt file at %s", _self.path) )

        -- instantiate a bitmapfont for parsing
        local bpfont = ex.bitmapfont.new()

        -- parse the bitmapfont txt file
        local pattern = wiz.bitmapfontImporter._pattern
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
                 bpfont.faceName = info.face
                 bpfont.size = info.size
                 bpfont.isBold = info.bold
                 bpfont.isItalic = info.italic
                 bpfont.isUnicode = info.unicode
                 bpfont.isSmooth = info.smooth
                 bpfont.isAA = info.aa

            -- parse the common
            elseif t.command == "common" then
                local info = convert ( 
                                 t, 
                                 { "lineHeight", "pages", "scaleW", "scaleH" },
                                 function (_k,_text)
                                     return tonumber(_text) 
                                 end 
                             )
                 bpfont.lineHeight = info.lineHeight
                 bpfont.pages = info.pages
                 bpfont.pageWidth = info.scaleW
                 bpfont.pageHeight = info.scaleH

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
                if _self.bundle:exists( imagefile ) then
                    bpfont.pageInfos[pageinfo.id] = _self.bundle:load(imagefile)
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
                bpfont.charInfos[charinfo.id] = charinfo

            -- parse the kernings
            elseif t.command == "kernings" then
                if tonumber(t.count) ~= 0 then 
                    bpfont.hasKerning = true
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
                table.add( bpfont.kerningInfos, kerningInfo )
            end
        end

        file:close()

        --
        return bpfont
    end,
})
