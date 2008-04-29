/* Small C bindings test program */

#include <ftgl.h>

int main(int argc, char *argv[])
{
    FTGLfont *f;

    if(argc < 2)
        return 1;

    f = ftglCreateBitmapFont(argv[1]);
    if(f == NULL)
        return 2;

    ftglDestroyFont(f);

    return 0;
}

