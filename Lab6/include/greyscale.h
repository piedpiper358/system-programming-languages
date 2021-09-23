
#include "image.h"

#ifndef _GREYSCALE_H_
#define _GREYSCALE_H_


typedef enum {
 PRINT_LIGHTNESS = 0,
 PRINT_AVERAGE,
 PRINT_LUMINOSITY
 /* more */
 } print_type;

 extern const double to_sepia[3][3]; 
 extern const double to_luminosity[3][3];
  extern const double to_luminosity2[3][3];
    extern const double to_luminosity_vano[3][3];
  
  
  
int sepia(image_t const * const source, image_t* dest, const double matrix[3][3]);
 
int print_image(image_t const source);
int print_image_type(image_t const source, print_type type);


int lightness(image_t const * const source, image_t* dest);
int average(image_t const * const source, image_t* dest);
int luminosity(image_t const * const source, image_t* dest);


int sign(int arg);

#endif

