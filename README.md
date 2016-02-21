### HPX Projects

This is a collection of small demos showing different functionalities from <a href="http://stellar.cct.lsu.edu/tag/hpx/">HPX</a>. 

All parts are based on Visual C++ under VS 2015. 

<a href="http://stellar.cct.lsu.edu/downloads/">HPX</a> version: **0.9.11**

<a href="http://www.boost.org/users/history/version_1_60_0.html">BOOST</a> version: **1.60**

<a href="https://www.open-mpi.org/software/hwloc/v1.11/">HWLOC</a> version: **1.11.0**

The configuration procedure of HPX with Visual Studio is rather complex and can quickly lead to very confusing errors.

Therefore I'd recommend to use my small tutorial on building <a href="https://github.com/brakmic/hpx/blob/b3feb9561fecc1ef4b52717d70332c8148104cdd/docs/tutorial/win32/howto.md">HPX under Windows</a>.

#### Configuration

To make the configuration of Project-Options easier I've extracted some `default` properties into a separate `prop` file.

<img src="http://fs5.directupload.net/images/160220/slueu7c6.png" />

I'm using the following system-variables to access Boost, HwLoc and HPX libraries:

```

BOOST_ROOT = C:\lib\boost
HWLOC_ROOT = C:\bin\hwloc
HPX_ROOT   = C:\bin\hpx
```

In my `PATH` there are some additional entries pointing at subdirectories inside the above roots:

```

%BOOST_ROOT%\lib
%HPX_ROOT%\bin
```

This is, of course, not mandatory and you can create your own paths. What's important is that you have 
the libs installed and accessible under some system-wide variables.

#### Visual Studio Project Properties

After having compiled and installed the libraries (boost, hpx & hwloc) you have to insert certain *library* and *include* paths. These settings will look like in the screenshot below. There's a separate properties-file with several `defaults` available so you can more easily adapt the project to your environment. The most important part will be the different library `ROOTs`. 

<img src="http://fs5.directupload.net/images/160220/ih3v7et5.png"/>

#### Compilation

The compilation is straightforward. Just use the standard **Debug/Release** facilities.

#### Execution

Currently, everything the whole execution logic is packed into **a single ugly** `source file`. At least the participating objects and functions are defined over several `cpp` and `hpp` files. But soon I'll provide a better structure. The main focus will be on `actions` and `components`. This project already contains a few <a href="http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions.html">actions</a> and a <a href="http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/components.html">component</a> implementing some (a)synchronous methods. There's also a separate DLL-Project available that defines another HPX-Component (`SmallServer.dll`) to be used in this demo.  The output is *console-based* and currently looks like this:

<img src="http://fs5.directupload.net/images/160221/otovusdf.png" /> 

The program's `main` is located in `HpxTest_1.cpp` which contains a special `hpx_main` function
where HPX kicks in. To make the app aware of this additional `main` function we have to
execute another HPX-function called `hpx::init`. Of course, this is not the only way to start an 
HPX app. There are <a href="http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applications.html">several possibilities</a> for different use-cases.

<img src="http://fs5.directupload.net/images/160221/yccrybig.png" />

In our case the `hpx::main` contains a bunch of calls to other functions which utilize
different functionalities from HPX.

<img src="http://fs5.directupload.net/images/160221/clw34huh.png"/> 

- Applying **(a)synchronous** `actions`. 

In HPX actions are like wrappers that map to `real functions`.
And it doesn't matter if they're available locally or on some other machine. In fact, HPX maintans its own 
`registry` for managing actions and components so you don't have to fiddle around with memory addressing. Instead,
HPX assigns a globally unique id to a `thing`. Only this Id is needed to localize a `thing`. Also, HPX can move
`things` around the global memory. For example, when there's no sufficient memory on a certain machine HPX can take 
some components and move them to other machine within the cluster. HPX does this by using `parcels` which are basically
`serialized` functions and/or components. HPX also <a href="http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions/action_invocation.html">extends</a> the standard C++ syntax for asynchronous function calling.

- **Continuations** demo.  

A <a href="http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions/action_invocation/apply_continue.html">continuation</a> allows us to chain several functions together and forward their results down the chain.

- **Error handling** in HPX

Asynchronous functions throw *asynchronous* errors. And in highly parallel systems errors are really hard to handle. But HPX keeps the complexity away by providing
<a href="http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/applying_actions/action_error_handling.html">nice facilities</a> for location-agnostic error handling.

- **Components**

HPX supports <a href="http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/components.html">remotely manageable</a> components. In this demo part we initialize a component and call it's (a)synchronous methods to manipulate a number.

- **Components from DLLs**

HPX also <a href="http://stellar.cct.lsu.edu/files/hpx-0.9.11/html/hpx/manual/init/configuration/loading_components.html#hpx.manual.init.configuration.loading_components.component_example">supports loading components from DLLs</a>. In this example we have a `SmallServer.dll` that lives in a project of the same name.

<img src="http://fs5.directupload.net/images/160221/y5z2f2n5.png" />

Our client app `HpxTest_1.exe` should be able to load and execute exported methods from **SmallServer.dll**. This is done the `standard way` via `#include "smallserver.h"` where the needed `function declarations` & `component exports` are located. It's important to know that in this file **no function definitions** should be located.
Any function definition in this header file will ultimately lead to weird `dllimport errors`. Put your function definitions into `SmallServer.cpp`. The import library file SmallServer.lib is located in the Output directory: `x64/Debug` respective `x64/Release`. HpxTest_1.exe needs this file for mapping to SmallServer-exports. 

*If you'd prefer some other location take care of properly setting the import-library paths in Project Settings.*

<img src="http://fs5.directupload.net/images/160221/lkzx9t7i.png" />

#### License

<a href="https://github.com/brakmic/HPX_Projects/blob/master/LICENSE">MIT</a>