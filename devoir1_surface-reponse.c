#include "../base.c"
#define  N 4 //taille des matrices et vecteurs
#define PTS 5 // Taille du maillage
char name[]="Normale surface bicubique";
char message[]="Normale surface bicubique";
typedef double matrice[N*N];
typedef double vecteur[N];

double pointTab[PTS][PTS][3]; //Reseaux de point pour le calcul des normales

// A implementer
void AfficheMaillage(int n, double *couleur); //Affiche les lignes des facettes
void NormaleMaillage(int n, double *couleur); // Affiche les normales aux facettes

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

void produitMatriceMatrice(int taille,matrice a,matrice b, matrice r){
	int l,c,k;
	#define A(ligne,colonne) a[colonne*taille+ligne]
	#define B(ligne,colonne) b[colonne*taille+ligne]
	#define R(ligne,colonne) r[colonne*taille+ligne]
	//...
	for(l=0;l<taille;l++)
		for(c=0;c<taille;c++){
			R(l,c)=0;
			for(k=0;k<taille;k++)
					R(l,c)=R(l,c)+A(l,k)*B(k,c);
		}
	#undef A
	#undef B
	#undef R
}

void produitMatriceVecteur(int taille,matrice m,vecteur v,vecteur r) {
	int l,c;
	#define M(ligne,colonne) m[colonne*taille+ligne]
  for (l=0;l<taille;l++ ) {
    r[l] = 0 ;
    for (c=0;c<taille;c++ )
      v[l] = v[l]+  M(l,c)*v[c];
	}
	#undef M
}

void produitVecteurMatrice(int taille,vecteur v,matrice m,vecteur r) {
	int l,c;
	#define M(ligne,colonne) m[colonne*taille+ligne]
  for (l=0;l<taille;l++ ) {
    r[l] = 0 ;
    for (c=0;c<taille;c++ )
      r[l] = r[l]+  M(c,l)*v[c];
	}
	#undef M
}

double produitVecteurVecteur(int taille,vecteur vl, vecteur vc){
	int i;
	double r =0;
  for (i=0;i<taille;i++ )
    r = r+ vl[i]* vc[i];
  return r;
}


void transposeMatrice(int taille,matrice m,matrice r){
	int l,c;
	#define M(ligne,colonne) m[colonne*taille+ligne]
	#define R(ligne,colonne) r[colonne*taille+ligne]
  for (l=0;l<taille;l++ )
    for (c=0;c<taille;c++ )
      R(l,c) = M(c,l);
  #undef M
	#undef R
}

void surfaceBicubique(int n,matrice M, matrice MP,matrice X,matrice Y,matrice Z,
												double *couleur){
  matrice TX,MX,TY,MY,TZ,MZ,MT ;
  int i,j;
  transposeMatrice(N,MP,MT) ; // mt <- (mp)T
  produitMatriceMatrice(N,M,X,MX) ; //mx <- m . x
  produitMatriceMatrice(N,MX,MT,TX) ;// tx <- m. x . mt
  produitMatriceMatrice(N,M,Y,MY) ;
	produitMatriceMatrice(N,MY,MT,TY);
  produitMatriceMatrice(N,M,Z,MZ) ;
  produitMatriceMatrice(N,MZ,MT,TZ) ;
  glColor3dv(couleur);
  glBegin(GL_POINTS);
  for ( i = 0 ; i < n ; i++ ) {
    double s =(double) i/(double) (n-1) ;
    vecteur S = { s*s*s,s*s,s,1.0F } ;
    for ( j = 0 ; j < n ; j++ ) {
      double t =(double) j/(double) (n-1) ;
      vecteur T = { t*t*t,t*t,t,1.0F } ;
      vecteur D ;
      produitVecteurMatrice(N,S,TX,D) ; // d <- S . tx = S m .a . (mp)T
      double x = produitVecteurVecteur(N,D,T) ;
      produitVecteurMatrice(N,S,TY,D) ;
      double y = produitVecteurVecteur(N,D,T) ;
      produitVecteurMatrice(N,S,TZ,D) ;
      double z = produitVecteurVecteur(N,D,T) ;
      glVertex3d(x,y,z);
      pointTab[i][j][0]=x;pointTab[i][j][1]=y;pointTab[i][j][2]=z;
		}
	}

	glEnd();
}



