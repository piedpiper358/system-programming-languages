
#include <stdio.h>
#include <stdlib.h>



#include "image.h"
#include "greyscale.h"


/* #include <wchar.h> */ /* wchar_t */  /* UTF-8 */
/*#define _GNU_SOURCE 1 */ /* wprintf */ 


unsigned char max3(unsigned char a, unsigned char b, unsigned char c)
{
	if(a>b)
	{
		if(a>c)
			{return a;}
		else {return c;}
	}
	else
	{
		if(b>c)
			{return b;}
		else {return c;}
	}
}
unsigned char min3(unsigned char a, unsigned char b, unsigned char c)
{
	if(a<b)
	{
		if(a<c)
			{return a;}
		else {return c;}
	}
	else
	{
		if(b<c)
			{return b;}
		else {return c;}
	}
}
unsigned char min2(unsigned char a, unsigned char b)
{
	return a<b ? a : b;
}
unsigned char max2(unsigned char a, unsigned char b)
{
	return a>b ? a : b;
}


int sign(int arg)
{
	return arg>0 ? 1 : arg<0 ? -1  : 0;
	/* return (arg>0)-(arg<0); */
}


			

int print_image(image_t const source)
{
	/* char* str =" ░▒▓█"; */
	int i, j;
	
	
	 for(j=source.height>0 ? source.height-1 : 0; source.height>0 ? j>=0 : j<abs(source.height); source.height>0 ? j-- : j++)
	{ 
		for (i=0; i<source.width; i++)
		{				
			if(source.data[j*source.width+i].r<50)
				{printf("  ");}
			else
			{
				if(source.data[j*source.width+i].r<100)
						{printf("░░");}
				else 
				{
					if(source.data[j*source.width+i].r<150)
						{printf("▒▒");}
					else 
					{
						if(source.data[j*source.width+i].r<200)
							{printf("▓▓");}
						else
							{printf("██");}
					}
				}
			}		
		}
		printf("\n");
	}
	 return 0;
 }
 
 int print_image_type(image_t const source, print_type type)
{
	/* char* str =" ░▒▓█"; */
	int i, j;
	
	image_t tmp;
	
	switch(type)
	{
		 case PRINT_LIGHTNESS:
		 lightness(&source, &tmp);
		 break;
		case PRINT_AVERAGE:
		average(&source, &tmp);
		 break;
		case PRINT_LUMINOSITY:
		luminosity(&source, &tmp);
		 break;
	}
	
	
	 for(j=tmp.height>0 ? tmp.height-1 : 0; tmp.height>0 ? j>=0 : j<abs(tmp.height); tmp.height>0 ? j-- : j++)
	{ 
		for (i=0; i<tmp.width; i++)
		{				
			if(tmp.data[j*tmp.width+i].r<50)
				{printf("  ");}
			else
			{
				if(tmp.data[j*tmp.width+i].r<100)
						{printf("░░");}
				else 
				{
					if(tmp.data[j*tmp.width+i].r<150)
						{printf("▒▒");}
					else 
					{
						if(tmp.data[j*tmp.width+i].r<200)
							{printf("▓▓");}
						else
							{printf("██");}
					}
				}
			}		
		}
		printf("\n");
	}
	
	free(tmp.data);
	 return 0;
 }
 
 
 
 int print_image_wcchar(image_t const source)
{
	/* wchar_t str[] =L" ░▒▓█sdfsd"; */
	char str[] =" ░▒▓█sdfsd";
	int i, j;
	int index;
	/* printf("%s\n\n", "ррпагрп"); */
	printf("%s\n\n uwdjfdf=%lu", str, sizeof(wchar_t));
	printf("%c%c%c%c%c%c%c%c%c%c%c%c\n\n", str[0],str[1], str[2], str[3], str[4], str[5], str[6], str[7], str[8], str[9], str[10], str[11]);
	
	
		for(j=source.height-1; j>=0; j--)
			{ 
			for (i=0; i<source.width; i++)
			{
				index=source.data[j*source.width+i].r/50;
				
					printf("%c%c%c%c",str[index], str[index+1], str[index+2], str[index+3]);
					/* wprintf(L"%c", str[1]); */
					
				}
				printf("\n");
			}

	 return 0;
 }




int print_image_lum_pos(image_t const source)
{
	double greyscale; /*  ---- */
	int i, j;
	
	
	/* printf(" ----\n \n"); */
	puts("\33[31mHello \33[42;34mworld\33[0m\n");
		for(j=source.height-1; j>=0; j--)
			{ 
			for (i=0; i<source.width; i++)
			{
				
					greyscale=0.299*source.data[j*source.width+i].r+0.587*source.data[j*source.width+i].g+0.114*source.data[j*source.width+i].b;

					
					if(greyscale<50)
					{
						printf("  ");
					}
					else
					{
						if(greyscale<100)
						{printf("--");}
						else 
						{
							if(greyscale<150)
							{printf("--");}
						else {
							if(greyscale<200)
							{printf("--");}
							else
							
							
							printf("--");}
						}
					}
					
				}
				printf("\n");
			}
	
	 return 0;
 }
 
 

 
