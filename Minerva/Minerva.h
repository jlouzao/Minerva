// Minerva.h: archivo de encabezado principal para la aplicación PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error incluye 'stdafx.h' antes de incluir este archivo para PCH
#endif

#include "resource.h"		// Símbolos principales


// CMinervaApp:
// Consulte la sección Minerva.cpp para obtener información sobre la implementación de esta clase
//

class CMinervaApp : public CWinApp
{
public:
	CMinervaApp();

// Reemplazos
	public:
	virtual BOOL InitInstance();

// Implementación

	DECLARE_MESSAGE_MAP()
};

extern CMinervaApp theApp;
