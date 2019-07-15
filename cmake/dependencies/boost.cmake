set( uri_Boost_VERSION
    1.64.0
    )

set( uri_Boost_COMPONENTS
    )

if (ANDROID)
    set(Boost_USE_STATIC_LIBS ON)
endif()

find_package(
    Boost
        ${uri_Boost_VERSION}
    REQUIRED
    COMPONENTS
        ${uri_Boost_COMPONENTS}
    )
