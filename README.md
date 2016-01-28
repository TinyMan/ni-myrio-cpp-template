# ni-myrio-cpp-template
A Template eclipse project for NI MyRio, defining build settings for C++11

# How To Use It
* **Prerequiste**  
You should follow the guide at http://www.ni.com/tutorial/14619/en/  
However, you don't have to bother with PATH environement variable and Eclipse project, just install **C/C++ Development Tools for NI Linux Real-Time, Eclipse Edition 2014** at http://digital.ni.com/express.nsf/bycode/Eclipse2014 and then import the **C_Support_for_NI_myRIO_vX.X.zip** into the your workspace  (the template project will refer to **C Suport for NI myRIO/source**)  
  
  *Remark:*  
>The template project is made for 64-bit Windows, and have the compiler path set to **C:\Program Files (x86)\National Instruments\Eclipse\14.0\arm\sysroots\i686-nilrtsdk-mingw32\usr\bin\armv7a-vfp-neon-nilrt-linux-gnueabi**  
>Change this to **C:\Program Files\National Instruments\Eclipse\14.0\arm\sysroots\i686-nilrtsdk-mingw32\usr\bin\armv7a-vfp-neon-nilrt-linux-gnueabi** if you are using 32-bit Windows  

* **Clone repository** (outside of your workspace)  
```
git clone https://github.com/TinyMan/ni-myrio-cpp-template
```
* **Import into Eclipse 2014**  
  * Using the eclipse version installed with NI Support for C/C++ 2014, choose **File**>**Import**>**Existing Project into Workspace** and click next  
  * Select the root directory of the repository you just cloned  
  * Check **Copy projects into workspace**  
  * Finish the importation
* **Build**  
You can build the project. You are ready to go !

# TODO
* Add remote target to Run/debug on MyRio
* Add helper classes for Manipulating MyRIO (based on NI examples)
