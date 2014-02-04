cmake_minimum_required (VERSION 2.6)
project (xmpp-socket)
AUX_SOURCE_DIRECTORY(src CTR_SOURCES)
add_executable(xmpp-socket ${CTR_SOURCES})

find_library(OPENSSL_LIB ssl $ENV{OPENSSL_LIB_PATH})
target_link_libraries(xmpp-socket ${OPENSSL_LIB})

find_library(CRYPTO_LIB crypto $ENV{CRYPTO_LIB_PATH})
target_link_libraries(xmpp-socket ${CRYPTO_LIB})


#find_library(EXPAT_LIB expat $ENV{EXPAT_LIB_PATH})
#target_link_libraries(xmpp-socket ${EXPAT_LIB})

#LINK_DIRECTORIES(/usr/lib/)
#TARGET_LINK_LIBRARIES(xmpp-socket strophe)
target_link_libraries(xmpp-socket strophe)
target_link_libraries(xmpp-socket expat)
target_link_libraries(xmpp-socket resolv)
target_link_libraries(xmpp-socket socket)
#target_link_libraries(xmpp-socket json-c)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

set (CMAKE_INSTALL_PREFIX /)
install (TARGETS xmpp-socket DESTINATION usr/bin)
install (FILES ./conf/xmpp-socket.conf DESTINATION etc PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ GROUP_WRITE )

