target("Snake")

    -- set kind
    if is_plat("android") then
        set_kind("shared")
    else
        set_kind("binary")
    end

    -- add source files
    add_files("SampleCode/**.cpp")
    if is_plat("android") then
        add_files("BuildAndroid/jni/*.cpp")
    else
        add_files("BuildLinux/*.cpp")
    end

    after_build(function (target)

        -- is android?
        if val("plat") == "android" then

            -- trace
            print("building Snake:app")

            -- copy libnative.so
            os.cp(target:targetfile(), "$(scriptdir)/BuildAndroid/app/libs/armeabi-v7a/libnative.so")

            -- get sdk
            local sdk = val("sdk")
            assert(sdk, "please set --sdk=xxx first!")

            -- build app
            local oldir = os.cd("$(scriptdir)/BuildAndroid")
            io.gsub("local.properties", "sdk.dir=.*\n", "sdk.dir=" .. sdk .. "\n")
            if os.host() == "windows" then
                os.execv(path.join(os.curdir(), "gradlew.bat"), {":app:assembleDebug"})
            else
                local java_home = os.iorun("/usr/libexec/java_home -v 1.8")
                if java_home then
                    os.setenv("JAVA_HOME", java_home:trim())
                end
                os.runv(path.join(os.curdir(), "gradlew"), {":app:assembleDebug"})
            end
            os.cd(oldir)
        end
    end)