void description(){
	matrice x={-3/4.0,-3/4.0,-3/4.0,-3/4.0,
			   -1/4.0,-1/4.0,-3/4.0,-1/4.0,
				1/4.0, 1/4.0,-3/4.0, 1/4.0,
				3/4.0, 3/4.0, 3/4.0, 3/4.0};

	matrice y={-3/4.0,-1/4.0, 1/4.0, 3/4.0,
			   -1/4.0,-1/4.0, 1/4.0, 3/4.0,
				1/4.0,-1/4.0, 1/4.0, 3/4.0,
				3/4.0,-1/4.0, 1/4.0, 3/4.0};

	matrice z={-1/4.0, 3/4.0,-1/4.0,-2/4.0,
				1/4.0, 2/4.0,-1/4.0, 1/4.0,
				2/4.0,-1/4.0, 1/4.0, 3/4.0,
			   -1/4.0, 1/4.0,-1/4.0, 3/4.0};

	matrice bezier={-1.0, 3.0,-3.0, 1.0,
					 3.0,-6.0, 3.0, 0.0,
					-3.0, 3.0, 0.0, 0.0,
					 1.0, 0.0, 0.0, 0.0};

	matrice nrubs={-1.0/6, 3.0/6,-3.0/6, 1.0/6,
					3.0/6,-6.0/6,   0.0, 4.0/6,
				   -3.0/6, 3.0/6, 3.0/6, 1.0/6,
				    1.0/6,   0.0,   0.0, 0.0};


	surfaceBicubique(PTS,bezier, nrubs,x,y,z,ROUGE);
	AfficheMaillage(PTS,BLEU);
	NormaleMaillage(PTS, VERT);
}
void anime(){}
void initialisation(){}
void clavier(unsigned char key){}
void redimension(int width, int height){}


void AfficheMaillage(int n, double *couleur){
	double x, x2, y , y2, z , z2 , x3 , y3 ,z3;
	int i, j;

	for ( i = 0 ; i < n-1 ; i++ ) {
      for ( j = 0 ; j < n-1 ; j++ ) {
        double t =(double) j/(double) (n-1) ;
        x = pointTab[i][j][0];
		y = pointTab[i][j][1];
		z = pointTab[i][j][2];

		x2 = pointTab[i][j+1][0];
		y2 = pointTab[i][j+1][1];
		z2 = pointTab[i][j+1][2];

		x3 = pointTab[i+1][j][0];
		y3 = pointTab[i+1][j][1];
		z3 = pointTab[i+1][j][2];

		glColor3dv(couleur);
	    glBegin(GL_TRIANGLES);

		glVertex3d(x,y,z);
		glColor3dv(ROUGE);
		glVertex3d(x2,y2,z2);
		glColor3dv(JAUNE);
		glVertex3d(x3,y3,z3);


  		}
  	}
	glEnd();
}


void NormaleMaillage(int n, double *couleur){
	double xa, xb, ya , yb, za , zb , xc , yc ,zc;
	int i, j;
	vecteur NormalBrut, NormalNormaliser, Norme05;

	for ( i = 0 ; i < n-1 ; i++ ) {
      for ( j = 0 ; j < n-1 ; j++ ) {
        double t =(double) j/(double) (n-1) ;
        xa = pointTab[i][j][0];
		ya = pointTab[i][j][1];
		za = pointTab[i][j][2];

		xb = pointTab[i][j+1][0];
		yb = pointTab[i][j+1][1];
		zb = pointTab[i][j+1][2];

		xc = pointTab[i+1][j][0];
		yc = pointTab[i+1][j][1];
		zc = pointTab[i+1][j][2];

		vecteur AB = { xb-xa,yb-ya,zb-za,0.5F } ;
		vecteur AC = { xc-xa,yc-ya,zc-za,0.5F } ;

		ProduitVectoriel(AB,AC,NormalBrut); // afin d'obtenir un vecteur normal au deux autre
		Normaliser(NormalBrut,NormalNormaliser);
		MultiplicationScalaire(0.5,NormalNormaliser,Norme05);

		double oa[]={xa,ya,za};
		double ob[]={xb,yb,zb};
		double oc[]={xc,yc,zc};

    	double n0a[]= { xa + Norme05[0], ya + Norme05[1], za + Norme05[2]} ;
		double n0b[]= { xb + Norme05[0], yb + Norme05[1], zb + Norme05[2]} ;
		double n0c[]= { xc + Norme05[0], yc + Norme05[1], zc + Norme05[2]} ;

    	affiche_vecteur(oa,n0a,BLEU);
		affiche_vecteur(ob,n0b,ROUGE);
		affiche_vecteur(oc,n0c,JAUNE);


  		}
  	}
	glEnd();
}
