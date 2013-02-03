// DlgBuscaVenta.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgBuscaCompra.h"
#include ".\DlgBuscaCompra.h"
#include "BD.h"


/******************************************************************************************/
// Cuadro de diálogo de CDlgBuscaCompra
/******************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgBuscaCompra, CDialog)
CDlgBuscaCompra::CDlgBuscaCompra(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBuscaCompra::IDD, pParent)
	, m_strNumCompra(_T(""))
	, m_strCuenta(_T(""))
	, m_strDesCuenta(_T(""))
{
}

/******************************************************************************************/
CDlgBuscaCompra::~CDlgBuscaCompra()
{
}

/******************************************************************************************/
void CDlgBuscaCompra::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUMCOMPRA, m_strNumCompra);
	DDV_MaxChars(pDX, m_strNumCompra, 10);
	DDX_Text(pDX, IDC_CUENTA, m_strCuenta);
	//DDX_Control(pDX, IDC_NUMOFERTA, m_cNumOferta);
	DDX_Text(pDX, IDC_DESCUENTA, m_strDesCuenta);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgBuscaCompra, CDialog)
	ON_EN_KILLFOCUS(IDC_NUMCOMPRA, OnEnKillfocusNumCompra)
	ON_BN_CLICKED(IDC_BTN_VENTA, OnBnClickedBtnCompra)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgBuscaCompra
/******************************************************************************************/
BOOL CDlgBuscaCompra::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se establece la Base de Datos para el diálogo de búsqueda
	m_dlgBusqueda.SetConexion(m_db);

	if (m_iTipo == GESTCOMPRA)
		GetDlgItem(IDC_STATIC_NUMERO)->SetWindowText("Nº de Pedido: ");
	else if (m_iTipo == GESTALBARAN)
		GetDlgItem(IDC_STATIC_NUMERO)->SetWindowText("Nº de Albarán: ");

	GetDlgItem(IDC_NUMCOMPRA)->SetFocus();

	return FALSE;
}

/******************************************************************************************/
void CDlgBuscaCompra::OnEnKillfocusNumCompra()
{
	CString strNumVentaOld = m_strNumCompra;

	GetDlgItem(IDC_NUMCOMPRA)->GetWindowText(m_strNumCompra);
	m_strNumCompra = m_strNumCompra.Trim();

	if (!m_strNumCompra.IsEmpty())
	{
		if (m_iTipo == GESTCOMPRA)
		{
			// Si el pedido no existe se deja el anterior y se da un mensaje de error
			if (!BuscaNumCompra())
			{
				AfxMessageBox(IDS_COMPRA_NO_EXISTE);
				m_strNumCompra = strNumVentaOld;
				GetDlgItem(IDC_NUMCOMPRA)->SetFocus();
			}
		}
		if (m_iTipo == GESTALBARAN)
		{
			// Si el albarán no existe se deja el anterior y se da un mensaje de error
			if (!BuscaNumAlbCompra())
			{
				AfxMessageBox(IDS_ALBARAN_NO_EXISTE);
				m_strNumCompra = strNumVentaOld;
				GetDlgItem(IDC_NUMCOMPRA)->SetFocus();
			}
		}
		BuscaNumAlbCompra();
	}
	else
		m_strCuenta.Empty();

	UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgBuscaCompra::OnBnClickedBtnCompra()
{
	INT_PTR status;

	if (m_iTipo == GESTCOMPRA)
		m_dlgBusqueda.SetTipo(CDialogBusqueda::COMPRAS);
	else if (m_iTipo == GESTALBARAN)
		m_dlgBusqueda.SetTipo(CDialogBusqueda::ALBCOMPRA);
	
	m_dlgBusqueda.SetConexion(m_db);
	status = m_dlgBusqueda.DoModal();
	if (status == IDOK)
	{
		m_strNumCompra = m_dlgBusqueda.GetCodigo();
		m_strCuenta = m_dlgBusqueda.GetDescripcion();
		BuscaDesCuenta();
	}

	UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgBuscaCompra::OnBnClickedOk()
{
	// Se comprueba que haya una venta seleccionada
	GetDlgItem(IDC_NUMCOMPRA)->GetWindowText(m_strNumCompra);
	if (m_strNumCompra.IsEmpty())
	{
		/*if (m_iTipo == OFERTA)
			AfxMessageBox(IDC_NO_OFERTA);
		else if (m_iTipo == PEDIDO)
			AfxMessageBox(IDC_NO_PEDIDO);
		else if (m_iTipo == ALBARAN)
			AfxMessageBox(IDC_NO_ALBARAN);
		return;*/
	}
	OnOK();
}
/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgBuscaCompra::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgBuscaCompra::SetTipo(int iTipo)
{
	m_iTipo = iTipo;
}
/******************************************************************************************/
CString CDlgBuscaCompra::GetNumCompra()
{
	return m_strNumCompra;
}
/******************************************************************************************/
BOOL CDlgBuscaCompra::BuscaNumAlbCompra()
{
	BOOL bExists = FALSE;
	CAlbCompra rsAlbCompra(m_db);

	rsAlbCompra.m_strFilter = "NALBCOM = " + m_strNumCompra;
	if (!rsAlbCompra.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	// Si el pedido existe se busca el nombre del Cliente
	if (!rsAlbCompra.m_NPEDCOM.IsEmpty())
	{
		m_strNumCompra = rsAlbCompra.m_NALBCOM.Trim();
		m_strCuenta = rsAlbCompra.m_CUENTA.Trim();

		bExists = TRUE;
	}

	rsAlbCompra.Close();

	return bExists;
}
/******************************************************************************************/
BOOL CDlgBuscaCompra::BuscaNumCompra()
{
	BOOL bExists = FALSE;
	CCompras rsCompra(m_db);

	rsCompra.m_strFilter = "NPEDCOM = " + m_strNumCompra;
	if (!rsCompra.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	// Si el pedido existe se busca el nombre del Cliente
	if (!rsCompra.m_NPEDCOM.IsEmpty())
	{
		m_strNumCompra = rsCompra.m_NPEDCOM.Trim();
		m_strCuenta = rsCompra.m_CUENTA.Trim();
		BuscaDesCuenta();

		bExists = TRUE;
	}

	rsCompra.Close();

	return bExists;
}
/******************************************************************************************/
void CDlgBuscaCompra::BuscaDesCuenta()
{
	if (m_strCuenta.IsEmpty())
		return;

	CCuentas rsCuentas(m_db);

	rsCuentas.m_strFilter = "CUENTA = '" + m_strCuenta + "'";
	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	if (!rsCuentas.m_CUENTA.IsEmpty())
		m_strDesCuenta = rsCuentas.m_NOMBRE.Trim();
	else
		m_strDesCuenta.Empty();

	rsCuentas.Close();

}
