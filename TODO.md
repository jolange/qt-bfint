#### TODO
- interrupt reasons
- error checks (range checks, parsing/check brackets "online")
- VS-Project sets target name to qt-bfint<version>.exe but linker creates qt-bfint.exe
- doxygen
- cancel in file-dialogs
- about-resource


#### Bugs
- no closing brace => loop-sequence to end of file
- GOL does not work (how are multi-sign inputs handled there? writing to next cells?)

#### Planned Features
- undo/redo in menu: use the actions of QTextBrowser
- output: show inputs? different colouring (html)? http://qt-project.org/doc/qt-4.8/richtext-syntaxhighlighter.html
- static build windows
  * download in release
  * link in readme
