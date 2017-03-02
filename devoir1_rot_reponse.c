#include "../base.c"
char name[]="Devoir 1 - autour d'un axe !";
char message[200];
int scene=0; // 0: glRotated, 1 Rotated
double theta=90;

typedef double matrice[16];


void Rotated(double theta,double x,double y,double z){
	double a=theta/180*M_PI;
    matrice m;
    double A = sqrt(x*x+z*z);
    double AngleY = acos(1/y);
    double AngleX = acos(1/x);
// P
#define M(ligne,colonne) m[colonne*4+ligne]
     M(0,0)= cos(AngleY) ;M(0,1)= sin(AngleY)*sin(AngleX) ;                            M(0,2)=(1/2)*(sin(AngleY + AngleX) + sin(AngleY - AngleX)) ; M(0,3)= 0;
     M(1,0)= 0 ;          M(1,1)= cos(AngleX) ;                                        M(1,2)= -sin(AngleX) ;	                                    M(1,3)= 0;
     M(2,0)= -sin(AngleY);M(2,1)= (1/2)*(sin(AngleY + AngleX) + sin(AngleX - AngleY)); M(2,2)=(1/2)*(cos(AngleY + AngleX) + cos(AngleX - AngleY));  M(2,3)= 0;
     M(3,0)= 0 ;          M(3,1)= 0;                                                   M(3,2)= 0 ;                                                  M(3,3)= 1;
#undef M
    glMultMatrixd(m);
// La matrice de rotation Z
#define M(ligne,colonne) m[colonne*4+ligne]
    M(0,0)= ;M(0,1)=;M(0,2)= ; M(0,3)=;
    M(1,0)=  ;M(1,1)= ;M(1,2)=;	M(1,3)=;
    M(2,0)=   ;M(2,1)= ;M(2,2)=;	M(2,3)=;
    M(3,0)=  ;M(3,1)=      ;M(3,2)= ;M(3,3)=;
#undef M
    glMultMatrixd(m);
// Q
#define M(ligne,colonne) m[colonne*4+ligne]
    M(0,0)= cos(AngleY);                                          M(0,1)= 0;           M(0,2)= -sin(AngleY);                                        M(0,3)= 0;
    M(1,0)= sin(AngleY)*sin(AngleX);                              M(1,1)= cos(AngleX); M(1,2)=(1/2)*(sin(AngleY + AngleX) + sin(AngleX - AngleY));	M(1,3)= 0;
    M(2,0)= (1/2)*(sin(AngleY + AngleX) + sin(AngleY - AngleX));  M(2,1)= -sin(AngleX);M(2,2)=(1/2)*(cos(AngleY + AngleX) + cos(AngleX - AngleY));	M(2,3)= 0;
    M(3,0)= 0 ;                                                   M(3,1)= 0;           M(3,2)= 0 ;                                                  M(3,3)= 1;
#undef M
    glMultMatrixd(m);

}

void menuchoix(int selection){
    scene = selection;// A ecrire
}

void initialisation(){
    int mScene;
	mScene=glutCreateMenu(menuchoix);
    glutAddMenuEntry("Rotated",0);
    glutAddMenuEntry("glRotated",1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    coord = 2;
    information=1;
    division=16;
    quadrillage=1;// A ecrire
}

void clavier(unsigned char key){}
void redimension(int width, int height){}
void anime(){}


void description(){
    double direction[]={0.5,0.5,0};
    glPushMatrix();
    affiche_vecteur(ORIGINE,direction,NOIR);
    switch(scene){
        case 0:
            Rotated(theta,1/sqrt(2),1/sqrt(2),0);
            break;
        case 1:
            glRotated(theta,1/sqrt(2),1/sqrt(2),0);
            break;
    }
    glColor3dv(ORANGE);
    glutWireCube(1.0);
    glPopMatrix();
}
