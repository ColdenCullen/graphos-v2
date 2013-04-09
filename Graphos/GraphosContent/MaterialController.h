#ifndef _MATERIAL_CONTROLLER_H_
#define _MATERIAL_CONTROLLER_H_

#include "Texture.h"

namespace Graphos
{
	namespace Content
	{
		class MaterialController
		{
		public:
			MaterialController( void );

		private:
			Texture* textures;
		};
	}
}

#endif //_MATERIAL_CONTROLLER_H_