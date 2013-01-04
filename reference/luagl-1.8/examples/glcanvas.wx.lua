-----------------------------------------------------------------------------
-- Name:		glcanvas.wx.lua
-- Purpose:		wxLua and LuaGL sample
-- Author:		Tin Benjamin Matuka
-- Created:		31/01/2011
-- Copyright:	(c) 2011 Tin Benjamin Matuka. All rights reserved.
-- Licence:		Public Domain
-- Comment:		I only left in comments for code that deals with making
--				wxLua and LuaGL interact
-----------------------------------------------------------------------------

package.cpath = package.cpath..";./?.dll;./?.so;../lib/?.so;../lib/vc_dll/?.dll;../lib/bcc_dll/?.dll;../lib/mingw_dll/?.dll;/usr/lib/lua/5.1/?.so;"
require("wx")
require("luagl")

function render()
	context:SetCurrent(canvas)
	
	gl.ClearColor(0, 0, 0, 0)
	gl.Clear(gl.COLOR_BUFFER_BIT)
	
	gl.Begin('TRIANGLES')
		gl.Vertex( 0,  0.75, 0)
		gl.Vertex(-0.75, -0.75, 0)
		gl.Vertex( 0.75, -0.75, 0)
	gl.End()
	
	canvas:SwapBuffers()
end

frame = nil
frame = wx.wxFrame( wx.NULL, wx.wxID_ANY, "wxLua + LuaGL Demo", wx.wxDefaultPosition, wx.wxSize(450, 450), wx.wxDEFAULT_FRAME_STYLE )

local fileMenu = wx.wxMenu()
fileMenu:Append(wx.wxID_EXIT, "E&xit", "Quit the program")

local helpMenu = wx.wxMenu()
helpMenu:Append(wx.wxID_ABOUT, "&About", "About the wxLua + LuaGL Demo")

local menuBar = wx.wxMenuBar()
menuBar:Append(fileMenu, "&File")
menuBar:Append(helpMenu, "&Help")
frame:SetMenuBar(menuBar)

frame:CreateStatusBar(1)
frame:SetStatusText("Welcome to wxLua + LuaGL Demo.")

frame:Connect(wx.wxID_EXIT, wx.wxEVT_COMMAND_MENU_SELECTED,
			  function (event) frame:Close(true) end )

frame:Connect(wx.wxID_ABOUT, wx.wxEVT_COMMAND_MENU_SELECTED,
	function (event)
		wx.wxMessageBox('wxLua + LuaGL Demo.\n'..
						'Written by Tin Benjamin Matuka\n'..
						'www.sh1fty.com',
						"About wxLua + LuaGL Demo",
						wx.wxOK + wx.wxICON_INFORMATION,
						frame)
	end )

-- This is where the GLCanvas is created
canvas = wx.wxGLCanvas(frame, wx.wxID_ANY, wx.wxDefaultPosition, wx.wxDefaultSize, wx.wxEXPAND)

-- A GLContext is created
context = wx.wxGLContext(canvas)

-- Connect the PAINT event to the render function
canvas:Connect(wx.wxEVT_PAINT, render)

-- Refresh the canvas so that it gets properly resized and rendered.
canvas:Refresh()

frame:Show(true)

wx.wxGetApp():MainLoop()
