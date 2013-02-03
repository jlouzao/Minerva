// DlgInformesCobros.cpp: archivo de implementación
//
/******************************************************************************************/

#include "stdafx.h"
#include "DlgInformesCobros.h"
#include "BD.h"
#include ".\dlginformescobros.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgInformesCobros
/******************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgInformesCobros, CDialog)
CDlgInformesCobros::CDlgInformesCobros(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInformesCobros::IDD, pParent)
	, m_strElem1(_T(""))
	, m_strElem2(_T(""))
	, m_strCuenta1(_T(""))
	, m_strCuenta2(_T(""))
	, m_strCentro1(_T(""))
	, m_strCentro2(_T(""))
	, m_fecha1(0)
	, m_fecha2(0)
	, m_strEstado1(_T(""))
	, m_strEstado2(_T(""))
	, m_strDesEstado1(_T(""))
	, m_strDesEstado2(_T(""))
{
}

/******************************************************************************************/
CDlgInformesCobros::~CDlgInformesCobros()
{
}

/******************************************************************************************/
void CDlgInformesCobros::DoDataExchange(CDataExchange* pDX)
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
	DDX_Text(pDX, IDC_ESTADO1, m_strEstado1);
	DDV_MaxChars(pDX, m_strEstado1, 1);
	DDX_Text(pDX, IDC_ESTADO2, m_strEstado2);
	DDV_MaxChars(pDX, m_strEstado2, 1);
	DDX_Text(pDX, IDC_DESESTADO1, m_strDesEstado1);
	DDX_Text(pDX, IDC_DESESTADO2, m_strDesEstado2);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgInformesCobros, CDialog)
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
	ON_EN_KILLFOCUS(IDC_ESTADO1, OnEnKillfocusEstado1)
	ON_EN_KILLFOCUS(IDC_ESTADO2, OnEnKillfocusEstado2)
	ON_BN_CLICKED(IDC_BTN_ESTADO1, OnBnClickedBtnEstado1)
	ON_BN_CLICKED(IDC_BTN_ESTADO2, OnBnClickedBtnEstado2)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgInformesCobros
/******************************************************************************************/


/******************************************************************************************/
BOOL CDlgInformesCobros::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_dlgBusquedaElementos.SetConexion(m_db);
	m_dlgBusquedaClientes.SetConexion(m_db);
	m_dlgBusquedaCentros.SetConexion(m_db);
	m_dlgBusquedaEstados.SetConexion(m_db);

	m_dlgBusquedaElementos.InicializarListas();

	return TRUE;
}

