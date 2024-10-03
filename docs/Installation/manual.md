<div id="top">
<h1>manual installation</h1>
</div>

<hr>

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [Linux, macOS](#linux-macos)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

<hr>

#### Linux, macOS

```Shell
cd src

conan install . --output-folder=../build --build=missing

cd ../build

cmake -S ../src -B . -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake  -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Release

# cmake --build . --parallel <number of CPU cores>
cmake --build .
```

> NOTE  
> generate Doxygen documentation with `cd build && cmake --build . --target doxygen`

<p align="right">(<a href="#top">back to top</a>)</p>
