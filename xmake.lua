add_rules("mode.debug", "mode.release")

-- Request static SDL3 built from source
add_requires("libsdl3", {configs = {shared = false}, system = false})
add_requires("libsdl3_image", {configs = {shared = false}, system = false})
add_requires("libsdl3_ttf", {configs = {shared = false}, system = false})
set_languages("c17")

if is_mode("release") then
    add_ldflags("-s", {force = true})
end

target("hsh")
    set_kind("binary")
    add_files("src/*.c")
    add_includedirs("include")
    add_packages("libsdl3", {public = true})
    add_packages("libsdl3_image", {public = true})
    add_packages("libsdl3_ttf", {public = true})

    -- Add symbol link of the resource folder
    after_build(function (target)
      local target_dir = target:targetdir()
      local link_name = path.join(target_dir, "res")
      local res_source = path.absolute("res")
      if not os.exists(link_name) then
        os.ln(res_source, link_name)
      end
    end)
