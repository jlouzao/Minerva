// Minerva.h: archivo de encabezado principal para la aplicaci�n PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error incluye 'stdafx.h' antes de incluir este archivo para PCH
#endif

#include "resource.h"		// S�mbolos principales


// CMinervaApp:
// Consulte la secci�n Minerva.cpp para obtener informaci�n sobre la implementaci�n de esta clase
//

class CMinervaApp : public CWinApp
{
public:
	CMinervaApp();

// Reemplazos
	public:
	virtual BOOL InitInstance();

// Implementaci�n

	DECLARE_MESSAGE_MAP()
};

extern CMinervaApp theApp;
