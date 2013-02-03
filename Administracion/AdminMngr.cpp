// AdminMngr.cpp: archivo de implementación
//

#include "stdafx.h"
#include "AdminMngr.h"
#include "DlgGestionUsuarios.h"

/**************************************************************************************/
// CAdministracion
/**************************************************************************************/

IMPLEMENT_DYNAMIC(CAdministracion, CWnd)
CAdministracion::CAdministracion()
{
}

/**************************************************************************************/
CAdministracion::~CAdministracion()
{
}

/**************************************************************************************/
BEGIN_MESSAGE_MAP(CAdministracion, CWnd)
END_MESSAGE_MAP()


/**************************************************************************************/
// Controladores de mensajes de CAdministracion
/**************************************************************************************/

/**************************************************************************************/
// FUNCIONES
/**************************************************************************************/
void CAdministracion::Init(CDatabase *db, CWnd* pParent)
{
	m_db = db;
	m_pParent = pParent;
}

/**************************************************************************************/
HRESULT CAdministracion::GestionUsuarios()
{
	HRESULT hErr = S_OK;

	CDlgGestionUsuarios dlgGestionUsuarios(m_pParent);
	dlgGestionUsuarios.SetConexion(m_db);
	dlgGestionUsuarios.DoModal();

	return hErr;
}

