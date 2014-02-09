#qt-bfint
[Qt4](https://qt-project.org/) based [Brainfuck](http://en.wikipedia.org/wiki/Brainfuck) Interpreter GUI

Copyright 2014 Johannes Lange,
for **License** see [LICENSE file](LICENSE)

##### Building
- **Prerequisites**: [Qt4](https://qt-project.org/)
- **Linux**: In the base-path (where the qt-bfint.pro is located):
<pre><code>$ qmake
$ make
$ ./bin/qt-bfint
</pre></code>
- **Windows** with Visual Studio (2010):
Generate .vcproj-file via <code>$ qmake -spec win32-msvc2010 -tp vc</code>
and open it in VS.

##### [TODO](TODO.md)s, known bugs, planned features
