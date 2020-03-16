#include "config.h"
#include "glOric.h"

#define INK_BLACK	0
#define INK_RED		1
#define INK_GREEN	2
#define INK_YELLOW	3
#define INK_BLUE	4
#define INK_MAGENTA	5
#define INK_CYAN	6
#define INK_WHITE	7
#define LORES_SCREEN_ADDRESS 0xBB80
#define HIRES_SCREEN_ADDRESS 0xA000

#define LORES_SCREEN_WIDTH 40
#define LORES_SCREEN_HEIGHT 26

#define TEXT_50Hz	26
#define HIRES_50Hz	30

#define TEXTURE_1 'b'
#define TEXTURE_2 '*'
#define TEXTURE_3 'y'
#define TEXTURE_4 'h'
#define TEXTURE_5 'm'
#define TEXTURE_6 'r'
#define TEXTURE_7 'f'


unsigned char tab_color [] = {INK_CYAN, INK_YELLOW, INK_MAGENTA, INK_BLUE, INK_GREEN, INK_RED, INK_CYAN, INK_YELLOW} ;

#define LARG 4
#define DIST 20
#define HAUT 26
#define POS 11
#define PROF 8
#define SPACE 6
#define MAX_LARG 12
#define MAX_HAUT 23
#define MAX_PROF 60

#define SCREW 1
char geomPipe []= {
/* Nb Coords = */ 20,
/* Nb Faces = */ 8,
/* Nb Segments = */ 16,
/* Nb Particules = */ 6,
// Coord List : X, Y, Z, unused
     DIST,  -LARG,      -HAUT,  0, 
     DIST,  -LARG, -POS-SPACE,  1,
     DIST,   LARG, -POS-SPACE,  2,
     DIST,   LARG,      -HAUT,  3,
     
     DIST,  -LARG,          0,  4, 
     DIST,  -LARG,       -POS,  5,
     DIST,   LARG,       -POS,  6,
     DIST,   LARG,          0,  7,
 
 DIST+PROF, -LARG+SCREW,  -POS-SPACE,  8, 
 DIST+PROF, +LARG-SCREW,  -POS-SPACE,  9,
 DIST+PROF, -LARG+SCREW,        -POS, 10,
 DIST+PROF,  LARG-SCREW,        -POS, 11,

         12, -MAX_LARG,           0, 12, 
         12, +MAX_LARG,           0, 13,
         12, +MAX_LARG,   -MAX_HAUT, 14,
         12, -MAX_LARG,   -MAX_HAUT, 15,

  MAX_PROF, -MAX_LARG,           0, 16, 
  MAX_PROF, +MAX_LARG,           0, 17,
  MAX_PROF, +MAX_LARG,   -MAX_HAUT, 18,
  MAX_PROF, -MAX_LARG,   -MAX_HAUT, 19,

//          0, -MAX_LARG, -MAX_HAUT/2, 20, 
//   MAX_PROF, -MAX_LARG, -MAX_HAUT/2, 21,
//   MAX_PROF, +MAX_LARG, -MAX_HAUT/2, 22,
//          0, +MAX_LARG, -MAX_HAUT/2, 23,

// Face List : idxPoint1, idxPoint2, idxPoint3, character 
  0, 1, 2, TEXTURE_4+128,
  0, 2, 3, TEXTURE_4+128,
  4, 5, 6, TEXTURE_4+128,
  4, 6, 7, TEXTURE_4+128,
  1, 2, 8, TEXTURE_4,
  2, 8, 9, TEXTURE_4,
 5, 6, 10, TEXTURE_4,
 6,10, 11, TEXTURE_4,
// Segment List : idxPoint1, idxPoint2, idxPoint3, character 
0, 1, 'i'+128, 0,
1, 2, 'k'+128, 0,
2, 3, 'g'+128, 0,
// 0, 3, 'k'+128, 0,
4, 5, 'i'+128, 0,
5, 6, 'k'+128, 0,
6, 7, 'g'+128, 0,
// 4, 7, 'k'+128, 0,
// 1, 8, '/'+128, 0,
// 2, 9, '/'+128, 0,
// 10,5, '/'+128, 0,
// 11,6, '/'+128, 0,
8, 9, 'k'+128, 0,
10, 11, 'k'+128, 0,

16, 12, '.', 0,
17, 13, '.', 0,
14, 18, '.', 0,
15, 19, '.', 0,
16, 17, '-', 0,
17, 18, ':', 0,
18, 19, '-', 0,
19, 16, ':', 0,

// 20, 21, '.', 0,
// 21, 22, '.', 0,
// 22, 23, '.', 0,


// Particule List : idxPoint1, character 
1, 'l'+128,
2, 'j'+128,
5, 'l'+128,
6, 'j'+128,
4, ' ',
7, ' ',

};



