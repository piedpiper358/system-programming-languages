/* #define _USE_MATH_DEFINES
#include <math.h>  */
#define M_PI 3.14159265358979323846
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <fcntl.h> /* open */
#include <unistd.h>  /* read */
#include <stdint.h> /* uint32_t */
#include <string.h> /* strlen strcpy */
#include <stdio_ext.h> /* __fpurge */


#define NUM_MAIN_MENU_ITEMS 5
#define NUM_MORPH_MENU_ITEMS 4
#define NUM_PRINT_MENU_ITEMS 3


#include "image.h"
#include "bmp.h"
#include "greyscale.h"
#include "rotate.h"


int main( int argc, char** argv );
FILE* OpenFileI();
FILE* OpenFileN(char* path);


 int erode(image_t const * const source, image_t* dest );
 int dilate(image_t const * const source, image_t* dest);
  int erode_bin(image_t const * const source, image_t* dest );
  int dilate_bin(image_t const * const source, image_t* dest );
  
/* image_t erode(image_t const source ); */

 int find_max(char a, char b){
	return a >= b ? a : b;
}
int find_min(char a, char b){
	return a >= b ? b : a;
}

char* replace(char* arg){
	int i;
	/* char newstr[10]; */
	char* newstr = malloc(sizeof(char)*strlen(arg));
	newstr=strcpy(newstr, arg);
	for(i=0; i<strlen(arg); i++)
	{
		if(arg[i]==',')
		{
			newstr[i]='.';
		}
	}
	return newstr;
}

int scanfdouble(double* arg){
	/* int i; */
	 /* char str[255];  */
	char* str= malloc(sizeof(char)*100);
	scanf("%s", str);
	
	/* for(i=0; i<strlen(str); i++)
	{
		if(str[i]==',')
		{
			str[i]='.';
		}
	} */
	str=replace(str);
	*arg=atof(str);
	return 0;
}



int main_debug( int argc, char** argv ) {
	
	int ret;
	image_t img;
	FILE* fp;
	/* double angle; */
	
	/* printf("%lu\n\n", sizeof(uint32_t)); */
		
		fp = OpenFileN(argv[1]);
		if (fp == NULL) /* a+b		rwb */
		{
			printf("Can't open file. Please try again.");
			return 1;
		}
		ret = from_bmp(fp, &img);
	if(ret)
	{
		printf("From_BMP_Error %i", ret);
	}
	
/* img = rotate_right(img); */
/*  img = rotate_given(img, (double)45);
  img = rotate_given(img, (double)45);
   img = rotate_given(img, (double)45);*/
   
   /* img = rotate_left(img); */
   /* img = rotate_upside_down(img); */
   
  /*  printf("Enter blyat'");
   scanf("%lf", &angle);
   printf("%.100f\n ", angle);
	img = rotate_all(img, (double)angle); */
	
	 /* img = rotate_upside_down(img);  */
	/* img = rotate_given(img, (double)45); */
	 /* ret = rotate_right_and_free(&img,&img); */
	 /* print_image(lightness(img));  */
	 /* img = luminosity(img); */
	  /* img=erode_bin(img); */
	 /* img = rotate(img, ROTATE_CLOCKWISE); */
	
	
	printf("The image has been successfully rotated.\n");
	ret = to_bmp(fp, &img);
	if(ret)
	{
		printf("To_BMP_Error %i", ret);
	}
	
	free(img.data);
	fclose(fp);
	
	return 0;
}


