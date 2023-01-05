#include "BINGUS_Engine.h"
#include <math.h>
//--------------------------------------------------------------------------------------------------------------------------------

void AttachObject(SceneObject* object, Scene* scene, int position)
{
	scene->ObjectCount++;

	int i;
	SceneObject* p = scene->SceneObjects;

	if (p == NULL)
	{
		scene->SceneObjects = object;
		object->NextObject = NULL;
	}
	else
	{
		if (position == 0)
		{
			object->NextObject = scene->SceneObjects;
			scene->SceneObjects = object;
		}
		else
		{
			for (i = 0; i < position; i++)
			{
				if (p->NextObject == NULL)
				{
					break;
				}
				p = p->NextObject;
			}
			object->NextObject = p->NextObject;
			p->NextObject = object;
		}
	}
	scene->LastUpadte = object;
}

void AttachObjectToLast(SceneObject* object, Scene* scene)
{
	scene->ObjectCount++;

	SceneObject* p = scene->SceneObjects;
	
	if (p == NULL) scene->SceneObjects = object;
	else
	{
		while (p->NextObject != NULL)
		{
			p = p->NextObject;
		}
		p->NextObject = object;
	}
	object->NextObject = NULL;
	scene->LastUpadte = object;
}

void AttachObjectToFirst(SceneObject* object, Scene* scene)
{
	scene->ObjectCount++;

	if (scene->SceneObjects == NULL) object->NextObject = NULL;
	else object->NextObject = scene->SceneObjects;
	scene->SceneObjects = object;
	scene->LastUpadte = object;
}

void Destroy(Scene* scene)
{
	SceneObject* p1 = scene->SceneObjects, * p2;
	while (p1 != NULL)
	{
		p2 = p1;
		p1 = p1->NextObject;
		free(p2);
	}
}


void Render(SceneObject* p, WindowBuffer* window_buffer)
{
	while (p != NULL)
	{
		switch (p->ObjectType)
		{
		case COORDINATE:
		{
			DrawPixel(p->Object.Point.p.x, p->Object.Point.p.y, p->Color, window_buffer);
		} break;
		case LINE:
		{
			UINT x0, y0, x1, y1, color;
			x0 = p->Object.Rect.p1.x;
			y0 = p->Object.Rect.p1.y;
			x1 = p->Object.Rect.p2.x;
			y1 = p->Object.Rect.p2.y;
			color = p->Color;
			DrawLine(x0, y0, x1, y1, color, window_buffer);
		} break;
		case TRIANGLE:
		{
			UINT x0, y0, x1, y1, x2, y2, color;
			x0 = p->Object.Quad.p1.x;
			y0 = p->Object.Quad.p1.y;
			x1 = p->Object.Quad.p2.x;
			y1 = p->Object.Quad.p2.y;
			x2 = p->Object.Quad.p3.x;
			y2 = p->Object.Quad.p3.y;
			color = p->Color;
			DrawTri(x0, y0, x1, y1, x2, y2, color, window_buffer);
		} break;
		case RECTANGLE:
		{
			UINT x0, y0, x1, y1, color;
			x0 = p->Object.Rect.p1.x;
			y0 = p->Object.Rect.p1.y;
			x1 = p->Object.Rect.p2.x;
			y1 = p->Object.Rect.p2.y;
			color = p->Color;
			if (p->IsFilled) FillRect(x0, y0, x1, y1, color, window_buffer);
			else DrawRect(x0, y0, x1, y1, color, window_buffer);
		} break;
		case QUAD:
		{
			UINT x0, y0, x1, y1, x2, y2, x3, y3, color;
			x0 = p->Object.Quad.p1.x;
			y0 = p->Object.Quad.p1.y;
			x1 = p->Object.Quad.p2.x;
			y1 = p->Object.Quad.p2.y;
			x2 = p->Object.Quad.p3.x;
			y2 = p->Object.Quad.p3.y;
			x3 = p->Object.Quad.p4.x;
			y3 = p->Object.Quad.p4.y;
			color = p->Color;
			DrawQuad(x0, y0, x1, y1, x2, y2, x3, y3, color, window_buffer);
		} break;
		case CIRCLE:
		{
			UINT x0, y0, r, width, color, width_color;
			x0 = p->Object.Circ.Center.x;
			y0 = p->Object.Circ.Center.y;
			r = p->Object.Circ.Radius;
			width = p->Width;
			color = p->Color;
			width_color = p->WidthColor;
			if (p->IsFilled) FillCirc(x0, y0, r, width, color, width_color, window_buffer);
			else DrawCirc(x0, y0, r, width, color, window_buffer);
		} break;
		}
		p = p->NextObject;
	}
}

void RenderDelayed(SceneObject* p, WindowBuffer* window_buffer, unsigned int t)
{
	Render(p, window_buffer);
	Sleep(t);
}

void RenderFromLastUpdate(Scene* scene, WindowBuffer* window_buffer)
{
	FillScreen(scene->BackgroundColor, window_buffer);
	SceneObject* p = scene->LastUpadte;
	Render(p, window_buffer);
}

