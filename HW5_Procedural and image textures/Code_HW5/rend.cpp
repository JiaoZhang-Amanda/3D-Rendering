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
    //    mat =
    //    {
    //        1,  0,           0,           0,
    //        0,  cos(angel),  -sin(angel), 0,
    //        0,  sin(angel),  cos(angel),  0,
    //        0,  0,           0,           1
    //    };
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
    //    mat =
    //    {
    //        cos(angel),  0,  sin(angel),  0,
    //        0,           1,  0,           0,
    //        -sin(angel), 0,  cos(angel),  0,
    //        0,           0,  0,           1
    //    };
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
    //    mat =
    //    {
    //        cos(angel),  -sin(angel),  0,  0,
    //        sin(angel),  cos(angel),   0,  0,
    //        0,           0,            1,  0,
    //        0,           0,            0,  1
    //    };
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
    //    mat =
    //    {
    //        1, 0, 0, translate[0],
    //        0, 1, 0, translate[1],
    //        0, 0, 1, translate[2],
    //        0, 0, 0, 1
    //    };
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
    //    mat =
    //        scale[0], 0,        0,        0,
    //        0,        scale[1], 0,        0,
    //        0,        0,        scale[2], 0,
    //        0,        0,        0,        1
    //    };
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
    //Initialize camera
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
    
    //initialize
    interp_mode = GZ_RGB_COLOR;
    numlights = 0;
    //initialize Ka, the specular color
    GzColor ka = DEFAULT_AMBIENT;
    Ka[X] = ka[X];
    Ka[Y] = ka[Y];
    Ka[Z] = ka[Z];
    //initialize Kd, the specular color
    GzColor kd = DEFAULT_DIFFUSE;
    Kd[X] = kd[X];
    Kd[Y] = kd[Y];
    Kd[Z] = kd[Z];
    //initialize Ks, the specular color
    GzColor ks = DEFAULT_SPECULAR;
    Ks[X] = ks[X];
    Ks[Y] = ks[Y];
    Ks[Z] = ks[Z];

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
    //    Xsp =
    //    {
    //        xres / 2, 0,       0,       xres / 2,
    //        0,      -yres / 2, 0,       yres / 2,
    //        0,      0,       INT_MAX, 0,
    //        0,      0,       0,       1
    //    };
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
    
    //    m_camera.Xpi =
    //    {
    //        1, 0, 0,   0,
    //        0, 1, 0,   0,
    //        0, 0, 1/d,   0,
    //        0, 0, 1 / d, 1
    //    };
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
    //    m_camera.Xiw =
    //    {
    //        X_axis[0], X_axis[1], X_axis[2], -(X_axis[0] * C[0] + X_axis[1] * C[1] + X_axis[2] * C[2]),
    //        Y_axis[0], X_axis[1], Y_axis[2], -(Y_axis[0] * C[0] + Y_axis[1] * C[1] + Y_axis[2] * C[2]),
    //        Z_axis[0], X_axis[1], Z_axis[2], -(Z_axis[0] * C[0] + Z_axis[1] * C[1] + Z_axis[2] * C[2]),
    //        0,         0,         0,         1
    //    };
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
                Xnorm[matlevel][i][j] = 0;
            }
        }
        Xnorm[matlevel][0][0] = 1;
        Xnorm[matlevel][1][1] = 1;
        Xnorm[matlevel][2][2] = 1;
        Xnorm[matlevel][3][3] = 1;
    }else{
        //multiple the Ximage matrix
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
        //add Xnorm
        if (matlevel == 1) {
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    Xnorm[matlevel][i][j] = 0;
                }
            }
            Xnorm[matlevel][0][0] = 1;
            Xnorm[matlevel][1][1] = 1;
            Xnorm[matlevel][2][2] = 1;
            Xnorm[matlevel][3][3] = 1;
        }else{
            float k;
            GzMatrix R;
            k = 1/sqrt(matrix[0][0] * matrix[0][0] + matrix[1][0] * matrix[1][0] + matrix[2][0] * matrix[2][0]);
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                    R[i][j] = matrix[i][j] * k;
                }
                R[i][3] = 0;
                R[3][i] = 0;
            }
            R[3][3] = 1;
            //multiple the Xnorm matrix
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    Xnorm[matlevel][i][j] = 0;
                }
            }
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    for(int k = 0; k < 4; k++){
                        Xnorm[matlevel][i][j] = Xnorm[matlevel][i][j] + Xnorm[matlevel - 1][i][k] * R[k][j];
                    }
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
    if (i > xres || i < 0 || j > yres || j < 0) {
    return GZ_SUCCESS;
        
    }
    if (r < 0) { r = 0; }
    else if (r > 4095) { r = 4095; }
    if (g < 0) { r = 0; }
    else if (g > 4095) { g = 4095; }
    if (b < 0) { r = 0; }
    else if (b > 4095) { b = 4095; }
    
    /* HW1.4 write pixel values into the buffer */
    pixelbuffer[ARRAY(i, j)].red = r;
    pixelbuffer[ARRAY(i, j)].alpha = a;
    pixelbuffer[ARRAY(i, j)].blue = b;
    pixelbuffer[ARRAY(i, j)].green = g;
    pixelbuffer[ARRAY(i, j)].z = z;

	return GZ_SUCCESS;
}


