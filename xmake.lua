set_xmakever("2.9.5")

add_rules("mode.debug", "mode.release", "mode.releasedbg")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})
if is_plat("windows") then
    add_rules("plugin.vsxmake.autoupdate")
end

local packages = {
    "nlohmann_json v3.11.3",
    "spdlog v1.14.1",
}

for _, package in ipairs(packages) do
    add_requires(package)
    add_packages(package:match("^[^ ]+"))
end

set_languages("c++23")
-- set_arch("x86")

target("Project")
    set_default(true)

    set_kind("binary")
    add_files("src/entry/main.cpp")

    -- set_kind("shared")
    -- add_files("src/entry/dllmain.cpp")

    set_pcxxheader("src/base/stdafx.h")
    add_files("src/base/*.cpp")
    -- add_files("src/*.cpp")
