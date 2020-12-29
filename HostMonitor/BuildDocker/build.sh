image_x64=gui-lite-x64:0.2
image_arm=gui-lite-armhf:0.3
image_all=gui-lite:0.2

test_and_build()
{
    if [ -e "$1/HostMonitor" ]; then
        echo "HostMonitor for $1 has been built"
    else
        cd ../
        rm CMakeCache.txt
        cmake $4 . && make
        cd BuildDocker
        mv ../BuildLinux/HostMonitor $1/HostMonitor
    fi

    docker rmi -f $2
    docker build --build-arg input=$1 --build-arg base=$3 -t $2 .
}

# build image
test_and_build x64 $image_x64 ubuntu
test_and_build arm $image_arm arm32v7/ubuntu "-D CMAKE_C_COMPILER='/usr/bin/arm-linux-gnueabihf-gcc' -D CMAKE_CXX_COMPILER='/usr/bin/arm-linux-gnueabihf-g++'"

# release
docker login
docker tag $image_x64 idea4good/$image_x64
docker push idea4good/$image_x64

docker tag $image_arm idea4good/$image_arm
docker push idea4good/$image_arm

docker manifest create idea4good/$image_all idea4good/$image_x64 idea4good/$image_arm
docker manifest annotate idea4good/$image_all idea4good/$image_x64 --arch amd64
docker manifest annotate idea4good/$image_all idea4good/$image_arm --arch arm
docker manifest push idea4good/$image_all --purge

# check & testing
docker image inspect $image_x64
docker run -it --privileged -v /dev:/dev $image_x64
docker image inspect $image_arm
docker run -it --privileged -v /dev:/dev $image_arm
