-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 09:32:40 AM | Sunday,February
-- Description  : 
-- ======================================================================================

local asset_db = editor.asset_db

local windowActive
local logo
local checkerboard
local box
local grossini_dance

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

    checkerboard = asset_db.load("Checkerboard_64x64.png")
    logo = asset_db.load("ex2d_logo.png")
    box = asset_db.load("box.png")
    windowActive = asset_db.load("windowActive.png")

    grossini_dance = asset_db.load("grossini_dance_09.png")
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
    if cnt >= 1 then
        return
    end
    cnt = cnt + 1 

    local screen_center = ex.vec2f( ex.canvas.width * 0.5,
                                    ex.canvas.height * 0.5 )

    ex_c.canvas_clear( 0.5, 0.5, 0.5 )
    -- ex_c.canvas_clear( 0.0, 0.0, 0.0 )

        -- local size = math.max( ex.canvas.width, ex.canvas.height )
        -- ex.canvas.draw_image( checkerboard, 
        --                       0, 0, size, size,
        --                       0, 0, checkerboard.width * 10, checkerboard.height * 10 )
        -- ex.canvas.draw_image( logo, 
        --                       ex.canvas.width - 10 - logo.width * 0.5, 
        --                       ex.canvas.height - 10 - logo.height * 0.5,
        --                       logo.width * 0.5,
        --                       logo.height * 0.5 )

        --
        -- local pos1 = screen_center - ex.vec2f( grossini_dance.width, grossini_dance.height ) * 0.5
        local pos1 = ex.vec2f.zero
        ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        ex.canvas.draw_image( grossini_dance, pos1.x, pos1.y )

        --
        local pos2 = screen_center - ex.vec2f( grossini_dance.width, grossini_dance.height ) * 0.5
        -- -- local pos2 = pos1 + ex.vec2f( 0.0, grossini_dance.height ) + ex.vec2f(0.5,0.0)
        -- -- local pos2 = pos1 + ex.vec2f( 0.0, grossini_dance.height ) + ex.vec2f(0.5,0.0)
        -- local pos2 = screen_center
        -- -- pos2 = ex.vec2f( math.ceil(pos2.x), math.ceil(pos2.y) )
        ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        ex.canvas.draw_image( grossini_dance, pos2.x, pos2.y )

        -- ex.canvas.draw_image( btfont1.pageInfos[0], 0.0, 0.0 )
        ex.canvas.draw_bitmap_text( "Hello World!\n[OK]\n[Cancel]", btfont1, 100, 10 )

        ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        ex.canvas.draw_image_border( box, 
                                     100, 100, 300, 300,
                                     3, 3, 3, 3 )

        ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        ex.canvas.draw_image_border( windowActive, 
                                     0, 0, ex.canvas.width, ex.canvas.height,
                                     16, 16, 27, 16 )

    ex_c.canvas_flush()
end
