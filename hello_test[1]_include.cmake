if(EXISTS "C:/Users/User/Documents/SCORP/COSC345/hello_test[1]_tests.cmake")
  include("C:/Users/User/Documents/SCORP/COSC345/hello_test[1]_tests.cmake")
else()
  add_test(hello_test_NOT_BUILT hello_test_NOT_BUILT)
endif()