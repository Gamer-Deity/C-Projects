// De 23/10/2021 a 29/12/2021

#define _USE_MATH_DEFINES

#include <Windows.h>
#include <stdio.h>
#include <math.h>

#define START_OFFSET_X -2.3f
#define START_OFFSET_Y -1

#define START_ZOOM_X 1
#define START_ZOOM_Y 1

#define START_MAX_ITER 7

#define M_LIMIT_MODULUS 2
#define J_LIMIT_MODULUS 100

enum FRACTALS {
	MANDELBROT,
	JULIA
} fractals;

struct Offset {
	double x = START_OFFSET_X, y = START_OFFSET_Y;
};

struct Zoom {
	double x = START_ZOOM_X, y = START_ZOOM_Y;
};

struct Start {
	double x = 0.0f, y = 0.0f;
};
struct End {
	double x = 0.0f, y = 0.0f;
};
struct Pan {
	Start start;
	End end;
};

struct Window_Buffer {
	UINT width, height;
	void* memory;

	BITMAPINFO bitmap_info;
};

Offset offset;

Zoom zoom;

Pan pan;

Window_Buffer window_buffer;

POINT window_pos;
POINT mouse_pos;

HWND window;
HDC hdc;

int max_iter = START_MAX_ITER;
FRACTALS fractal = MANDELBROT;
double cx, cy;
bool mButtonIsPressed = false, switch_julia = false;


void TotalReset()
{
	offset.x = START_OFFSET_X;
	offset.y = START_OFFSET_Y;
	zoom.x = START_ZOOM_X;
	zoom.y = START_ZOOM_Y;
	max_iter = START_MAX_ITER;
}

void Reset()
{
	offset.x = START_OFFSET_X;
	offset.y = START_OFFSET_Y;
	zoom.x = START_ZOOM_X;
	zoom.y = START_ZOOM_Y;
}

void ScreenToPoint(UINT x, UINT y, double* px, double* py)
{
	*px = ((double)x / ((window_buffer.width / 4) * zoom.x)) + (offset.x);
	*py = ((double)y / ((window_buffer.height / 2) * zoom.y)) + (offset.y);
}

UINT GetRedRGB(int x)
{
	return (255 / max_iter) * x * 0x010000L;
}

UINT GetGreenRGB(int x)
{
	return (UINT)((sin(((2 * M_PI) / max_iter) * (double)x - M_PI / 2) + 1) * 255 / 2 * 0x000100L);
}

UINT GetBlueRGB(int x)
{
	return 255 - 255 / max_iter * x;
}

void GetJuliaValue(UINT x00, UINT y00, double c_x, double c_y, UINT* pixel)
{
	double x0, y0, x, y, xTemp;
	int iter;

	ScreenToPoint(x00, y00, &x0, &y0);

	iter = 0, x = x0, y = y0;
	while (x * x + y * y < (double)(J_LIMIT_MODULUS * J_LIMIT_MODULUS) && iter < max_iter)
	{
		xTemp = x * x - y * y + c_x;
		y = 2 * x * y + c_y;
		x = xTemp;
		iter++;
	}

	if (iter < max_iter)
	{
		*pixel = GetRedRGB(iter) + GetGreenRGB(iter) + GetBlueRGB(iter);
	}
	else *pixel = 0;
}

void GetMandelbrotValue(UINT x00, UINT y00, UINT* pixel)
{
	double x0, y0, x, y, xTemp;
	int iter;

	ScreenToPoint(x00, y00, &x0, &y0);

	iter = 0, x = 0, y = 0;
	while (x * x + y * y < (double)(M_LIMIT_MODULUS * M_LIMIT_MODULUS) && iter < max_iter)
	{
		xTemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xTemp;
		iter++;
	}

	if (iter < max_iter)
	{
		*pixel = GetRedRGB(iter) + GetGreenRGB(iter) + GetBlueRGB(iter);
	}
	else *pixel = 0;
}

