
#include <stdio.h>
#include "image.h"


#ifndef _BMP_H_
#define _BMP_H_


/* deserializer */
 typedef enum {
 READ_OK = 0,
 READ_ERROR,
 READ_INVALID_SIGNATURE,
 READ_INVALID_BITS,
 READ_INVALID_HEADER, 
 READ_INVALID_PIXELS,
 READ_OUT_OF_MEMORY
 /* more codes */
 } read_error_code_t;

 typedef enum {
 WRITE_OK = 0,
 WRITE_ERROR
 /* more codes */
 } write_error_code_t;
 
 
 read_error_code_t from_bmp( FILE* in, struct image_t* const read ); 
 write_error_code_t to_bmp( FILE* out, struct image_t const* img );
 

#endif

 


 /* image_t from_jpg( FILE* );...
 * and other deserializers are possible
 * All information needed will be
 * stored in image_t structure */

 /* makes a rotated copy */

 
 /* serializer */
 
 /* write_error_code_t to_bmp( FILE* out, struct image_t const* img );
 */

