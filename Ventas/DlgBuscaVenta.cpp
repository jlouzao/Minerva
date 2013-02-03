// DlgBuscaVenta.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgBuscaVenta.h"
#include ".\DlgBuscaVenta.h"
#include "BD.h"
#include "Etiquetas.h"


/******************************************************************************************/
// Cuadro de diálogo de CDlgBuscaVenta
/******************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgBuscaVenta, CDialog)
CDlgBuscaVenta::CDlgBuscaVenta(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBuscaVenta::IDD, pParent)
	, m_strNumVenta(_T(""))
	, m_strCuenta(_T(""))
	, m_strDesCuenta(_T(""))
{
}

/******************************************************************************************/
CDlgBuscaVenta::~CDlgBuscaVenta()
{
}

/******************************************************************************************/
void CDlgBuscaVenta::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMVENTA, m_strNumVenta);
	DDV_MaxChars(pDX, m_strNumVenta, 10);
	DDX_Text(pDX, IDC_CUENTA, m_strCuenta);
	//DDX_Control(pDX, IDC_NUMOFERTA, m_cNumOferta);
	DDX_Text(pDX, IDC_DESCUENTA, m_strDesCuenta);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgBuscaVenta, CDialog)
	ON_EN_KILLFOCUS(IDC_NUMVENTA, OnEnKillfocusNumVenta)
	ON_BN_CLICKED(IDC_BTN_VENTA, OnBnClickedBtnVenta)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgBuscaVenta
/******************************************************************************************/
BOOL CDlgBuscaVenta::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se establece la Base de Datos para el diálogo de búsqueda
	//m_dlgBusqueda.SetConexion(m_db);

	if (m_iTipo == OFERTA)
		GetDlgItem(IDC_STATIC_NUMERO)->SetWindowText("Nº de Oferta: ");
	else if (m_iTipo == PEDIDO)
		GetDlgItem(IDC_STATIC_NUMERO)->SetWindowText("Nº de Pedido: ");
	else if (m_iTipo == ALBARAN)
		GetDlgItem(IDC_STATIC_NUMERO)->SetWindowText("Nº de Albarán: ");

	GetDlgItem(IDC_NUMVENTA)->SetFocus();

	return FALSE;
}

