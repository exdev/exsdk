-- ======================================================================================
-- File         : test_rect.lua
-- Author       : Wu Jie 
-- Last Change  : 05/09/2013 | 20:18:52 PM | Thursday,May
-- Description  : 
-- ======================================================================================

return {

    background = "checkerboard",
    width = 800,
    height = 600,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    init = function () 
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    repaint = function ( _root_el )
        local x, y = 10, 10
        local w, h = 180, 30

        -- ======================================================== 
        -- 
        -- ======================================================== 

        ex.canvas.color = ex.color4f.black
        ex.canvas.draw_rect ( x, y, w, h )

        ex.canvas.color = ex.color4f ( 1.0, 0.0, 1.0, 0.6 )
        ex.canvas.draw_filled_rect ( x, y, w, h )

        -- ======================================================== 
        -- 
        -- ======================================================== 

        y = y + 45
        ex.canvas.color = ex.color4f.black
        ex.canvas.draw_rect ( x, y, w, h, 5 )

        ex.canvas.color = ex.color4f ( 1.0, 1.0, 0.0, 0.6 )
        ex.canvas.draw_filled_rect ( x, y, w, h )

        x = x + w + 10
        ex.canvas.color = ex.color4f.blue
        ex.canvas.draw_rect ( x, y, w, h, 10 )

        x = 10
        y = y + h + 10
        ex.canvas.color = ex.color4f.red
        ex.canvas.draw_rect ( x, y, w, h, 8 )
    end
}

