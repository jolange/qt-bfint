#qt-bfint
[Qt4](https://qt-project.org/) based [Brainfuck](http://en.wikipedia.org/wiki/Brainfuck) Interpreter GUI

Copyright 2014 Johannes Lange,
for **License** see [LICENSE file](LICENSE)

![Screenshot](https://raw.githubusercontent.com/johannes-lange/qt-bfint/master/resources/qt-bfint.png)

##### Building
- **Prerequisites**: [Qt4](https://qt-project.org/)
- **Linux**: In the base-path (where the qt-bfint.pro is located):
<pre><code>$ qmake
$ make
$ ./bin/qt-bfint</pre></code>
- **Windows**
 * in Visual Studio Command prompt
<pre><code>$ qmake
$ nmake release</pre></code>
 * static build (static build of Qt necessary): add <code>CONFIG += static</code> to qt-bfint.pro, then repeat step above
 * with Visual Studio (2010) IDE: Generate .vcproj-file via <code>$ qmake -spec win32-msvc2010 -tp vc</code>
   and open it in VS. (Note: VS-Project sets target name to qt-bfintVERSION.exe (<- change this is in VS manually)
   but linker creates qt-bfint.exe)
 * or just get precompiled [binary](https://github.com/johannes-lange/qt-bfint/releases/download/v0.1/qt-bfint_win-binary.zip)

##### [TODO](TODO.md)s, known bugs, planned features

##### [Release](https://github.com/johannes-lange/qt-bfint/releases) notes:
- development Version 0.2b: nested loops work, variable tape size
- 2014-02-11 [Version 0.1](https://github.com/johannes-lange/qt-bfint/releases/tag/v0.1): first released version
