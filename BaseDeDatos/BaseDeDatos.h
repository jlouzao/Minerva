// BaseDeDatos.h: archivo de encabezado principal del archivo DLL de BaseDeDatos
//

#pragma once

#ifndef __AFXWIN_H__
	#error incluye 'stdafx.h' antes de incluir este archivo para PCH
#endif

#include "resource.h"		// S�mbolos principales


// CBaseDeDatosApp
// Consultar BaseDeDatos.cpp para realizar la implementaci�n de esta clase
//

class CBaseDeDatosApp : public CWinApp
{
public:
	CBaseDeDatosApp();

// Reemplazos
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
