// BaseDeDatos.cpp: define las rutinas de inicializaci�n del archivo DLL.
//

#include "stdafx.h"
#include "BaseDeDatos.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	Nota:
//
//		Si este archivo DLL se vincula de forma din�mica con los archivos DLL de MFC,
//		las funciones que se exporten desde el archivo DLL y
//		a las que se llame en MFC deben agregar la macro AFX_MANAGE_STATE
//		al principio de la funci�n.
//
//		Por ejemplo:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// colocar aqu� el cuerpo de la funci�n est�ndar
//		}
//
//		Es de suma importancia que esta macro aparezca en todas las funciones
//		antes de que se llamen en MFC. Esto significa que debe aparecer
//		en la primera instrucci�n de la funci�n, 
//		antes incluso de cualquier declaraci�n de variables de objetos,
//		ya que sus constructores pueden generar llamadas al archivo DLL de MFC.
//		
//
//		Consulte las notas t�cnicas 33 y 58 de MFC para obtener
//		detalles adicionales.
//

// CBaseDeDatosApp

BEGIN_MESSAGE_MAP(CBaseDeDatosApp, CWinApp)
END_MESSAGE_MAP()


// Construcci�n de CBaseDeDatosApp

CBaseDeDatosApp::CBaseDeDatosApp()
{
	// TODO: agregar aqu� el c�digo de construcci�n,
	// Colocar toda la inicializaci�n importante en InitInstance
}


// El �nico objeto CBaseDeDatosApp

CBaseDeDatosApp theApp;


// Inicializaci�n de CBaseDeDatosApp

BOOL CBaseDeDatosApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
