FTGL Version 1.3

This project will build a static library (archive) in this directory.

FTGL requires the Freetype2 library (version 2.0.3 or later) and OpenGL (glu version 1.2 or later). You may need to edit the paths to point to the correct place. It also uses STL containers.

To use FTGL in your own projects you will need to link against this lib and include the FTGL headers located in the src directory. Your project will also need to point to Freetype and OpenGL.

For instructions on using Freetype go to www.freetype.org
For instructions on using OpenGL go to www.opengl.org

Please contact me if you have any suggestions, feature requests, or problems.

Note: Problems building freetype on MAC OSX

When using make to build freetype you may come across the following error...

ld: -undefined error must be used when -twolevel_namespace is in effect
/usr/bin/libtool: internal link edit command failed
make: *** [/freetype/objs/libfreetype.la] Error 1

This is because of a change in the way 10.1 runtime enviroment handles shared libraries. See http://developer.apple.com/techpubs/macosx/ReleaseNotes/TwoLevelNamespaces.html for more details.

This problem will go away when freetype is upgraded to use the latest version of libtool. In the meantime try this hack:)

run make setup and make as per usual
if/when it barfs with the above error message edit the file builds/unix/libtool
search for the line ...

allow_undefined_flag="-undefined suppress"

and comment it out. Stick a # in front.
type make again and bobs your aunty's live in lover. Then continue as per the instruction that came with freetype.

Henry Maddocks
henryj@paradise.net.nz
http://homepages.paradise.net.nz/henryj/
