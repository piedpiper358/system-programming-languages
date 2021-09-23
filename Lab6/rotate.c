#include <stdio.h>
#include <stdlib.h> 
#include <math.h> 


#include "image.h"
#include "bmp.h"
#include "greyscale.h"  /* sign */
#include "rotate.h"

 
 int rotate_all(image_t*  source, image_t* dest, double angle )
 {
	if(fmod(angle, 360.0)==0)
	{
		printf("Used function:  nothing\n");
		*dest=*source;  
		return 0;
	}
	
	if(fmod(angle, 270.0)==0)
	{
		printf("Used function:  rotate_left\n");
		return rotate_left(source, dest);
	}
	if(fmod(angle, 180.0)==0)
	{
		printf("Used function:  rotate_upside_down\n");
		return rotate_upside_down(source, dest);
	}
	if(fmod(angle, 90.0)==0)
	{
		printf("Used function:  rotate_right\n");
		return rotate_right(source, dest);
	}
	else
	{
		printf("Used function:  rotate_given\n");
		return rotate_given(source, dest, angle);
	}
	
	
	/* switch((int)angle/90.0)
	{
		case 1:
			printf("90!!!\n");
			dest=rotate_right(source);
			break;
		case 2:  
			printf("180!!!\n");
			dest=rotate_180(source);
			break;
		case 3:  
			printf("270!!!\n");
			dest=rotate_left(source);
			break;
		default:
			printf("smth!!!\n");
			dest=rotate_given(source, angle);
			break;
	} */
 }
  int rotate_precision(image_t const * const source, image_t* dest)
  {
	  /* говно жопа сложнаа */
	  return 0;
  }

 int rotate_right(image_t const * const source, image_t* dest)
 {
	int i, j;
	/* double xpos, ypos; */
	image_t tmp;
	tmp.height=sign(source->height)*source->width;
	tmp.width=abs(source->height);
	tmp.data=(pixel_t*)calloc(sizeof(pixel_t), tmp.width*abs(tmp.height));
	
	/* tmp.data=calloc( sizeof(pixel_t*), tmp.width);
	for (i=0; i< tmp.width; i++)
	{
		tmp.data[i]=(pixel_t*)calloc(sizeof(pixel_t), tmp.height);
	} */
	
	if(tmp.data==NULL)
	{
		return ROTATE_OUT_OF_MEMORY;
	}

	for (i=0; i<tmp.width; i++)
	{
		for(j=0; j<abs(tmp.height); j++)
		{ 
	
		 /* tmp.data[j*tmp.width+i]=source->data[i*source->width+j];  зеркало*/
		 /*  tmp.data[j][i]=source->data[i][tmp.height-1-j]; */
			/* tmp.data[j*tmp.width+i]=source->data[j*source->width+i]; */ /* без изменений */
		 
		 
		if(source->height>0)
			tmp.data[j*tmp.width+i]=source->data[i*source->width+(source->width-1-j)];
		else 
			tmp.data[j*tmp.width+i]=source->data[(abs(source->height)-1-i)*source->width+j];
			
			
			/* xpos=-sign(source->height)*((double)j-abs(tmp.height)/2.0)+ source->width/2.0;
			ypos=sign(source->height)*((double)i-tmp.width/2.0)+ abs(source->height)/2.0;
			tmp.data[j*tmp.width+i]=source->data[(int)(round(ypos)*(double)source->width+round(xpos))]; */
			
		}
	}
	 if(source==dest)
	 {
		 /* printf("They are the same!!!\n"); */
		 free(source->data);
		 
	 }
	 *dest=tmp;
	 
	 return 0;
 }
 
 
 int rotate_left(image_t const * const source, image_t* dest )
 {
	int i, j;
	image_t tmp;
	tmp.height=sign(source->height)*source->width;
	tmp.width=abs(source->height);
	tmp.data=(pixel_t*)calloc(sizeof(pixel_t), tmp.width*abs(tmp.height));
	if(tmp.data==NULL)
	{
		return ROTATE_OUT_OF_MEMORY;
	}

	 for (i=0; i<tmp.width; i++)
	 {
		 for(j=0; j<abs(tmp.height); j++)
		 { 
	
		 /* tmp.data[j*tmp.width+i]=source->data[i*source->width+j];  */
			/* tmp.data[j*tmp.width+i]=source->data[j*source->width+i]; */ /* без изменений */
			
			
			 if(source->height>0)
				 tmp.data[j*tmp.width+i]=source->data[(abs(source->height)-1-i)*source->width+j];
			  
			 else 
				tmp.data[j*tmp.width+i]=source->data[i*source->width+(source->width-1-j)];
		 }
	 }
	 
	 if(source==dest)
	 {
		 /* printf("They are the same!!!\n"); */
		 free(source->data);
		 
	 }
	 *dest=tmp;
	 
	 return 0;
 }
 
 
 
 
 int rotate_upside_down(image_t const * const source, image_t* dest)
 {
	int i, j;
	image_t tmp;
	tmp.height=-source->height;
	tmp.width=source->width;
	tmp.data=(pixel_t*)calloc(sizeof(pixel_t), tmp.width*abs(tmp.height));
	if(tmp.data==NULL)
	{
		return ROTATE_OUT_OF_MEMORY;
	}

	
	for (i=0; i<tmp.width; i++)
	{
		for(j=0; j<abs(tmp.height); j++)
		{ 
			tmp.data[j*tmp.width+i]=source->data[j*source->width+(source->width-1-i)];
		} 
	}
	if(source==dest)
	 {
		 /* printf("They are the same!!!\n"); */
		 free(source->data);
		 
	 }
	 *dest=tmp;
	 
	 return 0;
	 
	 
	/* source->height=-source->height;
	return source; */
 }
 
 
 
 int rotate(image_t const * const source, image_t* dest, rotate_type type )
 {
	int i, j;
	image_t tmp;
	tmp.height=source->width;
	tmp.width=source->height;
	tmp.data=(pixel_t*)calloc(sizeof(pixel_t), tmp.width*tmp.height);
	if(tmp.data==NULL)
	{
		return ROTATE_OUT_OF_MEMORY;
	}

	
	for (i=0; i<tmp.width; i++)
	 {
		 for(j=0; j<tmp.height; j++)
		 {
			switch (type)
			{
				case 0: 
					tmp.data[j*tmp.width+i]=source->data[i*source->width+(tmp.height-1-j)];
					break;
				case 1:  
					tmp.data[j*tmp.width+i]=source->data[(source->height-1-i)*source->width+j];
					break;
			}
		 }
	 }
	 if(source==dest)
	 {
		 /* printf("They are the same!!!\n"); */
		 free(source->data);
		 
	 }
	 *dest=tmp;
	 
	 return 0;
 }

 double cosdeg(double arg)
 {
	 return cos(arg*acos(-1.0)/180); /* pi/180 */
 }
 double sindeg(double arg)
 {
	 return sin(arg*acos(-1.0)/180);
 }
 
 
 

 int rotate_given(image_t const * const source, image_t* dest, double angle )
 {
	double xpos, ypos;
	int i, j;
	image_t tmp;
	
	tmp.width=abs(source->width*cosdeg(angle))+abs(source->height*sindeg(angle));
	tmp.height= sign(source->height)* (abs(source->height*cosdeg(angle))+abs(source->width*sindeg(angle)));
	tmp.data=(pixel_t*)calloc(sizeof(pixel_t), tmp.width*abs(tmp.height));
	/* double anchorw=tmp.width/2.0;
	double anchorh=tmp.height/2.0; */
	if(tmp.data==NULL)
	{
		return ROTATE_OUT_OF_MEMORY;
	}

	 
	for (i=0; i<tmp.width; i++)
	{
		for(j=0; j<abs(tmp.height); j++)
		{ 
			xpos=((double)i-tmp.width/2.0)*cosdeg(angle)- sign(source->height)*((double)j-abs(tmp.height)/2.0)*sindeg(angle)+ source->width/2.0;
			ypos=((double)j-abs(tmp.height)/2.0)*cosdeg(angle)+ sign(source->height)*((double)i-tmp.width/2.0)*sindeg(angle)+ abs(source->height)/2.0;
			
			if (((int)round(xpos)>0) && ((int)round(xpos)< source->width) && ((int)round(ypos)>0) && ((int)round(ypos)< abs(source->height)))
			{
				tmp.data[j*tmp.width+i]=source->data[(int)(round(ypos)*(double)source->width+round(xpos))];
			}
			else
			{
				tmp.data[j*tmp.width+i]=white_pixel;
			}
			
			/* ansi!! if (((int)floor(xpos)>0) && ((int)floor(xpos)< source->width) && ((int)floor(ypos)>0) && ((int)floor(ypos)< abs(source->height)))
			{
				tmp.data[j*tmp.width+i]=source->data[(int)(floor(ypos)*(double)source->width+floor(xpos))];
			}
			else
			{
				tmp.data[j*tmp.width+i]=white_pixel;
			} */
		}
	}
	 if(source==dest)
	 {
		 /* printf("They are the same!!!\n"); */
		 free(source->data);
		 
	 }
	 *dest=tmp;
	 
	 return 0;
 }
 
 
  

 /* ---------archive-----------------------------------------------------------*/
 image_t rotate_given_new(image_t const source, double angle )
 {
	int i, j;
	double xpos, ypos;
	image_t dest;
	
	dest.width=abs(source.width*cosdeg(angle))+abs(source.height*sindeg(angle));
	dest.height=abs(source.height*cosdeg(angle))+abs(source.width*sindeg(angle));
	dest.data=(pixel_t*)calloc(sizeof(pixel_t), dest.width*dest.height);
	
	if(dest.data==NULL)
	{
		printf("Error");
		/* errno=1; */
	}

	 
	for (i=0; i<source.width; i++)
	{
		for(j=0; j<source.height; j++)
		{ 
	
			xpos=(((double)i-source.width/2.0)*cosdeg(angle)+ ((double)j-source.height/2.0)*sindeg(angle))+ dest.width/2.0;
			ypos=(((double)j-source.height/2.0)*cosdeg(angle)- ((double)i-source.width/2.0)*sindeg(angle))+ dest.height/2.0;

			if ((((int)xpos>=0) && ((int)xpos< dest.width)) && (((int)ypos>=0) && ((int)ypos< dest.height)))
			{
				dest.data[(int)(floor(ypos)*dest.width+floor(xpos))]=source.data[j*source.width+i];
			}
			else 
			{
				dest.data[j*dest.width+i]=white_pixel; /* // говно // */
			}
		}
	 }
	 
	 free(source.data);
	 return dest;
 }
 
 image_t rotate_given_pos(image_t const source, double angle )
 {
	double xpos, ypos;
	int i, j;
	image_t dest;
	
	dest.width=abs(source.width*cosdeg(angle))+abs(source.height*sindeg(angle));
	dest.height=abs(source.height*cosdeg(angle))+abs(source.width*sindeg(angle));
	dest.data=(pixel_t*)calloc(sizeof(pixel_t), dest.width*dest.height);
	/* double anchorw=dest.width/2.0;
	double anchorh=dest.height/2.0; */
	if(dest.data==NULL)
	{
		printf("Error");
		/* errno=1; */
	}

	 
	for (i=0; i<dest.width; i++)
	{
		for(j=0; j<dest.height; j++)
		{ 
			xpos=(((double)i-dest.width/2.0)*cosdeg(angle)- ((double)j-dest.height/2.0)*sindeg(angle))+ source.width/2.0;
			ypos=(((double)j-dest.height/2.0)*cosdeg(angle)+ ((double)i-dest.width/2.0)*sindeg(angle))+ source.height/2.0;
	 
			if ((((int)round(xpos)>0) && ((int)round(xpos)< source.width)) && (((int)round(ypos)>0) && ((int)round(ypos)< source.height)))
			{
				dest.data[j*dest.width+i]=source.data[(int)(round(ypos)*(double)source.width+round(xpos))];  /* если round, то -1 */
			}
			else
			{
				dest.data[j*dest.width+i]=white_pixel;
			}
		}
	}
	 free(source.data);
	 return dest;
 }

 image_t rotate_right_and_not_free(image_t const source)
 {
	int i, j;
	/* double xpos, ypos; */
	image_t dest;
	dest.height=sign(source.height)*source.width;
	dest.width=abs(source.height);
	dest.data=(pixel_t*)calloc(sizeof(pixel_t), dest.width*abs(dest.height));
	
	/* dest.data=(pixel_t*)calloc( sizeof(pixel_t*), dest.width);
	for (i=0; i< dest.width; i++)
	{
		dest.data[i]=(pixel_t*)calloc(sizeof(pixel_t), dest.height);
	} */
	
	if(dest.data==NULL)
	{
		printf("Error");
		/* errno=1; */
	}

	for (i=0; i<dest.width; i++)
	{
		for(j=0; j<abs(dest.height); j++)
		{ 
	
		 /* dest.data[j*dest.width+i]=source.data[i*source.width+j];  зеркало*/
		 /*  dest.data[j][i]=source.data[i][dest.height-1-j]; */
			/* dest.data[j*dest.width+i]=source.data[j*source.width+i]; */ /* без изменений */
		 
		 
		if(source.height>0)
			dest.data[j*dest.width+i]=source.data[i*source.width+(source.width-1-j)];
		else 
			dest.data[j*dest.width+i]=source.data[(abs(source.height)-1-i)*source.width+j];
			
			
			/* xpos=-sign(source.height)*((double)j-abs(dest.height)/2.0)+ source.width/2.0;
			ypos=sign(source.height)*((double)i-dest.width/2.0)+ abs(source.height)/2.0;
			dest.data[j*dest.width+i]=source.data[(int)(round(ypos)*(double)source.width+round(xpos))]; */
			
		}
	}
	 
	 free(source.data);
	 return dest;
 }