#include "Utility.h"
#include "Rect.h"
#include "Point.h"


unsigned short OpenMediaFile(const char * file)
{
	return 0;
}

void OpenMediaFilePlay(unsigned short mediaID)
{
}

void OpenMediaFileStop(unsigned short mediaID)
{
}

void CloseMediaFile(unsigned short mediaID)
{
}

bool PointInRect(const Rect & rect, const Point & point)
{
	return
		(point.x > rect.left &&
			point.x < rect.right &&
			point.y > rect.top &&
			point.y < rect.bottom);
}
