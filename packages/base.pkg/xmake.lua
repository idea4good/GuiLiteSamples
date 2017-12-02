-- the base package
option("base")
    
    -- set category
    set_category("package")

    -- for windows
    if is_plat("windows") then 
        add_cxxflags("-EHsc")
        add_defines("UNICODE", "_UNICODE")
        add_ldflags("-nodefaultlib:\"msvcrt.lib\"")
        add_links("ws2_32", "IPHlpApi", "kernel32", "user32", "gdi32")
    else
        add_defines("__linux__")
        add_links("pthread", "dl")
    end

