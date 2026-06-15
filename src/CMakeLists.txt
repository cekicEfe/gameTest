add_library(RevEngineCore STATIC
    ${EngineCoreFiles}
)

    
target_link_libraries(RevEngineCore PUBLIC ${CoreDependencies})

    
target_include_directories (
    RevEngineCore
    PUBLIC
    ${CoreIncludeDirs}
)
    
