// BaseDeDatos.cpp: define las rutinas de inicialización del archivo DLL.
//

#include "stdafx.h"
#include "BaseDeDatos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	Nota:
//
//		Si este archivo DLL se vincula de forma dinámica con los archivos DLL de MFC,
//		las funciones que se exporten desde el archivo DLL y
//		a las que se llame en MFC deben agregar la macro AFX_MANAGE_STATE
//		al principio de la función.
//
//		Por ejemplo:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// colocar aquí el cuerpo de la función estándar
//		}
//
//		Es de suma importancia que esta macro aparezca en todas las funciones
//		antes de que se llamen en MFC. Esto significa que debe aparecer
//		en la primera instrucción de la función, 
//		antes incluso de cualquier declaración de variables de objetos,
//		ya que sus constructores pueden generar llamadas al archivo DLL de MFC.
//		
//
//		Consulte las notas técnicas 33 y 58 de MFC para obtener
//		detalles adicionales.
//

// CBaseDeDatosApp

BEGIN_MESSAGE_MAP(CBaseDeDatosApp, CWinApp)
END_MESSAGE_MAP()


// Construcción de CBaseDeDatosApp

CBaseDeDatosApp::CBaseDeDatosApp()
{
	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}


// El único objeto CBaseDeDatosApp

CBaseDeDatosApp theApp;


// Inicialización de CBaseDeDatosApp

BOOL CBaseDeDatosApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
