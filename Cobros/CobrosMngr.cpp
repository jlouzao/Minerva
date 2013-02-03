// CobrosMngr.cpp: archivo de implementación
//

#include "stdafx.h"
#include "CobrosMngr.h"
#include "DlgGestionCobros.h"
#include "DlgIntroCobros.h"
#include "DlgInformesCobros.h"

/***********************************************************************************************/
// CVentasMngr
/***********************************************************************************************/
IMPLEMENT_DYNAMIC(CCobrosMngr, CWnd)
CCobrosMngr::CCobrosMngr()
{
}

/***********************************************************************************************/
CCobrosMngr::~CCobrosMngr()
{
}

/***********************************************************************************************/
BEGIN_MESSAGE_MAP(CCobrosMngr, CWnd)
END_MESSAGE_MAP()


/***********************************************************************************************/
// Controladores de mensajes de CCobrosMngr
/***********************************************************************************************/

/**************************************************************************************/
// FUNCIONES
/**************************************************************************************/
void CCobrosMngr::Init(CDatabase *db, CWnd* pParent)
{
	m_db = db;
	m_pParent = pParent;
}

/**************************************************************************************/
void CCobrosMngr::NuevoCobro()
{
	CDlgGestionCobros dlgGestionCobros(m_pParent);
	dlgGestionCobros.SetConexion(m_db);
	dlgGestionCobros.SetTipo(NUEVO);
	dlgGestionCobros.DoModal();
}


/**************************************************************************************/
void CCobrosMngr::ModificacionCobro()
{
	CDlgGestionCobros dlgGestionCobros(m_pParent);
	dlgGestionCobros.SetConexion(m_db);
	dlgGestionCobros.SetTipo(MODIFICACION);
	dlgGestionCobros.DoModal();
}

/**************************************************************************************/
void CCobrosMngr::IntroCobros()
{
	CDlgIntroCobros dlgIntroCobros(m_pParent);
	dlgIntroCobros.SetConexion(m_db);
	dlgIntroCobros.DoModal();
}

/**************************************************************************************/
void CCobrosMngr::RecepAceptos()
{
}

/**************************************************************************************/
void CCobrosMngr::InformeCobros()
{
	CDlgInformesCobros dlgInformesCobros;
	dlgInformesCobros.SetConexion(m_db);
	dlgInformesCobros.DoModal();
}
