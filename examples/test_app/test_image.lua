-- ======================================================================================
-- File         : test_image.lua
-- Author       : Wu Jie 
-- Last Change  : 05/09/2013 | 20:06:32 PM | Thursday,May
-- Description  : 
-- ======================================================================================

local assets = wiz.assets

local logo
local grossini_dance

return {

    background = "checkerboard",
    width = 800,
    height = 600,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function ( _root_el ) 
        -- load image
        logo = assets.load("assets/ex2d_logo.png")
        grossini_dance = assets.load("assets/grossini_dance_09.png")

        -- grossini_dance:lock( grossini_dance.width/2, grossini_dance.height/2, 10, 10 )
        -- for x=0,10 do
        --     for y=0,10 do
        --         grossini_dance:set_pixel( x, y, ex.color4f( 0.5, 0.5, 0.5, 0.5 ) )
        --     end
        -- end
        -- grossini_dance:unlock()
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
        local x, y = 10, 10

        -- logo
        ex.canvas.color = ex.color4f.white
        local size = { w = logo.width * 0.6, h = logo.height * 0.6 } 
        ex.canvas.draw_image( logo, 
                              ex.canvas.width - 10 - size.w, 
                              ex.canvas.height - 10 - size.h,
                              size.w,
                              size.h )

        -- ======================================================== 
        -- test transparent 
        -- ======================================================== 

        -- 
        ex.canvas.color = ex.color4f.white
        ex.canvas.draw_image( grossini_dance, x, y )

        --
        x = x + grossini_dance.width + 10
        ex.canvas.color = ex.color4f.red
        ex.canvas.draw_image( grossini_dance, x, y )

        --
        x = x + grossini_dance.width + 10
        ex.canvas.color = ex.color4f ( 1.0, 1.0, 1.0, 0.4 )
        ex.canvas.draw_image( grossini_dance, x, y )
    end
}

