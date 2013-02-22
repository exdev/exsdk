-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 09:32:40 AM | Sunday,February
-- Description  : 
-- ======================================================================================

local asset_db = editor.asset_db

local tex1
local btfont1
local btfont2

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function init() 
    print ( "" )
    print ( "=======================" )
    print ( "start" )
    print ( "=======================" )
    print ( "" )

    tex1 = asset_db.load("grossini_dance_09.png")
    btfont1 = asset_db.load("BerlinSansFB_MonoOutline.bft")
    btfont2 = asset_db.load("MolotShadow.bft")
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function deinit() 
    ex_c.close_project()

    print ( "" )
    print ( "=======================" )
    print ( "end" )
    print ( "=======================" )
    print ( "" )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function update()
    -- TODO
    -- print ( "Hello World!" )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local cnt = 0
function render()
    -- if cnt >= 1 then
    --     return
    -- end

    ex_c.canvas_clear( 0.5, 0.5, 0.5 )

    -- ex.canvas.draw_texture( ex.vec2f(0.0,0.0), btfont2.pageInfos[0] )
    -- ex.canvas.draw_texture( ex.vec2f(0.0,0.0), tex1 )
    ex.canvas.draw_text( ex.vec2f(0.0,0.0), btfont1, "Hello World " )
    -- ex.canvas.draw_texture( ex.vec2f(0.0,50.0), btfont1.pageInfos[0] )

    ex_c.canvas_flush()

    cnt = cnt + 1 
end