void DrawWindowsons(void)
{
	UINT* pixel = (UINT*)window_buffer.memory;
	//for (UINT y = 0; y < window_buffer.height; y++)
	for (UINT y = window_buffer.height; y > 0; y--)
	{
		for (UINT x = 0; x < window_buffer.width; x++)
		{
			switch (fractal)
			{
				case MANDELBROT:
				{
					GetMandelbrotValue(x, y, pixel);
					break;
				}
				case JULIA:
				{
					GetJuliaValue(x, y, cx, cy, pixel);
					break;
				}
			}
			pixel++;
		}
	}

	// Render
	StretchDIBits(hdc, 0, 0, window_buffer.width, window_buffer.height, 0, 0, window_buffer.width, window_buffer.height, window_buffer.memory, &window_buffer.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
}

void ChangeWindowText(HWND hwnd)
{
	char c[130];
	sprintf_s(c, sizeof(c), "(%d, %d) | (%d, %d) | (%.1lf, %.1lf) | Mandelbrot_Set | Max_Iterations: %u | Zoom: X:x%.3lf Y:x%.3lf", window_pos.x, window_pos.y, mouse_pos.x, mouse_pos.y, pan.end.x, -pan.end.y, max_iter, zoom.x, zoom.y);
	SetWindowText(hwnd, c);
}

LRESULT CALLBACK window_callback(_In_ HWND	hwnd, _In_ UINT	uMsg, _In_ WPARAM	wParam, _In_ LPARAM lParam)
{
	LRESULT result = 0;
	static bool paintOK;

	switch (uMsg)
	{
		case WM_CREATE:
		{
			paintOK = false;
		}
		return 0;

		case WM_PAINT:
		{
			if (!paintOK) {
				DrawWindowsons();
				paintOK = true;
			}
		}
		return 0;

		case WM_KEYUP:
		{
			if (wParam == 'J') switch_julia = false;
		}
		return 0;

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_CONTROL:
				{
					if (GetKeyState('R') & 0x8000)
					{
						TotalReset();
						ChangeWindowText(hwnd);
						DrawWindowsons();
					}
				}
				break;
				case 'R':
				{
					if (GetKeyState(VK_CONTROL) & 0x8000) TotalReset();
					else Reset();
					ChangeWindowText(hwnd);
					DrawWindowsons();
				}
				break;
				case 'J':
				{
					ScreenToPoint(mouse_pos.x, mouse_pos.y, &cx, &cy);
					switch_julia = true;
					fractal = JULIA;
					DrawWindowsons();
				}
				break;
				case 'M':
				{
					fractal = MANDELBROT;
					DrawWindowsons();
				}
				break;
			}
		}
		return 0;

		case WM_MOUSEMOVE:
		{
			GetCursorPos(&mouse_pos);
			ScreenToClient(hwnd, &mouse_pos);

			ScreenToPoint(mouse_pos.x, mouse_pos.y, &pan.end.x, &pan.end.y);
			if (mButtonIsPressed)
			{
				offset.x -= (pan.end.x - pan.start.x);
				offset.y -= (pan.end.y - pan.start.y);
				ScreenToPoint(mouse_pos.x, mouse_pos.y, &pan.start.x, &pan.start.y);

				DrawWindowsons();
			}

			ChangeWindowText(hwnd);
		}
		return 0;

		case WM_MBUTTONDOWN:
		{
			GetCursorPos(&mouse_pos);
			ScreenToClient(hwnd, &mouse_pos);

			mButtonIsPressed = true;

			ScreenToPoint(mouse_pos.x, mouse_pos.y, &pan.start.x, &pan.start.y);
		}
		return 0;

		case WM_MBUTTONUP:
		{
			mButtonIsPressed = false;
		}
		return 0;

		case WM_MOUSEWHEEL:
		{
			int val = 0;
			switch ((short)LOWORD(wParam))
			{
				case MK_SHIFT:
				{
					val = 1;
				}
				break;

				case MK_CONTROL:
				{
					val = 10;
				}
				break;

				case MK_SHIFT | MK_CONTROL:
				{
					val = 100;
				}
				break;

				case MK_SHIFT | MK_CONTROL | MK_MBUTTON:
				{
					val = 1000;
				}
				break;

				default:
				{
					double MouseWorldX_BeforeZoom, MouseWorldY_BeforeZoom;
					ScreenToPoint(mouse_pos.x, mouse_pos.y, &MouseWorldX_BeforeZoom, &MouseWorldY_BeforeZoom);

					if ((short)HIWORD(wParam) > 0)
					{
						zoom.x *= 1.1f;
						zoom.y *= 1.1f;
					}
					else
					{
						zoom.x /= 1.1f;
						zoom.y /= 1.1f;
					}
					double MouseWorldX_AfterZoom, MouseWorldY_AfterZoom;
					ScreenToPoint(mouse_pos.x, mouse_pos.y, &MouseWorldX_AfterZoom, &MouseWorldY_AfterZoom);

					offset.x += (MouseWorldX_BeforeZoom - MouseWorldX_AfterZoom);
					offset.y += (MouseWorldY_BeforeZoom - MouseWorldY_AfterZoom);
				}
				break;
			}

			if (val > 0)
			{
				if ((short)HIWORD(wParam) > 0)
				{
					max_iter += val;
				}
				else
				{
					if (max_iter - val >= 0)
					{
						max_iter -= val;
					}
					else
					{
						max_iter = 0;
					}
				}
			}
			ChangeWindowText(hwnd);
			DrawWindowsons();
		}
		return 0;

		case WM_MOVE:
		{
			window_pos.x = (short)(lParam);
			window_pos.y = (short)(lParam >> 16);
			ChangeWindowText(hwnd);
		}
		return 0;

		case WM_CLOSE:
		{
			DestroyWindow(hwnd);
		}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		return 0;

		case WM_SIZE:
		{
			RECT rect;
			GetClientRect(hwnd, &rect);
			window_buffer.width = rect.right - rect.left;
			window_buffer.height = rect.bottom - rect.top;

			int size = window_buffer.width * window_buffer.height * sizeof(UINT);

			if (window_buffer.memory) VirtualFree(window_buffer.memory, 0, MEM_RELEASE);
			window_buffer.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			window_buffer.bitmap_info.bmiHeader.biSize = sizeof(window_buffer.bitmap_info.bmiHeader);
			window_buffer.bitmap_info.bmiHeader.biWidth = window_buffer.width;
			window_buffer.bitmap_info.bmiHeader.biHeight = window_buffer.height;
			window_buffer.bitmap_info.bmiHeader.biPlanes = 1;
			window_buffer.bitmap_info.bmiHeader.biBitCount = 32;	// 4 BYTES (32 BITS)
			window_buffer.bitmap_info.bmiHeader.biCompression = BI_RGB;

			paintOK = FALSE;
		}
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Create Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = window_callback;

	// Register Class
	RegisterClass(&window_class);

	// Create Window
	window = CreateWindowA(window_class.lpszClassName, "(0, 0) | Mandelbrot_Set", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	hdc = GetDC(window);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}