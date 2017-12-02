 
-- the sqlite3 package
option("sqlite3")

    -- show menu
    set_showmenu(true)

    -- set category
    set_category("package")

    -- set description
    set_description("The sqlite3 package")

    -- set language: c99, c++11
    set_languages("c99", "cxx11")

    -- add defines to config.h if checking ok
    add_defines_h("$(prefix)_PACKAGE_HAVE_SQLITE3")

    -- add links for checking
    add_links("sqlite3")

    -- add link directories
    add_linkdirs("lib/$(plat)/$(arch)")

    -- add c includes for checking
    add_cincludes("sqlite3.h")

    -- add include directories
    add_includedirs("inc/$(plat)", "inc")
