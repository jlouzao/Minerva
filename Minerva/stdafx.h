// stdafx.h: archivo de inclusión para archivos de inclusión estándar del sistema,
// o archivos de inclusión específicos del proyecto utilizados frecuentemente,
// pero cambiados rara vez

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Excluir material rara vez utilizado de encabezados de Windows
#endif

// Modificar las siguientes secciones define si su objetivo es una plataforma distinta a las especificadas a continuación.
// Consulte la referencia MSDN para obtener la información más reciente sobre los valores correspondientes a diferentes plataformas.
#ifndef WINVER				// Permitir el uso de características específicas de Windows 95 y Windows NT 4 o posterior.
#define WINVER 0x0400		// Cambiar para establecer el valor apropiado para Windows 98 y Windows 2000 o posterior.
#endif

#ifndef _WIN32_WINNT		// Permitir el uso de características específicas de Windows NT 4 o posterior.
#define _WIN32_WINNT 0x0400		// Cambiar para establecer el valor apropiado para Windows 98 y Windows 2000 o posterior.
#endif						

#ifndef _WIN32_WINDOWS		// Permitir el uso de características específicas de Windows 98 o posterior.
#define _WIN32_WINDOWS 0x0410 // Cambiar para establecer el valor apropiado para Windows Me o posterior.
#endif

#ifndef _WIN32_IE			// Permitir el uso de características específicas de Internet Explorer 4.0 o posterior.
#define _WIN32_IE 0x0400	// Cambiar para establecer el valor apropiado para IE 5.0 o posterior.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// Algunos constructores CString serán explícitos

// Desactiva la ocultación de MFC para algunos mensajes de advertencia comunes y, muchas veces, omitidos de forma consciente
#define _AFX_ALL_WARNINGS

#include <afxdb.h>			// Acceso a Base de Datos
#include <afxwin.h>         // Componentes principales y estándar de MFC
#include <afxext.h>         // Extensiones de MFC
#include <afxdisp.h>        // Clases de automatización de MFC

#include <afxdtctl.h>		// Compatibilidad MFC para controles comunes de Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Compatibilidad MFC para controles comunes de Windows
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxdhtml.h>

