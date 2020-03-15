
#ifndef GLORIC_H
#define GLORIC_H


extern void glProject (char *tabpoint2D, char *tabpoint3D, unsigned char nbPoints, unsigned char options);

 // Camera Position
extern int CamPosX;
extern int CamPosY;
extern int CamPosZ;

 // Camera Orientation
extern char CamRotZ;			// -128 -> 127 unit : 2PI/(2^8 - 1)
extern char CamRotX;

// Geometry buffers ;
extern unsigned char nbPoints;
extern unsigned char nbFaces;
extern unsigned char nbSegments;
extern unsigned char nbParticules;


extern signed char points3dX[];
extern signed char points3dY[];
extern signed char points3dZ[];

extern unsigned char particulesPt[];
extern unsigned char particulesChar[];

extern unsigned char segmentsPt1[];
extern unsigned char segmentsPt2[];
extern unsigned char segmentsChar[];

extern unsigned char facesPt1[];
extern unsigned char facesPt2[];
extern unsigned char facesPt3[];
extern unsigned char facesChar[];


extern char          fbuffer[];  // frame buffer SCREEN_WIDTH * SCREEN_HEIGHT

#endif