set_xmakever("2.9.8")

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

if is_plat("windows") then
    set_arch("x64")
elseif is_plat("linux") then
    set_arch("x86_64")
end

set_policy("build.warning", true)
set_warnings("all", "extra")
if is_mode("debug") then
    set_runtimes("MDd")
    set_symbols("debug")
    set_optimize("none")
    add_defines("DEBUG")
elseif is_mode("releasedbg") then
    set_runtimes("MDd")
    set_symbols("debug")
    set_optimize("fastest")
    add_defines("DEBUG")
else
    set_runtimes("MD")
    set_symbols("hidden")
    set_strip("all")
    set_optimize("fastest")
    add_defines("NDEBUG")
end

includes("src/common")
includes("src/app1")