void RenderScene(Scene* scene, WindowBuffer* window_buffer)
{
	FillScreen(scene->BackgroundColor, window_buffer);
	SceneObject* p = scene->SceneObjects;
	Render(p, window_buffer);
}

void RenderSceneDelayed(Scene* scene, WindowBuffer* window_buffer, unsigned int t)
{
	RenderScene(scene, window_buffer);
	Sleep(t);
}

//--------------------------------------------------------------------------------------------------------------------------------


void ScreenToPoint(UINT x, UINT y, double* px, double* py, int zoom_x, int zoom_y, int offset_x, int offset_y, WindowBuffer* window_buffer)
{
	*px = ((double)x / ((double)window_buffer->width) * ((double)zoom_x)) + ((double)offset_x);
	*py = ((double)y / ((double)window_buffer->height) * ((double)zoom_y)) + ((double)offset_y);
}

void PointToScreen(double x, double y, UINT* px, UINT* py, int zoom_x, int zoom_y, int offset_x, int offset_y, WindowBuffer *window_buffer)
{
	UNREFERENCED_PARAMETER(window_buffer);

}

//--------------------------------------------------------------------------------------------------------------------------------

int DrawPixel(UINT x, UINT y, UINT color, const WindowBuffer* window_buffer)
{
	UINT* pixel = (UINT*)window_buffer->memory;
	if (x < window_buffer->width && y < window_buffer->height)
	{
		pixel[x + y * window_buffer->width] = color;
		return 1;
	}
	return 0;
}

void DrawLine(int x0, int y0, int x1, int y1, UINT color, const WindowBuffer* window_buffer)
{
	UINT uCount;
	float fx0, fy0, fx1, fy1, fStepX, fStepY, dx, dy;
	fx0 = (float)x0;
	fy0 = (float)y0;
	fx1 = (float)x1;
	fy1 = (float)y1;
	dx = fx1 - fx0;
	dy = fy1 - fy0;


	if (Mod(dx) > Mod(dy))
	{
		if (dx > 0)
		{
			fStepX = 1;
			uCount = (UINT)Mod(dx);
			fStepY = dy / dx;
		}
		else
		{
			fStepX = -1;
			uCount = (UINT)Mod(dx);
			fStepY = -dy / dx;
		}
	}
	else
	{
		if (dy > 0)
		{
			fStepX = dx / dy;
			uCount = (UINT)Mod(dy);
			fStepY = 1;
		}
		else
		{
			fStepX = -dx / dy;
			uCount = (UINT)Mod(dy);
			fStepY = -1;
		}
	}

	for (UINT i = 0; i < uCount; i++)
	{
		DrawPixel(lroundf(fx0), lroundf(fy0), color, window_buffer);
		fx0 += fStepX;
		fy0 += fStepY;
	}
}

void DrawTri(int x0, int y0, int x1, int y1, UINT x2, UINT y2, UINT color, const WindowBuffer* window_buffer)
{
	DrawLine(x0, y0, x1, y1, color, window_buffer);
	DrawLine(x1, y1, x2, y2, color, window_buffer);
	DrawLine(x2, y2, x0, y0, color, window_buffer);
}

void DrawRect(int x0, int y0, int x1, int y1, UINT color, const WindowBuffer* window_buffer)
{
	DrawQuad(x0, y0, x1, y0, x1, y1, x0, y1, color, window_buffer);
}

void FillRect(int x0, int y0, int x1, int y1, UINT color, const WindowBuffer* window_buffer)
{
	for (int y = y0; y < y1; y++)
		DrawLine(x0, y, x1, y, color, window_buffer);
}

void FillScreen(UINT color, const WindowBuffer* window_buffer)
{
	for (UINT y = 0; y < window_buffer->height; y++)
		for (UINT x = 0; x < window_buffer->width; x++)
			DrawPixel(x, y, color, window_buffer);
}

void DrawQuad(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, UINT color, const WindowBuffer* window_buffer)
{
	DrawLine(x0, y0, x1, y1, color, window_buffer);
	DrawLine(x1, y1, x2, y2, color, window_buffer);
	DrawLine(x2, y2, x3, y3, color, window_buffer);
	DrawLine(x3, y3, x0, y0, color, window_buffer);
}

void DrawCirc(int x0, int y0, int r, int width, UINT color, const WindowBuffer* window_buffer)
{
	for (int i = r; r <= i + width; r++)
	{
		for (int y = -r; y <= r; y++)
		{
			for (int x = -r; x <= r; x++)
			{
				double dx = x;
				double dy = y;
				if ((int)sqrt(dx * dx + dy * dy) == r)
				{
					DrawPixel(x0 + x, y0 + y, color, window_buffer);
				}
			}
		}
	}
}

void FillCirc(int x0, int y0, int r, int width, UINT color, UINT width_color, const WindowBuffer* window_buffer)
{
	for (int i = 0; i <= r; i++)
	{
		DrawCirc(x0, y0, i, 1, color, window_buffer);
	}
	DrawCirc(x0, y0, r, width, width_color, window_buffer);
}