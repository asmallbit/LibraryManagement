# 1.cmake version，指定cmake版本
cmake_minimum_required(VERSION 3.19)

# 2.project name，指定项目的名称，一般和项目的文件夹名称对应
PROJECT(library)

# 3.head file path，头文件目录
INCLUDE_DIRECTORIES("C:/msys64/mingw64/include")    # 依赖于自己的mingw64安装路径
INCLUDE_DIRECTORIES("include")

# 添加 src 子目录
# add_subdirectory(src)

# set environment variable，设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error , undefined symbol"
# SET(library ${DIR_SRCS})

# 4.设置源文件
SET(sources
        src/borrow.c
        src/library.c
        src/rest.c
)
# 5.设置头文件
SET(headers
        include/library.h
        include/borrow.h
        include/rest.h
        C:/msys64/mingw64/include       # 依赖于自己的mingw64安装路径
)

# 6.创建静态库
add_library(AllFunctions ${sources} ${headers})

# 7.add executable file，添加要编译的可执行文件
# link_libraries(libraryFunctions AllFunctions)
add_executable(library main.c)


# 7.add link library，添加可执行文件所需要的库，比如我们用到了libm.so（命名规则：lib+name+.so），就添加该库的名称
target_link_libraries(library AllFunctions)

# Thanks to: https://www.jianshu.com/p/55be9d4fc033