int main/* _release */( int argc, char** argv ) {
	
	int choice=0;
	int ret=1;
	image_t img;
	FILE* fp;
	double angle;
	
	
	if (argc<2 || (fp = OpenFileN(argv[1])) == NULL ) 
	{
		fp = OpenFileI();	
	}
	ret = from_bmp(fp, &img);
	if(ret)
	{
		printf("From_BMP_Error %i", ret);
		return ret;
	}
	if (argc<3 || atoi(argv[2])<1 || atoi(argv[2])>NUM_MAIN_MENU_ITEMS)
	{
		do{
			printf("\nWhat do you want to do?\n");
			printf("1 - Rotate\n");
			printf("2 - Morphological operations\n");
			printf("3 - Print\n");
			printf("4 - Sepia\n");
			printf("5 - Luminosity\n");
			printf("Your choice: ");
			scanf("%i", &choice);
			__fpurge(stdin);
			if(choice<1 || choice>NUM_MAIN_MENU_ITEMS)
			{
				printf("I don't know what you mean. Please try again.\n");
			}
		
		} while(choice<1 || choice>NUM_MAIN_MENU_ITEMS);
	}
	else 
	{
		choice=atoi(argv[2]);
	}
	
	switch (choice)
	{
		case 1: 
			printf("Enter the angle value: ");
			/* scanf("%lf", &angle); */
			scanfdouble(&angle);
			ret = rotate_all(&img, &img, (double)angle);
			if(ret)
			{
				printf("Rotate_Error %i", ret);
			}
			break;
		case 2: 
			choice=0;
			if (argc<4 || atoi(argv[3])<1 || atoi(argv[3])>NUM_MORPH_MENU_ITEMS)
			{
				do{
					printf("\nMorphological operations:\n");
					printf("1 - Erote\n");
					printf("2 - Erote_bin\n");
					printf("3 - Dilate\n");
					printf("4 - Dilate_bin\n");
					printf("Your choice: ");
					scanf("%i", &choice);
					__fpurge(stdin);
					if(choice<1 || choice>NUM_MORPH_MENU_ITEMS)
					{
						printf("I don't know what you mean. Please try again.\n");
					}
		
				} while(choice<1 || choice>NUM_MORPH_MENU_ITEMS);
			}
			else 
			{
				choice=atoi(argv[3]);
			}
	
			switch (choice)
			{
				case 1: 
					ret = erode(&img, &img);
					break;
				case 2: 
					ret = erode_bin(&img, &img);
					break;
				case 3: 
					ret = dilate(&img, &img);
					break;
				case 4: 
					ret = dilate_bin(&img, &img);
					break;
				default:
					printf("I don't know what you mean. Please try again.\n");
					break;
			} 
			break;
		case 3: 
			choice=0;
			if (argc<4 || atoi(argv[3])<1 || atoi(argv[3])>NUM_PRINT_MENU_ITEMS)
			{
				do{
					printf("\nWhich way of translation into grayscale do you prefer?\n");
					printf("1 - Lightness\n");
					printf("2 - Average\n");
					printf("3 - Luminosity\n");
					printf("Your choice: ");
					scanf("%i", &choice);
					__fpurge(stdin);
					if(choice<1 || choice>NUM_PRINT_MENU_ITEMS)
					{
						printf("I don't know what you mean. Please try again.\n");
					}
			
				} while(choice<1 || choice>NUM_PRINT_MENU_ITEMS);
			}
			else 
			{
				choice=atoi(argv[3]);
			}
	
			switch (choice)
			{
				case 1: 
					print_image_type(img, PRINT_LIGHTNESS);
					break;
				case 2: 
					print_image_type(img, PRINT_AVERAGE);
					break;
				case 3: 
					print_image_type(img, PRINT_LUMINOSITY);
					break;
				default:
					printf("I don't know what you mean. Please try again.\n");
					break;
			} 
			/* print_image_type(img, choice); */
		
			/* ret = luminosity(&img, &img);
			print_image(img); */
			break;
		case 4:
			ret = sepia(&img, &img, to_sepia);
			break;
		case 5:
			ret = luminosity(&img,&img);
			break;
		default:
			printf("I don't know what you mean. Please try again.\n");
			break;
	}
	
	ret = to_bmp(fp, &img); 
	if(ret)
	{
		printf("To_BMP_Error %i", ret);
	}
	
	free(img.data);
	printf("The action was performed.\n");
	fclose(fp);
	
	return 0;
}
 
 
FILE* OpenFileI()
{
	FILE *fp = NULL;
	char path[255];
	do {
		rewind(stdin);
		printf("\nEnter the absolute path to the file.\n");
		scanf("%s", path);
			
		if ((fp = fopen(path, "r+b")) == NULL) /* a+b		rwb */
		{
			printf("Can't open file. Please try again.");
		};

	} while (fp == NULL);
		
	return fp;
}


FILE* OpenFileN(char* path)
{
	/* FILE* fp = fopen(path, "r+b"); */ /* a+b		rwb */
	return fopen(path, "r+b");
}


