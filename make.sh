#cmake -DCMAKE_BUILD_TYPE=Release -B ./build && cmake --build build -j4 --config Release
#g++ -std=c++17 -O3 -Wall -march=native -o main main.cpp

function build_cpp() {

    #Update the submodule and initialize
    #git submodule update --init
    echo "cpu_num = " $parallel

    #Save current directory
    current_dir="${PWD}"

    #The folder in which we will build
    build_dir='./build'
    if [ -d $build_dir ]; then
        echo "Deleted folder: ${build_dir}"
        rm -rf $build_dir
    fi

    #Create building folder
    echo "Created building folder: ${build_dir}"
    mkdir $build_dir

    echo "Entering folder: ${build_dir}"
    cd $build_dir

    echo "Start building ..."
    if [ $1 -eq 1 ]; then
        cmake .. -DBUILD_TESTING=YES $cmake_gen
    elif [ $1 -eq 2 ]; then
        cmake .. -DBUILD_TESTING=YES -DBUILD_DROGON_SHARED=ON -DCMAKE_CXX_VISIBILITY_PRESET=hidden -DCMAKE_VISIBILITY_INLINES_HIDDEN=1 $cmake_gen
    else
        cmake .. -DCMAKE_BUILD_TYPE=release $cmake_gen
    fi

    #If errors then exit
    # shellcheck disable=SC2181
    if [ "$?" != "0" ]; then
        # shellcheck disable=SC2242
        exit -1
    fi

    $make_program $make_flags

    #If errors then exit
    # shellcheck disable=SC2181
    if [ "$?" != "0" ]; then
        # shellcheck disable=SC2242
        exit -1
    fi

    #echo "Installing ..."
    #sudo $make_program install

    #Go back to the current directory
    cd $current_dir

    echo "Starting ..."
    $build_dir/Learning-Cpp
    #Ok!
}

make_program=make
make_flags=''
cmake_gen=''
parallel=1

case $(uname) in
 FreeBSD)
    nproc=$(sysctl -n hw.ncpu)
    ;;
 Darwin)
    nproc=$(sysctl -n hw.ncpu) # sysctl -n hw.ncpu is the equivalent to nproc on macOS.
    ;;
 *)
    nproc=$(nproc)
    ;;
esac

# simulate ninja's parallelism
case nproc in
 1)
    parallel=$(( nproc + 1 ))
    ;;
 2)
    parallel=$(( nproc + 1 ))
    ;;
 *)
    parallel=$(( nproc + 2 ))
    ;;
esac

if [ -f /bin/ninja ]; then
    make_program=ninja
    cmake_gen='-GNinja'
else
    make_flags="$make_flags -j$parallel"
fi

if [ "$1" = "-t" ]; then
    build_cpp 1
elif [ "$1" = "-tshared" ]; then
    build_cpp 2
else
    build_cpp 0
fi