/******************************************************************************************/
void CDlgInformesCobros::OnEnKillfocusElem1()
{
	CString strElemOld = m_strElem1;

	GetDlgItem(IDC_ELEM1)->GetWindowText(m_strElem1);

	if (m_strElem1 == strElemOld)
		return;

	if (!m_strElem1.IsEmpty())
	{
		if (!BuscaFactura(m_strElem1))
		{
			AfxMessageBox(IDC_FACTURA_NO_EXISTS);
			m_strElem1 = strElemOld;
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
void CDlgInformesCobros::OnBnClickedBtnElem1()
{
	INT_PTR status;

	m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::FACTURAS);

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
void CDlgInformesCobros::OnEnKillfocusElem2()
{
	CString strElemOld = m_strElem1;

	GetDlgItem(IDC_ELEM2)->GetWindowText(m_strElem2);

	if (m_strElem2 == strElemOld)
		return;

	if (!m_strElem2.IsEmpty())
	{
		if (!BuscaFactura(m_strElem2))
		{
			AfxMessageBox(IDC_FACTURA_NO_EXISTS);
			m_strElem2 = strElemOld;
		}

		GetDlgItem(IDC_ELEM2)->SetWindowText(m_strElem2);
	}
}

/******************************************************************************************/
void CDlgInformesCobros::OnBnClickedBtnElem2()
{
	INT_PTR status;

	m_dlgBusquedaElementos.SetTipo(CDialogBusqueda::FACTURAS);

	status = m_dlgBusquedaElementos.DoModal();
	if (status == IDOK)
	{
		m_strElem2 = m_dlgBusquedaElementos.GetCodigo();
		GetDlgItem(IDC_ELEM2)->SetWindowText(m_strElem2);
	}
}

/******************************************************************************************/
void CDlgInformesCobros::OnEnKillfocusCuenta1()
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
void CDlgInformesCobros::OnBnClickedBtnCuentas1()
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
void CDlgInformesCobros::OnEnKillfocusCuenta2()
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
void CDlgInformesCobros::OnBnClickedBtnCuentas2()
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
void CDlgInformesCobros::OnEnKillfocusCentro1()
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
void CDlgInformesCobros::OnBnClickedBtnCentros1()
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
void CDlgInformesCobros::OnEnKillfocusCentro2()
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
void CDlgInformesCobros::OnBnClickedBtnCentros2()
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
void CDlgInformesCobros::OnEnKillfocusEstado1()
{
	CString strEstadoOld = m_strEstado1;

	GetDlgItem(IDC_ESTADO1)->GetWindowText(m_strEstado1);

	if (!m_strEstado1.IsEmpty())
	{
		if (!BuscaEstado(m_strEstado1, m_strDesEstado1))
		{
			AfxMessageBox(IDC_ESTADO_NO_EXISTS);
			m_strEstado1 = strEstadoOld;
		}

		GetDlgItem(IDC_ESTADO1)->SetWindowText(m_strEstado1);
		GetDlgItem(IDC_DESESTADO1)->SetWindowText(m_strDesEstado1);

		if (m_strEstado2.IsEmpty())
		{
			m_strEstado2 = m_strEstado1;
			GetDlgItem(IDC_ESTADO2)->SetWindowText(m_strEstado2);
			m_strDesEstado2 = m_strDesEstado1;
			GetDlgItem(IDC_DESESTADO2)->SetWindowText(m_strDesEstado2);
		}
	}
	else
	{
		m_strEstado1.Empty();
		GetDlgItem(IDC_DESESTADO1)->SetWindowText(m_strEstado1);
	}
}

/******************************************************************************************/
void CDlgInformesCobros::OnBnClickedBtnEstado1()
{
	INT_PTR status;

	m_dlgBusquedaEstados.SetTipo(CDialogBusqueda::ESTADOS);
	status = m_dlgBusquedaEstados.DoModal();
	if (status == IDOK)
	{
		m_strEstado1 = m_dlgBusquedaEstados.GetCodigo();
		m_strDesEstado1 = m_dlgBusquedaEstados.GetDescripcion();
		GetDlgItem(IDC_ESTADO1)->SetWindowText(m_strEstado1);
		GetDlgItem(IDC_DESESTADO1)->SetWindowText(m_strDesEstado1);

		if (m_strEstado2.IsEmpty())
		{
			m_strEstado2 = m_strEstado1;
			GetDlgItem(IDC_ESTADO2)->SetWindowText(m_strEstado2);
			m_strDesEstado2 = m_strDesEstado1;
			GetDlgItem(IDC_DESESTADO2)->SetWindowText(m_strDesEstado2);
		}
	}
}

/******************************************************************************************/
void CDlgInformesCobros::OnEnKillfocusEstado2()
{
	CString strEstadoOld = m_strEstado2;

	GetDlgItem(IDC_ESTADO2)->GetWindowText(m_strEstado2);

	if (!m_strEstado2.IsEmpty())
	{
		if (!BuscaEstado(m_strEstado2, m_strDesEstado2))
		{
			AfxMessageBox(IDC_ESTADO_NO_EXISTS);
			m_strEstado2 = strEstadoOld;
		}

		GetDlgItem(IDC_ESTADO2)->SetWindowText(m_strEstado2);
		GetDlgItem(IDC_DESESTADO2)->SetWindowText(m_strDesEstado2);
	}
	else
	{
		m_strEstado2.Empty();
		GetDlgItem(IDC_DESESTADO2)->SetWindowText(m_strEstado2);
	}
}

/******************************************************************************************/
void CDlgInformesCobros::OnBnClickedBtnEstado2()
{
	INT_PTR status;

	m_dlgBusquedaEstados.SetTipo(CDialogBusqueda::ESTADOS);
	status = m_dlgBusquedaEstados.DoModal();
	if (status == IDOK)
	{
		m_strEstado2 = m_dlgBusquedaEstados.GetCodigo();
		m_strDesEstado2 = m_dlgBusquedaEstados.GetDescripcion();
		GetDlgItem(IDC_ESTADO2)->SetWindowText(m_strEstado2);
		GetDlgItem(IDC_DESESTADO2)->SetWindowText(m_strDesEstado2);
	}
}

/******************************************************************************************/
void CDlgInformesCobros::OnBnClickedOk()
{
	UpdateData();

	CDlgInformes dlgInformes;

	dlgInformes.SetDatos(m_db, COBRO);
	dlgInformes.SetFormula(m_strElem1, m_strElem2, m_fecha1, m_fecha2, m_strCuenta1, 
		m_strCuenta2, m_strCentro1,	m_strCentro2, m_strEstado1, m_strEstado2);
	dlgInformes.DoModal();
	
	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgInformesCobros::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
/*void CDlgInformesCobros::SetTipo(int iTipo)
{
	m_iTipo = iTipo;
}*/

/******************************************************************************************/
/*BOOL CDlgInformesCobros::BuscaOferta(CString strNumOferta)
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
/*BOOL CDlgInformesCobros::BuscaPedido(CString strNumPedido)
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
/*BOOL CDlgInformesCobros::BuscaAlbaran(CString strNumAlbaran)
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
*/
/******************************************************************************************/
BOOL CDlgInformesCobros::BuscaFactura(CString strNumFactura)
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
BOOL CDlgInformesCobros::BuscaCliente(CString strCuenta)
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
BOOL CDlgInformesCobros::BuscaCentro(CString strCentro)
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

/******************************************************************************************/
BOOL CDlgInformesCobros::BuscaEstado(CString strEstado, CString &strDesEstado)
{
	BOOL bExists = FALSE;

	for (int i=0; i<iNumEstados; i++)
	{
		if (strEstado == lstEstados[i])
		{
			bExists = TRUE;
			break;
		}
	}

    if (bExists)
	{
		strDesEstado = lstDesEstados[i];
	}
	return bExists;
}

