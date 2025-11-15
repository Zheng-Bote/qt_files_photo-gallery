function(Doxygen input output)

  find_package(Doxygen)
  if (NOT DOXYGEN_FOUND)
    add_custom_target(doxygen COMMAND false
                              COMMENT "Doxygen not found")
    return()
  endif()

  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_HTML_OUTPUT ${PROJECT_BINARY_DIR}/${output})

  set(DOXYGEN_HTML_COLORSTYLE "TOGGLE")
  set(DOXYGEN_FILE_PATTERNS *.c *.cpp *.h *.hpp)
  doxygen_add_docs(example_docs "${CMAKE_CURRENT_SOURCE_DIR}/src" ALL)
  
     
  UseDoxygenAwesomeCss()
  UseDoxygenAwesomeExtensions()

  doxygen_add_docs(doxygen ${PROJECT_SOURCE_DIR} COMMENT "Generate HTML documentation")
endfunction()

macro(UseDoxygenAwesomeCss)
  include(FetchContent)
  FetchContent_Declare(doxygen-awesome-css
    GIT_REPOSITORY
      https://github.com/jothepro/doxygen-awesome-css.git
    GIT_TAG
      v2.3.3
  )
  FetchContent_MakeAvailable(doxygen-awesome-css)
  set(DOXYGEN_GENERATE_TREEVIEW     YES)
  set(DOXYGEN_HAVE_DOT              YES)
  set(DOXYGEN_DOT_IMAGE_FORMAT      svg)
  set(DOXYGEN_DOT_TRANSPARENT       YES)
  set(DOXYGEN_HTML_EXTRA_STYLESHEET
      ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome.css)
endmacro()

macro(UseDoxygenAwesomeExtensions)
  set(DOXYGEN_HTML_EXTRA_FILES
    ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome-darkmode-toggle.js
    ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome-fragment-copy-button.js
    ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome-paragraph-link.js
    ${doxygen-awesome-css_SOURCE_DIR}/doxygen-awesome-interactive-toc.js
  )

  execute_process(COMMAND doxygen ${PROJECT_SOURCE_DIR}/configure/Doxyfile -w html header.html footer.html style.css
                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src})
#  execute_process(COMMAND sed -i "/<\\/head>/r ${PROJECT_SOURCE_DIR}/configure/extra_headers" header.html
#                  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/src})
#  set(DOXYGEN_HTML_HEADER ${PROJECT_BINARY_DIR}/header.html)
endmacro()
