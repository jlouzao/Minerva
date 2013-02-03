// AlmacenMngr.cpp: archivo de implementación
//

#include "stdafx.h"
#include "AlmacenMngr.h"
#include "DlgRegularizaciones.h"
#include "DlgTransferencias.h"
#include "DlgExistencias.h"

/**************************************************************************************/
// CAlmacenMngr
/**************************************************************************************/

IMPLEMENT_DYNAMIC(CAlmacenMngr, CWnd)
CAlmacenMngr::CAlmacenMngr()
{
}

/**************************************************************************************/
CAlmacenMngr::~CAlmacenMngr()
{
}


/**************************************************************************************/
BEGIN_MESSAGE_MAP(CAlmacenMngr, CWnd)
END_MESSAGE_MAP()

/**************************************************************************************/
// Controladores de mensajes de CAlmacenMngr
/**************************************************************************************/


/**************************************************************************************/
// FUNCIONES
/**************************************************************************************/
void CAlmacenMngr::Init(CDatabase *db, CWnd* pParent)
{
	m_db = db;
	m_pParent = pParent;
}

/**************************************************************************************/
void CAlmacenMngr::ExistenciasPorArticulo()
{
	CDlgExistencias dlgExistencias(m_pParent);
	dlgExistencias.SetConexion(m_db);
	dlgExistencias.DoModal();
}

/**************************************************************************************/
void CAlmacenMngr::Regularizaciones()
{
	CDlgRegularizaciones dlgRegularizaciones(m_pParent);
	dlgRegularizaciones.SetConexion(m_db);
	dlgRegularizaciones.DoModal();
}

/**************************************************************************************/
void CAlmacenMngr::Transferencias()
{
	CDlgTransferencias dlgTransferencias(m_pParent);
	dlgTransferencias.SetConexion(m_db);
	dlgTransferencias.DoModal();
}
