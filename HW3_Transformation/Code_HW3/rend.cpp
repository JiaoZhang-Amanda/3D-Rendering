/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"

#define PI (float) 3.14159265358979323846

int GzRender::GzRotXMat(float degree, GzMatrix mat)
{
    float angel = (float)(degree / 180) * PI;
//	mat =
//	{
//		1,  0,           0,           0,
//		0,  cos(angel),  -sin(angel), 0,
//		0,  sin(angel),  cos(angel),  0,
//		0,  0,           0,           1
//	};
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = cos(angel);
	mat[1][2] = -sin(angel);
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = sin(angel);
	mat[2][2] = cos(angel);
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
/* HW 3.1
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value
*/

	return GZ_SUCCESS;
}

int GzRender::GzRotYMat(float degree, GzMatrix mat)
{
    float angel = (float)(degree / 180) * PI;
//	mat =
//	{
//		cos(angel),  0,  sin(angel),  0,
//		0,           1,  0,           0,
//		-sin(angel), 0,  cos(angel),  0,
//		0,           0,  0,           1
//	};
	mat[0][0] = cos(angel);
	mat[0][1] = 0;
	mat[0][2] = sin(angel);
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = -sin(angel);
	mat[2][1] = 0;
	mat[2][2] = cos(angel);
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
/* HW 3.2
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value
*/

	return GZ_SUCCESS;
}

int GzRender::GzRotZMat(float degree, GzMatrix mat)
{
    float angel = (float)(degree / 180) * PI;
//	mat =
//	{
//		cos(angel),  -sin(angel),  0,  0,
//		sin(angel),  cos(angel),   0,  0,
//		0,           0,            1,  0,
//		0,           0,            0,  1
//	};
	mat[0][0] = cos(angel);
	mat[0][1] = -sin(angel);
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = sin(angel);
	mat[1][1] = cos(angel);
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
    
/* HW 3.3
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
*/

	return GZ_SUCCESS;
}

int GzRender::GzTrxMat(GzCoord translate, GzMatrix mat)
{
//	mat =
//	{
//		1, 0, 0, translate[0],
//		0, 1, 0, translate[1],
//		0, 0, 1, translate[2],
//		0, 0, 0, 1
//	};
	mat[0][0] = 1;
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = translate[0];

	mat[1][0] = 0;
	mat[1][1] = 1;
	mat[1][2] = 0;
	mat[1][3] = translate[1];

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = 1;
	mat[2][3] = translate[2];

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
/* HW 3.4
// Create translation matrix
// Pass back the matrix using mat value
*/

	return GZ_SUCCESS;
}


int GzRender::GzScaleMat(GzCoord scale, GzMatrix mat)
{
//	mat =
//		scale[0], 0,        0,        0,
//		0,        scale[1], 0,        0,
//		0,        0,        scale[2], 0,
//		0,        0,        0,        1
//	};
	mat[0][0] = scale[0];
	mat[0][1] = 0;
	mat[0][2] = 0;
	mat[0][3] = 0;

	mat[1][0] = 0;
	mat[1][1] = scale[1];
	mat[1][2] = 0;
	mat[1][3] = 0;

	mat[2][0] = 0;
	mat[2][1] = 0;
	mat[2][2] = scale[2];
	mat[2][3] = 0;

	mat[3][0] = 0;
	mat[3][1] = 0;
	mat[3][2] = 0;
	mat[3][3] = 1;
/* HW 3.5
// Create scaling matrix
// Pass back the matrix using mat value
*/

	return GZ_SUCCESS;
}


