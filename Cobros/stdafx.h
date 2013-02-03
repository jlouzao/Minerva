// stdafx.h: archivo de inclusión de los archivos de inclusión estándar del sistema,
// o archivos de inclusión específicos de un proyecto utilizados frecuentemente,
// pero rara vez modificados

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Excluir material rara vez utilizado de encabezados de Windows
#endif

// Modificar las siguientes secciones define si su objetivo es una plataforma distinta a las especificadas a continuación.
// Consulte la referencia MSDN para obtener la información más reciente sobre los valores correspondientes a diferentes plataformas.
#ifndef WINVER				// Permitir el uso de características específicas de Windows 95 y Windows NT 4 o posterior.
#define WINVER 0x0400		// Cambiar al valor apropiado correspondiente a Windows 98 y a Windows 2000 o posterior.
#endif

#ifndef _WIN32_WINNT		// Permitir el uso de características específicas de Windows NT 4 o posterior.
#define _WIN32_WINNT 0x0400	// Cambiar al valor apropiado correspondiente a Windows 2000 o posterior.
#endif						

#ifndef _WIN32_WINDOWS		// Permitir el uso de características específicas de Windows 98 o posterior.
#define _WIN32_WINDOWS 0x0410 // Cambiar para establecer el valor apropiado para Windows Me o posterior.
#endif

#ifndef _WIN32_IE			// Permitir el uso de características específicas de Internet Explorer 4.0 o posterior.
#define _WIN32_IE 0x0400	// Cambiar para establecer el valor apropiado para IE 5.0 o posterior.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// Algunos constructores CString serán explícitos

#include <afxwin.h>         // Componentes principales y estándar de MFC
#include <afxext.h>         // Extensiones de MFC
#include <afxtempl.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // Clases OLE de MFC
#include <afxodlgs.h>       // Clases de cuadros de diálogo OLE de MFC
#include <afxdisp.h>        // Clases de automatización de MFC
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// Clases de bases de datos ODBC MFC
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// Clases de bases de datos DAO MFC
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// Compatibilidad MFC para controles comunes de Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Compatibilidad MFC para Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

