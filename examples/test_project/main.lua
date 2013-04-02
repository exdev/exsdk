-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 09:32:40 AM | Sunday,February
-- Description  : 
-- ======================================================================================

local asset_db = editor.asset_db

local img1
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

    img1 = asset_db.load("grossini_dance_09.png")
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
    cnt = cnt + 1 

    local screen_center = ex.vec2f( ex.canvas.width * 0.5,
                                    ex.canvas.height * 0.5 )

    ex_c.canvas_clear( 0.5, 0.5, 0.5 )
    -- ex_c.canvas_clear( 0.0, 0.0, 0.0 )

        --
        -- local pos1 = screen_center - ex.vec2f( img1.width, img1.height ) * 0.5
        local pos1 = ex.vec2f.zero
        ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        ex.canvas.draw_image( img1, pos1.x, pos1.y )

        --
        local pos2 = screen_center - ex.vec2f( img1.width, img1.height ) * 0.5
        -- -- local pos2 = pos1 + ex.vec2f( 0.0, img1.height ) + ex.vec2f(0.5,0.0)
        -- -- local pos2 = pos1 + ex.vec2f( 0.0, img1.height ) + ex.vec2f(0.5,0.0)
        -- local pos2 = screen_center
        -- -- pos2 = ex.vec2f( math.ceil(pos2.x), math.ceil(pos2.y) )
        ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        ex.canvas.draw_image( img1, pos2.x, pos2.y )

        -- ex.canvas.draw_image( btfont1.pageInfos[0], 0.0, 0.0 )
        ex.canvas.draw_bitmap_text( "Hello World", btfont1, 50, 10 )
        ex.canvas.draw_bitmap_text( "hello world", btfont2, 50, 50 )

    ex_c.canvas_flush()
end
