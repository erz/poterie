// OpenGLControl.cpp: Implementierungsdatei
//

#include "stdafx.h"
//#include "OpenGLDialog.h"
#include "OpenGLControl.h"
#include "VariablesGlobales.h"
#define PI 3.14
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLControl

COpenGLControl::COpenGLControl()
{
	dc = NULL;
	rotation = 0.0f;
	timerImage = 0;
	NumeroImage = 0;
}

COpenGLControl::~COpenGLControl()
{
	if (dc)
	{
		delete dc;
	}
}


BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	//{{AFX_MSG_MAP(COpenGLControl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COpenGLControl 


void COpenGLControl::InitGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);							
	glEnable(GL_DEPTH_TEST);					
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void COpenGLControl::DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT
		 |  GL_DEPTH_BUFFER_BIT);

	
	//glEnable( GL_POLYGON_SMOOTH );
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	//glEnable( GL_BLEND );
	//glEnable( GL_LIGHTING );
	glLoadIdentity();
	
	glRotatef(-rotation, 1,0,0);
	//glRotatef(30.0, 0,0,1);
	
	//***************************
	// ON DESSINE ICI
	//***************************	
	
	
	vector<Point*> tmp=*(seq->getCourbe(NumeroImage)->getPointsControle());
	
	float sil[22][2];

	int inf=380;
	for(int u=0;u<seq->getCourbe(0)->getPointsControle()->size();u++)
	{
		if((380-tmp[u]->x)<inf) inf=tmp[u]->x;
	}

	int recadrage=seq->getData(NumeroImage)->ouverture+(tmp[0]->x-inf);
	int maxpts=seq->getCourbe(0)->getPointsControle()->size()-1;
	
	for(int u=0;u<seq->getCourbe(0)->getPointsControle()->size();u++)
	{
		
			sil[u+3][0]=(int)(380-tmp[maxpts-u]->x)-inf+recadrage;
			sil[u+3][1]=(int)tmp[maxpts-u]->y-tmp[0]->y;
			//cout<<"X:"<<sil[u][0]<<endl;
			//cout<<"Y:"<<sil[u][1]<<endl;cout<<"*********"<<endl;				
	}

	sil[0][0]=(int)(380-tmp[maxpts]->x)-inf+recadrage;
	sil[0][1]=(int)tmp[maxpts]->y-tmp[0]->y;
	sil[1][0]=(int)(380-tmp[maxpts]->x)-inf+recadrage;
	sil[1][1]=(int)tmp[maxpts]->y-tmp[0]->y;
	sil[2][0]=(int)(380-tmp[maxpts]->x)-inf;
	sil[2][1]=(int)tmp[maxpts]->y-tmp[0]->y;

	GLfloat vknots[12] = {0.0, 0.0, 0.0,1.0,1.0,2.0,2.0,3.0,3.0,4.0,4.0,4.0};
	float uknots[30];
	int numuknots;
	int order=3;
	int numsilpts=maxpts+4;
	//Matrice permettant de générer les pts de controle (rotation)
    float B[][3]= {   { 1.0, 0.0, 1.0},{ 0.707, 0.707, 0.707}
                 ,{ 0.0, 1.0, 1.0},{-0.707, 0.707, 0.707}
				 ,{-1.0, 0.0, 1.0},{-0.707,-0.707, 0.707}
				 ,{ 0.0,-1.0, 1.0},{ 0.707,-0.707, 0.707}
				 ,{ 1.0, 0.0, 1.0}};

    GLfloat ctlpoints[9][80][4];   
	int i,j,s;
	int last_index=numsilpts-1;
	   
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

	/***************On remplit les vecteurs de noeuds*********************/
       numuknots=numsilpts+2+order;
	   uknots[0]=0;
	   uknots[1]=0;
	   uknots[2]=0;
	   for (i=3;i<numuknots-3;i++)
		     uknots[i]=i;
	   uknots[numuknots-3]=i+1;
	   uknots[numuknots-2]=i+1;
	   uknots[numuknots-1]=i+1;

	
	/*************On remplit les pts de controles*************************/
	
    for (j=0;j<=last_index;j++)
	    for (i=0;i<9;i++) 
		{
            ctlpoints[i][j][1] =sil[j][1]*B[8-i][2];
            ctlpoints[i][j][0] =sil[j][0]*B[8-i][0];
            ctlpoints[i][j][2] =sil[j][0]*B[8-i][1];
            ctlpoints[i][j][3] =B[8-i][2];
		}
	    
	 	
   for (i=0;i<9;i++)
   {
		ctlpoints[i][last_index+1][1] =ctlpoints[i][0][1];
        ctlpoints[i][last_index+1][0] =ctlpoints[i][0][0];
        ctlpoints[i][last_index+1][2] =ctlpoints[i][0][2];
        ctlpoints[i][last_index+1][3] =ctlpoints[i][0][3];
   }
   for (i=0;i<9;i++) 
   {
        ctlpoints[i][last_index+2][1] =ctlpoints[i][1][1];
        ctlpoints[i][last_index+2][0] =ctlpoints[i][1][0];
        ctlpoints[i][last_index+2][2] =ctlpoints[i][1][2];
        ctlpoints[i][last_index+2][3] =ctlpoints[i][1][3];
  }

	theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb,GLU_SAMPLING_METHOD, GLU_DOMAIN_DISTANCE);
	gluNurbsProperty(theNurb,GLU_U_STEP,10);
	gluNurbsProperty(theNurb,GLU_V_STEP,10);
	
	gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
    gluNurbsProperty(theNurb, GLU_CULLING, GLU_TRUE);
	glRotatef(180.0, 1.0,0,0);
	glScalef (0.004, 0.004, 0.004);
	
	gluNurbsSurface(theNurb, 
            12, vknots,      
            numuknots, uknots,  
            80 * 4,      
            4,           
            &ctlpoints[0][0][0],  
            3,order,                
            GL_MAP2_VERTEX_4);
		 
        gluEndSurface(theNurb);
	   
    glPopMatrix();


    glFlush();


	

	///////////////////////////
	//FIN DU DESSIN
	///////////////////////////
	SwapBuffers(dc->m_hDC);
}



