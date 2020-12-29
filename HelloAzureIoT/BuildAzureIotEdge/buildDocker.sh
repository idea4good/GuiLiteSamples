arch=amd64
if [ ! -z "$1" ];
then
    arch=$1
fi
echo building $arch image
image=acryou.azurecr.io/gui-lite-module:0.1-$arch

# build
cd ./modules/gui-lite-module

if [ "$arch" = "arm" ];
then
    docker build -f Dockerfile.arm32v7 -t $image .
else
    docker build -f Dockerfile.amd64 -t $image .
fi
rm Dockerfile

# publish
docker login acryou.azurecr.io -u acrYou -p Z56xs/tVgp1HGo1VXdnJcW55mSJmK6oA
docker push --disable-content-trust $image
