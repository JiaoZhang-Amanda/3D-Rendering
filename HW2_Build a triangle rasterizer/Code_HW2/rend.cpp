#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"


/***********************************************/
/* HW1 methods: copy here the methods from HW1 */

GzRender::GzRender(int xRes, int yRes)
{
	xres = xRes;
	yres = yRes;

	framebuffer = (char *)malloc(sizeof(char) * 3 * xRes * yRes);

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
			GzPut(i, j, 990, 800, 650, 1, MAXINT);
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
	fprintf(outfile, "P6 %d %d 255\nRGBRGBRGB", xres, yres);

	for (int i = 0; i < xres; i++) {
		for (int j = 0; j < yres; j++) {
			GzIntensity r = pixelbuffer[xres * j + i].red >> 4;
			GzIntensity g = pixelbuffer[xres * j + i].green >> 4;
			GzIntensity b = pixelbuffer[xres * j + i].blue >> 4;
			fwrite(&r, 1, 1, outfile);
			fwrite(&g, 1, 1, outfile);
			fwrite(&b, 1, 1, outfile);
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


/***********************************************/
/* HW2 methods: implement from here */

int GzRender::GzPutAttribute(int numAttributes, GzToken	*nameList, GzPointer *valueList) 
{
	for (int i = 0; i < numAttributes; i++) {
		if (nameList[i] == GZ_RGB_COLOR) {
			GzColor* colorPoint = (GzColor*)(valueList[0]);
			flatcolor[0] = (*colorPoint)[0];
			flatcolor[1] = (*colorPoint)[1];
			flatcolor[2] = (*colorPoint)[2];
		}
	}
/* HW 2.1
-- Set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
-- In later homeworks set shaders, interpolaters, texture maps, and lights
*/

	return GZ_SUCCESS;
}

int GzRender::GzPutTriangle(int	numParts, GzToken *nameList, GzPointer *valueList) 
/* numParts - how many names and values */
{
	for (int i = 0; i < numParts; i++) {
		if (nameList[i] == GZ_NULL_TOKEN) {}
		else if(nameList[i] == GZ_POSITION){
			//set coord to 3 verts.
			GzCoord vert[3];
			GzCoord* coordPointer = (GzCoord*)valueList[0];
			for (int j = 0; j < 3; j++) {
				vert[j][0] = (*(coordPointer + j))[0];
				vert[j][1] = (*(coordPointer + j))[1];
				vert[j][2] = (*(coordPointer + j))[2];
			}
			//sort verts by y-coords
			for (int j = 1;j < 3; j++) {
				GzCoord tmp;
				for (int k = 0; k < 3; k++) {
					tmp[k] = vert[j][k];
				}
				int m;
				for (m = j - 1; m >= 0 && vert[m][1] > tmp[1]; m--) {
					for (int k = 0; k < 3; k++) {
						vert[m + 1][k] = vert[m][k];
					}
				}
				for (int k = 0; k < 3; k++) {
					vert[m + 1][k] = tmp[k];
				}
			}

			//set up edges; sort it by L/R
			Edge Gzedge[3];
			int orient = 0;
			Gzedge[0].assign(vert[0], vert[1]);
			Gzedge[1].assign(vert[1], vert[2]);
			Gzedge[2].assign(vert[0], vert[2]);
			if (vert[0][1] == vert[1][1]) {
				orient = 0; //inverted tri
			}else if(vert[1][1] == vert[2][1]){
				orient = 1; //regular tri
			}else{
				float slopeX0 = Gzedge[0].slopeX(Gzedge[0].start, Gzedge[0].end);
				float slopeX2 = Gzedge[2].slopeX(Gzedge[2].start, Gzedge[2].end);
				if (slopeX0 < slopeX2) {
					orient = 2; //L tri
				}else if(slopeX0 > slopeX2){	
					orient = 3; //R tri
				}
			}
			//calculate slope
			float slopeX0 = Gzedge[0].slopeX(Gzedge[0].start, Gzedge[0].end);
			float slopeX1 = Gzedge[1].slopeX(Gzedge[1].start, Gzedge[1].end);
			float slopeX2 = Gzedge[2].slopeX(Gzedge[2].start, Gzedge[2].end);
			float slopeZ0 = Gzedge[0].slopeZ(Gzedge[0].start, Gzedge[0].end);
			float slopeZ1 = Gzedge[1].slopeZ(Gzedge[1].start, Gzedge[1].end);
			float slopeZ2 = Gzedge[2].slopeZ(Gzedge[2].start, Gzedge[2].end);
			float deltaY = ceil(vert[0][1]) - vert[0][1];
			float slopeZ = 0;
			float deltaX = 0;
			//Initialize current for edge 0 and edge 2
			Gzedge[0].current[0] = vert[0][0] + slopeX0 * deltaY;
			Gzedge[0].current[1] = vert[0][1] + deltaY;
			Gzedge[0].current[2] = vert[0][2] + slopeZ0 * deltaY;
			Gzedge[2].current[0] = vert[0][0] + slopeX2 * deltaY;
			Gzedge[2].current[1] = vert[0][1] + deltaY;
			Gzedge[2].current[2] = vert[0][2] + slopeZ2 * deltaY;
			//Span
			Span spanLine;
			int a = 0;
			int b = 0;
			GzPixel color;
			flatcolor[0] = (short)((int)(flatcolor[0] * ((1 << 12) - 1)));
			flatcolor[1] = (short)((int)(flatcolor[1] * ((1 << 12) - 1)));
			flatcolor[2] = (short)((int)(flatcolor[2] * ((1 << 12) - 1)));
			//the first area
			while (Gzedge[0].current[1] < Gzedge[0].end[1]) {
				if (orient == 2 || orient == 1) {
					spanLine.assign(Gzedge[0].current, Gzedge[2].current);
					deltaX = ceil(Gzedge[0].current[0]) - Gzedge[0].current[0];
					slopeZ = spanLine.slopeZ(Gzedge[0].current, Gzedge[2].current);
					spanLine.current[0] = Gzedge[0].current[0] + deltaX;
					spanLine.current[1] = Gzedge[0].current[1];
					spanLine.current[2] = Gzedge[0].current[2] + deltaX * slopeZ;
				}
				else if (orient == 3) {
					spanLine.assign(Gzedge[2].current, Gzedge[0].current);
					deltaX = ceil(Gzedge[2].current[0]) - Gzedge[2].current[0];
					slopeZ = spanLine.slopeZ(Gzedge[2].current, Gzedge[0].current);
					spanLine.current[0] = Gzedge[2].current[0] + deltaX;
					spanLine.current[1] = Gzedge[2].current[1];
					spanLine.current[2] = Gzedge[2].current[2] + deltaX * slopeZ;
				}
				while (((orient == 2 || orient == 1) && spanLine.current[0] < Gzedge[2].current[0]) || (orient == 3 && spanLine.current[0] < Gzedge[0].current[0]))
				{
					a = (int)spanLine.current[0];
					b = (int)Gzedge[0].current[1];
					if (spanLine.current[2] < 0) { continue; }
					GzGet(a, b, &color.red, &color.green, &color.blue, &color.alpha, &color.z);
					if (spanLine.current[2] < color.z) {
						GzPut(a, b, flatcolor[0], flatcolor[1], flatcolor[2], 0, (GzDepth)spanLine.current[2]);
					}
					spanLine.current[0]++;
					spanLine.current[2] += slopeZ;
				}
				Gzedge[0].current[0] += slopeX0;
				Gzedge[0].current[1]++;
				Gzedge[0].current[2] += slopeZ0;
				Gzedge[2].current[0] += slopeX2;
				Gzedge[2].current[1]++;
				Gzedge[2].current[2] += slopeZ2;
			}
			
			deltaY = ceil(vert[1][1]) - vert[1][1];
			Gzedge[1].current[0] = vert[1][0] + slopeX1 * deltaY;
			Gzedge[1].current[1] = vert[1][1] + deltaY;
			Gzedge[1].current[2] = vert[1][2] + slopeZ1 * deltaY;

			//the next area
			while (Gzedge[1].current[1] < Gzedge[1].end[1]){
				if (orient == 2) {
					spanLine.assign(Gzedge[1].current, Gzedge[2].current);
					deltaX = ceil(Gzedge[1].current[0]) - Gzedge[1].current[0];
					slopeZ = spanLine.slopeZ(Gzedge[1].current, Gzedge[2].current);
					spanLine.current[0] = Gzedge[1].current[0] + deltaX;
					spanLine.current[1] = Gzedge[1].current[1];
					spanLine.current[2] = Gzedge[1].current[2] + deltaX * slopeZ;
				}
				else if (orient == 0 || orient == 3) {
					spanLine.assign(Gzedge[2].current, Gzedge[1].current);
					deltaX = ceil(Gzedge[2].current[0]) - Gzedge[2].current[0];
					slopeZ = spanLine.slopeZ(Gzedge[2].current, Gzedge[1].current);
					spanLine.current[0] = Gzedge[2].current[0] + deltaX;
					spanLine.current[1] = Gzedge[2].current[1];
					spanLine.current[2] = Gzedge[2].current[2] + deltaX * slopeZ;
				}
				while (((orient == 3 || orient == 0) && spanLine.current[0] < Gzedge[1].current[0]) || (orient == 2 && spanLine.current[0] < Gzedge[2].current[0]))
				{
					a = (int)spanLine.current[0];
					b = (int)Gzedge[1].current[1];
					if (spanLine.current[2] < 0) { continue; }
					GzGet(a, b, &color.red, &color.green, &color.blue, &color.alpha, &color.z);
					if (spanLine.current[2] < color.z) {
						GzPut(a, b, flatcolor[0], flatcolor[1], flatcolor[2], 0, (GzDepth)spanLine.current[2]);
					}
					spanLine.current[0]++;
					spanLine.current[2] += slopeZ;
				}
				Gzedge[1].current[0] += slopeX1;
				Gzedge[1].current[1]++;
				Gzedge[1].current[2] += slopeZ1;
				Gzedge[2].current[0] += slopeX2;
				Gzedge[2].current[1]++;
				Gzedge[2].current[2] += slopeZ2;
			}

		
		}
	}
/* HW 2.2
-- Pass in a triangle description with tokens and values corresponding to
      GZ_NULL_TOKEN:		do nothing - no values
      GZ_POSITION:		3 vert positions in model space
-- Invoke the rastrizer/scanline framework
-- Return error code
*/

	return GZ_SUCCESS;
}


