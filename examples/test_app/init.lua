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
test = wiz.app.dofile("test_rect.lua") 

-- ------------------------------------------------------------------ 
-- Desc: 
local checkerboard = nil
local bg_color = { 0.5, 0.5, 0.5 }
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
    window.view.on_repaint = on_repaint

    if test.background ~= nil then 
        if test.background == "checkerboard" then 
            checkerboard = wiz.asset_db.load("assets/Checkerboard_64x64.png")
        elseif type(test.background) == "table" then
            bg_color = test.background
        end
    end

    test.init()
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

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

on_repaint = function ( _element )
    ex_c.canvas_set_blending ( ex.blend_op.add, ex.blend_mode.alpha, ex.blend_mode.inverse_alpha )
    ex_c.canvas_clear( bg_color[1], bg_color[2], bg_color[3] )

        -- background
        if checkerboard ~= nil then
            ex.canvas.color = ex.color4f.white
            local size = math.max( ex.canvas.width, ex.canvas.height )
            ex.canvas.draw_image( checkerboard, 
                                  0, 0, size, size,
                                  0, 0, checkerboard.width * 10, checkerboard.height * 10 )
        end


        --
        test.repaint(_element)

        -- ui.layout(_element)
        -- _element:debug_draw()

    ex_c.canvas_flush()
end
