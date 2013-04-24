
if app.platform == "windows" then
    app:open_project( "d:/dev/exdev/exsdk/examples/test_project/" )
elseif app.platform == "macosx" then
    app:open_project( "/Users/Johnny/exdev/exsdk/examples/test_project/" )
end
