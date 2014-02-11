### TODO
- static build windows
  * download in release
  * link in readme
- http://stackoverflow.com/questions/19013696/how-to-generate-a-visual-studio-project-file-when-i-build-my-qmake-project

#### Bugs
- GOL does not work (how are multi-sign inputs handled there? writing to next cells?)
- VS-Project sets target name to qt-bfint<version>.exe (<- change this is in VS manually) but linker creates qt-bfint.exe
- appending [.] to hello world: maxloops=10 no ouput, maxloops>=11 works

#### Planned Features
- undo/redo in menu: use the actions of QTextBrowser
- save file: automatically add extension
- choose cell/tape size in UI
- output: show inputs? different colouring (html)? http://qt-project.org/doc/qt-4.8/richtext-syntaxhighlighter.html
- doxygen

