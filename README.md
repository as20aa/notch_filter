# C++ notch filter
## tips
* 项目中使用了开源项目AudioFile，但是在引用时stdfx.h出现错误，右键单击stdfx.h，点击属性，更改c++/precomplied
header/precomplied header选项为create precompiled header；此外，还需要将AudioFile.cpp添加到Resource Files
文件夹，将AudioFile.h添加到Header Files文件夹，右键AudioFile.cpp文件，按照上面的选项设置为do not use 
complied header.