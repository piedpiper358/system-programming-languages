#include <stdio.h>
#include <stdlib.h> 


#include "image.h"
#include "bmp.h"


 #pragma pack(push, 2)
typedef struct bmp_header_t{
	uint16_t bfType;
	uint32_t bfileSize;
	uint32_t bfReserved;
	/*  uint16_t bfReserved1;
	 uint16_t bfReserved2; */
	
	
	uint32_t bfOffBits;
	uint32_t biSize;
	uint32_t biWidth;
	int32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
} bmp_header_t;
#pragma pack(pop)

typedef struct BITMAPFILEHEADER{
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1;
	uint16_t bfReserved2;
	uint32_t bfOffBits;
} BITMAPFILEHEADER;	

typedef struct BITMAPINFO{
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
} BITMAPINFO;

 

read_error_code_t from_bmp( FILE* in, image_t* const read )
{
	int offset=0;
	int i;
	int ret;
	bmp_header_t bmph;/* BITMAPFILEHEADER */
	
	
	fread(&bmph, sizeof(bmph), 1, in);
		if ((ret=ferror(in)))
		return READ_INVALID_HEADER;
	read->width=bmph.biWidth;
	read->height=bmph.biHeight;
	read->data=(pixel_t*)calloc(sizeof(pixel_t), read->width*abs(read->height));
		if(read->data==NULL)
		return READ_OUT_OF_MEMORY; 
	
	
	/* двумерный массив */ /* read->data=(pixel_t**)calloc( sizeof(pixel_t*), read->width);
	for (i=0; i< read->width; i++)
	{
		read->data[i]=(pixel_t*)calloc(sizeof(pixel_t), read->height);
	}
	 */
	fseek(in, bmph.bfOffBits, SEEK_SET);
	
	for (i=0; i< abs(read->height); i++)
	{
		offset+= fread(read->data+offset, sizeof(pixel_t), read->width, in);
			if ((ret=ferror(in)))
			return READ_ERROR;
		
		/* fseek(in, (read->width*sizeof(pixel_t)+3)/4*4 // & (-4)// , SEEK_CUR); */
		
		fseek(in, (4-read->width*sizeof(pixel_t)%4)%4, SEEK_CUR);
			if ((ret=ferror(in)))
			return READ_INVALID_PIXELS; /* READ_ERROR; */

	}
	 return READ_OK;
}

 write_error_code_t to_bmp( FILE* out, struct image_t const* img )
  {
	  int ret;
	  int i;
	  int offset;
	  
	/*   uint32_t newSize=(img->width*sizeof(pixel_t)+(4-img->width*sizeof(pixel_t)%4)%4)*img->height*sizeof(pixel_t);
	  
	  
	 fseek(out, 2, SEEK_SET);
		if ((ret=ferror(out)))
		return WRITE_ERROR;
	fwrite(&newSize, sizeof(uint32_t), 1, out);
		if ((ret=ferror(out)))
		return WRITE_ERROR;
	
	fseek(out, 34, SEEK_SET);
		if ((ret=ferror(out)))
		return WRITE_ERROR;
	fwrite(&newSize, sizeof(uint32_t), 1, out);
		if ((ret=ferror(out)))
		return WRITE_ERROR; */
	  
	 
	/* fseek(out, 10, SEEK_SET);
		ret=ferror(out);
		if (ret)
		return WRITE_ERROR;
	 fread(&offset, sizeof(uint32_t), 1, out);
		ret=ferror(out);
		if (ret)
		return WRITE_ERROR; */
	
	fseek(out, 18, SEEK_SET);
		if ((ret=ferror(out)))
		return WRITE_ERROR;
	fwrite(&(img->width), sizeof(uint32_t), 1, out);
		if ((ret=ferror(out)))
		return WRITE_ERROR;
	/* 
	fseek(out, 22, SEEK_SET);
		if ((ret=ferror(out)))
		return WRITE_ERROR;
	 */
	 fwrite(&(img->height), sizeof(uint32_t), 1, out);
		if ((ret=ferror(out)))
		return WRITE_ERROR;
	
	fseek(out, 10, SEEK_SET);
		if ((ret=ferror(out)))
		return WRITE_ERROR;
	fread(&offset, sizeof(uint32_t), 1, out);
		if ((ret=ferror(out)))
		return WRITE_ERROR;
	  
	fseek(out, offset, SEEK_SET);
	  
	  
	offset=0;
	  
	  
	for (i=0; i< abs(img->height); i++)
	{
		offset+= fwrite(img->data+offset, sizeof(pixel_t), img->width, out);
			if ((ret=ferror(out)))
			return WRITE_ERROR;
		
		fwrite(&white_pixel,(4-img->width*sizeof(pixel_t)%4)%4 , 1, out);
		/* fseek(out, (4-img->width*sizeof(pixel_t)%4)%4, SEEK_CUR);
			if ((ret=ferror(out)))
			return WRITE_ERROR; */

	}
	  
	
	fflush(out);
	return WRITE_OK;
  }
 