GzRender::GzRender(int xRes, int yRes)
{
    xres = xRes;
    yres = yRes;
    
    pixelbuffer = (GzPixel*)malloc(sizeof(GzPixel) * xRes * yRes);

	framebuffer = (char*) malloc (3 * sizeof(char) * xRes * yRes);
/* HW1.1 create a framebuffer for MS Windows display:
-- set display resolution
-- allocate memory for framebuffer : 3 bytes(b, g, r) x width x height
-- allocate memory for pixel buffer
*/

    matlevel = 0; // the stack is empty
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){//set transform matrix
            Xsp[i][j] = 0; //initialize the Xsp, pers to screen
            m_camera.Xiw[i][j] = 0; //initialize the Xiw, world to image
            m_camera.Xpi[i][j] = 0; //initialize the Xpi, perspective projection
        }
    }
    //Initial camera
    m_camera.FOV = DEFAULT_FOV;
    m_camera.worldup[X] = 0;
    m_camera.worldup[Y] = 1;
    m_camera.worldup[Z] = 0;
    m_camera.lookat[X] = 0;
    m_camera.lookat[Y] = 0;
    m_camera.lookat[Z] = 0;
    m_camera.position[X] = DEFAULT_IM_X;
    m_camera.position[Y] = DEFAULT_IM_Y;
    m_camera.position[Z] = DEFAULT_IM_Z;
    
/* HW 3.6
- setup Xsp and anything only done once 
- init default camera 
*/ 
}

GzRender::~GzRender()
{
    free(pixelbuffer);
    free(framebuffer);
/* HW1.2 clean up, free buffer memory */

}

int GzRender::GzDefault()
{
    for (int i = 0; i < xres; i++) {
        for (int j = 0; j < yres; j++) {
            GzPut(i, j, 990, 800, 650, 1, INT_MAX);
        }
    }
/* HW1.3 set pixel buffer to some default values - start a new frame */

	return GZ_SUCCESS;
}

