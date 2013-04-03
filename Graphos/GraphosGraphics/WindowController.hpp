#ifndef _WINDOWCONTROLLER_H_
#define _WINDOWCONTROLLER_H_

#include <GL/glincludes.h>

#ifdef _WIN32
 #include "Resource.h"
 #include "stdafx.h"
#endif

#include "SettingsController.hpp"
#include "Input.h"
#include "../GraphosMath/GraphosMath.h"

#define BACKFACE_CULLING true

using namespace Graphos::Math;

namespace Graphos
{
	namespace Graphics
	{
#pragma region PlatformWindowController
		class PlatformWindowController
		{
		public:
			virtual bool		Initialize( void ) = 0;
			virtual void		Shutdown( void ) = 0;
			virtual void		Resize( bool fullScreen, unsigned int newWidth = 0, unsigned int newHeight = 0 ) = 0;

			// Getters
			unsigned int		GetWidth( void )	{ return width; }
			unsigned int		GetHeight( void )	{ return height; }
			HDC&				GetDeviceContext( void ) { return deviceContext; }
			HGLRC&				GetRenderContext( void ) { return renderContext; }
			Matrix4&			GetPerspectiveMatrix( void ) { return perspectiveMatrix; }

		protected:
			unsigned int		width;
			unsigned int		height;
			bool				fullScreen;

			Matrix4				perspectiveMatrix;
			HDC					deviceContext;
			HGLRC				renderContext;
		};
#pragma endregion

#pragma region Win32Controller
#ifdef _WIN32
		class Win32Controller : public PlatformWindowController
		{
		public:
			bool				Initialize( void );
			void				Shutdown( void );
			void				Resize( bool fullScreen, unsigned int newWidth = 0, unsigned int newHeight = 0 );
			void				MessageLoop( void );

			// Getters
			HWND				GetHWnd( void ) { return hWnd; }

			friend class		WindowController;

		private:
								Win32Controller( void ) { }
								Win32Controller( Win32Controller& );
			void				operator=( Win32Controller& );

			HINSTANCE			hInstance;						// Current Windows application instance
			HWND				hWnd;							// Current Windows window

			static
			LRESULT CALLBACK	WndProc( HWND, UINT, WPARAM, LPARAM );
		};
#endif
#pragma endregion

#pragma region WindowController
		class WindowController
		{
		public:
#ifdef _WIN32
			static
			Win32Controller&	Get( void )
			{
				static Win32Controller instance;
				return instance;
			}
#endif

		private:
								WindowController( void ) { }
								WindowController( const WindowController& );
			void				operator=( const WindowController& );
		};
#pragma endregion
	}
}

#endif//_WINDOWCONTROLLER_H_