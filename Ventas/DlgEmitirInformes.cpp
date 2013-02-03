// DlgEmitirInformes.cpp: archivo de implementación
//
/******************************************************************************************/

#include "stdafx.h"
#include "Ventas.h"
#include "DlgEmitirInformes.h"
#include ".\dlgemitirinformes.h"
#include "Etiquetas.h"
#include "BD.h"

#define TITULO_OFERTA   "Emisión de ofertas"
#define TITULO_PEDIDO   "Emisión de pedidos"
#define TITULO_ALBARAN  "Emisión de albaranes"
#define TITULO_FACTURA  "Emisión de facturas"
#define TITULO_FACTURA_ORIGEN  "Emisión de facturas origen"

#define OFERTA1   "Oferta inicial:"
#define OFERTA2   "Oferta final:"
#define PEDIDO1   "Pedido inicial:"
#define PEDIDO2   "Pedido final:"
#define ALBARAN1  "Albarán inicial:"
#define ALBARAN2  "Albarán final:"
#define FACTURA1  "Factura inicial:"
#define FACTURA2  "Factura final:"

/******************************************************************************************/
// Cuadro de diálogo de CDlgEmitirInformes
/******************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgEmitirInformes, CDialog)
CDlgEmitirInformes::CDlgEmitirInformes(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEmitirInformes::IDD, pParent)
	, m_strElem1(_T(""))
	, m_strElem2(_T(""))
	, m_strCuenta1(_T(""))
	, m_strCuenta2(_T(""))
	, m_strCentro1(_T(""))
	, m_strCentro2(_T(""))
	, m_fecha1(0)
	, m_fecha2(0)
{
}

/******************************************************************************************/
CDlgEmitirInformes::~CDlgEmitirInformes()
{
}

/******************************************************************************************/
void CDlgEmitirInformes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ELEM1, m_strElem1);
	DDV_MaxChars(pDX, m_strElem1, 10);
	DDX_Text(pDX, IDC_ELEM2, m_strElem2);
	DDV_MaxChars(pDX, m_strElem2, 10);
	DDX_Text(pDX, IDC_CUENTA1, m_strCuenta1);
	DDV_MaxChars(pDX, m_strCuenta1, 9);
	DDX_Text(pDX, IDC_CUENTA2, m_strCuenta2);
	DDV_MaxChars(pDX, m_strCuenta2, 9);
	DDX_Text(pDX, IDC_CENTRO1, m_strCentro1);
	DDV_MaxChars(pDX, m_strCentro1, 3);
	DDX_Text(pDX, IDC_CENTRO2, m_strCentro2);
	DDV_MaxChars(pDX, m_strCentro2, 3);
	DDX_DateTimeCtrl(pDX, IDC_FECHA1, m_fecha1);
	DDX_DateTimeCtrl(pDX, IDC_FECHA2, m_fecha2);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgEmitirInformes, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_ELEM1, OnEnKillfocusElem1)
	ON_BN_CLICKED(IDC_BTN_ELEM1, OnBnClickedBtnElem1)
	ON_EN_KILLFOCUS(IDC_ELEM2, OnEnKillfocusElem2)
	ON_BN_CLICKED(IDC_BTN_ELEM2, OnBnClickedBtnElem2)
	ON_EN_KILLFOCUS(IDC_CUENTA1, OnEnKillfocusCuenta1)
	ON_BN_CLICKED(IDC_BTN_CUENTAS1, OnBnClickedBtnCuentas1)
	ON_EN_KILLFOCUS(IDC_CUENTA2, OnEnKillfocusCuenta2)
	ON_BN_CLICKED(IDC_BTN_CUENTAS2, OnBnClickedBtnCuentas2)
	ON_EN_KILLFOCUS(IDC_CENTRO1, OnEnKillfocusCentro1)
	ON_BN_CLICKED(IDC_BTN_CENTROS1, OnBnClickedBtnCentros1)
	ON_EN_KILLFOCUS(IDC_CENTRO2, OnEnKillfocusCentro2)
	ON_BN_CLICKED(IDC_BTN_CENTROS2, OnBnClickedBtnCentros2)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgEmitirInformes
/******************************************************************************************/