int erode(image_t const * const source, image_t* dest )/*min val from neighborhood*/
 {
	int i, j;
	image_t result;
	
	result.height=source->height;
	result.width=source->width;
	result.data=calloc(sizeof(pixel_t), result.width*result.height);


	for (i=0; i<result.width; i++)
	 {
		 for(j=0; j<result.height; j++)
		 {/*we greyscale first, then equate*/
		 	source->data[j*result.width+i].r=(int)(source->data[j*result.width+i].r*0.221)+(int)(source->data[j*result.width+i].g*0.587)+(int)(source->data[j*result.width+i].b*0.114);
		 	source->data[j*result.width+i].g=source->data[j*result.width+i].r;
		 	source->data[j*result.width+i].b=source->data[j*result.width+i].r;

		 	result.data[j*result.width+i]=source->data[j*result.width+i];
		 }
	 }

	if(result.data==NULL)
	{
		return 1;
	}
	for (i=0; i<result.width; i++)
	 {
		 for(j=0; j<result.height; j++)
		 {
			 /*  printf("i=%i\tj=%i\t%i\n", i, j, j*result.width+i); */
		 	if (i+1<=result.width){
			  result.data[j*result.width+i].g=find_min(source->data[j*result.width+i+1].g, result.data[j*result.width+i].g);
			/* printf("right"); */
			}
			if (i-1>=0){
			/* printf("left"); */
			  result.data[j*result.width+i].g=find_min(source->data[j*result.width+i-1].g, result.data[j*result.width+i].g);
			}
			if (j-1>=0){
			/* printf("bot"); */
			  result.data[j*result.width+i].g=find_min(source->data[(j-1)*result.width+i].g, result.data[j*result.width+i].g);
			}
			if (j+1 <= result.height){
			/* printf("top"); */
			  result.data[j*result.width+i].g=find_min(source->data[(j+1)*result.width+i].g, result.data[j*result.width+i].g);
			}
		 /* printf("\n"); */
		 	result.data[j*result.width+i].r=result.data[j*result.width+i].g;
		 	result.data[j*result.width+i].b=result.data[j*result.width+i].g;
		}
	}
	 if(source==dest)
	 {
		 /* printf("They are the same!!!\n"); */
		 free(source->data);
		 
	 }
	 *dest=result;
	 
	 return 0;
 }
 
 
int dilate(image_t const * const source, image_t* dest)/*max val from neighborhood*/
 {
	int i, j;
	image_t result;
	
	result.height=source->height;
	result.width=source->width;
	result.data=calloc(sizeof(pixel_t), result.width*result.height);

	if(result.data==NULL)
	{
		return 1;
	}
	for (i=0; i<result.width; i++)
	 {
		 for(j=0; j<result.height; j++)
		 {/* we greyscale first, then equate */
		 	source->data[j*result.width+i].r=(int)(source->data[j*result.width+i].r*0.221)+(int)(source->data[j*result.width+i].g*0.587)+(int)(source->data[j*result.width+i].b*0.114);
		 	source->data[j*result.width+i].g=source->data[j*result.width+i].r;
		 	source->data[j*result.width+i].b=source->data[j*result.width+i].r;

		 	result.data[j*result.width+i]=source->data[j*result.width+i];
		 }
	 }
	 
	 /* luminosity(source, &result); */
	 
	for (i=0; i<result.width; i++)
	 {
		 for(j=0; j<result.height; j++)
		 {
			  /* printf("i=%i\tj=%i\t%i\n", i, j, j*result.width+i); */
		 	if (i+1<=result.width){
			  result.data[j*result.width+i].r=find_max(source->data[j*result.width+i+1].r, result.data[j*result.width+i].r);
			/* printf("right"); */
			}
			if (i-1>=0){
			/* printf("left"); */
			  result.data[j*result.width+i].r=find_max(source->data[j*result.width+i-1].r, result.data[j*result.width+i].r);
			}
			if (j-1>=0){
			/* printf("bot"); */
			  result.data[j*result.width+i].r=find_max(source->data[(j-1)*result.width+i].r, result.data[j*result.width+i].r);
			}
			if (j+1 <= result.height){
			/* printf("top"); */
			  result.data[j*result.width+i].r=find_max(source->data[(j+1)*result.width+i].r, result.data[j*result.width+i].r);
			}
		 /* printf("\n"); */
		 	result.data[j*result.width+i].g=result.data[j*result.width+i].r;
		 	result.data[j*result.width+i].b=result.data[j*result.width+i].r;
			  /*i++;*/
		}
	}
	 if(source==dest)
	 {
		 /* printf("They are the same!!!\n"); */
		 free(source->data);
		 
	 }
	 *dest=result;
	 
	 return 0;
 }

