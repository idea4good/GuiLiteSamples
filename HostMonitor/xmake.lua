target("HostMonitor")
    set_kind("binary")
    add_packages("sqlite3")
    add_includedirs("SampleCode/include", "SampleCode/source")
    add_files("SampleCode/**.cpp")
    if is_plat("linux") then
        add_files("BuildLinux/*.cpp")
    elseif is_plat("windows") then
        add_files("BuildWin32/**.cpp")
    end

    -- copy sqlite3.dll and audio files to $(buildir)
    if is_plat("windows") then
        after_build(function (target)
            os.cp("$(projectdir)/packages/sqlite3.pkg/lib/windows/$(arch)/sqlite3.dll", "$(buildir)")
            os.cp("$(scriptdir)/BuildWin32/sample_native/*.wav", "$(buildir)")
        end)
    end
