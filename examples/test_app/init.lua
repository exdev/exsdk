-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 09:32:40 AM | Sunday,February
-- Description  : 
-- ======================================================================================

-- test = wiz.dofile("test_ttf_font.lua") 
-- test = wiz.dofile("test_bitmap_font.lua") 
-- test = wiz.dofile("test_image.lua") 
-- test = wiz.dofile("test_border.lua") 
-- test = wiz.dofile("test_rect.lua") 
test = wiz.dofile("test_layout.lua") 
-- test = wiz.dofile("test_css.lua") 

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

wiz.onInit = function () 
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
    local window = wiz.window( test.width or 640, test.height or 480 )
    window.root:set_dirty()

    local draw = window.root.draw
    window.root.draw = function ( _el )
        draw(_el)
        test.repaint(_el)
        -- _el:debug_draw()
    end

    if test.background ~= nil then 
        if test.background == "checkerboard" then 
            window.background = wiz.assets.load("assets/Checkerboard_64x64.png")
        elseif type(test.background) == "table" then
            window.background = test.background
        end
    end

    wiz.assets.load("assets/VeraMono.ttf")

    --
    test.init( window.root )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

wiz.onExit = function () 
    wiz:close_app()

    print ( "" )
    print ( "=======================" )
    print ( "end" )
    print ( "=======================" )
    print ( "" )
end
