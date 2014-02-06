qt-bfint
========
Qt4 based Brainfuck Interpreter GUI

Copyright 2014 Johannes Lange,
for **License** see LICENSE file

__Building__

- **Linux**:
In the base-path (where the qt-bfint.pro is located):
<pre><code>$ qmake
$ make
$ ./build/qt-bfint
</pre></code>

- **Windows** with Visual Studio (2010):
Generate .vcproj-file via <code>$ qmake.exe -spec win32-msvc2010 -tp vc</code>
and open it in VS.

__TODO__
- loop counter for interruption
- error checks (range checks)
- QInputDialog
- input Queue?
- saving, opening, examples
