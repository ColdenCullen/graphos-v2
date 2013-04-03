#ifndef _GRAPHICS_CONTROLLER_H_
#define _GRAPHICS_CONTROLLER_H_

#include "WindowController.hpp"
#include "ShaderController.h"

namespace Graphos
{
	namespace Graphics
	{
		class GraphicsController
		{
		public:
			enum				GLFunctions
									: int { BEGIN, END };

			bool				Initialize( void );
			void				Resize( bool fullScreen, unsigned int newWidth = 0, unsigned int newHeight = 0 );
			void				CallGLFunction( GLFunctions function );

			void				MessageLoop( void ) { WindowController::Get().MessageLoop(); }

			static
			GraphicsController&	Get( void )
			{
				static GraphicsController instance;
				return instance;
			}

		private:
								GraphicsController( void ) { }
								GraphicsController( const GraphicsController& );
			void				operator=( const GraphicsController& );
		};
	}
}

#endif//_GRAPHICS_CONTROLLER_H_