/******************************************************************************************/
void CDlgBuscaVenta::OnEnKillfocusNumVenta()
{
	CString strNumVentaOld = m_strNumVenta;

	GetDlgItem(IDC_NUMVENTA)->GetWindowText(m_strNumVenta);
	m_strNumVenta = m_strNumVenta.Trim();

	if (!m_strNumVenta.IsEmpty())
	{
		if (m_iTipo == OFERTA)
		{
				// Si la oferta no existe se deja la anterior y se da un mensaje de error
			if (!BuscaNumOferta())
			{
				AfxMessageBox(IDC_OFERTA_NO_EXISTS);
				m_strNumVenta = strNumVentaOld;
				GetDlgItem(IDC_NUMVENTA)->SetFocus();
			}
		}
		if (m_iTipo == PEDIDO)
		{
			// Si el pedido no existe se deja el anterior y se da un mensaje de error
			if (!BuscaNumPedido())
			{
				AfxMessageBox(IDC_PEDIDO_NO_EXISTS);
				m_strNumVenta = strNumVentaOld;
				GetDlgItem(IDC_NUMVENTA)->SetFocus();
			}
		}
		if (m_iTipo == ALBARAN)
		{
			// Si el albarán no existe se deja el anterior y se da un mensaje de error
			if (!BuscaNumAlbaran())
			{
				AfxMessageBox(IDC_ALBARAN_NO_EXISTS);
				m_strNumVenta = strNumVentaOld;
				GetDlgItem(IDC_NUMVENTA)->SetFocus();
			}
		}
	}
	else
		m_strCuenta.Empty();

	UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgBuscaVenta::OnBnClickedBtnVenta()
{
	INT_PTR status;

	if (m_iTipo == OFERTA)
		m_dlgBusqueda->SetTipo(CDialogBusqueda::OFERTAS);
	else if (m_iTipo == PEDIDO)
		m_dlgBusqueda->SetTipo(CDialogBusqueda::PEDIDOS);
	else if (m_iTipo == ALBARAN)
		m_dlgBusqueda->SetTipo(CDialogBusqueda::ALBARANES);

	status = m_dlgBusqueda->DoModal();
	if (status == IDOK)
	{
		m_strNumVenta = m_dlgBusqueda->GetCodigo();
		m_strCuenta = m_dlgBusqueda->GetDescripcion();
		BuscaDesCuenta();
	}

	UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgBuscaVenta::OnBnClickedOk()
{
	// Se comprueba que haya una venta seleccionada
	GetDlgItem(IDC_NUMVENTA)->GetWindowText(m_strNumVenta);
	if (m_strNumVenta.IsEmpty())
	{
		if (m_iTipo == OFERTA)
			AfxMessageBox(IDC_NO_OFERTA);
		else if (m_iTipo == PEDIDO)
			AfxMessageBox(IDC_NO_PEDIDO);
		else if (m_iTipo == ALBARAN)
			AfxMessageBox(IDC_NO_ALBARAN);
		return;
	}
	OnOK();
}


/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgBuscaVenta::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgBuscaVenta::SetTipo(int iTipo)
{
	m_iTipo = iTipo;
}

/******************************************************************************************/
void CDlgBuscaVenta::SetLista(CDialogBusqueda *dlgBusqueda)
{
	m_dlgBusqueda = dlgBusqueda;
}

/******************************************************************************************/
CString CDlgBuscaVenta::GetNumVenta()
{
	return m_strNumVenta;
}

/******************************************************************************************/
BOOL CDlgBuscaVenta::BuscaNumOferta()
{
	BOOL bExists = FALSE;
	CProforma rsProforma(m_db);

	//rsProforma.m_strFilter = "NUMPROFOR LIKE '" + m_strNumOferta + "'";
	//if (!rsProforma.Open(CRecordset::dynaset, "SELECT DISTINCT NUMPROFOR, NUMPEDIDO, NUMALB, FECHPROF, FECHPRE, FECHALB, FECHFAC, FECHENT, CUENTA FROM PROFORMA"))
	rsProforma.m_strFilter = "NUMPROFOR = " + m_strNumVenta;
	if (!rsProforma.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la oferta existe se busca el nombre del Cliente
	if (!rsProforma.m_NUMPROFOR.IsEmpty())
	{
		m_strNumVenta = rsProforma.m_NUMPROFOR.Trim();
		m_strCuenta = rsProforma.m_CUENTA.Trim();
		BuscaDesCuenta();

		bExists = TRUE;
	}

	rsProforma.Close();

	return bExists;
}


/******************************************************************************************/
BOOL CDlgBuscaVenta::BuscaNumPedido()
{
	BOOL bExists = FALSE;
	CPedidos rsPedidos(m_db);

	//rsPedidos.m_strFilter = "NUMPEDIDO LIKE '" + m_strNumVenta + "'";
	rsPedidos.m_strFilter = "NUMPEDIDO = " + m_strNumVenta;
	if (!rsPedidos.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el pedido existe se busca el nombre del Cliente
	if (!rsPedidos.m_NUMPEDIDO.IsEmpty())
	{
		m_strNumVenta = rsPedidos.m_NUMPEDIDO.Trim();
		m_strCuenta = rsPedidos.m_CUENTA.Trim();
		BuscaDesCuenta();

		bExists = TRUE;
	}

	rsPedidos.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgBuscaVenta::BuscaNumAlbaran()
{
	BOOL bExists = FALSE;
	CAlbaran rsAlbaran(m_db);

	//rsAlbaran.m_strFilter = "NUMALB LIKE '" + m_strNumVenta + "'";
	rsAlbaran.m_strFilter = "NUMALB = " + m_strNumVenta;
	if (!rsAlbaran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el albarán existe se busca el nombre del Cliente
	if (!rsAlbaran.m_NUMALB.IsEmpty())
	{
		m_strNumVenta = rsAlbaran.m_NUMALB.Trim();
		m_strCuenta = rsAlbaran.m_CUENTA.Trim();
		BuscaDesCuenta();

		bExists = TRUE;
	}

	rsAlbaran.Close();

	return bExists;
}

/******************************************************************************************/
void CDlgBuscaVenta::BuscaDesCuenta()
{
	if (m_strCuenta.IsEmpty())
		return;

	CCuentas rsCuentas(m_db);

	rsCuentas.m_strFilter = "CUENTA = '" + m_strCuenta + "'";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	if (!rsCuentas.m_CUENTA.IsEmpty())
		m_strDesCuenta = rsCuentas.m_NOMBRE.Trim();
	else
		m_strDesCuenta.Empty();

	rsCuentas.Close();

}