/******************************************************************************************/
BOOL CDlgEmitirInformes::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Según el tipo que sea se asigna un título al diálogo y el nombre del elemento
	switch(m_iTipo)
	{
		case OFERTA:
			SetWindowText(TITULO_OFERTA);
			GetDlgItem(IDC_STATIC_ELEM1)->SetWindowText(OFERTA1);
			GetDlgItem(IDC_STATIC_ELEM2)->SetWindowText(OFERTA2);
			break;
		case PEDIDO:
			SetWindowText(TITULO_PEDIDO);
			GetDlgItem(IDC_STATIC_ELEM1)->SetWindowText(PEDIDO1);
			GetDlgItem(IDC_STATIC_ELEM2)->SetWindowText(PEDIDO2);
			break;
		case ALBARAN:
			SetWindowText(TITULO_ALBARAN);
			GetDlgItem(IDC_STATIC_ELEM1)->SetWindowText(ALBARAN1);
			GetDlgItem(IDC_STATIC_ELEM2)->SetWindowText(ALBARAN2);
			break;
		case FACTURA:
			SetWindowText(TITULO_FACTURA);
			GetDlgItem(IDC_STATIC_ELEM1)->SetWindowText(FACTURA1);
			GetDlgItem(IDC_STATIC_ELEM2)->SetWindowText(FACTURA2);
			break;
		case FACTURA_ORIGEN:
			SetWindowText(TITULO_FACTURA_ORIGEN);
			GetDlgItem(IDC_STATIC_ELEM1)->SetWindowText(FACTURA1);
			GetDlgItem(IDC_STATIC_ELEM2)->SetWindowText(FACTURA2);
			break;
	}

	m_dlgBusquedaElementos.SetConexion(m_db);
	m_dlgBusquedaClientes.SetConexion(m_db);
	m_dlgBusquedaCentros.SetConexion(m_db);

	m_dlgBusquedaElementos.InicializarListas();

	return TRUE;
}

