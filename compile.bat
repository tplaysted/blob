@ REM Version 1.1 Ahmet
@ echo %PATH%
g++ -o opencv_test opencv_test.cpp -std=c++17 -I "C:\msys64\mingw64\include\opencv4"^
    -L "C:\msys64\mingw64\bin"^
    -lopencv_core-409^
    -lopencv_highgui-409^
    -lopencv_imgcodecs-409^
    -lopencv_imgproc-409^
    -lopencv_videoio-409
@ REM g++ -o opencv_test opencv_test.cpp -std=c++17 -I "C:\msys64\mingw64\include\opencv4" -L "C:\msys64\mingw64\bin" -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc