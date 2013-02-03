// Minerva.cpp : define los comportamientos de las clases para la aplicación.
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


// Construcción de CMinervaApp

CMinervaApp::CMinervaApp()
{
	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}


// El único objeto CMinervaApp

CMinervaApp theApp;


// Inicialización de CMinervaApp

BOOL CMinervaApp::InitInstance()
{
	// Windows XP requiere InitCommonControls() si un manifiesto de 
	// aplicación especifica el uso de ComCtl32.dll versión 6 o posterior para habilitar
	// estilos visuales. De lo contrario, se generará un error al crear ventanas.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Inicialización estándar
	// Si no utiliza estas características y desea reducir el tamaño
	// del archivo ejecutable final, debe quitar de entre las siguientes rutinas
	// las rutinas de inicialización específicas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuración
	// TODO: debe modificar esta cadena para que sea adecuada,
	// como el nombre de la empresa u organización
	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));

	CMinervaDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: insertar aquí el código para controlar 
		//  cuándo se descarta el cuadro de diálogo con Aceptar
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: insertar aquí el código para controlar 
		//  cuándo se descarta el cuadro de diálogo con Cancelar
	}

	// Dado que el cuadro de diálogo se ha cerrado, devolver FALSE para salir
	//  de la aplicación en vez de iniciar el suministro de mensajes de dicha aplicación.
	return FALSE;
}
