// VentasMngr.cpp: archivo de implementación
//

#include "stdafx.h"
#include "VentasMngr.h"
#include "DlgGestionVentas.h"
#include "DlgAceptaOferta.h"
#include "DlgBuscaVenta.h"
#include "DlgPreparacionAlbaran.h"
#include "DlgSelecObra.h"
#include "DlgFacturacion.h"
#include "DlgFactura.h"
#include "Etiquetas.h"
#include "DlgCalendario.h"
#include "DlgEmitirInformes.h"

/***********************************************************************************************/
// CVentasMngr
/***********************************************************************************************/
IMPLEMENT_DYNAMIC(CVentasMngr, CWnd)
CVentasMngr::CVentasMngr()
{
}

/***********************************************************************************************/
CVentasMngr::~CVentasMngr()
{
}

/***********************************************************************************************/
BEGIN_MESSAGE_MAP(CVentasMngr, CWnd)
END_MESSAGE_MAP()


/***********************************************************************************************/
// Controladores de mensajes de CVentasMngr
/***********************************************************************************************/

/**************************************************************************************/
// FUNCIONES
/**************************************************************************************/
void CVentasMngr::Init(CDatabase *db, CWnd* pParent)
{
	m_db = db;
	m_pParent = pParent;
}

/**************************************************************************************/
void CVentasMngr::GestionOfertas()
{
	CDlgGestionVentas dlgGestionVentas(m_pParent);
	dlgGestionVentas.SetConexion(m_db);
	dlgGestionVentas.SetTipo(OFERTA);
	dlgGestionVentas.DoModal();
}

/**************************************************************************************/
void CVentasMngr::AceptaOferta()
{
	CDlgAceptaOferta dlgAceptaOferta(m_pParent);
	dlgAceptaOferta.SetConexion(m_db);
	dlgAceptaOferta.DoModal();
}
/**************************************************************************************/

void CVentasMngr::GestionPedidos()
{
	CDlgGestionVentas dlgGestionVentas(m_pParent);
	dlgGestionVentas.SetConexion(m_db);
	dlgGestionVentas.SetTipo(PEDIDO);
	dlgGestionVentas.DoModal();
}

/**************************************************************************************/

void CVentasMngr::GestionAlbaranes()
{
	CDlgGestionVentas dlgGestionVentas(m_pParent);
	dlgGestionVentas.SetConexion(m_db);
	dlgGestionVentas.SetTipo(ALBARAN);
	dlgGestionVentas.DoModal();
}

/**************************************************************************************/
void CVentasMngr::PreparacionAlbaranes()
{
	CDlgPreparacionAlbaran dlgPreparacionAlbaran(m_pParent);
	dlgPreparacionAlbaran.SetConexion(m_db);
	dlgPreparacionAlbaran.DoModal();
}

/**************************************************************************************/
void CVentasMngr::AltaModObra()
{
	CDlgSelecObra dlgSelecObra(m_pParent);
	dlgSelecObra.SetConexion(m_db);
	dlgSelecObra.SetTipo(ALTAMOD);
	dlgSelecObra.DoModal();
}

/**************************************************************************************/
void CVentasMngr::CierreObra()
{
	CDlgSelecObra dlgSelecObra(m_pParent);
	dlgSelecObra.SetConexion(m_db);
	dlgSelecObra.SetTipo(CIERRE);
	dlgSelecObra.DoModal();
}

/**************************************************************************************/
void CVentasMngr::ConsultaObra()
{
	CDlgSelecObra dlgSelecObra(m_pParent);
	dlgSelecObra.SetConexion(m_db);
	dlgSelecObra.SetTipo(CONSULTA);
	dlgSelecObra.DoModal();
}

/**************************************************************************************/
void CVentasMngr::Facturacion()
{
	CDlgFacturacion dlgFacturacion(m_pParent);
	dlgFacturacion.SetConexion(m_db);
	dlgFacturacion.DoModal();
}

/**************************************************************************************/
void CVentasMngr::ModificaFactura()
{
	CDlgFactura dlgFactura(m_pParent);
	dlgFactura.SetConexion(m_db);
	dlgFactura.DoModal();
}


/**************************************************************************************/
void CVentasMngr::CalendarioLaboral()
{
	CDlgCalendario dlgCalendario;
	dlgCalendario.SetConexion(m_db);
	dlgCalendario.DoModal();
}

/**************************************************************************************/
void CVentasMngr::EmitirOfertas()
{
	CDlgEmitirInformes dlgEmitirInformes;
	dlgEmitirInformes.SetConexion(m_db);
	dlgEmitirInformes.SetTipo(OFERTA);
	dlgEmitirInformes.DoModal();
}

/**************************************************************************************/
void CVentasMngr::EmitirPedidos()
{
	CDlgEmitirInformes dlgEmitirInformes;
	dlgEmitirInformes.SetConexion(m_db);
	dlgEmitirInformes.SetTipo(PEDIDO);
	dlgEmitirInformes.DoModal();
}

/**************************************************************************************/
void CVentasMngr::EmitirAlbaranes()
{
	CDlgEmitirInformes dlgEmitirInformes;
	dlgEmitirInformes.SetConexion(m_db);
	dlgEmitirInformes.SetTipo(ALBARAN);
	dlgEmitirInformes.DoModal();
}

/**************************************************************************************/
void CVentasMngr::EmitirFacturas()
{
	CDlgEmitirInformes dlgEmitirInformes;
	dlgEmitirInformes.SetConexion(m_db);
	dlgEmitirInformes.SetTipo(FACTURA);
	dlgEmitirInformes.DoModal();
}

/**************************************************************************************/
void CVentasMngr::EmitirFacturasOrigen()
{
	CDlgEmitirInformes dlgEmitirInformes;
	dlgEmitirInformes.SetConexion(m_db);
	dlgEmitirInformes.SetTipo(FACTURA_ORIGEN);
	dlgEmitirInformes.DoModal();
}