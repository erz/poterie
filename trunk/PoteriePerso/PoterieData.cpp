#include "stdafx.h"
#include "PoterieData.h"

CPoterieData::CPoterieData(CPoterieImage *im)
{
	//std::cout << "hop" << std::endl;
	if(im->getContour() != NULL)
	{
		std::vector<Point *> pts = *(im->getContour());
		for (int i=0; i < pts.size(); ++i)
		{
			//std::cout << "X\t" << pts[i]->x << "\tY\t" << pts[i]->y << std::flush;
		}
	}
}


void CPoterieData::RefreshListe()
{

}