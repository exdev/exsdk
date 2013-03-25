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

    -- canvas.init()

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

    local screen_center = ex.vec2f( ex.canvas.width() * 0.5,
                                    ex.canvas.height() * 0.5 )

    ex_c.canvas_clear( 0.5, 0.5, 0.5 )
    -- ex_c.canvas_clear( 0.0, 0.0, 0.0 )
    ex_c.canvas_set_blending ( ex.blend_op.add 
                             , ex.blend_mode.alpha
                             , ex.blend_mode.inverse_alpha )

        -- local pos1 = screen_center - ex.vec2f( img1.width, img1.height ) * 0.5
        -- local pos1 = ex.vec2f.zero
        -- ex.canvas.draw_texture( pos1, -- destination 
        --                         ex.vec2f(0.0,0.0), -- anchor
        --                         ex.vec2f(1.0,1.0), -- scale 
        --                         0.0,               -- angle in degrees
        --                         ex.color4f( 1.0, 1.0, 1.0, 1.0 ), -- color
        --                         img1 )

        local pos2 = screen_center - ex.vec2f( img1.width, img1.height ) * 0.5
        -- -- local pos2 = pos1 + ex.vec2f( 0.0, img1.height ) + ex.vec2f(0.5,0.0)
        -- -- local pos2 = pos1 + ex.vec2f( 0.0, img1.height ) + ex.vec2f(0.5,0.0)
        -- local pos2 = screen_center
        -- -- pos2 = ex.vec2f( math.ceil(pos2.x), math.ceil(pos2.y) )
        -- ex.canvas.draw_texture( pos2, -- destination 
        --                         ex.vec2f(img1.width, img1.height) * 0.5, -- anchor
        --                         ex.vec2f(1.0,1.0), -- scale 
        --                         0.0,               -- angle in degrees
        --                         ex.color4f( 1.0, 1.0, 1.0, 1.0 ), -- color
        --                         img1 )
        -- -- ex.canvas.draw_texture( ex.vec2f(0.0,0.0), btfont2.pageInfos[0] )
        -- -- ex.canvas.draw_text( ex.vec2f(0.0,0.0), btfont1, "Hello World " )
        -- -- ex.canvas.draw_texture( ex.vec2f(0.0,50.0), btfont1.pageInfos[0] )

        ex_c.gui_draw_texture ( img1._cptr,
                                pos2.x, pos2.y, img1.width, img1.height,
                                0, 0, 0, 0,
                                0, 0, img1.width, img1.height,
                                1.0, 1.0, 1.0, 1.0 )

    ex_c.canvas_flush()
end
