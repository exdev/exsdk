-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 09:32:40 AM | Sunday,February
-- Description  : 
-- ======================================================================================

-- test = wiz.app.dofile("test_ttf_font.lua") 
-- test = wiz.app.dofile("test_bitmap_font.lua") 
-- test = wiz.app.dofile("test_image.lua") 
-- test = wiz.app.dofile("test_border.lua") 
-- test = wiz.app.dofile("test_rect.lua") 
-- test = wiz.app.dofile("test_layout.lua") 
test = wiz.app.dofile("test_css.lua") 

-- ------------------------------------------------------------------ 
-- Desc: 
local old_draw
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
    local window = wiz.window( test.width or 640, test.height or 480 )
    window.view = ui.element()
    window.view:set_dirty()

    local draw = window.view.draw
    window.view.draw = function ( _view )
        draw(_view)
        test.repaint(_view)

        -- ui.layout(_view)
        -- _view:debug_draw()
    end

    if test.background ~= nil then 
        if test.background == "checkerboard" then 
            window.background = wiz.asset_db.load("assets/Checkerboard_64x64.png")
        elseif type(test.background) == "table" then
            window.background = test.background
        end
    end

    --
    test.init( window.view )
    ui.layout(window.view)
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
