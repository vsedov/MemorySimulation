set_project("CS2850assignment2")

-- '-Wall,-Wextra' equivalent
set_warnings("allextra")

-- set C standards
set_languages("c99")

-- Build modes
add_rules("mode.debug", "mode.release", "mode.valgrind")

if is_mode("debug") then
  on_config(function(target)
    -- is debug mode now? xmake f -m debug
    if is_mode("debug") then
      -- enable the debug symbols
      if not target:get("symbols") then
        target:set("symbols", "debug")
      end

      -- disable optimization
      if not target:get("optimize") then
        target:set("optimize", "none")
      end
    end
  end)
end
-- define rule: valgrind mode
if is_mode("valgrind") then
  on_config(function(target)
    -- is valgrind mode now? xmake f -m valgrind
    if is_mode("valgrind") then
      -- enable the debug symbols
      if not target:get("symbols") then
        target:set("symbols", "debug")
      end

      -- enable optimization
      if not target:get("optimize") then
        if is_plat("android", "iphoneos") then
          target:set("optimize", "smallest")
        else
          target:set("optimize", "fastest")
        end
      end
    end
  end)
end
if is_mode("release") then
  -- '-Ofast' equivalent
  set_optimize("aggresive")
  -- Strip unneeded debugging symbols
  set_strip("all")
  -- Hide symbols
  set_symbols("hidden")

  set_warnings("all", "error")
end

-- preprocessor variables
if is_plat("macosx") then
  add_defines("USE_PWD_SHELL", "MACOS")
else
  add_defines("USE_PWD_SHELL")
end

-- third-party dependencies
add_requires("lua >= 5.3.6", "libx11", "libxrandr", "xorgproto", "log.c")

-- headers directories
add_includedirs("src/include")

-- log.c library
package("log.c")
set_description("A simple logging library implemented in C99")
set_sourcedir(path.join(os.scriptdir(), "helper/log.c/src/"))

on_install(function(package)
  -- Create directories
  -- Generate static log.c library
  os.run("gcc -DLOG_USE_COLOR -c -o log.o log.c")
  os.run("ar rcs liblog.a log.o")
  -- Copy libraries and headers
  os.cp("*.h", package:installdir("include"))
  os.cp("*.a", package:installdir("lib"))
end)
on_test(function(package)
  assert(package:check_csnippets({
    test = [[
          #include <log.h>
          void test(int argc, char** argv) {
            log_info("log.c working? - %s", "yes");
          }
        ]],
  }, { configs = {
    languages = "c99",
  } }))
end)
package_end()

target("CS2850assignment2")

set_kind("binary")
set_default(true)

-- Source files
add_files("src/*.c")
-- add_files("src/includge/*.h")

-- Add third-party dependencies
add_packages("lua", "libx11", "libxrandr", "xorgproto", "log.c")

-- Precompile main lcfetch header to optimize compile time
set_pcheader("src/include/step4.h")
