#ifndef     __FTGLTextureFont__
#define     __FTGLTextureFont__

#include "FTGL.h"
#include "FTFont.h"

class FTTextureGlyph;


/**
 * FTGLTextureFont is a specialisation of the FTFont class for handling
 * Texture mapped fonts
 *
 * @see     FTFont
 */
class  FTGL_EXPORT FTGLTextureFont : public FTFont
{
    public:
        /**
         * Open and read a font file. Sets Error flag.
         *
         * @param fontname  font file name.
         */
        FTGLTextureFont( const char* fontname);
        
        /**
         * Open and read a font from a buffer in memory. Sets Error flag.
         *
         * @param pBufferBytes  the in-memory buffer
         * @param bufferSizeInBytes  the length of the buffer in bytes
         */
        FTGLTextureFont( const unsigned char *pBufferBytes, size_t bufferSizeInBytes);
        
        /**
         * Destructor
         */
        virtual ~FTGLTextureFont();
        
        /**
         * Get the total width of the texture that holds this font
         */
        GLsizei TextureWidth() const { return textureWidth;}
        
        /**
         * Get the total height of the texture that holds this font
         */
        GLsizei TextureHeight() const { return textureHeight;}
        
        /**
         * Renders a string of characters
         * 
         * @param string    'C' style string to be output.   
         */
        virtual void render( const char* string);
        
        /**
         * Renders a string of characters
         * 
         * @param string    wchar_t string to be output.     
         */
        virtual void render( const wchar_t* string);

        
    private:
        inline virtual FTGlyph* MakeGlyph( unsigned int g);
                
        /**
         * Constructs the internal glyph cache.
         *
         * This a list of glyphs processed for openGL rendering NOT
         * freetype glyphs
         */
        virtual bool MakeGlyphList();

        /**
         * Get the size of a block of memory required to layout the glyphs
         *
         * Calculates a width and height based on the glyph sizes and the
         * number of glyphs. It over estimates.
         */
        inline void GetSize();

        /**
         * Creates a 'blank' OpenGL texture object.
         *
         * The format is GL_ALPHA and the params are
         * GL_TEXTURE_WRAP_S = GL_CLAMP
         * GL_TEXTURE_WRAP_T = GL_CLAMP
         * GL_TEXTURE_MAG_FILTER = GL_LINEAR
         * GL_TEXTURE_MIN_FILTER = GL_LINEAR
         * Note that mipmapping is NOT used
         */
        inline int CreateTexture();
        
        /**
         * The maximum texture dimension on this OpenGL implemetation
         */
        GLsizei maxTextSize;
        
        /**
         * The minimum texture width required to hold the glyphs
         */
        GLsizei textureWidth;
        
        /**
         * The minimum texture height required to hold the glyphs
         */
        GLsizei textureHeight;
        
        /**
         *An array of texture ids
         */
        unsigned long glTextureID[128];
        
        /**
         * The number of textures required to hold the glyphs
         */
        unsigned int numTextures;

        /**
         * The memory where the textures are built before being transferred 
         * to OpenGL
         */
        unsigned char* textMem;
        
        /**
         * The max height for glyphs in the current font
         */
        int glyphHeight;

        /**
         * The max width for glyphs in the current font
         */
        int glyphWidth;

        /**
         * A value to be added to the height and width to ensure that
         * glyphs don't overlap in the texture
         */
        unsigned int padding;
        
        /**
         *
         */
         unsigned int numGlyphs;
        
        /**
         */
        unsigned int remGlyphs;

        /**
         */
        int xOffset;

        /**
         */
        int yOffset;

};


#endif // __FTGLTextureFont__


