#include <GL/glew.h>
#if defined( _WIN32 )
 #include <GL/wglew.h>
 #include <GL/GL.h>
#elif defined( __APPLE__ )
 //#include <GL/glxew.h>
 #include <OpenGL/GL.h>
 #include <AGL/AGL.h>
#endif
