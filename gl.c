#include "config.h"
#include "glOric.h"

#define LORES_SCREEN_WIDTH 40
#define LORES_SCREEN_HEIGHT 26



/*  __                             
 * / _\     ___   ___  _ __    ___ 
 * \ \     / __| / _ \| '_ \  / _ \
 * _\ \   | (__ |  __/| | | ||  __/
 * \__/    \___| \___||_| |_| \___|
 */                                
/*                                                                              
                                      16____________________________\_______17 
                                     //           ..          .     .\      /| 
                                   //           ..          ..      .      / | 
                                 //            .           .        .     /  | 
                               //            ..           .         .    /   | 
                             //             .            .          .   /    | 
                           //             ..            .           .  /     | 
                         //             ..            ..            . /      | 
                       //              .             .              ./       | 
                     //              _____________  .               /        | 
                   //               4              7              //.        | 
                 //               ..|              |             /  .        | 
               //               ..  |       10.... | ____11     /   . HAUT  |  
             //                .    |      ..      |     /     /    .        | 
           //                ..     |     .        |    /     /     .        | 
         //                 .       |   ..         |   /     /      .        | 
       //                 ..        |  .           |  /     /       .        | 
     //                 ..          |..            | /     /        .        | 
   //                               5______________6/     /         .        | 
 12.....................................................13          .        | 
 |                                                                  .        | 
 |                                                                  .        | 
 |                                                                  .        | 
 |                             SPACE            /                   .        | 
 |                                            /_______\\____/       .        | 
 |                                         ///8        /\ /9        .        | 
 |                                       //    PROF  //  /          .        | 
 |                                     //           /   /         \ .        | 
 |                                   //17________\\/__/______\_____\\_______18 
 |                                   1               2        \.            /  
 |                                 //:               |        .\           /   
 |                               //  :               |       .  ||        /    
 |                             //    :               |      .            /     
 |                           //      :               |     .            /      
 |                         //        :               |    .            /       
 |                       //          :               |   .            /        
 |                     //            :               |  .            /         
 |                   //             .0_______________3 . MAX_PROF   /          
 |                 //              .     2*LARG      ..           //           
 |               //              ..                 .            /             
 |             //               .                  .            /              
 |           //             T ..                  .            /               
 |         //              S .                   .            /                
 |       //              I ..                   .            /                 
 |     //              D ..                    .            /                  
 |   //                 .                     .            /                   
 | //                 ..                     .            /                    
 |/                                        \\            /                     
 15..........................M.A.X._.L.A.R G\\..........14                     
                                             \\\                               
                    
*/

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
/* Nb Coords = */       20,
/* Nb Faces = */        8,
/* Nb Segments = */     16,
/* Nb Particules = */   6,
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

// Face List : idxPoint1, idxPoint2, idxPoint3, character 
  0, 1, 2, 'h'+128,
  0, 2, 3, 'h'+128,
  4, 5, 6, 'h'+128,
  4, 6, 7, 'h'+128,
  1, 2, 8, 'h',
  2, 8, 9, 'h',
 5, 6, 10, 'h',
 6,10, 11, 'h',
// Segment List : idxPoint1, idxPoint2, idxPoint3, character 
0, 1, 'i'+128, 0,
1, 2, 'k'+128, 0,
2, 3, 'g'+128, 0,
4, 5, 'i'+128, 0,
5, 6, 'k'+128, 0,
6, 7, 'g'+128, 0,
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
// Particule List : idxPoint1, character 
1, 'l'+128,
2, 'j'+128,
5, 'l'+128,
6, 'j'+128,
4, ' ',
7, ' ',
};

void initGl (){
    int ii;

    /*
     * Scene geometry
     */
    nbPoints     = 0;
    nbSegments   = 0;
    nbFaces      = 0;
    nbParticules = 0;

    addGeom(0, 0, 0, 1, 1, 1, 0, geomPipe);

    /* 
     * Camera position  and Orientation 
     */
    CamPosX = 12;
    CamPosY = 0;
    CamPosZ = -13;

    CamRotZ = 0;
    CamRotX = 0;

    change_char(36, 0x80, 0x40, 020, 0x10, 0x08, 0x04, 0x02, 0x01);
    for (ii = 0; ii<=LORES_SCREEN_HEIGHT; ii++){
        fbuffer[ii*LORES_SCREEN_WIDTH]=COLOR ;
        fbuffer[ii*LORES_SCREEN_WIDTH+1]=INK ;
    }
}

/*     ___                         _               
 *    /   \ _ __   __ _ __      __(_) _ __    __ _ 
 *   / /\ /| '__| / _` |\ \ /\ / /| || '_ \  / _` |
 *  / /_// | |   | (_| | \ V  V / | || | | || (_| |
 * /___,'  |_|    \__,_|  \_/\_/  |_||_| |_| \__, |
 *                                          |___/ 
 */

extern signed char points2aH[];
extern signed char points2aV[];

void glDrawParticules(){
    unsigned char ii;
    unsigned char idxPt;

    for (ii = 0; ii < nbParticules; ii++) {
        idxPt    = particulesPt[ii];
        zplot(
            (SCREEN_WIDTH -points2aH[idxPt]) >> 1,      // PX
            (SCREEN_HEIGHT - points2aV[idxPt]) >> 1,    // PY
            0, // points2dL[idxPt]-2,                   // distance
            particulesChar[ii]                          // character 2 display
        );
    }
}


/*    ___         _  _      _ 
 *   / __\ _   _ (_)| |  __| |
 *  /__\//| | | || || | / _` |
 * / \/  \| |_| || || || (_| |
 * \_____/ \__,_||_||_| \__,_|
 */                           

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





/*                          
 *   /\/\    ___  __   __  ___ 
 *  /    \  / _ \ \ \ / / / _ \
 * / /\/\ \| (_) | \ V / |  __/
 * \/    \/ \___/   \_/   \___|
 *                            
 */
void moveShape (unsigned char pos, unsigned char counter){

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

