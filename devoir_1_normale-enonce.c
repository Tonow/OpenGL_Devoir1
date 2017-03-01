#include "../base.c"
char name[]="Sphère normale";
char message[200];
void wireSphere(double radius,int slice,int stack);
void anime(){}

typedef double vecteur[3] ;

void MultiplicationScalaire(double alpha,vecteur v1,vecteur v){
	v[0] = v1[0] * alpha;
	v[1] = v1[1] * alpha;
	v[2] = v1[2] * alpha;
}

void ProduitVectoriel(vecteur u,vecteur v,vecteur w){
	w[0] = u[1] * v[2] - v[1] * u[2];
	w[1] = u[2] * v[0] - v[2] * u[0];
	w[2] = u[0] * v[1] - v[0] * u[1]; }

double ProduitScalaire(vecteur u,vecteur v){
	return (u[0] * v[0] + u[1] * v[1] + u[2] * v[2]);
}

double Norme(vecteur v){
	return sqrt(ProduitScalaire(v,v));
}

void Normaliser(vecteur v1,vecteur v){
	MultiplicationScalaire(1/Norme(v1),v1,v);
}


void description(){
	glColor3dv(ROUGE);
	wireSphere(0.5,10,5);
}

//Mes initialisations 
void initialisation(){ }
void clavier(unsigned char key){}
void redimension(int width, int height){}

void wireSphere(double radius, int slice,int stack){
	double theta,phi,cost,costs,sint,sints,sinp,sinps,z,zs;
	int i,j;
	double incrSlice =  2 * M_PI / (double) slice;
	double incrStack =   M_PI / (double) stack;
	phi = 0; // Angle stack
	theta = 0; //Angle slice 
	double p0[]={0,0,0};
	for(i=0;i<slice;i++){
		cost=radius*cos(theta);sint=radius*sin(theta);
		costs=radius*cos(theta+incrSlice);sints=radius*sin(theta+incrSlice);
		phi=0;
		for(j=0;j<=stack;j++){
			z = radius * cos(phi); sinp = sin(phi);
			zs = radius * cos(phi+incrStack);sinps=sin(phi+incrStack);
			// Calcule et affichage de la normale à écrire.
			glBegin(GL_LINE_LOOP);
				glVertex3d(cost*sinp,sint*sinp,z);
				glVertex3d(cost*sinps,sint*sinps,zs);
				glVertex3d(costs*sinps,sints*sinps,zs);
				glVertex3d(costs*sinp,sints*sinp,z);
			glEnd();
			phi= phi + incrStack;
		}
		theta = theta + incrSlice;
	}
}