void COpenGLControl::Create(CRect rect, CWnd *parent)
{

	Height=rect.Height();
	Width=rect.Width();
	CString className = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH),
		NULL);

	CreateEx(
		0,
		className,
		CString("OpenGL"),
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		rect,
		parent,
		0);

}

void COpenGLControl::OnPaint() 
{
	rotation += 1.5f;

	timerImage += 1.5f;

	if (timerImage > 360.)
	{
		NumeroImage = (NumeroImage+1)%(seq->getNbImages());
		timerImage = 0;
		rotation = 0;
	}

	if (rotation >= 360.0f)
	{
		rotation -= 360.0f;
	}

	/** OpenGL section **/

	openGLDevice.makeCurrent();
	

	DrawGLScene();
}

void COpenGLControl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (cy == 0)								
	{
		cy = 1;						
	}


	glViewport(0,0,cx,cy);	

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();						

	//gluOrtho2D(0.0, 500.0 * 200, 0.0, 500);
	glOrtho(-1.0f,1.0f,-1.0f,1.0f,1.0f,-1.0f);
	//gluPerspective(45.0f,cx/cy,0.1f,100.0f);
	
	glMatrixMode(GL_MODELVIEW);						
	glLoadIdentity();

	GLfloat ambientProperties[] = {0.8f, 0.8f, 0.08f, 1.0f};
    GLfloat positionProperties[] = {2.0f, 2.0f, -2.0f, 0.0f};
   
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    glLightfv( GL_LIGHT0, GL_POSITION, positionProperties);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambientProperties);
}


int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	dc = new CClientDC(this);
	
	openGLDevice.create(dc->m_hDC);

	InitGL();

	return 0;
}

BOOL COpenGLControl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}


