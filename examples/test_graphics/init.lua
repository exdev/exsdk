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
        ex.painter.color = ex.color4f.white
        ex.painter.bitmap_text( "Hello World", font2, 10, 10 )

        ex.painter.color = ex.color4f.green
        ex.painter.text( "Hello World", font1, 100, 100 )

        ex.painter.color = ex.color4f.white
        local size = { w = logo.width, h = logo.height } 
        ex.painter.image( logo, 
                          _self.width - 10 - size.w, 
                          _self.height - 10 - size.h,
                          size.w,
                          size.h )
    end


    -- create window 2
    local window2 = wiz.ui_window( 400, 800 )
    window2.background = { 0, 128, 255 }
    window2.on_repaint = function ( _self )
        ex.painter.color = ex.color4f.white
        ex.painter.bitmap_text( "Hello World", font2, 10, 10 )
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
