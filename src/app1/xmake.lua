add_deps("common")
add_links("common")

target("app1")
    set_default(true)
    set_kind("binary")
    -- set_kind("shared")
    
    set_policy("build.merge_archive", true)

    add_includedirs("./", {public = true})

    -- add_files("*.cpp")
    add_files("entry/main.cpp")
    -- add_files("entry/dllmain.cpp")