// Utilidades.cpp: define las rutinas de inicializaci�n del archivo DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE UtilidadesDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Quitar lo siguiente si se utiliza lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Inicializando Utilidades.DLL\n");
		
		// Inicializaci�n �nica del archivo DLL de extensi�n
		if (!AfxInitExtensionModule(UtilidadesDLL, hInstance))
			return 0;

		// Insertar este archivo DLL en la cadena de recursos
		// NOTA: si un archivo DLL est�ndar de MFC, como un control ActiveX,
		//  vincula de forma impl�cita el archivo DLL de extensi�n,
		//  en vez de una aplicaci�n MFC,
		//  quite esta l�nea de DllMain y col�quela en
		//  otra funci�n que se haya exportado del archivo DLL de extensi�n. El archivo DLL est�ndar
		//  que utiliza el archivo DLL de extensi�n llama de forma expl�cita
		//  a esa funci�n para inicializar el archivo DLL de extensi�n. De lo contrario,
		//  el objeto CDynLinkLibrary no se adjunta a la cadena de recursos
		//  del archivo DLL est�ndar y se pueden producir
		//  problemas graves.

		new CDynLinkLibrary(UtilidadesDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Finalizando Utilidades.DLL\n");

		// Finalizar la biblioteca antes de llamar a los destructores
		AfxTermExtensionModule(UtilidadesDLL);
	}
	return 1;   // aceptar
}