int GzRender::GzGet(int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
    if (i > xres || i < 0 || j > yres || j < 0) {
        return GZ_FAILURE;
    }
    *r = pixelbuffer[ARRAY(i, j)].red;
    *g = pixelbuffer[ARRAY(i, j)].green;
    *b = pixelbuffer[ARRAY(i, j)].blue;
    *a = pixelbuffer[ARRAY(i, j)].alpha;
    *z = pixelbuffer[ARRAY(i, j)].z;
/* HW1.5 retrieve a pixel information from the pixel buffer */

	return GZ_SUCCESS;
}


int GzRender::GzFlushDisplay2File(FILE* outfile)
{
    fprintf(outfile, "P6 %d %d 255\nRGBRGBRGB", xres, yres);
    
    for (int i = 0; i < xres; i++) {
        for (int j = 0; j < yres; j++) {
            GzIntensity r = pixelbuffer[ARRAY(j, i)].red >> 4;
            GzIntensity g = pixelbuffer[ARRAY(j, i)].green >> 4;
            GzIntensity b = pixelbuffer[ARRAY(j, i)].blue >> 4;
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
            if ((*colorPoint)[RED] < 0) {
                (*colorPoint)[RED] = 0;
            }
            if ((*colorPoint)[GREEN] < 0) {
                (*colorPoint)[GREEN] = 0;
            }
            if ((*colorPoint)[BLUE] < 0) {
                (*colorPoint)[BLUE] = 0;
            }
            if ((*colorPoint)[RED] > 4095) {
                (*colorPoint)[RED] = 4095;
            }
            if ((*colorPoint)[GREEN] > 4095) {
                (*colorPoint)[GREEN] = 4095;
            }
            if ((*colorPoint)[BLUE] > 4095) {
                (*colorPoint)[BLUE] = 4095;
            }
            flatcolor[RED] = (*colorPoint)[0];
            flatcolor[GREEN] = (*colorPoint)[1];
            flatcolor[BLUE] = (*colorPoint)[2];
        }else if(nameList[i] == GZ_INTERPOLATE){
            int* inter = (int*)(valueList[i]);
            interp_mode = (*inter);
        }else if(nameList[i] == GZ_DIRECTIONAL_LIGHT){
            if(numlights >= MAX_LIGHTS){return GZ_FAILURE;}
            GzLight* diret_light = (GzLight*)(valueList[i]);
            lights[numlights].color[X] = diret_light->color[X];
            lights[numlights].color[Y] = diret_light->color[Y];
            lights[numlights].color[Z] = diret_light->color[Z];
            lights[numlights].direction[X] = diret_light->direction[X];
            lights[numlights].direction[Y] = diret_light->direction[Y];
            lights[numlights].direction[Z] = diret_light->direction[Z];
            normalizeCoord(lights[numlights].direction);
            numlights++;
        }else if(nameList[i] == GZ_AMBIENT_LIGHT){
            GzLight* ambit_light = (GzLight*)(valueList[i]);
            ambientlight.color[X] = ambit_light->color[X];
            ambientlight.color[Y] = ambit_light->color[Y];
            ambientlight.color[Z] = ambit_light->color[Z];
        }else if(nameList[i] == GZ_AMBIENT_COEFFICIENT){
            GzColor* ambit_coe = (GzColor*)(valueList[i]);
            Ka[X] = (*ambit_coe)[X];
            Ka[Y] = (*ambit_coe)[Y];
            Ka[Z] = (*ambit_coe)[Z];
        }else if(nameList[i] == GZ_DIFFUSE_COEFFICIENT){
            GzColor* diff_coe = (GzColor*)(valueList[i]);
            Kd[X] = (*diff_coe)[X];
            Kd[Y] = (*diff_coe)[Y];
            Kd[Z] = (*diff_coe)[Z];
        }else if(nameList[i] == GZ_SPECULAR_COEFFICIENT){
            GzColor* spec_coe = (GzColor*)(valueList[i]);
            Ks[X] = (*spec_coe)[X];
            Ks[Y] = (*spec_coe)[Y];
            Ks[Z] = (*spec_coe)[Z];
        }else if(nameList[i] == GZ_DISTRIBUTION_COEFFICIENT){
            float* sp = (float*)(valueList[i]);
            spec = (*sp);
        }else if(nameList[i] == GZ_TEXTURE_MAP){
            GzTexture texture = (GzTexture)(valueList[i]);
            tex_fun = texture;
        }
    }
/* HW 2.1
-- Set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
-- In later homeworks set shaders, interpolaters, texture maps, and lights
*/

/*
- GzPutAttribute() must accept the following tokens/values:

- GZ_RGB_COLOR					GzColor		default flat-shade color
- GZ_INTERPOLATE				int			shader interpolation mode
- GZ_DIRECTIONAL_LIGHT			GzLight
- GZ_AMBIENT_LIGHT            	GzLight		(ignore direction)
- GZ_AMBIENT_COEFFICIENT		GzColor		Ka reflectance
- GZ_DIFFUSE_COEFFICIENT		GzColor		Kd reflectance
- GZ_SPECULAR_COEFFICIENT       GzColor		Ks coef's
- GZ_DISTRIBUTION_COEFFICIENT   float		spec power
*/

	return GZ_SUCCESS;
}

