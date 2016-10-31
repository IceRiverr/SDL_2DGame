
#ifndef  _WINDOW_H_
#define _WINDOW_H_
#include "Header.h"
class Window
{
public:
	Window();
	~Window();
	void Destroy();
	int Init(int w, int h, char* title);
	void HandleEvent(SDL_Event& e);

public:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Rect* m_pCamera;
	int m_nScreenW;
	int m_nScreenH;

private:
	char* m_Title;
	bool m_bMouseFocus;
	bool m_bKeyboardFocus;
};

#endif // ! _WINDOW_H_
