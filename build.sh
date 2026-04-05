FILE=./build
if test -d "$FILE";
then
    cd build
#    cmake -G Ninja \
#    -DCMAKE_C_COMPILER=clang \
#    -DCMAKE_CXX_COMPILER=clang++ \
#    -DJOLT_SAMPLES=OFF \
#    -DJOLT_UNIT_TESTS=OFF \
#    -DJOLT_DEBUG_RENDERER=OFF \
#    -DJPH_USE_DX12=OFF \
#    -DJPH_USE_DXC=OFF \
#    -DJPH_USE_VK=OFF \
#    -DJPH_USE_MTL=OFF \
#    -DJPH_USE_CPU_COMPUTE=ON \
#    ../
    cmake --build .
else
    rm -rf ./build
    mkdir build

    cd build
    
    cmake -G Ninja \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DENABLE_CPP20_MODULE=ON\
    -DJOLT_SAMPLES=OFF \
    -DJOLT_UNIT_TESTS=OFF \
    -DJOLT_DEBUG_RENDERER=OFF \
    -DJPH_USE_DX12=OFF \
    -DJPH_USE_DXC=OFF \
    -DJPH_USE_VK=OFF \
    -DJPH_USE_MTL=OFF \
    -DJPH_USE_CPU_COMPUTE=ON \
    ../

    cmake --build .
fi
