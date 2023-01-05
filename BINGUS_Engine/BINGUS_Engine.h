#pragma once

#define _USE_MATH_DEFINES

#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//--------------------------------------------------------------------------------------------------------------------------------

//typedef int bool;
#define true 1
#define false 0

//--------------------------------------------------------------------------------------------------------------------------------

#define ALLOCATE_WINDOW_BUFFER																	\
	RECT rect;																					\
	GetClientRect(hwnd, &rect);																	\
	window_buffer.width = rect.right - rect.left;												\
	window_buffer.height = rect.bottom - rect.top;												\
																								\
	int buffer_size = window_buffer.width * window_buffer.height * sizeof(UINT);						\
																								\
	if (window_buffer.memory) VirtualFree(window_buffer.memory, 0, MEM_RELEASE);				\
	window_buffer.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);		\
																								\
	window_buffer.bitmap_info.bmiHeader.biSize = sizeof(window_buffer.bitmap_info.bmiHeader);	\
	window_buffer.bitmap_info.bmiHeader.biWidth = window_buffer.width;							\
	window_buffer.bitmap_info.bmiHeader.biHeight = window_buffer.height;						\
	window_buffer.bitmap_info.bmiHeader.biPlanes = 1;											\
	window_buffer.bitmap_info.bmiHeader.biBitCount = 32;	/* 4 BYTES (32 BITS) */				\
	window_buffer.bitmap_info.bmiHeader.biCompression = BI_RGB;

//void Create_Window(HWND* window, HDC* hdc, HINSTANCE hInstance, void* window_callback)
//{
//	/* Create Window Class */
//	WNDCLASS window_class = {};
//	window_class.style = CS_HREDRAW | CS_VREDRAW;
//	window_class.lpszClassName = "Window Class";
//	window_class.lpfnWndProc = (WNDPROC)window_callback;
//	
//	/* Register Class */
//	RegisterClass(&window_class);
//	
//	/* Create Window */
//	*window = CreateWindowA(window_class.lpszClassName, "BINGUS_Engine Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
//	*hdc = GetDC(*window);
//}
//--------------------------------------------------------------------------------------------------------------------------------

#define Clamp(min, val, max) ((val) < (min) ? (min) : ((val) > (max) ? (max) : (val))
#define Mod(x) ((x) >= 0 ? (x) : -(x))

//--------------------------------------------------------------------------------------------------------------------------------

typedef struct _WindowBuffer {
	UINT width, height;
	void* memory;

	BITMAPINFO bitmap_info;
} WindowBuffer;

//--------------------------------------------------------------------------------------------------------------------------------

typedef enum _ObjectType {
	COORDINATE,
	LINE,
	TRIANGLE,
	RECTANGLE,
	QUAD,
	CIRCLE
} ObjectType;


typedef struct _Point {
	POINT p;
} Point;

typedef struct _Line {
	POINT p1, p2;
} Line;

typedef struct _Tri {
	POINT p1, p2, p3;
} Tri;

typedef struct _Rect {
	POINT p1, p2;
} Rect;

typedef struct _Quad {
	POINT p1, p2, p3, p4;
} Quad;

typedef struct _Circ {
	POINT Center;
	UINT Radius;
} Circ;


typedef struct _SceneObject {
	union {
		Point Point;
		Line Line;
		Tri Tri;
		Rect Rect;
		Quad Quad;
		Circ Circ;
	} Object;
	int ObjectType;
	BOOL IsFilled;
	UINT Width;
	UINT Color;
	UINT WidthColor;
	struct _SceneObject* NextObject;
} SceneObject;

typedef struct _Scene {
	SceneObject* SceneObjects;
	SceneObject* LastUpadte;
	UINT BackgroundColor;
	UINT ObjectCount;
} Scene;


void AttachObject(SceneObject* object, Scene* scene, int position);
void AttachObjectToFirst(SceneObject* object, Scene* scene);
void AttachObjectToLast(SceneObject* object, Scene* scene);
void Destroy(Scene* scene);

void Render(SceneObject* p, WindowBuffer* window_buffer);
void RenderDelayed(SceneObject* p, WindowBuffer* window_buffer, unsigned int t);
void RenderFromLastUpdate(Scene* scene, WindowBuffer* window_buffer);
void RenderScene(Scene* scene, WindowBuffer* window_buffer);
void RenderSceneDelayed(Scene* scene, WindowBuffer* window_buffer, unsigned int t);


//--------------------------------------------------------------------------------------------------------------------------------

void ScreenToPoint(UINT x, UINT y, double* px, double* py, int zoom_x, int zoom_y, int offset_x, int offset_y, WindowBuffer* window_buffer);
void PointToScreen(double x, double y, UINT* px, UINT* py, int zoom_x, int zoom_y, int offset_x, int offset_y, WindowBuffer* window_buffer);

//--------------------------------------------------------------------------------------------------------------------------------

int DrawPixel(UINT x, UINT y, UINT color, const WindowBuffer* window_buffer);
void DrawLine(int x0, int y0, int x1, int y1, UINT color, const WindowBuffer* window_buffer);
void DrawTri(int x0, int y0, int x1, int y1, UINT x2, UINT y2, UINT color, const WindowBuffer* window_buffer); void FillRect(int x0, int y0, int x1, int y1, UINT color, const WindowBuffer* window_buffer);
void DrawRect(int x0, int y0, int x1, int y1, UINT color, const WindowBuffer* window_buffer);
void FillRect(int x0, int y0, int x1, int y1, UINT color, const WindowBuffer* window_buffer);
void FillScreen(UINT color, const WindowBuffer* window_buffer);
void DrawQuad(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, UINT color, const WindowBuffer* window_buffer);
void DrawCirc(int x0, int y0, int r, int width, UINT color, const WindowBuffer* window_buffer);
void FillCirc(int x0, int y0, int r, int width, UINT color, UINT width_color, const WindowBuffer* window_buffer);