int lightness(image_t const * const source, image_t* dest)
{
	/*  The lightness method averages the most prominent and least prominent colors: (max(R, G, B) + min(R, G, B)) / 2. */
	int i, j;
	unsigned char lightness;
	pixel_t pix;
	image_t tmp=*source; 
	tmp.data=(pixel_t*)calloc(sizeof(pixel_t), tmp.width*abs(tmp.height));
	
	for (i=0; i<tmp.width; i++)
	{
		for(j=0; j<abs(tmp.height); j++)
		{ 
			pix=source->data[j*source->width+i];
			lightness=(max3(pix.r, pix.g, pix.b) + min3(pix.r, pix.g, pix.b)) / 2;
									
			tmp.data[j*source->width+i].r=lightness;
			tmp.data[j*source->width+i].g=lightness;
			tmp.data[j*source->width+i].b=lightness;
		}		
	}
	
	
	if(source==dest)
	 {
		 printf("They are the same!!!\n");
		 free(source->data);
		 
	 }
	 *dest=tmp;
	 
	 return 0;
/* 	return tmp; */
}


int average(image_t const * const source, image_t* dest)
{
	/* The average method simply averages the values: (R + G + B) / 3. */
	int i, j;
	unsigned char average;
	image_t tmp=*source; 
	tmp.data=(pixel_t*)calloc(sizeof(pixel_t), tmp.width*abs(tmp.height));
	
	
	for (i=0; i<tmp.width; i++)
	{
		for(j=0; j<abs(tmp.height); j++)
		{ 
				
			average=(source->data[j*source->width+i].r+source->data[j*source->width+i].g+source->data[j*source->width+i].b)/3;
			
			tmp.data[j*source->width+i].r=average;
			tmp.data[j*source->width+i].g=average;
			tmp.data[j*source->width+i].b=average;
		}		
	}
	if(source==dest)
	 {
		 printf("They are the same!!!\n");
		 free(source->data);
		 
	 }
	 *dest=tmp;
	 
	 return 0;
}


int luminosity(image_t const * const source, image_t* dest)
{
	/* The luminosity method is a more sophisticated version of the average method. The formula for luminosity is 0.21 R + 0.72 G + 0.07 B. */
	int i, j;
	unsigned char luminosity;
	image_t tmp=*source; 
	tmp.data=(pixel_t*)calloc(sizeof(pixel_t), tmp.width*abs(tmp.height));
	
	/* image_t tmp;
	tmp.height=source->height;
	tmp.width=source->width;
	tmp.data=(pixel_t*)calloc(sizeof(pixel_t), tmp.width*tmp.height); */
	
	for (i=0; i<tmp.width; i++)
	{
		for(j=0; j<abs(tmp.height); j++)
		{ 
				
			luminosity=0.299  /* 0.221 */*source->data[j*source->width+i].r+0.587*source->data[j*source->width+i].g+0.114*source->data[j*source->width+i].b;
			
			tmp.data[j*source->width+i].r=luminosity;
			tmp.data[j*source->width+i].g=luminosity;
			tmp.data[j*source->width+i].b=luminosity;
		}		
	}
	if(source==dest)
	 {
		 printf("They are the same!!!\n");
		 free(source->data);
		 
	 }
	 *dest=tmp;
	 
	 return 0;
}


/* cn1:
		dd 0.0, 0.393, 0.349, 0.272
	cn2:
		dd 0.0, 0.769, 0.686, 0.543
	cn3:
		dd 0.0, 0.189, 0.168, 0.131 */

const double to_sepia[3][3]={{0.393,0.769,0.189},{0.349,0.686,0.168},{0.272,0.534,0.131}};
/* const double to_luminosity_vano[3][3]={{0.299,0.587,0.114},{0.299,0.587,0.114},{0.299,0.587,0.114}};
const double to_luminosity[3][3]={{0.221,0.587,0.114},{0.221,0.587,0.114},{0.221,0.587,0.114}};
const double to_luminosity2[3][3]={{0.2126,0.7152,0.0722},{0.2126,0.7152,0.0722},{0.2126,0.7152,0.0722}}; */


int sepia(image_t const * const source, image_t* dest, const double matrix[3][3])
{
	int i, j;
	image_t tmp=*source; 
	tmp.data=(pixel_t*)calloc(sizeof(pixel_t), tmp.width*abs(tmp.height));
	
	for (i=0; i<tmp.width; i++)
	{
		for(j=0; j<abs(tmp.height); j++)
		{ 
				
			tmp.data[j*source->width+i].r=min2((unsigned char)matrix[0][0]*source->data[j*source->width+i].r+matrix[0][1]*source->data[j*source->width+i].g+matrix[0][2]*source->data[j*source->width+i].b,255);
			tmp.data[j*source->width+i].g=min2((unsigned char)matrix[1][0]*source->data[j*source->width+i].r+matrix[1][1]*source->data[j*source->width+i].g+matrix[1][2]*source->data[j*source->width+i].b,255);
			tmp.data[j*source->width+i].b=min2((unsigned char)matrix[2][0]*source->data[j*source->width+i].r+matrix[2][1]*source->data[j*source->width+i].g+matrix[2][2]*source->data[j*source->width+i].b,255);
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


/* 0.2126  0.7152	0.0722 */


