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

local function create_pattern () 
    local space = lpeg.space^0
    local name = lpeg.C(lpeg.alpha^1) * space
    local value = lpeg.C(lpeg.graph^1) * space
    local sep = lpeg.S(",;") * space
    local value_pair = lpeg.Cg(name * "=" * space * value) * sep^-1
    local command_pair = lpeg.Cg(lpeg.Cc("command") * name) * sep^-1
    return lpeg.Cf(lpeg.Ct("") * command_pair^-1 * value_pair^0, rawset)
end

--/////////////////////////////////////////////////////////////////////////////
-- 
--/////////////////////////////////////////////////////////////////////////////

local bitmapfont_importer = editor.importer.extend ({
    __typename = "bitmapfont_importer",

    -- constructor & destructor
    __init = function ( _self, _path )
        assert ( type(_path) == "string", "Type error: _path must be path" )
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

    _gen_table = function ( _self, _table, _keys, _func ) 
        local t = {}
        for i=1,#_keys do
            local k = _keys[i]
            t[k] = _func( k, _table[_keys] )
        end
        return t
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    exec = function (_self)
        local asset_db = editor.asset_db
        local asset_path = asset_db.fullpath(_self.path)
        local files = ex_c.fsys_files_in(asset_path)
        local file = nil

        -- get the first txt/fnt file
        for i=1,#files do
            local filename = files[i]
            if path.is( filename, {".txt",".fnt"} ) then
                file = io.open( asset_db.fullpath(path.join(_self.path,filename)), "r" )
                break
            end
        end
        assert ( file, string.format("Can't find .txt/.fnt file at %s", asset_path) )

        -- instantiate a bitmapfont for parsing
        local btfont = ex.bitmapfont.new()

        -- parse the bitmapfont txt file
        local pattern = editor.bitmapfont_importer._pattern
        for line in file:lines() do 
            local t = pattern:match(line)

            -- parse the basic info
            if t.command == "info" then
                local info = _self:_gen_table ( 
                                     t, 
                                     { "name", "size", "isBold", "isItalic", "isUnicode", "isSmooth", "isAA", "charset" },
                                     function (_k,_text)
                                         if _k == "size" then
                                             return tonumber(_text) 
                                         elseif _k == "isBold" 
                                             or _k == "isItalic" 
                                             or _k == "isUnicode" 
                                             or _k == "isSmooth" 
                                             or _k == "isAA" then
                                             return tonumber(_text) == 1 
                                         end
                                         return _text
                                     end 
                                 )
                 table.add( btfont, info )

            -- parse the char info
            elseif t.command == "char" then
                local charinfo = _self:_gen_table ( 
                                     t, 
                                     { "id", "x", "y", "width", "height", "xoffset", "yoffset", "xadvance", "page" },
                                     function (_k,_text) return tonumber(_text) end 
                                 )
                btfont.charInfos[charinfo.id] = charinfo

            -- parse the page
            elseif t.command == "page" then
                local pageinfo = _self:_gen_table ( 
                                     t, 
                                     { "id", "file" },
                                     function (_k,_text) 
                                         if _k == "id" then return tonumber(_text) end
                                         return _text
                                     end 
                                 )

                imagefile = path.join(_self.path,pageinfo.file)
                if asset_db.exists( imagefile ) then
                    btfont.pageInfos[pageinfo.id] = asset_db.load(imagefile)
                end
            end
        end

        --
        return btfont
    end,
})
__M.bitmapfont_importer = bitmapfont_importer

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

return __M