extern char          ch2disp;
extern signed char points2dL[];
extern signed char points2aH[];
extern signed char points2aV[];
extern signed char   P1X, P1Y;
void glDrawParticules(){
    unsigned char ii = 0;

    unsigned char idxPt, offPt, dchar;
    unsigned int  dist;


    for (ii = 0; ii < nbParticules; ii++) {
        idxPt    = particulesPt[ii];  // ii*SIZEOF_SEGMENT +0
        ch2disp = particulesChar[ii];    // ii*SIZEOF_SEGMENT +2
        // printf ("particules : %d %d\n ", idxPt, ch2disp);
        dchar = 0; //FIXME : points2dL[idxPt]-2 ;  to helps particule to be displayed
        P1X = (SCREEN_WIDTH -points2aH[idxPt]) >> 1;
        P1Y = (SCREEN_HEIGHT - points2aV[idxPt]) >> 1;

        zplot(P1X, P1Y, dchar, ch2disp);

    }

}

void addGeom(
    signed char   X,
    signed char   Y,
    signed char   Z,
    unsigned char sizeX,
    unsigned char sizeY,
    unsigned char sizeZ,
    unsigned char orientation,
    char          geom[]) {

    int kk;

    for (kk=0; kk< geom[0]; kk++){
        points3dX[nbPoints] = X + ((orientation == 0) ? sizeX * geom[4+kk*SIZEOF_3DPOINT+0]: sizeY * geom[4+kk*SIZEOF_3DPOINT+1]);// X + ii;
        points3dY[nbPoints] = Y + ((orientation == 0) ? sizeY * geom[4+kk*SIZEOF_3DPOINT+1]: sizeX * geom[4+kk*SIZEOF_3DPOINT+0]);// Y + jj;
        points3dZ[nbPoints] = Z + geom[4+kk*SIZEOF_3DPOINT+2]*sizeZ;// ;
        nbPoints++;
    }
    for (kk=0; kk< geom[1]; kk++){
        facesPt1[nbFaces] = nbPoints - (geom[0]-geom[4+geom[0]*SIZEOF_3DPOINT+kk*SIZEOF_FACE+0]);  // Index Point 1
        facesPt2[nbFaces] = nbPoints - (geom[0]-geom[4+geom[0]*SIZEOF_3DPOINT+kk*SIZEOF_FACE+1]);  // Index Point 2
        facesPt3[nbFaces] = nbPoints - (geom[0]-geom[4+geom[0]*SIZEOF_3DPOINT+kk*SIZEOF_FACE+2]);  // Index Point 3
        facesChar[nbFaces] = geom[4+geom[0]*SIZEOF_3DPOINT+kk*SIZEOF_FACE+3];  // Character
        nbFaces++;
    }
    for (kk=0; kk< geom[2]; kk++){
        segmentsPt1[nbSegments] = nbPoints - (geom[0]-geom[4+geom[0]*SIZEOF_3DPOINT+geom[1]*SIZEOF_FACE+kk*SIZEOF_SEGMENT + 0]);  // Index Point 1
        segmentsPt2[nbSegments] = nbPoints - (geom[0]-geom[4+geom[0]*SIZEOF_3DPOINT+geom[1]*SIZEOF_FACE+kk*SIZEOF_SEGMENT + 1]);  // Index Point 2
        segmentsChar[nbSegments] = geom[4+geom[0]*SIZEOF_3DPOINT+geom[1]*SIZEOF_FACE+kk*SIZEOF_SEGMENT + 2]; // Character
        nbSegments++;
    }
    for (kk=0; kk< geom[3]; kk++){
        particulesPt[nbParticules] = nbPoints - (geom[0]-geom[4 + geom[0]*SIZEOF_3DPOINT + geom[1]*SIZEOF_FACE + geom[2]*SIZEOF_SEGMENT + kk*SIZEOF_PARTICULE + 0]);  // Index Point
        particulesChar[nbParticules] = geom[4 + geom[0]*SIZEOF_3DPOINT + geom[1]*SIZEOF_FACE + geom[2]*SIZEOF_SEGMENT + kk*SIZEOF_PARTICULE + 1]; // Character
        nbParticules++;
    }
}

