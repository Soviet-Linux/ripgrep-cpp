# ripgrep-cpp
A rewrite of the original ripgrep written in go now the new one will be written c++

# Install

## Unix
For unix is more complex go to main.cpp comment all the bellow \
before:
```
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#define CURL_STATICLIB
#include "libs/curl.h"
#include "libs/curlver.h"
#include "libs/easy.h"
#include "libs/header.h"
#include "libs/mprintf.h"
#include "libs/multi.h"
#include "libs/options.h"
#include "libs/stdcheaders.h"
#include "libs/system.h"
#include "libs/urlapi.h"
#include "libs/websockets.h"
#include <sstream>
using namespace std;

```
after: 
```
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
// #define CURL_STATICLIB
// #include "libs/curl.h"
// #include "libs/curlver.h"
// #include "libs/easy.h"
// #include "libs/header.h"
// #include "libs/mprintf.h"
// #include "libs/multi.h"
// #include "libs/options.h"
// #include "libs/stdcheaders.h"
//#include "libs/system.h"
// #include "libs/urlapi.h"
// #include "libs/websockets.h"
#include <sstream>
using namespace std;

```
when you are done with this step go to the root of the repo and type \
```sudo make all``` \
optional to cleanup type: \
```sudo make clean```

## Windows
For windows you will need mingw-32 with gcc/g++ support to do this follow [this](https://code.visualstudio.com/docs/cpp/config-mingw) also dont pay attention to the configuration for vscode just pay attention to what is for mingw and windows \
after you are done with this step open a terminal in src folder and wrtie \
```g++ -Ofast main.cpp -o rg-cpp```

### Optional Step for windows only
If you want to make this executable from anywhere do the bellow
Firstly you must have done the above and have generated the .exe file 
1) if you have done that then go ahead and make a folder at the root of your disk (aka C:\) and copy the exe to it 
2) after that go and type at windows search ```Edit Environment Variables``` and click on edit system environment variables 
3) a new window will appear in this window click ```Environment Variables``` 
4) a new window will appear again in this scroll down in the system variables section until you see ```Path``` when you see it double click it 
5) a new window displaying all the PATH variables will be displayed press new then type the path to the exe like so ```C:\FOLDERTHATHOUSESEXE``` then press enter 
6) after this click ok then ok on the previous window then apply and ok on the last 
7) just reopen any terminal you had open and you will be able to just type ```rg-cpp --version``` and see the ripgrep-cpp version 

Created with luv 💙 by JohnVictoryz aka tutel
