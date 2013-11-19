-- ======================================================================================
-- File         : init.lua
-- Author       : Wu Jie 
-- Last Change  : 11/19/2013 | 16:03:32 PM | Tuesday,November
-- Description  : 
-- ======================================================================================

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

wiz.on_init = function () 
    print ( "" )
    print ( "=======================" )
    print ( "start" )
    print ( "=======================" )
    print ( "" )

    print("arguments = " .. #wiz.arguments)
    for i=1,#wiz.arguments do
        print(wiz.arguments[i])
    end

    -- create window
    local window = wiz.ui_window( 640, 480 )

    -- load resource, NOTE: texture resource must be load after first window created
    local font1 = wiz.assets.load("assets/VeraMono.ttf")
    local font2 = wiz.assets.load("assets/BerlinSansFB_MonoOutline.bft")
    local font3 = wiz.assets.load("assets/MolotShadow.bft")
    local logo = wiz.assets.load("assets/ex2d_logo.png")

    --
    window.on_repaint = function ( _self )
        ex.canvas.color = ex.color4f.white
        ex.canvas.draw_bitmap_text( "Hello World", font2, 10, 10 )

        ex.canvas.color = ex.color4f.green
        ex.canvas.draw_text( "Hello World", font1, 100, 100 )

        ex.canvas.color = ex.color4f.white
        local size = { w = logo.width * 0.6, h = logo.height * 0.6 } 
        ex.canvas.draw_image( logo, 
                              ex.canvas.width - 10 - size.w, 
                              ex.canvas.height - 10 - size.h,
                              size.w,
                              size.h )
    end
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

wiz.on_exit = function () 
    wiz:close_app()

    print ( "" )
    print ( "=======================" )
    print ( "end" )
    print ( "=======================" )
    print ( "" )
end
