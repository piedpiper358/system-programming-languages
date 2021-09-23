#include <stdint.h> /* uint32_t */

#ifndef _IMAGE_H_
#define _IMAGE_H_



#pragma pack(push, 2)
typedef struct pixel_t { unsigned char b,g,r; } pixel_t;
 #pragma pack(pop)
 

 #pragma pack(push, 2)
typedef struct image_t {
	uint32_t width/* , height */;/* uint_t */
	int32_t height;
	/* struct pixel_t* data; */
	/* struct */ pixel_t* data;
} image_t;
 #pragma pack(pop)

 
extern const pixel_t black_pixel;
extern const pixel_t white_pixel;
 

#endif

