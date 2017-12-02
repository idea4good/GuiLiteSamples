-- project
set_project("GuiLiteSamples")

-- version
set_version("1.0.1")
set_xmakever("2.1.6")

-- the debug or release mode
if is_mode("debug") then
    
    -- enable the debug symbols
    set_symbols("debug")

    -- disable optimization
    set_optimize("none")

    -- link libcmtd.lib
    if is_plat("windows") then 
        add_cxflags("-MTd") 
    end

elseif is_mode("release") then

    -- set the symbols visibility: hidden
    set_symbols("hidden")

    -- strip all symbols
    set_strip("all")

    -- enable fastest optimization
    set_optimize("fastest")

    -- link libcmt.lib
    if is_plat("windows") then 
        add_cxflags("-MT") 
    end
end

-- add package directories
add_packagedirs("packages")

-- add packages
add_packages("gui", "core", "base")

-- include project sources
includes("HostMonitor", "Snake") 
