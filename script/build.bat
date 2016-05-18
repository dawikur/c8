cd build

IF [%1]==[debug] GOTO DEBUG 

:RELEASE
cmake --build . --config Release && cd ..
GOTO EXIT

:DEBUG
cmake --build . --config Debug && cd ..

:EXIT