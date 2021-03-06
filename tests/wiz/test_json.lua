-- ======================================================================================
-- File         : init.lua
-- Author       : Wu Jie 
-- Last Change  : 05/08/2013 | 17:01:36 PM | Wednesday,May
-- Description  : 
-- ======================================================================================

function main()
    -- test_simple()           -- 1
    -- null_at_end_of_array()  -- 2
    -- null_object_value()     -- 3
    -- weird_numbers()         -- 4
    -- number_in_string()      -- 5
    -- test_generator()        -- 6
    -- test_to_value()         -- 7

    my_test ()
end

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

local counter = 0
function ok(assert_true, desc)
   local msg = ( assert_true and "ok " or "not ok " ) .. counter
   if ( desc ) then
      msg = msg .. " - " .. desc
   end
   print(msg)
   counter = counter + 1
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function tovalue(string)
   local result
   local stack = {
      function(val) result = val end
   }
   local obj_key
   local events = {
      value = function(_, val)
                 stack[#stack](val)
              end,
      open_array = function()
                      local arr = {}
                      local idx = 1
                      stack[#stack](arr)
                      table.insert(stack, function(val)
                                             arr[idx] = val
                                             idx = idx + 1
                                          end)
                   end,
      open_object = function()
                      local obj = {}
                      stack[#stack](obj)
                      table.insert(stack, function(val)
                                             obj[obj_key] = val
                                          end)
                   end,
      object_key = function(_, val)
                     obj_key = val
                  end,
      close = function()
                stack[#stack] = nil
             end,
   }

   json.parser({ events = events })(string)
   return result
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function my_test ()  
    local text  = [[
    {
        "float": 1.5,
        "hello": "what",
        "world": "johnny wu",
        "array": [ 1, 2, 3, 4 ],
        "table": {
            "player1": "johnny",  
            "player2": "ada"  
        }
    }
    ]]
    local obj = json.tovalue(text)
    debug.dump(obj)

    local obj2 = tovalue(text) 
    debug.dump(obj2)

    print ( "obj = " .. json.tostring (obj) )
    print ( "obj2 = " .. json.tostring (obj, {
        indent = "\t"
    }) )
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function test_to_value()
   local text = '[["float",1.5,"integer",5,"string","hello","empty",[],"false",false,"custom","custom json serializer","ostr_key",{"key":"value"},"obool_key",{"true":true},"onull_key",{"null":null}],10,10.3,10.3,"a string",null,false,true]'
   local val = json.tovalue(text)
   local got = json.tostring(val);

   ok(got == text,
      "json.tovalue(" .. text .. ") -> " .. got)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function test_generator()
   local strings = {}
   local generator = json.generator {
      printer = function(string)
                  table.insert(strings, string)
               end
   }

   local custom = { __gen_json = function(self, gen)
                                    gen:string("custom json serializer")
                                 end
                 }
   setmetatable(custom, custom)

   generator:open_array()
   generator:value({  "float",  1.5,
                      "integer", 5,
                      "string", "hello",
                      "empty", {}, -- defaults to an empty array.
                      "false", false,
                      "custom", custom,
                      "ostr_key", { key = "value" },
                      "obool_key", { [true] = true },
                      "onull_key", { [json.null] = json.null },
                   })
   generator:integer(10.3)
   generator:double(10.3)
   generator:number(10.3)
   generator:string("a string")
   generator:null()
   generator:boolean(false)
   generator:boolean(true)
   generator:open_object()
   generator:close_object()
   generator:close_array()

   local expect = '[["float",1.5,"integer",5,"string","hello","empty",[],"false",false,"custom","custom json serializer","ostr_key",{"key":"value"},"obool_key",{"true":true},"onull_key",{"null":null}],10,10.300000000000000711,10.3,"a string",null,false,true,{}]'
   local got = table.concat(strings)
   ok(expect == got, expect .. " == " .. got)
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function test_simple()
    -- Thanks to fab13n@github for this bug report:
    -- https://github.com/brimworks/lua-yajl/issues/8
    assert ( json.tovalue(json.tostring(0)) == 0 )

   local expect =
      '['..
      '"float",1.5,'..
      '"integer",5,'..
      '"true",true,'..
      '"false",false,'..
      '"null",null,'..
      '"string","hello",'..
      '"array",[1,2],'..
      '"object",{"key":"value"}'..
      ']'

   -- Input to tovalue matches the output of tostring:
   local got = json.tostring(tovalue(expect))
   ok(expect == got, expect .. " == " .. tostring(got))
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function null_at_end_of_array()
   local expect = '["something",null]'
   local got = json.tostring(tovalue(expect))
   ok(expect == got, expect .. " == " .. tostring(got))
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function null_object_value()
   local expect = '{"something":null}'
   local got = json.tostring(tovalue(expect))
   ok(expect == got, expect .. " == " .. tostring(got))
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function weird_numbers()
   -- See note in README about how we are broken when it comes to big numbers.
   local expect = '[1e+666,-1e+666,-0]'
   local got = json.tostring(tovalue(expect))
   ok(expect == got, expect .. " == " .. tostring(got))

   local nan = 0/0
   got = json.tostring { nan };
   ok("[-0]" == got, "NaN converts to -0 (got: " .. got .. ")")
end

-- ------------------------------------------------------------------ 
-- Desc: 
-- ------------------------------------------------------------------ 

function number_in_string()
   -- Thanks to agentzh for this bug report!
   local expect = '{"2":"two"}'
   local got = json.tostring {["2"]="two"}
   ok(expect == got, expect .. " == " .. tostring(got))
end

--/////////////////////////////////////////////////////////////////////////////
--
--/////////////////////////////////////////////////////////////////////////////

main()
