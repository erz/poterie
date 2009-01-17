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

	//***************************
	// ON DESSINE ICI
	//***************************
	/*
	int i, j;
    for (i = 0; i < 19; i++) 
	{
        for (j = 0; j < 8; j++) 
		{
			vector<Point*> tmp=*(seq->getCourbe(1)->getPointsControle());
			if(j!=0) ctlpoints[i][j][0] = (int)tmp[i]->x*cos((2.0*PI)/j);
            ctlpoints[i][j][1] = tmp[i]->y;
            if(j!=0) ctlpoints[i][j][2] = (int)-tmp[i]->x*sin((2.0*PI)/j);
        }
    }


	theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);

	seq->getCourbe(1)->getVecteurNoeuds();
	GLfloat Uknots[18] = {0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0,14.0,14.0};
	GLfloat knots[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};
	
	glPushMatrix();
    glRotatef(330.0, 1.,0.,0.);
    glScalef (0.5, 0.5, 0.5);

	  gluBeginSurface(theNurb);
        gluNurbsSurface(theNurb, 
            18, Uknots,
            8, knots,
            19 * 3,
            3,
            &ctlpoints[0][0][0], 
            19, 7,
            GL_MAP2_VERTEX_3);
        gluEndSurface(theNurb);
	
    glPopMatrix();
	*/
	cout<<"On affiche le triangle"<<endl;
	glRotatef(rotation,0.0f,1.0f,0.0f);

        glBegin(GL_TRIANGLES);
                glColor3f(1.0f,0.0f,0.0f);
                glVertex3f(1.0f,-1.0f,0.0f);
                glColor3f(0.0f,1.0f,0.0f);
                glVertex3f(-1.0f,-1.0f,0.0f);
                glColor3f(0.0f,0.0f,1.0f);
                glVertex3f(0.0f,1.0f,0.0f);
        glEnd();

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
