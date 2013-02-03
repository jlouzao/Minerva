// ComprasMngr.cpp: archivo de implementación
//

#include "stdafx.h"
#include "ComprasMngr.h"
#include "DlgRecepcionPedidos.h"
#include "DlgRecepcionFactura.h"
#include "ComprasDlg.h"

/***********************************************************************************************/
// CComprasMngr
/***********************************************************************************************/
IMPLEMENT_DYNAMIC(CComprasMngr, CWnd)
CComprasMngr::CComprasMngr()
{
}

/***********************************************************************************************/
CComprasMngr::~CComprasMngr()
{
}

/***********************************************************************************************/
BEGIN_MESSAGE_MAP(CComprasMngr, CWnd)
END_MESSAGE_MAP()


/***********************************************************************************************/
// Controladores de mensajes de CComprasMngr
/***********************************************************************************************/

/**************************************************************************************/
// FUNCIONES
/**************************************************************************************/
void CComprasMngr::Init(CDatabase *db, CWnd* pParent)
{
	m_db = db;
	m_pParent = pParent;
}

/**************************************************************************************/
void CComprasMngr::GestionCompras()
{
	CComprasDlg dlgCompras(m_pParent);
	dlgCompras.SetConexion(m_db);
	dlgCompras.SetTipo(GESTCOMPRAS);
	dlgCompras.DoModal();
}
/***************************************************************************************/
void CComprasMngr::GestionAlbaranes()
{
	CComprasDlg dlgCompras(m_pParent);
	dlgCompras.SetConexion(m_db);
	dlgCompras.SetTipo(GESTALBARAN);
	dlgCompras.DoModal();
}
/***************************************************************************************/
void CComprasMngr::GestionPedidos()
{
	CDlgRecepcionPedidos dlgPedidos(m_pParent);
	dlgPedidos.SetConexion(m_db);
	dlgPedidos.DoModal();
}
/***************************************************************************************/
void CComprasMngr::GestionFacturas()
{
	CDlgRecepcionFactura dlgFactura(m_pParent);
	dlgFactura.SetConexion(m_db);
	dlgFactura.DoModal();
}