int GzRender::GzPutTriangle(int numParts, GzToken *nameList, GzPointer *valueList)
/* numParts - how many names and values */
{
    GzCoord v[3]; //set vert for initialize
    GzCoord vert[3]; //trans to screen space
    GzCoord v_norm[3]; //set vertNorm for initialize
    GzCoord vert_norm[3]; //trans to image space
    //Vertex vert_tex[3];
    Vertex out_v[3];
    GzCoord face_normal = { 0, 0, 0 }; //for flat shading
    GzCoord face_normal_help = { 0, 0, 0 };
    for (int i = 0; i < numParts; i++) {
        if (nameList[i] == GZ_NULL_TOKEN) {}
        else if(nameList[i] == GZ_TEXTURE_INDEX){
            GzTextureIndex* texturePointer = (GzTextureIndex*)(valueList[2]);
            //set and assign texture
            for(int i = 0; i < 3; i++){
                out_v[i].tx = texturePointer[i][0];
                out_v[i].ty = texturePointer[i][1];
            }
            //assign texture
//            for(int i = 0; i < 3; i++){
//                out_v[i].tx = vert_tex[i].tx;
//                out_v[i].ty = vert_tex[i].ty;
//            }
            
        }
        else if (nameList[i] == GZ_NORMAL) {
            //set Normal, get v_norm
            GzCoord* coordPointer = (GzCoord*)(valueList[1]);
            for (int j = 0; j < 3; j++) {
                v_norm[j][X] = (*(coordPointer + j))[X];
                v_norm[j][Y] = (*(coordPointer + j))[Y];
                v_norm[j][Z] = (*(coordPointer + j))[Z];
            }
            //transfer vert form world to image
            float vert_help[4][3];
            float tmp[4][3];
            for (int j = 0; j < 3; j++)
            {
                tmp[0][j] = v_norm[j][X];
                tmp[1][j] = v_norm[j][Y];
                tmp[2][j] = v_norm[j][Z];
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
                        vert_help[m][n] = vert_help[m][n] + Xnorm[matlevel - 1][m][k] * tmp[k][n];
                    }
                }
            }
            
            for (int j = 0; j < 3; j++)
            {
                vert_norm[j][X] = vert_help[0][j] / vert_help[3][j];
                vert_norm[j][Y] = vert_help[1][j] / vert_help[3][j];
                vert_norm[j][Z] = vert_help[2][j] / vert_help[3][j];
            }
            //normalize normal
            normalizeCoord(vert_norm[X]);
            normalizeCoord(vert_norm[Y]);
            normalizeCoord(vert_norm[Z]);
            //assign norm to out_v
            for (int j = 0; j < 3; j++) {
                out_v[j].nx = vert_norm[j][X];
                out_v[j].ny = vert_norm[j][Y];
                out_v[j].nz = vert_norm[j][Z];
            }
            
            face_normal_help[X] = face_normal[X] * Xnorm[matlevel-1][0][0] + face_normal[Y] * Xnorm[matlevel-1][0][1] +
            face_normal[Z] * Xnorm[matlevel-1][0][2];
            face_normal_help[Y] = face_normal[X] * Xnorm[matlevel-1][1][0] + face_normal[Y] * Xnorm[matlevel-1][1][1] +
            face_normal[Z] * Xnorm[matlevel-1][1][2];
            face_normal_help[Z] = face_normal[X] * Xnorm[matlevel-1][2][0] + face_normal[Y] * Xnorm[matlevel-1][2][1] +
            face_normal[Z] * Xnorm[matlevel-1][2][2];
            float mod_res = sqrt((face_normal_help[X] * face_normal_help[X]) + (face_normal_help[Y] * face_normal_help[Y]) + (face_normal_help[Z] * face_normal_help[Z]));
            face_normal[X] = face_normal_help[X] / mod_res;
            face_normal[Y] = face_normal_help[Y] / mod_res;
            face_normal[Z] = face_normal_help[Z] / mod_res;
            normalizeCoord(face_normal);
        }
        else if (nameList[i] == GZ_POSITION) {
            //set coord to 3 verts.
            GzCoord* coordPointer = (GzCoord*)valueList[0];
            for (int j = 0; j < 3; j++) {
                v[j][X] = (*(coordPointer + j))[X];
                v[j][Y] = (*(coordPointer + j))[Y];
                v[j][Z] = (*(coordPointer + j))[Z];
            }
            //set face_normal
            face_normal[X] = ((v[1][Y] - v[0][Y]) * (v[2][Z] - v[0][Z])) - ((v[2][Y] - v[0][Y]) * (v[1][Z] - v[0][Z]));
            face_normal[Y] = ((v[1][Z] - v[0][Z]) * (v[2][X] - v[0][X])) - ((v[2][Z] - v[0][Z]) * (v[1][X] - v[0][X]));
            face_normal[Z] = ((v[1][X] - v[0][X]) * (v[2][Y] - v[0][Y])) - ((v[2][X] - v[0][X]) * (v[1][Y] - v[0][Y]));
            GzCoord res_normal;
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
            //assign to out_v
            for (int j = 0; j < 3; j++) {
                out_v[j].x = vert[j][X];
                out_v[j].y = vert[j][Y];
                out_v[j].z = vert[j][Z];
            }
        }
    }
    //sort verts by y-coords
    for (int j = 1; j < 3; j++) {
        Vertex tmp;
        tmp = out_v[j];
        int m;
        for (m = j - 1; m >= 0 && ((out_v[m].y > tmp.y) || ((out_v[m].y == tmp.y) && (out_v[m].x > tmp.x))); m--) {
            out_v[m + 1] = out_v[m];
        }
        out_v[m + 1] = tmp;
    }
    
    //GzColor color_sd;
    //shading calculation
    if(interp_mode == GZ_COLOR){
        GzColor color_sd;
        //get color for 3 vertexs
        for(int j = 0; j < 3; j++){
            getColor(out_v[j], color_sd);
            out_v[j].nx = color_sd[RED];
            out_v[j].ny = color_sd[GREEN];
            out_v[j].nz = color_sd[BLUE];
        }
    }else if(interp_mode == GZ_NORMALS){}
    else {//flat shading
        GzColor color_sd = { 0, 0, 0 };
        Vertex tri_norm;
        tri_norm.nx = face_normal[X];
        tri_norm.ny = face_normal[Y];
        tri_norm.nz = face_normal[Z];
        getColor(tri_norm, color_sd);
        flatcolor[RED] = color_sd[RED];
        flatcolor[GREEN] = color_sd[GREEN];
        flatcolor[BLUE] = color_sd[BLUE];
    }
    
    //calculate texture
    //perspective-correction: each vertex u,v to transform them to perspective space U,V
    //Transforming (warping) vertex parameter values to perspective space
    for(int i = 0; i < 3; i++){
        float v_z = out_v[i].z / (INT_MAX - out_v[i].z);
        out_v[i].tx = out_v[i].tx / (v_z + 1);
        out_v[i].ty = out_v[i].ty / (v_z + 1);
    }
    
    //set up edges; sort it by L/R
    Edge Gzedge[3];
    int orient = 0;
    Gzedge[0].assign(out_v[0], out_v[1]);
    Gzedge[1].assign(out_v[1], out_v[2]);
    Gzedge[2].assign(out_v[0], out_v[2]);
    if (out_v[0].y == out_v[1].y) {
        orient = 0; //inverted tri
    }else if(out_v[1].y == out_v[2].y){
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
    
    //Scan line
    //set up slope for scan line
    GzColor color;
    float slopeX0 = Gzedge[0].slopeX(Gzedge[0].start, Gzedge[0].end);
    float slopeX1 = Gzedge[1].slopeX(Gzedge[1].start, Gzedge[1].end);
    float slopeX2 = Gzedge[2].slopeX(Gzedge[2].start, Gzedge[2].end);
    float slopeZ0 = Gzedge[0].slopeZ(Gzedge[0].start, Gzedge[0].end);
    float slopeZ1 = Gzedge[1].slopeZ(Gzedge[1].start, Gzedge[1].end);
    float slopeZ2 = Gzedge[2].slopeZ(Gzedge[2].start, Gzedge[2].end);
    float deltaY = ceil(out_v[0].y) - out_v[0].y;
    float slopeZ = 0;
    float deltaX = 0;
    float slopezR;
    float slopezG;
    float slopezB;
    //set up slope for texture color
    float slopeTX0 = Gzedge[0].SlopeTx(Gzedge[0].start, Gzedge[0].end);
    float slopeTX1 = Gzedge[1].SlopeTx(Gzedge[1].start, Gzedge[1].end);
    float slopeTX2 = Gzedge[2].SlopeTx(Gzedge[2].start, Gzedge[2].end);
    float slopeTY0 = Gzedge[0].SlopeTy(Gzedge[0].start, Gzedge[0].end);
    float slopeTY1 = Gzedge[1].SlopeTy(Gzedge[1].start, Gzedge[1].end);
    float slopeTY2 = Gzedge[2].SlopeTy(Gzedge[2].start, Gzedge[2].end);
    
    //color slope
    //set up the slope for color
    float slopeCR0 = Gzedge[0].SlopeCR(Gzedge[0].start, Gzedge[0].end);
    float slopeCR1 = Gzedge[1].SlopeCR(Gzedge[1].start, Gzedge[1].end);
    float slopeCR2 = Gzedge[2].SlopeCR(Gzedge[2].start, Gzedge[2].end);
    float slopeCG0 = Gzedge[0].SlopeCG(Gzedge[0].start, Gzedge[0].end);
    float slopeCG1 = Gzedge[1].SlopeCG(Gzedge[1].start, Gzedge[1].end);
    float slopeCG2 = Gzedge[2].SlopeCG(Gzedge[2].start, Gzedge[2].end);
    float slopeCB0 = Gzedge[0].SlopeCB(Gzedge[0].start, Gzedge[0].end);
    float slopeCB1 = Gzedge[1].SlopeCB(Gzedge[1].start, Gzedge[1].end);
    float slopeCB2 = Gzedge[2].SlopeCB(Gzedge[2].start, Gzedge[2].end);
    //Initialize current for edge 0 and edge 2
    Gzedge[0].current.x = Gzedge[0].start.x + slopeX0 * deltaY;
    Gzedge[0].current.y = Gzedge[0].start.y + deltaY;
    Gzedge[0].current.z = Gzedge[0].start.z + slopeZ0 * deltaY;
    Gzedge[2].current.x = Gzedge[2].start.x + slopeX2 * deltaY;
    Gzedge[2].current.y = Gzedge[2].start.y + deltaY;
    Gzedge[2].current.z = Gzedge[2].start.z + slopeZ2 * deltaY;
    //initialize the edge cursor color for edge 0
    Gzedge[0].current.nx = Gzedge[0].start.nx + slopeCR0 * deltaY;
    Gzedge[0].current.ny = Gzedge[0].start.ny + slopeCG0 * deltaY;
    Gzedge[0].current.nz = Gzedge[0].start.nz + slopeCB0 * deltaY;
    //initialize the edge cursor color for edge 2
    Gzedge[2].current.nx = Gzedge[2].start.nx + slopeCR2 * deltaY;
    Gzedge[2].current.ny = Gzedge[2].start.ny + slopeCG2 * deltaY;
    Gzedge[2].current.nz = Gzedge[2].start.nz + slopeCB2 * deltaY;
    //initialize the edge cursor texture on edge 0
    Gzedge[0].current.tx = Gzedge[0].start.tx + slopeTX0 * deltaY;
    Gzedge[0].current.ty = Gzedge[0].start.ty + slopeTY0 * deltaY;
    //initialize the edge cursor texture on edge 2
    Gzedge[2].current.tx = Gzedge[2].start.tx + slopeTX2 * deltaY;
    Gzedge[2].current.ty = Gzedge[2].start.ty + slopeTY2 * deltaY;
    //Texture
    GzTextureIndex Tex = {0, 0};
    float slopeTX;
    float slopeTY;
    //Span
    Span spanLine;
    int a = 0;
    int b = 0;
    GzPixel color_scan;
    //the first area
    while (Gzedge[0].current.y < Gzedge[0].end.y) {
        if (orient == 2 || orient == 1) {
            //set span cursor position
            spanLine.assign(Gzedge[0].current, Gzedge[2].current);
            deltaX = ceil(Gzedge[0].current.x) - Gzedge[0].current.x;
            slopeZ = spanLine.slopeZ(Gzedge[0].current, Gzedge[2].current);
            spanLine.current.x = Gzedge[0].current.x + deltaX;
            spanLine.current.y = Gzedge[0].current.y;
            spanLine.current.z = Gzedge[0].current.z + deltaX * slopeZ;
            //set span cursor color
            slopezR = spanLine.SlopeZR(Gzedge[0].current, Gzedge[2].current);
            slopezG = spanLine.SlopeZG(Gzedge[0].current, Gzedge[2].current);
            slopezB = spanLine.SlopeZB(Gzedge[0].current, Gzedge[2].current);
            spanLine.current.nx = Gzedge[0].current.nx + deltaX * slopezR;
            spanLine.current.ny = Gzedge[0].current.ny + deltaX * slopezG;
            spanLine.current.nz = Gzedge[0].current.nz + deltaX * slopezB;
            //set span cursor texture
            slopeTX = spanLine.SlopeZtx(Gzedge[0].current, Gzedge[2].current);
            slopeTY = spanLine.SlopeZty(Gzedge[0].current, Gzedge[2].current);
            spanLine.current.tx = Gzedge[0].current.tx + deltaX * slopeTX;
            spanLine.current.ty = Gzedge[0].current.ty + deltaX * slopeTY;
        }
        else if (orient == 3) {
            //set span cursor position
            spanLine.assign(Gzedge[2].current, Gzedge[0].current);
            deltaX = ceil(Gzedge[2].current.x) - Gzedge[2].current.x;
            slopeZ = spanLine.slopeZ(Gzedge[2].current, Gzedge[0].current);
            spanLine.current.x = Gzedge[2].current.x + deltaX;
            spanLine.current.y = Gzedge[2].current.y;
            spanLine.current.z = Gzedge[2].current.z + deltaX * slopeZ;
            //set span cursor color
            slopezR = spanLine.SlopeZR(Gzedge[2].current, Gzedge[0].current);
            slopezG = spanLine.SlopeZG(Gzedge[2].current, Gzedge[0].current);
            slopezB = spanLine.SlopeZB(Gzedge[2].current, Gzedge[0].current);
            spanLine.current.nx = Gzedge[2].current.nx + deltaX * slopezR;
            spanLine.current.ny = Gzedge[2].current.ny + deltaX * slopezG;
            spanLine.current.nz = Gzedge[2].current.nz + deltaX * slopezB;
            //set span cursor texture
            slopeTX = spanLine.SlopeZtx(Gzedge[2].current, Gzedge[0].current);
            slopeTY = spanLine.SlopeZty(Gzedge[2].current, Gzedge[0].current);
            spanLine.current.tx = Gzedge[2].current.tx + deltaX * slopeTX;
            spanLine.current.ty = Gzedge[2].current.ty + deltaX * slopeTY;
        }
        while (((orient == 2 || orient == 1) && spanLine.current.x < Gzedge[2].current.x) ||(orient == 3 && spanLine.current.x < Gzedge[0].current.x))
        {
            a = (int)spanLine.current.x;
            b = (int)Gzedge[0].current.y;
            if (spanLine.current.z < 0) { continue; }
            GzGet(a, b, &color_scan.red, &color_scan.green, &color_scan.blue, &color_scan.alpha, &color_scan.z);
            if (spanLine.current.z < color_scan.z) {
                if (interp_mode == GZ_COLOR)
                {
                    //Transforming (unwarping) interpolated pixel values back to affine space
                    float tmp_z = spanLine.current.z / (INT_MAX - spanLine.current.z);
                    Tex[0] = spanLine.current.tx * (tmp_z + 1);
                    Tex[1] = spanLine.current.ty * (tmp_z + 1);
                    //Compute texture color = f(u,v) and evaluate shading equation
                    tex_fun(Tex[0], Tex[1], color);
                    color[RED] = color[RED] * spanLine.current.nx;
                    color[GREEN] = color[GREEN] * spanLine.current.ny;
                    color[BLUE] = color[BLUE] * spanLine.current.nz;
                    GzPut(a, b, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 0, (GzDepth)spanLine.current.z);
                }
                else if (interp_mode == GZ_NORMALS) {
                    //Transforming (unwarping) interpolated pixel values back to affine space
                    float tmp_z = spanLine.current.z / (INT_MAX - spanLine.current.z);
                    Tex[0] = spanLine.current.tx * (tmp_z + 1);
                    Tex[1] = spanLine.current.ty * (tmp_z + 1);
                    //Compute texture color = f(u,v) and evaluate shading equation
                    tex_fun(Tex[0], Tex[1], color);
                    memcpy(Ka, color, sizeof(GzColor));
                    memcpy(Kd, color, sizeof(GzColor));
                    normalizeNormal(spanLine.current);
                    getColor(spanLine.current, color);
                    GzPut(a, b, ctoi(color[0]), ctoi(color[1]), ctoi(color[2]), 0, (GzDepth)spanLine.current.z);
                }
                else {
                    GzPut(a, b, ctoi(flatcolor[0]), ctoi(flatcolor[1]), ctoi(flatcolor[2]), 0, (GzDepth)spanLine.current.z);
                }
            }
            //x++
            spanLine.current.x++;
            spanLine.current.z = spanLine.current.z + slopeZ;
            //span color++
            spanLine.current.nx = spanLine.current.nx + slopezR;
            spanLine.current.ny = spanLine.current.ny + slopezG;
            spanLine.current.nz = spanLine.current.nz + slopezB;
            //texture++
            spanLine.current.tx += slopeTX;
            spanLine.current.ty += slopeTY;
        }
        //y++
        Gzedge[0].current.x += slopeX0;
        Gzedge[0].current.y++;
        Gzedge[0].current.z += slopeZ0;
        Gzedge[2].current.x += slopeX2;
        Gzedge[2].current.y++;
        Gzedge[2].current.z += slopeZ2;
        //edge color++
        Gzedge[0].current.nx = Gzedge[0].current.nx + slopeCR0;
        Gzedge[0].current.ny = Gzedge[0].current.ny + slopeCG0;
        Gzedge[0].current.nz = Gzedge[0].current.nz + slopeCB0;
        Gzedge[2].current.nx = Gzedge[2].current.nx + slopeCR2;
        Gzedge[2].current.ny = Gzedge[2].current.ny + slopeCG2;
        Gzedge[2].current.nz = Gzedge[2].current.nz + slopeCB2;
        //texture++
        Gzedge[0].current.tx += slopeTX0;
        Gzedge[0].current.ty += slopeTY0;
        Gzedge[2].current.tx += slopeTX2;
        Gzedge[2].current.ty += slopeTY2;
        
    }
    deltaY = ceil(out_v[1].y) - out_v[1].y;
    //initialize the edge cursor color for edge 1
    Gzedge[1].current.x = Gzedge[1].start.x + slopeX1 * deltaY;
    Gzedge[1].current.y = Gzedge[1].start.y + deltaY;
    Gzedge[1].current.z = Gzedge[1].start.z + slopeZ1 * deltaY;
    //initialize the edge cursor color for edge 1
    Gzedge[1].current.nx = Gzedge[1].start.nx + slopeCR1 * deltaY;
    Gzedge[1].current.ny = Gzedge[1].start.ny + slopeCG1 * deltaY;
    Gzedge[1].current.nz = Gzedge[1].start.nz + slopeCB1 * deltaY;
    //initialize the edge cursor texture for edge 1
    Gzedge[1].current.tx = Gzedge[1].start.tx + slopeTX1 * deltaY;
    Gzedge[1].current.ty = Gzedge[1].start.ty + slopeTX1 * deltaY;
    
    //the next area
    while (Gzedge[1].current.y < Gzedge[1].end.y){
        if (orient == 2) {
            //set span cursor position
            spanLine.assign(Gzedge[1].current, Gzedge[2].current);
            deltaX = ceil(Gzedge[1].current.x) - Gzedge[1].current.x;
            slopeZ = spanLine.slopeZ(Gzedge[1].current, Gzedge[2].current);
            spanLine.current.x = Gzedge[1].current.x + deltaX;
            spanLine.current.y = Gzedge[1].current.y;
            spanLine.current.z = Gzedge[1].current.z + deltaX * slopeZ;
            //set span cursor color
            slopezR = spanLine.SlopeZR(Gzedge[1].current, Gzedge[2].current);
            slopezG = spanLine.SlopeZG(Gzedge[1].current, Gzedge[2].current);
            slopezB = spanLine.SlopeZB(Gzedge[1].current, Gzedge[2].current);
            spanLine.current.nx = Gzedge[1].current.nx + deltaX * slopezR;
            spanLine.current.ny = Gzedge[1].current.ny + deltaX * slopezG;
            spanLine.current.nz = Gzedge[1].current.nz + deltaX * slopezB;
            //set span cursor texture
            slopeTX = spanLine.SlopeZtx(Gzedge[1].current, Gzedge[2].current);
            slopeTY = spanLine.SlopeZty(Gzedge[1].current, Gzedge[2].current);
            spanLine.current.tx = Gzedge[1].current.tx + deltaX * slopeTX;
            spanLine.current.ty = Gzedge[1].current.ty + deltaX * slopeTY;
        }
        else if (orient == 0 || orient == 3) {
            spanLine.assign(Gzedge[2].current, Gzedge[1].current);
            deltaX = ceil(Gzedge[2].current.x) - Gzedge[2].current.x;
            slopeZ = spanLine.slopeZ(Gzedge[2].current, Gzedge[1].current);
            spanLine.current.x = Gzedge[2].current.x + deltaX;
            spanLine.current.y = Gzedge[2].current.y;
            spanLine.current.z = Gzedge[2].current.z + deltaX * slopeZ;
            //set span cursor color
            slopezR = spanLine.SlopeZR(Gzedge[2].current, Gzedge[1].current);
            slopezG = spanLine.SlopeZG(Gzedge[2].current, Gzedge[1].current);
            slopezB = spanLine.SlopeZB(Gzedge[2].current, Gzedge[1].current);
            spanLine.current.nx = Gzedge[2].current.nx + deltaX * slopezR;
            spanLine.current.ny = Gzedge[2].current.ny + deltaX * slopezG;
            spanLine.current.nz = Gzedge[2].current.nz + deltaX * slopezB;
            //set span cursor texture
            slopeTX = spanLine.SlopeZtx(Gzedge[2].current, Gzedge[1].current);
            slopeTY = spanLine.SlopeZty(Gzedge[2].current, Gzedge[1].current);
            spanLine.current.tx = Gzedge[2].current.tx + deltaX * slopeTX;
            spanLine.current.ty = Gzedge[2].current.ty + deltaX * slopeTY;
        }
        while (((orient == 3 || orient == 0) && spanLine.current.x < Gzedge[1].current.x) ||(orient == 2 && spanLine.current.x < Gzedge[2].current.x)){
            a = (int)spanLine.current.x;
            b = (int)Gzedge[1].current.y;
            if (spanLine.current.z < 0) { continue; }
            GzGet(a, b, &color_scan.red, &color_scan.green, &color_scan.blue, &color_scan.alpha, &color_scan.z);
            if (spanLine.current.z < color_scan.z) {
                if (interp_mode == GZ_COLOR)
                {
                    //Transforming (unwarping) interpolated pixel values back to affine space
                    float tmp_z = spanLine.current.z / (INT_MAX - spanLine.current.z);
                    Tex[0] = spanLine.current.tx * (tmp_z + 1);
                    Tex[1] = spanLine.current.ty * (tmp_z + 1);
                    //Compute texture color = f(u,v) and evaluate shading equation
                    tex_fun(Tex[0], Tex[1], color);
                    color[RED] = color[RED] * spanLine.current.nx;
                    color[GREEN] = color[GREEN] * spanLine.current.ny;
                    color[BLUE] = color[BLUE] * spanLine.current.nz;
                    GzPut(a, b, ctoi(spanLine.current.nx), ctoi(spanLine.current.ny), ctoi(spanLine.current.nz), 0, (GzDepth)spanLine.current.z);
                }
                else if(interp_mode == GZ_NORMALS){
                    //Transforming (unwarping) interpolated pixel values back to affine space
                    float tmp_z = spanLine.current.z / (INT_MAX - spanLine.current.z);
                    Tex[0] = spanLine.current.tx * (tmp_z + 1);
                    Tex[1] = spanLine.current.ty * (tmp_z + 1);
                    //Compute texture color = f(u,v) and evaluate shading equation
                    tex_fun(Tex[0], Tex[1], color);
                    memcpy(Ka, color, sizeof(GzColor));
                    memcpy(Kd, color, sizeof(GzColor));
                    normalizeNormal(spanLine.current);
                    getColor(spanLine.current, color);
                    GzPut(a, b, ctoi(color[RED]), ctoi(color[GREEN]), ctoi(color[BLUE]), 0, (GzDepth)spanLine.current.z);
                }else{
                    GzPut(a, b, ctoi(flatcolor[RED]), ctoi(flatcolor[GREEN]), ctoi(flatcolor[BLUE]), 0, (GzDepth)spanLine.current.z);
                }
            }
            spanLine.current.x++;
            spanLine.current.z += slopeZ;
            //span color++
            spanLine.current.nx = spanLine.current.nx + slopezR;
            spanLine.current.ny = spanLine.current.ny + slopezG;
            spanLine.current.nz = spanLine.current.nz + slopezB;
            //texture++
            spanLine.current.tx += slopeTX;
            spanLine.current.ty += slopeTY;
        }
        //y++
        Gzedge[1].current.x += slopeX1;
        Gzedge[1].current.y++;
        Gzedge[1].current.z += slopeZ1;
        Gzedge[2].current.x += slopeX2;
        Gzedge[2].current.y++;
        Gzedge[2].current.z += slopeZ2;
        //edge color++
        Gzedge[1].current.nx = Gzedge[1].current.nx + slopeCR1;
        Gzedge[1].current.ny = Gzedge[1].current.ny + slopeCG1;
        Gzedge[1].current.nz = Gzedge[1].current.nz + slopeCB1;
        Gzedge[2].current.nx = Gzedge[2].current.nx + slopeCR2;
        Gzedge[2].current.ny = Gzedge[2].current.ny + slopeCG2;
        Gzedge[2].current.nz = Gzedge[2].current.nz + slopeCB2;
        //texture++
        Gzedge[1].current.tx += slopeTX1;
        Gzedge[1].current.ty += slopeTY1;
        Gzedge[2].current.tx += slopeTX2;
        Gzedge[2].current.ty += slopeTY2;
        
    }
/* HW 2.2
-- Pass in a triangle description with tokens and values corresponding to
      GZ_NULL_TOKEN:		do nothing - no values
      GZ_POSITION:		3 vert positions in model space
-- Return error code
*/
/*
-- Xform positions of verts using matrix on top of stack 
-- Clip - just discard any triangle with any vert(s) behind view plane 
		- optional: test for triangles with all three verts off-screen (trivial frustum cull)
-- invoke triangle rasterizer  
*/

	return GZ_SUCCESS;
}

