target("common")
    set_default(true)
    set_kind("static")
    set_policy("build.merge_archive", true)
    -- set_policy("build.optimization.lto", false)
    -- set_policy("build.ccache", false)

    add_includedirs("./", {public = true})

    set_pcxxheader("base/stdafx.h")

    add_files("base/*.cpp")
