// Minerva.cpp : define los comportamientos de las clases para la aplicaci�n.
//

#include "stdafx.h"
#include "Minerva.h"
#include "MinervaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMinervaApp

BEGIN_MESSAGE_MAP(CMinervaApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// Construcci�n de CMinervaApp

CMinervaApp::CMinervaApp()
{
	// TODO: agregar aqu� el c�digo de construcci�n,
	// Colocar toda la inicializaci�n importante en InitInstance
}


// El �nico objeto CMinervaApp

CMinervaApp theApp;


// Inicializaci�n de CMinervaApp

BOOL CMinervaApp::InitInstance()
{
	// Windows XP requiere InitCommonControls() si un manifiesto de 
	// aplicaci�n especifica el uso de ComCtl32.dll versi�n 6 o posterior para habilitar
	// estilos visuales. De lo contrario, se generar� un error al crear ventanas.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Inicializaci�n est�ndar
	// Si no utiliza estas caracter�sticas y desea reducir el tama�o
	// del archivo ejecutable final, debe quitar de entre las siguientes rutinas
	// las rutinas de inicializaci�n espec�ficas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuraci�n
	// TODO: debe modificar esta cadena para que sea adecuada,
	// como el nombre de la empresa u organizaci�n
	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));

	CMinervaDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: insertar aqu� el c�digo para controlar 
		//  cu�ndo se descarta el cuadro de di�logo con Aceptar
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: insertar aqu� el c�digo para controlar 
		//  cu�ndo se descarta el cuadro de di�logo con Cancelar
	}

	// Dado que el cuadro de di�logo se ha cerrado, devolver FALSE para salir
	//  de la aplicaci�n en vez de iniciar el suministro de mensajes de dicha aplicaci�n.
	return FALSE;
}