int GzRender::GzBeginRender()
{
    //init frame buffer color, alpha, z
    for(int i = 0; i < xres; i++){
        for(int j = 0; j < yres; j++){
            pixelbuffer[xres * j + i].red = 990;
            pixelbuffer[xres * j + i].alpha = 1;
            pixelbuffer[xres * j + i].blue = 650;
            pixelbuffer[xres * j + i].green = 800;
            pixelbuffer[xres * j + i].z = INT_MAX;
        }
    }
    
    //set Xsp
//	Xsp =
//	{
//		xres / 2, 0,       0,       xres / 2,
//		0,      -yres / 2, 0,       yres / 2,
//		0,      0,       INT_MAX, 0,
//		0,      0,       0,       1
//	};
	float angel = (float)(m_camera.FOV / 180) * PI; //convert angeles from degree to radians
	float d = 1 / (tan(angel / 2));
	Xsp[0][0] = xres / 2.0;
	Xsp[0][1] = 0;
	Xsp[0][2] = 0;
	Xsp[0][3] = xres / 2.0;

	Xsp[1][0] = 0;
	Xsp[1][1] = -yres / 2.0;
	Xsp[1][2] = 0;
	Xsp[1][3] = yres / 2.0;

	Xsp[2][0] = 0;
	Xsp[2][1] = 0;
	Xsp[2][2] = INT_MAX;
	Xsp[2][3] = 0;

	Xsp[3][0] = 0;
	Xsp[3][1] = 0;
	Xsp[3][2] = 0;
	Xsp[3][3] = 1;
    
    //set Xpi
    
//	m_camera.Xpi =
//	{
//		1, 0, 0,   0,
//		0, 1, 0,   0,
//		0, 0, 1/d,   0,
//		0, 0, 1 / d, 1
//	};
	m_camera.Xpi[0][0] = 1;
	m_camera.Xpi[1][1] = 1;
	m_camera.Xpi[2][2] = 1/d;
	m_camera.Xpi[3][3] = 1;
	m_camera.Xpi[3][2] = 1/d;

    //set Xiw
    //compute Z_axis
    GzCoord Z_axis;
    GzCoord cl;
    cl[X] = m_camera.lookat[X] - m_camera.position[X];
    cl[Y] = m_camera.lookat[Y] - m_camera.position[Y];
    cl[Z] = m_camera.lookat[Z] - m_camera.position[Z];
    float cl_mod = sqrt(cl[X] * cl[X] + cl[Y] * cl[Y] + cl[Z] * cl[Z]); //normalize
    Z_axis[X] = cl[X] / cl_mod;
    Z_axis[Y] = cl[Y] / cl_mod;
    Z_axis[Z] = cl[Z] / cl_mod;
    //compute Y_axis
    GzCoord Y_axis;
    GzCoord up;
    up[X] = m_camera.worldup[X];
    up[Y] = m_camera.worldup[Y];
    up[Z] = m_camera.worldup[Z];
    float dp = up[X] * Z_axis[X] + up[Y] * Z_axis[Y] + up[Z] * Z_axis[Z]; //dot
    GzCoord up_new;
    up_new[X] = up[X] - Z_axis[X] * dp;
    up_new[Y] = up[Y] - Z_axis[Y] * dp;
    up_new[Z] = up[Z] - Z_axis[Z] * dp;
    float up_new_mod = sqrt(up_new[X] * up_new[X] + up_new[Y] * up_new[Y] + up_new[Z] * up_new[Z]);
    Y_axis[X] = up_new[X] / up_new_mod;
    Y_axis[Y] = up_new[Y] / up_new_mod;
    Y_axis[Z] = up_new[Z] / up_new_mod;
    //compute X_axis
    GzCoord X_axis;
    X_axis[X] = Y_axis[Y] * Z_axis[Z] - Y_axis[Z] * Z_axis[Y]; //cross
    X_axis[Y] = Y_axis[Z] * Z_axis[X] - Y_axis[X] * Z_axis[Z];
    X_axis[Z] = Y_axis[X] * Z_axis[Y] - Y_axis[Y] * Z_axis[X];
    //computer C
    GzCoord C;
    C[X] = m_camera.position[X];
    C[Y] = m_camera.position[Y];
    C[Z] = m_camera.position[Z];
    //get Xiw
//	m_camera.Xiw =
//	{
//		X_axis[0], X_axis[1], X_axis[2], -(X_axis[0] * C[0] + X_axis[1] * C[1] + X_axis[2] * C[2]),
//		Y_axis[0], X_axis[1], Y_axis[2], -(Y_axis[0] * C[0] + Y_axis[1] * C[1] + Y_axis[2] * C[2]),
//		Z_axis[0], X_axis[1], Z_axis[2], -(Z_axis[0] * C[0] + Z_axis[1] * C[1] + Z_axis[2] * C[2]),
//		0,         0,         0,         1
//	};
	m_camera.Xiw[0][0] = X_axis[X];
	m_camera.Xiw[0][1] = X_axis[Y];
	m_camera.Xiw[0][2] = X_axis[Z];
	m_camera.Xiw[0][3] = -(X_axis[X] * C[X] + X_axis[Y] * C[Y] + X_axis[Z] * C[Z]);

	m_camera.Xiw[1][0] = Y_axis[X];
	m_camera.Xiw[1][1] = Y_axis[Y];
	m_camera.Xiw[1][2] = Y_axis[Z];
	m_camera.Xiw[1][3] = -(Y_axis[X] * C[X] + Y_axis[Y] * C[Y] + Y_axis[Z] * C[Z]);

	m_camera.Xiw[2][0] = Z_axis[X];
	m_camera.Xiw[2][1] = Z_axis[Y];
	m_camera.Xiw[2][2] = Z_axis[Z];
	m_camera.Xiw[2][3] = -(Z_axis[X] * C[X] + Z_axis[Y] * C[Y] + Z_axis[Z] * C[Z]);

	m_camera.Xiw[3][0] = 0;
	m_camera.Xiw[3][1] = 0;
	m_camera.Xiw[3][2] = 0;
	m_camera.Xiw[3][3] = 1;
    GzPushMatrix(Xsp);
    GzPushMatrix(m_camera.Xpi);
    GzPushMatrix(m_camera.Xiw);
    
/* HW 3.7 
- setup for start of each frame - init frame buffer color,alpha,z
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms when needed 
*/ 

	return GZ_SUCCESS;
}

