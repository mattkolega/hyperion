set_project("hyperion")
set_version("0.1.0")

set_languages("c++20")

add_rules("mode.debug", "mode.release")

add_requires(
    "stb"
)

target("hyperion")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("stb")