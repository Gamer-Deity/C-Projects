// De 19/04/2022 a 27/12/2022
// Example Desmos Graph: https://www.desmos.com/calculator/jwb22dwhdt

#include "BINGUS_Engine.h"

SceneObject* sp;

WindowBuffer window_buffer;
POINT window_pos;
POINT mouse_pos;

Scene scene = { { NULL }, { 0 }, { 0 } };

HWND window;
HDC hdc;

bool mButtonIsPressed;
bool lButtonIsPressed;
bool rButtonIsPressed;

int size = 0;
int count = 0;

SceneObject* p1;
SceneObject* p2;
SceneObject* p3;
SceneObject* p4;
SceneObject* p5;
SceneObject* p6;
SceneObject* p7;
SceneObject* p8;
SceneObject* p9;
SceneObject* p10;
SceneObject* pl1;
SceneObject* pl2;
SceneObject* pl3;
SceneObject* pl4;
SceneObject* pl5;
SceneObject* pl6;
SceneObject* pl7;
SceneObject* pl8;
SceneObject* pl9;
SceneObject* pl10;
SceneObject* pl11;
SceneObject* pl12;


LRESULT CALLBACK window_callback(_In_ HWND	hwnd, _In_ UINT	uMsg, _In_ WPARAM	wParam, _In_ LPARAM lParam)
{
	srand((unsigned int)time(NULL));
	static bool paintOK;

	switch (uMsg)
	{
	case WM_CREATE:
	{
		srand(time(NULL)); 

		p1 = (SceneObject*)malloc(sizeof(SceneObject)); if (p1 == NULL) return -1; AttachObjectToFirst(p1, &scene);
		p2 = (SceneObject*)malloc(sizeof(SceneObject)); if (p2 == NULL) return -1; AttachObjectToFirst(p2, &scene);
		p3 = (SceneObject*)malloc(sizeof(SceneObject)); if (p3 == NULL) return -1; AttachObjectToFirst(p3, &scene);
		p4 = (SceneObject*)malloc(sizeof(SceneObject)); if (p4 == NULL) return -1; AttachObjectToFirst(p4, &scene);
		p5 = (SceneObject*)malloc(sizeof(SceneObject)); if (p5 == NULL) return -1; AttachObjectToFirst(p5, &scene);
		p6 = (SceneObject*)malloc(sizeof(SceneObject)); if (p6 == NULL) return -1; AttachObjectToFirst(p6, &scene);
		p7 = (SceneObject*)malloc(sizeof(SceneObject)); if (p7 == NULL) return -1; AttachObjectToFirst(p7, &scene);
		p8 = (SceneObject*)malloc(sizeof(SceneObject)); if (p8 == NULL) return -1; AttachObjectToFirst(p8, &scene);
		p9 = (SceneObject*)malloc(sizeof(SceneObject)); if (p8 == NULL) return -1; AttachObjectToFirst(p9, &scene);
		p10 = (SceneObject*)malloc(sizeof(SceneObject)); if (p8 == NULL) return -1; AttachObjectToFirst(p10, &scene);
		pl1 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl1 == NULL) return -1; AttachObjectToFirst(pl1, &scene);
		pl2 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl2 == NULL) return -1; AttachObjectToFirst(pl2, &scene);
		pl3 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl3 == NULL) return -1; AttachObjectToFirst(pl3, &scene);
		pl4 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl4 == NULL) return -1; AttachObjectToFirst(pl4, &scene);
		pl5 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl5 == NULL) return -1; AttachObjectToFirst(pl5, &scene);
		pl6 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl6 == NULL) return -1; AttachObjectToFirst(pl6, &scene);
		pl7 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl7 == NULL) return -1; AttachObjectToFirst(pl7, &scene);
		pl8 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl8 == NULL) return -1; AttachObjectToFirst(pl8, &scene);
		pl9 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl9 == NULL) return -1; AttachObjectToFirst(pl9, &scene);
		pl10 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl10 == NULL) return -1; AttachObjectToFirst(pl10, &scene);
		pl11 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl11 == NULL) return -1; AttachObjectToFirst(pl11, &scene);
		pl12 = (SceneObject*)malloc(sizeof(SceneObject)); if (pl12 == NULL) return -1; AttachObjectToFirst(pl12, &scene);

		paintOK = false;
	}
	return 0;

	case WM_PAINT:
	{
		if (!paintOK) {
			paintOK = true;
			return 0;
		}
	}
	break;

	case WM_MOUSEMOVE:
	{
		if (lButtonIsPressed)
		{
			GetCursorPos(&mouse_pos);
			ScreenToClient(hwnd, &mouse_pos);
			char c[100];
			sprintf_s(c, "BINGUS_Engine Test | ( %u , %u ) , ( %u , %u )", mouse_pos.x, mouse_pos.y, window_buffer.width, window_buffer.height);
			SetWindowText(window, c);

			p1->ObjectType = COORDINATE; // Left Vanishing Point
			p1->Object.Point.p.x = 200;
			p1->Object.Point.p.y = 500;
			p1->Color = 0xffffff;

			p2->ObjectType = COORDINATE; // Right Vanishing Point
			p2->Object.Point.p.x = 1000;
			p2->Object.Point.p.y = 500;
			p2->Color = 0xffffff;


			p3->ObjectType = COORDINATE; // Top Center Point (Front)
			p3->Object.Point.p.x = mouse_pos.x;
			p3->Object.Point.p.y = window_buffer.height - mouse_pos.y + 250;
			p3->Color = 0xff0000;

			p4->ObjectType = COORDINATE; // Bottom Center Point (Front)
			p4->Object.Point.p.x = p3->Object.Point.p.x;
			p4->Object.Point.p.y = p3->Object.Point.p.y - 500;
			p4->Color = 0xff0000;

			pl1->ObjectType = LINE; // Center Line (Front)
			pl1->Object.Line.p1.x = p3->Object.Point.p.x;
			pl1->Object.Line.p1.y = p3->Object.Point.p.y;
			pl1->Object.Line.p2.x = p4->Object.Point.p.x;
			pl1->Object.Line.p2.y = p4->Object.Point.p.y;
			pl1->Color = 0xff00ff;

			float B;
			float C;
			float X1;
			B = ((float)p3->Object.Point.p.y - (float)p2->Object.Point.p.y) / ((float)p3->Object.Point.p.x - (float)p2->Object.Point.p.x);
			C = ((float)p4->Object.Point.p.y - (float)p2->Object.Point.p.y) / ((float)p4->Object.Point.p.x - (float)p2->Object.Point.p.x);
			X1 = (200 - (float)p3->Object.Point.p.y + (float)p4->Object.Point.p.y + B * (float)p3->Object.Point.p.x - C * (float)p4->Object.Point.p.x) / (B - C);
			if (p3->Object.Point.p.x == p2->Object.Point.p.x)
			{
				float d = (p3->Object.Point.p.y - p2->Object.Point.p.y) * 2 / 5;
				p5->Object.Point.p.x = p3->Object.Point.p.x;
				p5->Object.Point.p.y = p2->Object.Point.p.y + (LONG)d;
			}
			else
			{
				p5->ObjectType = COORDINATE; // Top Right Point (Front)
				p5->Object.Point.p.x = (LONG)X1;
				p5->Object.Point.p.y = (LONG)(B * (X1 - (float)p3->Object.Point.p.x) + (float)p3->Object.Point.p.y);
				p5->Color = 0xff0000;
			}

			p6->ObjectType = COORDINATE; // Bottom Right Point (Front)
			p6->Object.Point.p.x = p5->Object.Point.p.x;
			p6->Object.Point.p.y = p5->Object.Point.p.y - 200;
			p6->Color = 0xff0000;

			pl2->ObjectType = LINE; // Right Line
			pl2->Object.Line.p1.x = p5->Object.Point.p.x;
			pl2->Object.Line.p1.y = p5->Object.Point.p.y;
			pl2->Object.Line.p2.x = p6->Object.Point.p.x;
			pl2->Object.Line.p2.y = p6->Object.Point.p.y;
			pl2->Color = 0xff0000;

			float D;
			float E;
			float X2;
			D = ((float)p3->Object.Point.p.y - (float)p1->Object.Point.p.y) / ((float)p3->Object.Point.p.x - (float)p1->Object.Point.p.x);
			E = ((float)p4->Object.Point.p.y - (float)p1->Object.Point.p.y) / ((float)p4->Object.Point.p.x - (float)p1->Object.Point.p.x);
			X2 = (200 - (float)p3->Object.Point.p.y + (float)p4->Object.Point.p.y + D * (float)p3->Object.Point.p.x - E * (float)p4->Object.Point.p.x) / (D - E);
			if (p3->Object.Point.p.x == p1->Object.Point.p.x)
			{
				float d = (p3->Object.Point.p.y - p1->Object.Point.p.y) * 2 / 5;
				p7->Object.Point.p.x = p3->Object.Point.p.x;
				p7->Object.Point.p.y = p1->Object.Point.p.y + (LONG)d;
			}
			else
			{
				p7->ObjectType = COORDINATE; // Top Left Point (Front)
				p7->Object.Point.p.x = (LONG)X2;
				p7->Object.Point.p.y = (LONG)(D * (X2 - (float)p3->Object.Point.p.x) + (float)p3->Object.Point.p.y);
				p7->Color = 0xff0000;
			}

			p8->ObjectType = COORDINATE; // Bottom Left Point (Front)
			p8->Object.Point.p.x = p7->Object.Point.p.x;
			p8->Object.Point.p.y = p7->Object.Point.p.y - 200;
			p8->Color = 0xff0000;

			pl3->ObjectType = LINE; // Left Line
			pl3->Object.Line.p1.x = p7->Object.Point.p.x;
			pl3->Object.Line.p1.y = p7->Object.Point.p.y;
			pl3->Object.Line.p2.x = p8->Object.Point.p.x;
			pl3->Object.Line.p2.y = p8->Object.Point.p.y;
			pl3->Color = 0xff0000;

			pl4->ObjectType = LINE; // Top Right Line (Front)
			pl4->Object.Line.p1.x = p3->Object.Point.p.x;
			pl4->Object.Line.p1.y = p3->Object.Point.p.y;
			pl4->Object.Line.p2.x = p5->Object.Point.p.x;
			pl4->Object.Line.p2.y = p5->Object.Point.p.y;
			pl4->Color = 0xffff00;

			pl5->ObjectType = LINE; // Bottom Right Line (Front)
			pl5->Object.Line.p1.x = p4->Object.Point.p.x;
			pl5->Object.Line.p1.y = p4->Object.Point.p.y;
			pl5->Object.Line.p2.x = p6->Object.Point.p.x;
			pl5->Object.Line.p2.y = p6->Object.Point.p.y;
			pl5->Color = 0xffff00;

			pl6->ObjectType = LINE; // Top Left Line (Front)
			pl6->Object.Line.p1.x = p3->Object.Point.p.x;
			pl6->Object.Line.p1.y = p3->Object.Point.p.y;
			pl6->Object.Line.p2.x = p7->Object.Point.p.x;
			pl6->Object.Line.p2.y = p7->Object.Point.p.y;
			pl6->Color = 0xffff00;

			pl7->ObjectType = LINE; // Bottom Left Line (Front)
			pl7->Object.Line.p1.x = p4->Object.Point.p.x;
			pl7->Object.Line.p1.y = p4->Object.Point.p.y;
			pl7->Object.Line.p2.x = p8->Object.Point.p.x;
			pl7->Object.Line.p2.y = p8->Object.Point.p.y;
			pl7->Color = 0xffff00;

			if (p3->Object.Point.p.y - p1->Object.Point.p.y <= 10 && p3->Object.Point.p.y - p1->Object.Point.p.y >= -10)
			{
				float A1 = (p1->Object.Point.p.y - (B * (X1 - p3->Object.Point.p.x) + p3->Object.Point.p.y - 200)) / (p1->Object.Point.p.x - X1);
				float A2 = (p2->Object.Point.p.y - (D * (X2 - p3->Object.Point.p.x) + p3->Object.Point.p.y - 200)) / (p2->Object.Point.p.x - X2);
				float A3 = (B * (X1 - p3->Object.Point.p.x) + p3->Object.Point.p.y - p1->Object.Point.p.y) / (X1 - p1->Object.Point.p.x);
				float A4 = (D * (X2 - p3->Object.Point.p.x) + p3->Object.Point.p.y - p2->Object.Point.p.y) / (X2 - p2->Object.Point.p.x);
				float A5 = A3 - 200 / (X1 - p1->Object.Point.p.x);
				float A6 = A4 - 200 / (X2 - p2->Object.Point.p.x);
				float X3 = (A1 * p1->Object.Point.p.x - A2 * p2->Object.Point.p.x - p1->Object.Point.p.y + p2->Object.Point.p.y) / (A1 - A2);

				p9->ObjectType = COORDINATE; // Top Center Point (Back)
				p9->Object.Point.p.x = (LONG)X3;
				p9->Object.Point.p.y = (LONG)(A4 * (X3 - p2->Object.Point.p.x) + p2->Object.Point.p.y);
				p9->Color = 0xff0000;

				p10->ObjectType = COORDINATE; // Top Center Point (Back)
				p10->Object.Point.p.x = (LONG)X3;
				p10->Object.Point.p.y = (LONG)(A6 * (X3 - p2->Object.Point.p.x) + p2->Object.Point.p.y);
				p10->Color = 0xff0000;
			}
			else
			{
				float a = ((float)p5->Object.Point.p.y - (float)p1->Object.Point.p.y) / ((float)p5->Object.Point.p.x - (float)p1->Object.Point.p.x);
				float b = (float)p1->Object.Point.p.x;
				float g = (float)p1->Object.Point.p.y;
				float d = ((float)p2->Object.Point.p.y - (float)p7->Object.Point.p.y) / ((float)p2->Object.Point.p.x - (float)p7->Object.Point.p.x);
				float e = (float)p2->Object.Point.p.x;
				float f = (float)p2->Object.Point.p.y;
				float x = (a * b - d * e - g + f) / (a - d);

				p9->ObjectType = COORDINATE; // Top Center Point (Back)
				p9->Object.Point.p.x = (LONG)x;
				p9->Object.Point.p.y = (LONG)(a * (x - b) + g);
				p9->Color = 0xff0000;

				a = ((float)p6->Object.Point.p.y - (float)p1->Object.Point.p.y) / ((float)p6->Object.Point.p.x - (float)p1->Object.Point.p.x);
				b = (float)p1->Object.Point.p.x;
				g = (float)p1->Object.Point.p.y;
				d = ((float)p2->Object.Point.p.y - (float)p8->Object.Point.p.y) / ((float)p2->Object.Point.p.x - (float)p8->Object.Point.p.x);
				e = (float)p2->Object.Point.p.x;
				f = (float)p2->Object.Point.p.y;
				//x = (a * b - d * e - g + f) / (a - d);

				p10->ObjectType = COORDINATE; // Top Center Point (Back)
				p10->Object.Point.p.x = (LONG)x;
				p10->Object.Point.p.y = (LONG)(a * (x - b) + g);
				p10->Color = 0xff0000;
			}
			
			pl8->ObjectType = LINE; // Center Line (Back)
			pl8->Object.Line.p1.x = p9->Object.Point.p.x;
			pl8->Object.Line.p1.y = p9->Object.Point.p.y;
			pl8->Object.Line.p2.x = p10->Object.Point.p.x;
			pl8->Object.Line.p2.y = p10->Object.Point.p.y;
			pl8->Color = 0x00ff00;
			
			pl9->ObjectType = LINE; // Top Right Line (Back)
			pl9->Object.Line.p1.x = p5->Object.Point.p.x;
			pl9->Object.Line.p1.y = p5->Object.Point.p.y;
			pl9->Object.Line.p2.x = p9->Object.Point.p.x;
			pl9->Object.Line.p2.y = p9->Object.Point.p.y;
			pl9->Color = 0x00ffff;
			
			pl10->ObjectType = LINE; // Bottom Right Line (Back)
			pl10->Object.Line.p1.x = p6->Object.Point.p.x;
			pl10->Object.Line.p1.y = p6->Object.Point.p.y;
			pl10->Object.Line.p2.x = p10->Object.Point.p.x;
			pl10->Object.Line.p2.y = p10->Object.Point.p.y;
			pl10->Color = 0x00ffff;
			
			pl11->ObjectType = LINE; // Top Left Line (Back)
			pl11->Object.Line.p1.x = p7->Object.Point.p.x;
			pl11->Object.Line.p1.y = p7->Object.Point.p.y;
			pl11->Object.Line.p2.x = p9->Object.Point.p.x;
			pl11->Object.Line.p2.y = p9->Object.Point.p.y;
			pl11->Color = 0x00ffff;
			
			pl12->ObjectType = LINE; // Bottom Left Line (Back)
			pl12->Object.Line.p1.x = p8->Object.Point.p.x;
			pl12->Object.Line.p1.y = p8->Object.Point.p.y;
			pl12->Object.Line.p2.x = p10->Object.Point.p.x;
			pl12->Object.Line.p2.y = p10->Object.Point.p.y;
			pl12->Color = 0x00ffff;

			RenderSceneDelayed(&scene, &window_buffer, 10);

			StretchDIBits(hdc, 0, 0, window_buffer.width, window_buffer.height, 0, 0, window_buffer.width, window_buffer.height, window_buffer.memory, &window_buffer.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
		}
	}
	return 0;

	case WM_LBUTTONDOWN:
	{
		lButtonIsPressed = true;
	}
	return 0;

	case WM_LBUTTONUP:
	{
		lButtonIsPressed = false;
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
		Destroy(&scene);
	}
	return 0;

	case WM_SIZE:
	{
		ALLOCATE_WINDOW_BUFFER;

		paintOK = FALSE;
	}
	return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	/* Create Window Class */
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Window Class";
	window_class.lpfnWndProc = window_callback;

	/* Register Class */
	RegisterClass(&window_class);

	/* Create Window */
	window = CreateWindowA(window_class.lpszClassName, "BINGUS_Engine Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	hdc = GetDC(window);

	MSG message;
		while (GetMessage(&message, NULL, 0, 0))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
}