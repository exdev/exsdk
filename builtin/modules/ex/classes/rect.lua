-- ======================================================================================
-- File         : rect.lua
-- Author       : Wu Jie 
-- Last Change  : 04/01/2013 | 20:02:19 PM | Monday,April
-- Description  : 
-- ======================================================================================

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

ex.rect = class ({
    __typename = "rect",
    __isvalue = true,

    -- constructor & destructor
    __init = function ( self, x, y, w, h )
        checkarg(x,"number")
        checkarg(y,"number")
        checkarg(w,"number")
        checkarg(h,"number")

        self.x = x
        self.y = y
        self.width = w
        self.height = h
    end,

    -- meta-methods
    __tostring = function (op)
        return string.format ( "{ %.3f, %.3f, %.3f, %.3f }", op.x, op.y, op.width, op.height )
    end,
    __concat = function (op1,op2)
        return tostring(op1)..tostring(op2)
    end,
    __len = function (op)
        return 4
    end,
    __eq = function (op1,op2)
        checkarg(op1,"rect")
        checkarg(op2,"rect")

        if op1.x == op2.x and
           op1.y == op2.y and
           op1.width == op2.width and
           op1.height == op2.height then
           return true
        end

        return false
    end,

    --/////////////////////////////////////////////////////////////////////////////
    -- properties
    --/////////////////////////////////////////////////////////////////////////////

    x = 0,
    y = 0,
    width = 1,
    height = 1,

    center = property {
        get = function (self) 
            return ex.vec2f( self.x + self.width * 0.5,  
                             self.y + self.height * 0.5 )  
        end,
    },

    min_x = property {
        get = function (self) return self.x end,
    },
    min_y = property {
        get = function (self) return self.y end,
    },
    max_x = property {
        get = function (self) return self.x + self.width end,
    },
    max_y = property {
        get = function (self) return self.y + self.height end,
    },

    left = property {
        get = function (self) return self.x end,
        set = function (self,v) self.x = v end
    },
    right = property {
        get = function (self) return self.y end,
        set = function (self,v) self.y = v end
    },
    top = property {
        get = function (self) return self.width end,
        set = function (self,v) self.width = v end
    },
    bottom = property {
        get = function (self) return self.height end,
        set = function (self,v) self.height = v end
    },

    --/////////////////////////////////////////////////////////////////////////////
    -- methods
    --/////////////////////////////////////////////////////////////////////////////

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    copy = function ( self )
        t = typeof (self)
        return t( self.x, self.y, self.width, self.height )
    end,

    -- ------------------------------------------------------------------ 
    -- Desc: 
    -- ------------------------------------------------------------------ 

    contains = function ( self, point )
        if point.x >= self.min_x and
           point.x < self.max_x and
           ponit.y >= self.min_x and
           point.y < self.max_x then
           return true
       end
       return false
    end,
}) 
