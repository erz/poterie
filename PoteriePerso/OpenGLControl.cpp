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
	//glEnable(GL_DEPTH_TEST);					
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void COpenGLControl::DrawGLScene()
{
	glClear(GL_COLOR_BUFFER_BIT
		 |  GL_DEPTH_BUFFER_BIT);


	glLoadIdentity();
	
	glRotatef(30.0, 1,0,0);
	//glRotatef(30.0, 0,0,1);
	//glRotatef(50.0, 0,1,0);
	//***************************
	// ON DESSINE ICI
	//***************************	
	GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };
	
	//glClearColor (0.0, 0.0, 0.0, 1.0);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	//glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glDepthFunc(GL_LEQUAL);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_AUTO_NORMAL);
    //glEnable(GL_NORMALIZE);

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

	int u,v;
	 for (u = 0; u < 19; u++) 
	 {
		 //cout<<"Courbe "<<u<<endl;
        for (v = 0; v < 4; v++) 
		{
			//cout<<"Pt controle "<<v<<endl;
			vector<Point*> tmp=*(seq->getCourbe(1)->getPointsControle());
            ctlpoints[u][v][0] =(int)((298-tmp[u]->x));//*cos((2.0*PI*v)/4));
            ctlpoints[u][v][1] = (int)tmp[u]->y-tmp[0]->y;
            
			  if ( (u == 1 || u == 2) && (v == 1 || v == 2))
					ctlpoints[u][v][2] = 5.0;//(int)(-(298-tmp[u]->x)*sin((2.0*PI*v)/4));
			  else
					ctlpoints[u][v][2] = -5.0;
			cout<<"X:"<<ctlpoints[v][u][0]<<"\tY:"<<ctlpoints[v][u][1]<<"\tZ:"<<ctlpoints[v][u][2]<<endl;
        }
    } 


	theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
	
	seq->getCourbe(1)->getVecteurNoeuds();
	GLfloat Uknots[18] = {0.0, 0.0, 0.0, 1.0,2.0, 3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,13.0,13.0};
	GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
	
	glPushMatrix();
    //glRotatef(45.0, 0.0,1.0,0.0);
    glScalef (0.005, 0.005, 0.005);

	  gluBeginSurface(theNurb);
          gluNurbsSurface(theNurb, 
            8, knots,
            8, knots,
            19 * 3,
            3,
            &ctlpoints[0][0][0], 
            4, 4,
            GL_MAP2_VERTEX_3);
        gluEndSurface(theNurb);

	
    glPopMatrix();
	/*
	cout<<"On affiche le triangle"<<endl;
	glRotatef(rotation,0.0f,1.0f,0.0f);
	glScalef (0.05, 0.05, 0.05);
        glBegin(GL_TRIANGLES);
                glColor3f(1.0f,0.0f,0.0f);
                glVertex3f(1.0f,-1.0f,0.0f);
                glColor3f(0.0f,1.0f,0.0f);
                glVertex3f(-1.0f,-1.0f,0.0f);
                glColor3f(0.0f,0.0f,1.0f);
                glVertex3f(0.0f,1.0f,0.0f);
        glEnd();
*/


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