void GzRender::normalizeCoord(GzCoord& v)
{
    float sum = v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z];
    float absoluteValue = sqrt(sum);
    v[X] = v[X] / absoluteValue;
    v[Y] = v[Y] / absoluteValue;
    v[Z] = v[Z] / absoluteValue;
}
void GzRender::normalizeNormal(Vertex& v)
{
    float sum = v.nx * v.nx + v.ny * v.ny + v.nz * v.nz;
    float absoluteValue = sqrt(sum);
    v.nx = v.nx / absoluteValue;
    v.ny = v.ny / absoluteValue;
    v.nz = v.nz / absoluteValue;
}
Vertex GzRender::normalize(const Vertex& v)
{
    float sum = v.x * v.x + v.y * v.y + v.z * v.z;
    float absoluteValue = sqrt(sum);
    Vertex vector;
    vector.x = v.x / absoluteValue;
    vector.y = v.y / absoluteValue;
    vector.z = v.z / absoluteValue;
    return vector;
}
int GzRender::getColor(const Vertex v, GzColor c){
    Vertex eye;
    eye.x = 0;
    eye.y = 0;
    eye.z = -1;
    
    Vertex normal;
    normal.x = v.nx;
    normal.y = v.ny;
    normal.z = v.nz;
    
    Vertex light_Dir;
    Vertex light_Col;
    Vertex reflect;
    Vertex sumD;
    Vertex sumS;
    sumS.x = 0;
    sumS.y = 0;
    sumS.z = 0;
    
    sumD.x = 0;
    sumD.y = 0;
    sumD.z = 0;
    float NL;
    float RE;
    float NE;
    for(int i = 0; i < numlights; i++){
        light_Dir.x = lights[i].direction[X];
        light_Dir.y = lights[i].direction[Y];
        light_Dir.z = lights[i].direction[Z];
        light_Col.x = lights[i].color[RED];
        light_Col.y = lights[i].color[GREEN];
        light_Col.z = lights[i].color[BLUE];
        NL = normal.x * light_Dir.x + normal.y * light_Dir.y + normal.z * light_Dir.z;
        NE = normal.x * eye.x + normal.y * eye.y + normal.z * eye.z;
        if(NL * NE < 0){continue;}
        else if(NL < 0 && NE < 0){
            //flip normal
            normal.x = -normal.x;
            normal.y = -normal.y;
            normal.z = -normal.z;
            NL = -NL;
        }
        
        //R = 2(N.L) N - L
        reflect.x = 2 * NL * normal.x - light_Dir.x;
        reflect.y = 2 * NL * normal.y - light_Dir.y;
        reflect.z = 2 * NL * normal.z - light_Dir.z;
        reflect = normalize(reflect);
        RE = reflect.x * eye.x + reflect.y * eye.y + reflect.z * eye.z;
        if(RE < 0){RE = 0;}
        else if(RE > 1){RE = 1;}
        RE = pow(RE, spec);
        
        //calculate sumD
        sumD.x = sumD.x + NL * light_Col.x;
        sumD.y = sumD.y + NL * light_Col.y;
        sumD.z = sumD.z + NL * light_Col.z;
        //calulate sumS
        sumS.x = sumS.x + RE * light_Col.x;
        sumS.y = sumS.y + RE * light_Col.y;
        sumS.z = sumS.z + RE * light_Col.z;
    }
    c[RED] = Ks[0] * sumS.x + Kd[0] * sumD.x + Ka[0] * ambientlight.color[0];
    c[GREEN] = Ks[1] * sumS.y + Kd[1] * sumD.y + Ka[1] * ambientlight.color[1];
    c[BLUE] = Ks[2] * sumS.z + Kd[2] * sumD.z + Ka[2] * ambientlight.color[2];
    //check color
    if(c[RED] > 1){c[RED] = 1;}
    if(c[GREEN] > 1){c[GREEN] = 1;}
    if(c[BLUE] > 1){c[BLUE] = 1;}
    if(c[RED] < 0){c[RED] = 0;}
    if(c[GREEN] < 0){c[GREEN] = 0;}
    if(c[BLUE] < 0){c[BLUE] = 0;}
    return GZ_SUCCESS;
}

