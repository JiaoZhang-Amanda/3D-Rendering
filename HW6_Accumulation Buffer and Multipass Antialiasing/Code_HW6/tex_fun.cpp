/* Texture functions for cs580 GzLib	*/
#include    "stdafx.h" 
#include	"stdio.h"
#include	"Gz.h"
#include "math.h"

GzColor	*image=NULL;
int xs, ys;
int reset = 1;

/* Image texture function */
int tex_fun(float u, float v, GzColor color)
{
  unsigned char		pixel[3];
  unsigned char     dummy;
  char  		foo[8];
  int   		i, j;
  FILE			*fd;

  if (reset) {          /* open and load texture file */
    fd = fopen ("texture", "rb");
    if (fd == NULL) {
      fprintf (stderr, "texture file not found\n");
      exit(-1);
    }
    fscanf (fd, "%s %d %d %c", foo, &xs, &ys, &dummy);
    image = (GzColor*)malloc(sizeof(GzColor)*(xs+1)*(ys+1));
    if (image == NULL) {
      fprintf (stderr, "malloc for texture image failed\n");
      exit(-1);
    }

    for (i = 0; i < xs*ys; i++) {	/* create array of GzColor values */
      fread(pixel, sizeof(pixel), 1, fd);
      image[i][RED] = (float)((int)pixel[RED]) * (1.0 / 255.0);
      image[i][GREEN] = (float)((int)pixel[GREEN]) * (1.0 / 255.0);
      image[i][BLUE] = (float)((int)pixel[BLUE]) * (1.0 / 255.0);
      }

    reset = 0;          /* init is done */
	fclose(fd);
  }
    //bounds-test u,v within [0,1]
    if(u>1){u=1;}
    if(u<0){u=0;}
    if(v<0){v=0;}
    if(v>1){v=1;}
    
    //scale by size of texture image [0, xs-1] [0, ys-1]
    float x = u * (xs - 1);
    float y = v * (ys - 1);
    float s = x - floor(x);
    float t = y - floor(y);
    
    //set color to interpolated GzColor value and return
    GzColor CA, CB, CC, CD;
    for(int i = 0; i < 3; i++){
        CA[i] = image[xs * (int)floor(y) + (int)floor(x)][i];
        CB[i] = image[xs * (int)floor(y) + (int)ceil(x)][i];
        CC[i] = image[xs * (int)ceil(y) + (int)ceil(x)][i];
        CD[i] = image[xs * (int)ceil(y) + (int)floor(x)][i];
    }
    for(int i = 0; i < 3; i++){
        color[i] = s * t * CC[i] + (1 - s) * t * CD[i] + s * (1 - t) * CB[i] + (1 - s) * (1 - t) * CA[i];
    }
    return GZ_SUCCESS;

/* bounds-test u,v to make sure nothing will overflow image array bounds */
/* determine texture cell corner values and perform bilinear interpolation */
/* set color to interpolated GzColor value and return */

  
	return GZ_SUCCESS;
}

/* Procedural texture function */
int ptex_fun(float u, float v, GzColor color)
{
    //bounds-test u,v within [0,1]
    if(u>1){u=1;}
    if(u<0){u=0;}
    if(v<0){v=0;}
    if(v>1){v=1;}
    
    //Simple Procedural Texture
    //Two colors are determined by odd/even intervals in u,v range [0,1]
    GzColor C1 = {0.0f, 0.0f, 0.0f};
    GzColor C2 = {1.0f, 0.0f, 0.0f};
    int N = 200;
    int U_interval = floor(u * N);
    int V_interval = floor(v * N);
    
    if(U_interval % 2 == V_interval % 2){
        for(int i = 0; i < 3; i++){
            color[i] = C1[i];
        }
    }else{
        for(int i = 0; i < 3; i++){
            color[i] = C2[i];
        }
    }

	return GZ_SUCCESS;
}

/* Free texture memory */
int GzFreeTexture()
{
	if(image!=NULL)
		free(image);
	return GZ_SUCCESS;
}

