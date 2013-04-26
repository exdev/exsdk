-- ======================================================================================
-- File         : main.lua
-- Author       : Wu Jie 
-- Last Change  : 02/17/2013 | 09:32:40 AM | Sunday,February
-- Description  : 
-- ======================================================================================

local asset_db = editor.asset_db

-- ------------------------------------------------------------------ 
-- Desc: 
local windowActive
local logo
local checkerboard
local box
local grossini_dance

local btfont1
local btfont2

local ttf_font1
local ttf_font2
-- ------------------------------------------------------------------ 

app.on_init = function () 
    print ( "" )
    print ( "=======================" )
    print ( "start" )
    print ( "=======================" )
    print ( "" )

    print("arguments = " .. #app.arguments)
    for i=1,#app.arguments do
        print(app.arguments[i])
    end

    editor.window( 640, 480 )

    checkerboard = asset_db.load("assets/Checkerboard_64x64.png")
    -- logo = asset_db.load("assets/ex2d_logo.png")
    -- box = asset_db.load("assets/box.png")
    -- windowActive = asset_db.load("assets/windowActive.png")

    -- grossini_dance = asset_db.load("assets/grossini_dance_09.png")
    -- btfont1 = asset_db.load("assets/BerlinSansFB_MonoOutline.bft")
    -- btfont2 = asset_db.load("assets/MolotShadow.bft")

    ttf_font1 = asset_db.load("assets/VeraMono.ttf")
    ttf_font2 = asset_db.load("assets/yahei.ttf")

    -- grossini_dance:lock( grossini_dance.width/2, grossini_dance.height/2, 10, 10 )
    -- for x=0,10 do
    --     for y=0,10 do
    --         grossini_dance:set_pixel( x, y, ex.color4f( 0.5, 0.5, 0.5, 0.5 ) )
    --     end
    -- end
    -- grossini_dance:unlock()

end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

app.on_exit = function () 
    app:close_project()

    print ( "" )
    print ( "=======================" )
    print ( "end" )
    print ( "=======================" )
    print ( "" )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

app.on_update = function ()
    -- TODO
    -- print ( "Hello World!" )
end

-- ------------------------------------------------------------------ 
-- Desc: 
local cnt = 0
-- ------------------------------------------------------------------ 

app.on_draw = function ()
    if cnt >= 1 then
        return
    end
    cnt = cnt + 1 

    local screen_center = ex.vec2f( ex.canvas.width * 0.5,
                                    ex.canvas.height * 0.5 )

    ex_c.canvas_clear( 0.5, 0.5, 0.5 )
    -- ex_c.canvas_clear( 0.0, 0.0, 0.0 )

        ex.canvas.color = ex.color4f.white

        local size = math.max( ex.canvas.width, ex.canvas.height )
        ex.canvas.draw_image( checkerboard, 
                              0, 0, size, size,
                              0, 0, checkerboard.width * 10, checkerboard.height * 10 )

        -- ttf_font1.size = 16
        -- ex.canvas.draw_outline_text( 
        --     string.format("frame = %d", cnt),
        --     ttf_font1, 
        --     ex.color4f.black,
        --     ex.color4f.white,
        --     1.0,
        --     ex.canvas.width - 100.0, 5 ) 

        -- ex.canvas.draw_image( logo, 
        --                       ex.canvas.width - 10 - logo.width * 0.5, 
        --                       ex.canvas.height - 10 - logo.height * 0.5,
        --                       logo.width * 0.5,
        --                       logo.height * 0.5 )

        -- --
        -- -- local pos1 = screen_center - ex.vec2f( grossini_dance.width, grossini_dance.height ) * 0.5
        -- local pos1 = ex.vec2f.zero
        -- ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        -- ex.canvas.draw_image( grossini_dance, pos1.x, pos1.y )

        -- --
        -- local pos2 = screen_center - ex.vec2f( grossini_dance.width, grossini_dance.height ) * 0.5
        -- -- -- local pos2 = pos1 + ex.vec2f( 0.0, grossini_dance.height ) + ex.vec2f(0.5,0.0)
        -- -- -- local pos2 = pos1 + ex.vec2f( 0.0, grossini_dance.height ) + ex.vec2f(0.5,0.0)
        -- -- local pos2 = screen_center
        -- -- -- pos2 = ex.vec2f( math.ceil(pos2.x), math.ceil(pos2.y) )
        -- ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        -- ex.canvas.draw_image( grossini_dance, pos2.x, pos2.y )

        -- ex.canvas.draw_image( btfont1.pageInfos[0], 0.0, 0.0 )
        -- ex.canvas.draw_bitmap_text( "hello world", btfont2, 100, 5 )
        -- ex.canvas.draw_bitmap_text( "Hello World!\n[OK]\n[Cancel]", btfont1, 100, 50 )

        -- ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        -- ex.canvas.draw_image_border( box, 
        --                              100, 100, 300, 300,
        --                              3, 3, 3, 3 )

        -- ex.canvas.color = ex.color4f( 1.0, 1.0, 1.0, 1.0 )
        -- ex.canvas.draw_image_border( windowActive, 
        --                              0, 0, ex.canvas.width, ex.canvas.height,
        --                              16, 16, 27, 16 )

        ttf_font1.size = 16
        ex.canvas.draw_outline_text( 
            -- "Hello World\nThis is Johnny.\nWhat the Fuck!", 
            project.cwd,
            ttf_font1, 
            ex.color4f.green,
            ex.color4f.black,
            2.0,
            10, 10 ) 

        ttf_font1.size = 18
        ex.canvas.draw_shadow_text( 
            -- "Hello World\nThis is Johnny.\nWhat the Fuck!", 
            app.cwd,
            ttf_font1, 
            ex.color4f.red,
            ex.color4f.black,
            ex.vec2f(1,1),
            10, 30 ) 

        -- ttf_font1.size = 20
        -- ex.canvas.draw_outline_text( 
        --     "abcdefghijklmnopqrstuvwxyz", 
        --     ttf_font1, 
        --     ex.color4f.black,
        --     ex.color4f.yellow,
        --     1.0,
        --     10, 10 ) 

        -- ttf_font1.size = 30
        -- ex.canvas.draw_outline_text( 
        --     "abcdefghijklmnopqrstuvwxyz", 
        --     ttf_font1, 
        --     ex.color4f.green,
        --     ex.color4f.black,
        --     2.0,
        --     10, 50 ) 

        -- ttf_font1.size = 40
        -- ex.canvas.draw_outline_text( 
        --     "abcdefghijklmnopqrstuvwxyz", 
        --     ttf_font1, 
        --     ex.color4f.white,
        --     ex.color4f.red,
        --     2.0,
        --     10, 100 ) 

        -- -- ======================================================== 
        -- -- 
        -- -- ======================================================== 

        -- local lines = {}
        -- file = io.open( asset_db.fullpath("assets/content.txt"), "r" )
        -- for line in file:lines() do 
        --     table.add( lines, line )
        -- end
        -- file:close()

        -- ttf_font2.size = 20
        -- for i=1,#lines do 
        --     line = lines[i]
        --     ex.canvas.draw_outline_text( 
        --         line, 
        --         ttf_font2, 
        --         ex.color4f.white,
        --         ex.color4f.black,
        --         1.0,
        --         10, 200 ) 
        -- end

    ex_c.canvas_flush()
end
