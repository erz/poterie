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

	glEnable( GL_POLYGON_SMOOTH );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );
	glLoadIdentity();
	
	//glRotatef(30.0, 1,0,0);
	//glRotatef(30.0, 0,0,1);
	
	//***************************
	// ON DESSINE ICI
	//***************************	
	
	
	//glClearColor (0.0, 0.0, 0.0, 1.0);
   

	/*
	glPushMatrix();
    glBegin(GL_LINES);
    glColor3ub(0,0,255);
    glVertex3i(0,0,0);
    glVertex3i(1,0,0);
    glColor3ub(0,255,0);
    glVertex3i(0,0,0);
    glVertex3i(0,1,0);
	glColor3ub(255,0,0);
    glVertex3i(0,0,0);
    glVertex3i(0,0,1);
    glEnd();
    glPopMatrix();
	*/
	//glClearColor (0.0, 0.0, 0.0, 1.0);
	int NumeroImage=1;
	vector<Point*> tmp=*(seq->getCourbe(NumeroImage)->getPointsControle());
	float sil[23][2];
	for(int u=0;u<19;u++)
	{
			if(u==0)
			{
				sil[0][0]=(int)(298-tmp[18-u]->x);
				sil[0][1]=(int)tmp[18-u]->y-tmp[0]->y;
				sil[1][0]=(int)(298-tmp[18-u]->x);
				sil[1][1]=(int)tmp[18-u]->y-tmp[0]->y;
				sil[2][0]=(int)(298-tmp[18-u]->x);
				sil[2][1]=(int)tmp[18-u]->y-tmp[0]->y;
				sil[3][0]=(int)(298-tmp[18-u]->x)+seq->getData(NumeroImage)->ouverture;
				sil[3][1]=(int)tmp[18-u]->y-tmp[0]->y;
			}
			sil[u+4][0]=(int)(298-tmp[18-u]->x);
			sil[u+4][1]=(int)tmp[18-u]->y-tmp[0]->y;
			
	}
	GLfloat vknots[12] = {0.0, 0.0, 0.0,0.25,0.25,0.5,0.5,0.75,0.75, 1.0,1.0, 1.0};
	float uknots[30];
	int numuknots;
	int order=3;
	int numsilpts=23;
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
	   for (i=0;i<numuknots;i++)
		     uknots[i]=i;
	
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
	glScalef (0.005, 0.005, 0.005);
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
	rotation += 0.01f;

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
