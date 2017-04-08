
/**
*
* Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
*
* This software is provided 'as-is', without any
* express or implied warranty. In no event will
* the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute
* it freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgment
*    in the product documentation would be appreciated but
*    is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __GPU__H_
#define __GPU__H_

#include "GPU_Transfer.h"
#include "GPU_Program.h"
#include "GPU_Sampler.h"
#include "Framework.h"

#define TRIANGLE 3
#define CUBE 36
#define QUAD 6

// A enum for the has function which says if the platform is supported
enum GRAPHIC_API {
	OPENGL,
	DIRECTX
};

// A class which collects info on the GPU for the user
class GPU
{
private:
	// the shader version which is being used
	const GLubyte * shaderVersion;
	// the graphics card type
	const GLubyte * renderer;
	// the version of GL running
	const GLubyte * version;
	// the vendor the made the card
	const GLubyte * vendor;
	// a boolean to track if the card was successfully grabbed
	GLboolean grabbedGPU;
public:
	// Constructor & Deconstructor
	GPU(GLboolean printDetails = GL_TRUE);
	~GPU();

	// returns if the systems has that API Type supported
	GLboolean has(GRAPHIC_API api, GLdouble version);
};

#endif