void change_char(char c, unsigned char patt01, unsigned char patt02, unsigned char patt03, unsigned char patt04, unsigned char patt05, unsigned char patt06, unsigned char patt07, unsigned char patt08) {
    unsigned char* adr;
    adr      = (unsigned char*)(0xB400 + c * 8);
    *(adr++) = patt01;
    *(adr++) = patt02;
    *(adr++) = patt03;
    *(adr++) = patt04;
    *(adr++) = patt05;
    *(adr++) = patt06;
    *(adr++) = patt07;
    *(adr++) = patt08;
}

#ifdef USE_COLOR


void prepare_colors() {
    int ii, jj;

	for (ii = 0; ii<=LORES_SCREEN_HEIGHT-NB_LESS_LINES_4_COLOR ; ii++){
		poke (LORES_SCREEN_ADDRESS+(ii*LORES_SCREEN_WIDTH)+0,HIRES_50Hz);
#ifdef USE_ZBUFFER
		fbuffer[ii*LORES_SCREEN_WIDTH]=HIRES_50Hz;
#endif // USE_ZBUFFER
		for (jj = 0; jj < 8; jj++) {
			poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*LORES_SCREEN_WIDTH)+1, tab_color[jj]);
			poke (HIRES_SCREEN_ADDRESS+((ii*8+jj)*LORES_SCREEN_WIDTH)+2, TEXT_50Hz);
		}
	}
}
void initColors(){

    prepare_colors();
    //              CYAN, YELLO, MAGE, BLUE GREEN, RED, CYAN, YELLO
    change_char('c', 0x7F, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x7F, 0x00);
	change_char('y', 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F);
	change_char('m', 0x00, 0x00, 0x7F, 0x00, 0x00, 0x7F, 0x00, 0x00);
	change_char('r', 0x00, 0x55, 0x7F, 0x00, 0x55, 0x7F, 0x00, 0x00);
	change_char('g', 0x55, 0xAA, 0x00, 0x00, 0x7F, 0x00, 0x55, 0xAA);
	change_char('b', 0xAA, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x55, 0x00);

	change_char('f', 0x00, 0xAA, 0x00, 0x55, 0x7F, 0x00, 0x00, 0xAA);

}
#endif

void initGl (){
    int ii;
    nbPoints     = 0;
    nbSegments   = 0;
    nbFaces      = 0;
    nbParticules = 0;

    CamPosX = 12;
    CamPosY = 0;
    CamPosZ = -13;

    CamRotZ = 0;
    CamRotX = 0;

    change_char(36, 0x80, 0x40, 020, 0x10, 0x08, 0x04, 0x02, 0x01);
#ifdef USE_COLOR
    // initColors();
#endif
	for (ii = 0; ii<=LORES_SCREEN_HEIGHT; ii++){
		fbuffer[ii*LORES_SCREEN_WIDTH]=COLOR ;//TEXT_50Hz;
		fbuffer[ii*LORES_SCREEN_WIDTH+1]=INK ;//TEXT_50Hz;
    }
    // printf ("***************\n");
    addGeom(0, 0, 0, 1, 1, 1, 0, geomPipe);
    // printf ("++++++++++++++++\n");get();
}


void moveShape (unsigned char pos, unsigned char counter){


    // points3dX[nbPoints] = X + ((orientation == 0) ? sizeX * geom[4+kk*SIZEOF_3DPOINT+0]: sizeY * geom[4+kk*SIZEOF_3DPOINT+1]);// X + ii;
    points3dX[ 0] = counter;
    points3dX[ 1] = counter;
    points3dX[ 2] = counter;
    points3dX[ 3] = counter;
    points3dX[ 4] = counter;
    points3dX[ 5] = counter;
    points3dX[ 6] = counter;
    points3dX[ 7] = counter;
    points3dX[ 8] = counter+PROF;
    points3dX[ 9] = counter+PROF;
    points3dX[10] = counter+PROF;
    points3dX[11] = counter+PROF;

    points3dZ[ 1] = -pos-SPACE;
    points3dZ[ 2] = -pos-SPACE;
    points3dZ[ 8] = -pos-SPACE;
    points3dZ[ 9] = -pos-SPACE;
    points3dZ[ 5] = -pos;
    points3dZ[ 6] = -pos;
    points3dZ[ 10] = -pos;
    points3dZ[ 11] = -pos;
    

}