/******************************************************************************************/
void CDlgEmitirInformes::OnEnKillfocusElem1()
{
	CString strElemOld = m_strElem1;

	GetDlgItem(IDC_ELEM1)->GetWindowText(m_strElem1);

	if (m_strElem1 == strElemOld)
		return;

	if (!m_strElem1.IsEmpty())
	{
		switch (m_iTipo)
		{
			case OFERTA:
				if (!BuscaOferta(m_strElem1))
				{
					AfxMessageBox(IDC_OFERTA_NO_EXISTS);
					m_strElem1 = strElemOld;
				}
				break;

			case PEDIDO:
				if (!BuscaPedido(m_strElem1))
				{
					AfxMessageBox(IDC_PEDIDO_NO_EXISTS);
					m_strElem1 = strElemOld;
				}
				break;

			case ALBARAN:
				if (!BuscaAlbaran(m_strElem1))
				{
					AfxMessageBox(IDC_ALBARAN_NO_EXISTS);
					m_strElem1 = strElemOld;
				}
				break;

			case FACTURA:
				if (!BuscaFactura(m_strElem1))
				{
					AfxMessageBox(IDC_FACTURA_NO_EXISTS);
					m_strElem1 = strElemOld;
				}
				break;

			case FACTURA_ORIGEN:
				if (!BuscaFactura(m_strElem1))
				{
					AfxMessageBox(IDC_FACTURA_NO_EXISTS);
					m_strElem1 = strElemOld;
				}
				break;
		}

		GetDlgItem(IDC_ELEM1)->SetWindowText(m_strElem1);
		if (m_strElem2.IsEmpty())
		{
			m_strElem2 = m_strElem1;
			GetDlgItem(IDC_ELEM2)->SetWindowText(m_strElem2);
		}
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnBnClickedBtnElem1()
{
	INT_PTR status;

	switch(m_iTipo)
	{
		case OFERTA:
			m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::OFERTAS);
			break;
		case PEDIDO:
			m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::PEDIDOS);
			break;
		case ALBARAN:
			m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::ALBARANES);
			break;
		case FACTURA:
			m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::FACTURAS);
			break;
		case FACTURA_ORIGEN:
			m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::FACTURAS);
			break;
	}

	status = m_dlgBusquedaElementos.DoModal();
	if (status == IDOK)
	{
		m_strElem1 = m_dlgBusquedaElementos.GetCodigo();
		GetDlgItem(IDC_ELEM1)->SetWindowText(m_strElem1);
		if (m_strElem2.IsEmpty())
		{
			m_strElem2 = m_strElem1;
			GetDlgItem(IDC_ELEM2)->SetWindowText(m_strElem2);
		}
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnEnKillfocusElem2()
{
	CString strElemOld = m_strElem1;

	GetDlgItem(IDC_ELEM2)->GetWindowText(m_strElem2);

	if (m_strElem2 == strElemOld)
		return;

	if (!m_strElem2.IsEmpty())
	{
		switch (m_iTipo)
		{
			case OFERTA:
				if (!BuscaOferta(m_strElem2))
				{
					AfxMessageBox(IDC_OFERTA_NO_EXISTS);
					m_strElem2 = strElemOld;
				}
				break;

			case PEDIDO:
				if (!BuscaPedido(m_strElem2))
				{
					AfxMessageBox(IDC_PEDIDO_NO_EXISTS);
					m_strElem2 = strElemOld;
				}
				break;

			case ALBARAN:
				if (!BuscaAlbaran(m_strElem2))
				{
					AfxMessageBox(IDC_ALBARAN_NO_EXISTS);
					m_strElem2 = strElemOld;
				}
				break;

			case FACTURA:
				if (!BuscaFactura(m_strElem2))
				{
					AfxMessageBox(IDC_FACTURA_NO_EXISTS);
					m_strElem2 = strElemOld;
				}
				break;

			case FACTURA_ORIGEN:
				if (!BuscaFactura(m_strElem2))
				{
					AfxMessageBox(IDC_FACTURA_NO_EXISTS);
					m_strElem2 = strElemOld;
				}
				break;

		}

		GetDlgItem(IDC_ELEM2)->SetWindowText(m_strElem2);
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnBnClickedBtnElem2()
{
	INT_PTR status;

	switch(m_iTipo)
	{
		case OFERTA:
			m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::OFERTAS);
			break;
		case PEDIDO:
			m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::PEDIDOS);
			break;
		case ALBARAN:
			m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::ALBARANES);
			break;
		case FACTURA:
			m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::FACTURAS);
			break;
		case FACTURA_ORIGEN:
			m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::FACTURAS);
			break;
	}

	status = m_dlgBusquedaElementos.DoModal();
	if (status == IDOK)
	{
		m_strElem2 = m_dlgBusquedaElementos.GetCodigo();
		GetDlgItem(IDC_ELEM2)->SetWindowText(m_strElem2);
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnEnKillfocusCuenta1()
{
	CString strCuentaOld = m_strCuenta1;

	GetDlgItem(IDC_CUENTA1)->GetWindowText(m_strCuenta1);

	if (m_strCuenta1 == strCuentaOld)
		return;

	if (!m_strCuenta1.IsEmpty())
	{
		// Si el cliente no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCliente(m_strCuenta1))
		{
			AfxMessageBox(IDC_CLIENTE_NO_EXISTS);
			m_strCuenta1 = strCuentaOld;
		}

		GetDlgItem(IDC_CUENTA1)->SetWindowText(m_strCuenta1);
		if (m_strCuenta2.IsEmpty())
		{
			m_strCuenta2 = m_strCuenta1;
			GetDlgItem(IDC_CUENTA2)->SetWindowText(m_strCuenta2);
		}
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnBnClickedBtnCuentas1()
{
	INT_PTR status;

	m_dlgBusquedaClientes.SetTipo(CDialogBusqueda::CLIENTES);
	status = m_dlgBusquedaClientes.DoModal();
	if (status == IDOK)
	{
		m_strCuenta1 = m_dlgBusquedaClientes.GetCodigo();
		GetDlgItem(IDC_CUENTA1)->SetWindowText(m_strCuenta1);

		if (m_strCuenta2.IsEmpty())
		{
			m_strCuenta2 = m_strCuenta1;
			GetDlgItem(IDC_CUENTA2)->SetWindowText(m_strCuenta2);
		}
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnEnKillfocusCuenta2()
{
	CString strCuentaOld = m_strCuenta2;

	GetDlgItem(IDC_CUENTA2)->GetWindowText(m_strCuenta2);

	if (m_strCuenta2 == strCuentaOld)
		return;

	if (!m_strCuenta2.IsEmpty())
	{
		// Si el cliente no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCliente(m_strCuenta2))
		{
			AfxMessageBox(IDC_CLIENTE_NO_EXISTS);
			m_strCuenta2 = strCuentaOld;
		}

		GetDlgItem(IDC_CUENTA2)->SetWindowText(m_strCuenta2);
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnBnClickedBtnCuentas2()
{
	INT_PTR status;

	m_dlgBusquedaClientes.SetTipo(CDialogBusqueda::CLIENTES);
	status = m_dlgBusquedaClientes.DoModal();
	if (status == IDOK)
	{
		m_strCuenta2 = m_dlgBusquedaClientes.GetCodigo();
		GetDlgItem(IDC_CUENTA2)->SetWindowText(m_strCuenta2);
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnEnKillfocusCentro1()
{
	CString strCentroOld = m_strCentro1;

	GetDlgItem(IDC_CENTRO1)->GetWindowText(m_strCentro1);

	if (!m_strCentro1.IsEmpty())
	{
		// Si el Centro no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCentro(m_strCentro1))
		{
			AfxMessageBox(IDC_CENTRO_NO_EXISTS);
			m_strCentro1 = strCentroOld;
		}

		GetDlgItem(IDC_CENTRO1)->SetWindowText(m_strCentro1);

		if (m_strCentro2.IsEmpty())
		{
			m_strCentro2 = m_strCentro1;
			GetDlgItem(IDC_CENTRO2)->SetWindowText(m_strCentro2);
		}
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnBnClickedBtnCentros1()
{
	INT_PTR status;

	m_dlgBusquedaCentros.SetTipo(CDialogBusqueda::CENTROS);
	status = m_dlgBusquedaCentros.DoModal();
	if (status == IDOK)
	{
		m_strCentro1 = m_dlgBusquedaCentros.GetCodigo();
		GetDlgItem(IDC_CENTRO1)->SetWindowText(m_strCentro1);

		if (m_strCentro2.IsEmpty())
		{
			m_strCentro2 = m_strCentro1;
			GetDlgItem(IDC_CENTRO2)->SetWindowText(m_strCentro2);
		}
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnEnKillfocusCentro2()
{
	CString strCentroOld = m_strCentro2;

	GetDlgItem(IDC_CENTRO2)->GetWindowText(m_strCentro2);

	if (!m_strCentro2.IsEmpty())
	{
		// Si el Centro no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCentro(m_strCentro2))
		{
			AfxMessageBox(IDC_CENTRO_NO_EXISTS);
			m_strCentro2 = strCentroOld;
		}

		GetDlgItem(IDC_CENTRO2)->SetWindowText(m_strCentro2);
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnBnClickedBtnCentros2()
{
	INT_PTR status;

	m_dlgBusquedaCentros.SetTipo(CDialogBusqueda::CENTROS);
	status = m_dlgBusquedaCentros.DoModal();
	if (status == IDOK)
	{
		m_strCentro2 = m_dlgBusquedaCentros.GetCodigo();
		GetDlgItem(IDC_CENTRO2)->SetWindowText(m_strCentro2);
	}
}

/******************************************************************************************/
void CDlgEmitirInformes::OnBnClickedOk()
{
	UpdateData();

	CDlgInformes dlgInformes;

	dlgInformes.SetDatos(m_db, m_iTipo);
	dlgInformes.SetFormula(m_strElem1, m_strElem2, m_fecha1, m_fecha2, m_strCuenta1, 
		m_strCuenta2, m_strCentro1,	m_strCentro2);
	dlgInformes.DoModal();
	
	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgEmitirInformes::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgEmitirInformes::SetTipo(int iTipo)
{
	m_iTipo = iTipo;
}

/******************************************************************************************/
BOOL CDlgEmitirInformes::BuscaOferta(CString strNumOferta)
{
	BOOL bExists = FALSE;
	CProforma rsProforma(m_db);

	rsProforma.m_strFilter = "NUMPROFOR = " + strNumOferta;
	if (!rsProforma.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la oferta existe se rellenan sus campos 
	if (!rsProforma.m_NUMPROFOR.IsEmpty())
		bExists = TRUE;

	rsProforma.Close();

	return bExists;	
}

/******************************************************************************************/
BOOL CDlgEmitirInformes::BuscaPedido(CString strNumPedido)
{
	BOOL bExists = FALSE;
	CPedidos rsPedido(m_db);

	rsPedido.m_strFilter = "NUMPEDIDO = " + strNumPedido;
	if (!rsPedido.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el pedido existe se rellenan sus campos 
	if (!rsPedido.m_NUMPEDIDO.IsEmpty())
		bExists = TRUE;

	rsPedido.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgEmitirInformes::BuscaAlbaran(CString strNumAlbaran)
{
	BOOL bExists = FALSE;
	CAlbaran rsAlbaran(m_db);

	rsAlbaran.m_strFilter = "NUMALB = " + strNumAlbaran;
	if (!rsAlbaran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el albarán existe se rellenan sus campos 
	if (!rsAlbaran.m_NUMALB.IsEmpty())
		bExists = TRUE;

	rsAlbaran.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgEmitirInformes::BuscaFactura(CString strNumFactura)
{
	BOOL bExists = FALSE;
	CFacturas rsFactura(m_db);

	rsFactura.m_strFilter = "NUMFAC = " + strNumFactura;
	if (!rsFactura.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	
	if (!rsFactura.m_NUMFAC.IsEmpty())
		bExists = TRUE;

	rsFactura.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgEmitirInformes::BuscaCliente(CString strCuenta)
{
	BOOL bExists = FALSE;
	CClientes rsClientes(m_db);

	rsClientes.m_strFilter = "CUENTA LIKE '" + strCuenta + "'";
	if (!rsClientes.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el cliente existe se rellenan sus campos 
	if (!rsClientes.m_CUENTA.IsEmpty())
		bExists = TRUE;

	rsClientes.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgEmitirInformes::BuscaCentro(CString strCentro)
{
	BOOL bExists = FALSE;
	CCentros rsCentros(m_db);

	rsCentros.m_strFilter = "CCENTRO LIKE '" + strCentro + "'";
	if (!rsCentros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el centro existe se rellena la descripción 
	if (!rsCentros.m_CCENTRO.IsEmpty())
		bExists = TRUE;

	rsCentros.Close();

	return bExists;
}