int GzRender::GzPutCamera(GzCamera camera)
{
    m_camera.FOV = camera.FOV;
    m_camera.worldup[X] = camera.worldup[X];
    m_camera.worldup[Y] = camera.worldup[Y];
    m_camera.worldup[Z] = camera.worldup[Z];
    m_camera.lookat[X] = camera.lookat[X];
    m_camera.lookat[Y] = camera.lookat[Y];
    m_camera.lookat[Z] = camera.lookat[Z];
    m_camera.position[X] = camera.position[X];
    m_camera.position[Y] = camera.position[Y];
    m_camera.position[Z] = camera.position[Z];
/* HW 3.8 
/*- overwrite renderer camera structure with new camera definition
*/

	return GZ_SUCCESS;	
}

int GzRender::GzPushMatrix(GzMatrix	matrix)
{
    if(matlevel >= MATLEVELS){
        return GZ_FAILURE;
    }
    if(matlevel == 0){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                Ximage[matlevel][i][j] = matrix[i][j];
            }
        }
    }else{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				Ximage[matlevel][i][j] = 0;
			}
		}
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                for(int k = 0; k < 4; k++){
                    Ximage[matlevel][i][j] = Ximage[matlevel][i][j] + Ximage[matlevel - 1][i][k] * matrix[k][j];
                }
            }
        }
    }
    matlevel++;
/* HW 3.9 
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	
	return GZ_SUCCESS;
}

int GzRender::GzPopMatrix()
{
    if(matlevel <= 0){return GZ_FAILURE;}
    matlevel--;
/* HW 3.10
- pop a matrix off the Ximage stack
- check for stack underflow
*/

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

int GzRender::GzPutTriangle(int numParts, GzToken *nameList, GzPointer *valueList)
/* numParts - how many names and values */
{
    for (int i = 0; i < numParts; i++) {
        if (nameList[i] == GZ_NULL_TOKEN) {}
        else if(nameList[i] == GZ_POSITION){
            //set coord to 3 verts.
			GzCoord v[3];
            GzCoord vert[3];
            GzCoord* coordPointer = (GzCoord*)valueList[0];
            for (int j = 0; j < 3; j++) {
                v[j][X] = (*(coordPointer + j))[X];
                v[j][Y] = (*(coordPointer + j))[Y];
                v[j][Z] = (*(coordPointer + j))[Z];
            }

			//convert 4D to 3D, transform vertex from world space to screen space
			float vert_help[4][3];
			float tmp[4][3];
			for (int j = 0; j < 3; j++)
			{
				tmp[0][j] = v[j][X];
				tmp[1][j] = v[j][Y];
				tmp[2][j] = v[j][Z];
				tmp[3][j] = 1;
			}
			for (int m = 0; m < 4; m++)
			{
				for (int n = 0; n < 3; n++)
				{
					vert_help[m][n] = 0;
				}
			}

			for (int m = 0; m < 4; m++)
			{
				for (int n = 0; n < 3; n++)
				{
					for (int k = 0; k < 4; k++)
					{
						//apply stack to every vertex before passing on to the rasterizer
						vert_help[m][n] = vert_help[m][n] + Ximage[matlevel - 1][m][k] * tmp[k][n]; 
					}
				}
			}
			for (int j = 0; j < 3; j++)
			{
				vert[j][X] = vert_help[0][j] / vert_help[3][j];
				vert[j][Y] = vert_help[1][j] / vert_help[3][j];
				vert[j][Z] = vert_help[2][j] / vert_help[3][j];
			}
			//check tri, skip tri with negative z(behind the view), and discard the useless triangle
			int check = 0;
			int out_check = 0;
			for (int j = 0; j < 3; j++)
			{
				if (vert[j][Z] < 0) //check if this triangle has vertex behind the camera
				{
					check = 1;
					break;
				}
				if ((vert[j][X] < 0 || vert[j][X]> xres) || (vert[j][Y] < 0 || vert[j][Y] > yres)) //check if this triangle is out of the screen
				{
					out_check++;
				}
			}
			if (check == 1 || out_check == 3) {
				continue;
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
     GZ_NULL_TOKEN:        do nothing - no values
     GZ_POSITION:        3 vert positions in model space
     -- Invoke the rastrizer/scanline framework
     -- Return error code
     */


	return GZ_SUCCESS;
}

