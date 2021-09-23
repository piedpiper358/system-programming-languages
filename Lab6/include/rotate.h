
#include <stdio.h>
#include "image.h"


#ifndef _ROTATE_H_
#define _ROTATE_H_

typedef enum {
 ROTATE_CLOCKWISE = 0,
 ROTATE_COUNTERCLOCKWISE
/*  ROTATE_LEFT, */
 /* ROTATE_180 */
 } rotate_type;
 
 
 typedef enum {
 ROTATE_OK = 0,
 ROTATE_OUT_OF_MEMORY
 /* more codes */
 } rotate_error_code_t;


 int rotate_all(image_t*  source, image_t* dest, double angle );
 int rotate_right(image_t const * const source, image_t* dest);
 int rotate_left(image_t const * const source, image_t* dest );
 int rotate_upside_down(image_t const * const source, image_t* dest);
 int rotate(image_t const * const source, image_t* dest, rotate_type type );
 int rotate_given(image_t const * const source, image_t* dest, double angle );
 
 
 
/* double sindeg(double arg);
double cosdeg(double arg); */



#endif

 






 



