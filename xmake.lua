add_rules("mode.debug", "mode.release")

-- Request static SDL3 built from source
add_requires("libsdl3", {configs = {shared = false}, system = false})
add_requires("libsdl3_image", {configs = {shared = false}, system = false})
set_languages("c17")

if is_mode("release") then
    add_ldflags("-s", {force = true})
end

target("hsh")
    set_kind("binary")
    add_files("src/*.c")
    add_packages("libsdl3", {public = true})
    add_packages("sdl3_image", {public = true})