int erode_bin(image_t const * const source, image_t* dest )
 {
	int i, j;
	 
	image_t result;
	
	result.height=source->height;
	result.width=source->width;
	result.data=calloc(sizeof(pixel_t), result.width*result.height);
	
	if(result.data==NULL)
	{
		return 1;
	}

	for (i=0; i<result.width; i++)/*looks and may be dumb, but prevents us from malloc trash errors (randomly generated black pixel ruin)*/
	 {
		 for(j=0; j<result.height; j++)
		 {
		 	result.data[j*result.width+i]=white_pixel;
		 }
	 }


	 for (i=0; i<result.width; i++)
	 {
		 for(j=0; j<result.height; j++)
		 {
		 if((result.data[j*result.width+i].r != 0) && (result.data[j*result.width+i].g != 0) && (result.data[j*result.width+i].b != 0))
			 result.data[j*result.width+i]=source->data[j*result.width+i];
		 if((source->data[j*result.width+i].r == 0) && (source->data[j*result.width+i].g == 0) && (source->data[j*result.width+i].b == 0))
		 {
			  /* printf("i=%i\tj=%i\t%i\n", i, j, j*result.width+i); */
		 	if (i+1<=result.width){
			  result.data[j*result.width+i+1]=black_pixel;
			/* printf("right"); */
			}
			if (i-1>=0){
			/* printf("left"); */
			  result.data[j*result.width+i-1]=black_pixel;
			}
			if (j-1>=0){
			/* printf("bot"); */
			  result.data[(j-1)*result.width+i]=black_pixel;
			}
			if (j+1 <= result.height){
			/* printf("top"); */
			  result.data[(j+1)*result.width+i]=black_pixel;
			}
		 /* printf("\n"); */
			  /*i++;*/
		  }
		}
	}
	  if(source==dest)
	 {
		 /* printf("They are the same!!!\n"); */
		 free(source->data);
		 
	 }
	 *dest=result;
	 
	 return 0;
 }

 int dilate_bin(image_t const * const source, image_t* dest )
 {
	int i, j;
	image_t result;
	
	result.height=source->height;
	result.width=source->width;
	result.data=calloc(sizeof(pixel_t), result.width*result.height);


	if(result.data==NULL)
	{
		return 1;
	}

	 for (i=0; i<result.width; i++)
	 {
		 for(j=0; j<result.height; j++)
		 {
		 if((result.data[j*result.width+i].r != 255) && (result.data[j*result.width+i].g != 255) && (result.data[j*result.width+i].b != 255))
			 result.data[j*result.width+i]=source->data[j*result.width+i];
		 if((source->data[j*result.width+i].r == 255) && (source->data[j*result.width+i].g == 255) && (source->data[j*result.width+i].b == 255))
		 {
			 /*  printf("i=%i\tj=%i\t%i\n", i, j, j*result.width+i); */
		 	if (i+1<=result.width){
			  result.data[j*result.width+i+1]=white_pixel;
			/* printf("right"); */
			}
			if (i-1>=0){
			/* printf("left"); */
			  result.data[j*result.width+i-1]=white_pixel;
			}
			if (j-1>=0){
			/* printf("bot"); */
			  result.data[(j-1)*result.width+i]=white_pixel;
			}
			if (j+1 <= result.height){
			/* printf("top"); */
			  result.data[(j+1)*result.width+i]=white_pixel;
			}
		 /* printf("\n"); */
			  /*i++;*/
		  }
		}
	}
	  if(source==dest)
	 {
		 /* printf("They are the same!!!\n"); */
		 free(source->data);
		 
	 }
	 *dest=result;
	 
	 return 0;
 }


 /* image_t erode(image_t const src )
 {
	 // uint32_t W; // 
	int i, j;
	image_t dest;
	
	dest.height=src.height;
	dest.width=src.width;
	dest.data=calloc(sizeof(pixel_t), dest.width*dest.height);
	
		
	if(dest.data==NULL)
	{
		printf("Error");
		errno=1;
	}

	 for (i=0; i<dest.width; i++)
	 {
		 for(j=0; j<dest.height; j++)
		 { 
		 if(1)
		 {
		 
			  dest.data[j*dest.width+i]=black_pixel;
		 }
		 else
		 {
			 dest.data[j*dest.width+i]=white_pixel;
		 }
			
		 }
	 }
	 
	 free(src.data);
	 return dest;
 }
  */