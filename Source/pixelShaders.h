/*

  ==============================================================================



    pixelShaders.h

    Created: 10 Dec 2016 10:30:13am

    Author:  hal



  ==============================================================================

*/




#ifndef PIXELSHADERS_H_INCLUDED

#define PIXELSHADERS_H_INCLUDED

#if defined JUCE_ANDROID

String fragmentShaderString =

"\n"
"precision "  JUCE_MEDIUMP " float;\n"
"\n"

"uniform "  JUCE_MEDIUMP "  float rainbowizer;\n"
"uniform "  JUCE_MEDIUMP "  float coordx;\n"
"uniform "  JUCE_MEDIUMP "  float coordy;\n"
"uniform "  JUCE_MEDIUMP "  float height;\n"
"uniform "  JUCE_MEDIUMP "  float width;\n"
"\n"
"\n"
"const int iterations = 200;\n"
"const float escapetest = 100.0;\n"
"\n"
"\n"

"float smooth_( vec2 pos, int iteration)\n"
"{\n"
"    float log_zn = log( pos.x*pos.x + pos.y*pos.y ) / 2.0;\n"
"    float nu = log( log_zn / log(2.0) ) / log(2.0);\n"
"\n"
"    return float(iteration) + 1.0 - nu;"
"}\n"
"\n"
"\n"
"\n"
"float plot( vec2 pos, vec2 offset ){\n"
"		\n"
"	bool escape = false;\n"
"	int iteration = 0;\n"
"	for(int i = 0; i < iterations; ++i)\n"
"	{\n"
"		if(pos.x * pos.x + pos.y * pos.y > escapetest * escapetest)\n"
"		{\n"
"			pos = vec2(0,escapetest);\n"
"			escape = true;\n"
"			break;\n"
"		}\n"
"		\n"
"		float x = pos.x*pos.x - pos.y*pos.y + offset.x;\n"
"    		float y = 2.0*pos.x*pos.y + offset.y;\n"
"    		pos.x = x;\n"
"		pos.y = y;\n"
"		\n"
"		++iteration;\n"
"	}\n"
"	\n"
"	float nu = smooth_(pos, iteration);\n"
"	if(escape) return nu;\n"
"	\n"
"	return (pos.x * pos.x + pos.y * pos.y) / (escapetest * escapetest);\n"
"}\n"
"\n"
"void main( void ) {\n"
"	vec2 offset = vec2(-0.5, -0.5);\n"
"	vec2 scale = vec2(4, 2.5);\n"
"	\n"
"	vec2 position = scale * (gl_FragCoord.xy / vec2 (width,height).xy + offset);\n"
"	\n"
"	//Mandelbrot\n"
"	vec2 man = position;\n"
"	\n"
"	//Julia\n"
"	//turned off vec2 jul = vec2((coordx - 0.5) * 2.0, (coordy - 0.5) * 2.0);\n"
"	\n"
"	float value1 = plot(position, man);\n"
"	//turned off float value2 = plot(position, jul);\n"
"	\n"
"	//turned offvec4 color1 = mix(value1, value1, value1);\n"
"	//turned offvec4 color2 = mix(red, white, value2);\n"
"	//turned offcolor2.a = 0.5;\n"
"	\n"
"	gl_FragColor =  vec4(value1,value1,value1, pixelAlpha);\n"
"\n"
"}";

#else

String fragmentShaderString =

"uniform "  JUCE_MEDIUMP "  float rainbowizer;\n"
"uniform "  JUCE_MEDIUMP "  float coordx;\n"
"uniform "  JUCE_MEDIUMP "  float coordy;\n"
"uniform "  JUCE_MEDIUMP "  float height;\n"
"uniform "  JUCE_MEDIUMP "  float width;\n"
"\n"
"\n"
"const int iterations = 200;\n"
"const float escapetest = 100.0;\n"
"\n"
"\n"

"float smooth_( vec2 pos, int iteration)\n"
"{\n"
"    float log_zn = log( pos.x*pos.x + pos.y*pos.y ) / 2.0;\n"
"    float nu = log( log_zn / log(2.0) ) / log(2.0);\n"
"\n"
"    return float(iteration) + 1.0 - nu;"
"}\n"
"\n"
"\n"
"\n"
"float plot( vec2 pos, vec2 offset ){\n"
"		\n"
"	bool escape = false;\n"
"	int iteration = 0;\n"
"	for(int i = 0; i < iterations; ++i)\n"
"	{\n"
"		if(pos.x * pos.x + pos.y * pos.y > escapetest * escapetest)\n"
"		{\n"
"			pos = vec2(0,escapetest);\n"
"			escape = true;\n"
"			break;\n"
"		}\n"
"		\n"
"		float x = pos.x*pos.x - pos.y*pos.y + offset.x;\n"
"    		float y = 2.0*pos.x*pos.y + offset.y;\n"
"    		pos.x = x;\n"
"		pos.y = y;\n"
"		\n"
"		++iteration;\n"
"	}\n"
"	\n"
"	float nu = smooth_(pos, iteration);\n"
"	if(escape) return nu;\n"
"	\n"
"	return (pos.x * pos.x + pos.y * pos.y) / (escapetest * escapetest);\n"
"}\n"
"\n"
"void main( void ) {\n"
"	vec2 offset = vec2(-0.5, -0.5);\n"
"	vec2 scale = vec2(4, 2.5);\n"
"	\n"
"	vec2 position = scale * (gl_FragCoord.xy / vec2 (width,height).xy + offset);\n"
"	\n"
"	//Mandelbrot\n"
"	vec2 man = position;\n"
"	\n"
"	//Julia\n"
"	//turned off vec2 jul = vec2((coordx - 0.5) * 2.0, (coordy - 0.5) * 2.0);\n"
"	\n"
"	float value1 = plot(position, man);\n"
"	//turned off float value2 = plot(position, jul);\n"
"	\n"
"	//turned offvec4 color1 = mix(value1, value1, value1);\n"
"	//turned offvec4 color2 = mix(red, white, value2);\n"
"	//turned offcolor2.a = 0.5;\n"
"	\n"
"	gl_FragColor =  vec4(value1,value1,value1, pixelAlpha);\n"
"\n"
"}";

#endif
#endif  // PIXELSHADERS_H_INCLUDED
