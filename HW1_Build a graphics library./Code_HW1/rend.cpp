#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"
/*   CS580 HW   */
#include    "stdafx.h"  
#include	"Gz.h"


GzRender::GzRender(int xRes, int yRes)
{
	xres = xRes;
	yres = yRes;
	//framebuffer = new char[3 * xRes * yRes];
	//pixelbuffer = new GzPixel[xRes * yRes];
	framebuffer = (char *)malloc(sizeof(char) * 3 *  xRes * yRes);

	pixelbuffer = (GzPixel*)malloc(sizeof(GzPixel) * xRes * yRes);

/* HW1.1 create a framebuffer for MS Windows display:
 -- set display resolution
 -- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
 -- allocate memory for pixel buffer
 */
}

GzRender::~GzRender()
{
	//delete pixelbuffer;
	//delete framebuffer;
	free(pixelbuffer);
	free(framebuffer);
/* HW1.2 clean up, free buffer memory */

}

int GzRender::GzDefault()
{
	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			GzPut(i, j, 990, 800, 650, 1, 1);
		}
	}
	
/* HW1.3 set pixel buffer to some default values - start a new frame */
	return GZ_SUCCESS;
}


int GzRender::GzPut(int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
	if (i >= xres || i < 0 || j >= yres || j < 0) {
		return GZ_SUCCESS;
	}
	if (r < 0) { r = 0; }
	else if (r > 4095) { r = 4095; }
	if (g < 0) { r = 0; }
	else if (g > 4095) { g = 4095; }
	if (b < 0) { r = 0; }
	else if (b > 4095) { b = 4095; }

/* HW1.4 write pixel values into the buffer */	
	pixelbuffer[xres * j + i].red = r;
	pixelbuffer[xres * j + i].alpha = a;
	pixelbuffer[xres * j + i].blue = b;
	pixelbuffer[xres * j + i].green = g;
	pixelbuffer[xres * j + i].z = z;
	return GZ_SUCCESS;
}


int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
	if (i >= xres || i < 0 || j >= yres || j < 0) {
		return GZ_FAILURE;
	}
	*r = pixelbuffer[xres * j + i].red;
	*g = pixelbuffer[xres * j + i].green;
	*b = pixelbuffer[xres * j + i].blue;
	*a = pixelbuffer[xres * j + i].alpha;
	*z = pixelbuffer[xres * j + i].z;
/* HW1.5 retrieve a pixel information from the pixel buffer */

	return GZ_SUCCESS;
}


int GzRender::GzFlushDisplay2File(FILE* outfile)
{
	fprintf(outfile, "P6 %d %d 255\r", xres, yres);

	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			GzIntensity r = pixelbuffer[xres * j + i].red >> 4;
			GzIntensity g = pixelbuffer[xres * j + i].green >> 4;
			GzIntensity b = pixelbuffer[xres * j + i].blue >> 4;
			fprintf(outfile, "%c%c%c", r, g, b);
		}
	}
/* HW1.6 write image to ppm file -- "P6 %d %d 255\r" */
	
	return GZ_SUCCESS;
}

int GzRender::GzFlushDisplay2FrameBuffer()
{
	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			int frameIndex = (xres * j + i) * 3;
			*(framebuffer + frameIndex) = (char)(pixelbuffer[xres * j + i].blue >> 4);
			*(framebuffer + frameIndex + 1) = (char)(pixelbuffer[xres * j + i].green >> 4);
			*(framebuffer + frameIndex + 2) = (char)(pixelbuffer[xres * j + i].red >> 4);
		}
	}
/* HW1.7 write pixels to framebuffer: 
	- put the pixels into the frame buffer
	- CAUTION: when storing the pixels into the frame buffer, the order is blue, green, and red 
	- NOT red, green, and blue !!!
*/

	return GZ_SUCCESS;
}