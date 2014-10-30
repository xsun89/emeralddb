cmake_minimum_required(VERSION 2.8.4)
project(emeralddb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/bson/src/lib/atomic_int.h
    src/bson/src/lib/base64.cpp
    src/bson/src/lib/base64.h
    src/bson/src/lib/md5.cpp
    src/bson/src/lib/md5.h
    src/bson/src/lib/md5.hpp
    src/bson/src/lib/nonce.cpp
    src/bson/src/lib/nonce.h
    src/bson/src/util/builder.h
    src/bson/src/util/embedded_builder.h
    src/bson/src/util/hex.h
    src/bson/src/util/json.cpp
    src/bson/src/util/json.h
    src/bson/src/util/misc.h
    src/bson/src/util/optime.h
    src/bson/src/util/time_support.h
    src/bson/src/bson-inl.h
    src/bson/src/bson.h
    src/bson/src/bson_db.h
    src/bson/src/bsonassert.h
    src/bson/src/bsonelement.h
    src/bson/src/bsonmisc.h
    src/bson/src/bsonobj.cpp
    src/bson/src/bsonobj.h
    src/bson/src/bsonobjbuilder.h
    src/bson/src/bsonobjiterator.h
    src/bson/src/bsontypes.h
    src/bson/src/inline_decls.h
    src/bson/src/oid.cpp
    src/bson/src/oid.h
    src/bson/src/ordering.h
    src/bson/src/stringdata.h
    src/include/core.hpp
    src/include/ossSocket.hpp
    src/include/pmd.hpp
    src/pmd/pmdMain.cpp
    src/aclocal.m4
    src/autoscan.log
    src/build.sh
    src/config.h.in
    src/configure.in.bak
    src/configure.scan
    src/Makefile.am
    src/missing
    build.sh)

add_executable(emeralddb ${SOURCE_FILES})