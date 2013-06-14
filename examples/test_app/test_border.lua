-- ======================================================================================
-- File         : test_border.lua
-- Author       : Wu Jie 
-- Last Change  : 05/09/2013 | 20:14:42 PM | Thursday,May
-- Description  : 
-- ======================================================================================

local asset_db = wiz.asset_db

local windowActive
local box

return {

    background = "checkerboard",
    width = 800,
    height = 600,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function ( _root_el ) 
        -- load image
        box = asset_db.load("assets/box.png")
        windowActive = asset_db.load("assets/windowActive.png")
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
        local x, y = 10, 10

        -- ======================================================== 
        -- test transparent 
        -- ======================================================== 

        ex.canvas.color = ex.color4f.white
        ex.canvas.draw_image_border( box, 
                                     x, y, 300, 300,
                                     3, 3, 3, 3 )

        x = x + 300 + 10
        ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        ex.canvas.draw_image_border( windowActive, 
                                     x, y, 400, 300,
                                     27, 16, 16, 16 )
    end
}

