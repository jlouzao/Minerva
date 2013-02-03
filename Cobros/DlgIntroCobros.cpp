// DlgIntroCobros.cpp: archivo de implementación
/******************************************************************************************/

#include "stdafx.h"
#include "DlgIntroCobros.h"
#include ".\dlgintrocobros.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgIntroCobros
/******************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgIntroCobros, CDialog)
CDlgIntroCobros::CDlgIntroCobros(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIntroCobros::IDD, pParent)
	, m_strCtaTesoreria(_T(""))
	, m_strDesCtaTesoreria(_T(""))
	, m_strCliente(_T(""))
	, m_strDesCliente(_T(""))
	, m_strFCobro(_T(""))
	, m_strDesFCobro(_T(""))
	, m_dImporte(0)
{
}

/******************************************************************************************/
CDlgIntroCobros::~CDlgIntroCobros()
{
}

/******************************************************************************************/
void CDlgIntroCobros::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COBROS, m_lstCobros);
	DDX_Text(pDX, IDC_EDIT_CTA_TESORERIA, m_strCtaTesoreria);
	DDV_MaxChars(pDX, m_strCtaTesoreria, 9);
	DDX_Text(pDX, IDC_EDIT_DESCTATESORERIA, m_strDesCtaTesoreria);
	DDX_Text(pDX, IDC_EDIT_CLIENTE, m_strCliente);
	DDV_MaxChars(pDX, m_strCliente, 9);
	DDX_Text(pDX, IDC_EDIT_DESCLIENTE, m_strDesCliente);
	DDX_Text(pDX, IDC_EDIT_FCOBRO, m_strFCobro);
	DDV_MaxChars(pDX, m_strFCobro, 3);
	DDX_Text(pDX, IDC_EDIT_DESFCOBRO, m_strDesFCobro);
	DDX_Text(pDX, IDC_IMPORTE, m_dImporte);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgIntroCobros, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_CTA_TESORERIA, OnEnKillfocusEditCtaTesoreria)
	ON_BN_CLICKED(IDC_BTN_CTATESORERIA, OnBnClickedBtnCtaTesoreria)
	ON_EN_KILLFOCUS(IDC_EDIT_CLIENTE, OnEnKillfocusEditCliente)
	ON_BN_CLICKED(IDC_BTN_CLIENTE, OnBnClickedBtnCliente)
	ON_EN_KILLFOCUS(IDC_EDIT_FCOBRO, OnEnKillfocusEditFcobro)
	ON_BN_CLICKED(IDC_BTN_FCOBRO, OnBnClickedBtnFcobro)
	ON_BN_CLICKED(ID_BUSCAR, OnBnClickedBuscar)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY(NM_CLICK, IDC_COBROS, OnNMClickCobros)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgIntroCobros
/******************************************************************************************/

/******************************************************************************************/
BOOL CDlgIntroCobros::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstCobros.SetExtendedStyle(m_lstCobros.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES);

	// Se introducen los nombres de las columnas
	m_lstCobros.InsertColumn(0,"", LVCFMT_LEFT, 22);			
	m_lstCobros.InsertColumn(1,"Nº Cobro", LVCFMT_LEFT, 130);
	m_lstCobros.InsertColumn(2,"Tipo", LVCFMT_LEFT, 40);
	m_lstCobros.InsertColumn(3,"Fecha", LVCFMT_LEFT, 110);
	m_lstCobros.InsertColumn(4,"Importe", LVCFMT_LEFT, 110);

	m_dlgBusquedaCuentas.SetConexion(m_db);
	m_dlgBusquedaClientes.SetConexion(m_db);
	m_dlgBusquedaFCobro.SetConexion(m_db);

	GetDlgItem(ID_BUSCAR)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	return FALSE;
}

/******************************************************************************************/
void CDlgIntroCobros::OnEnKillfocusEditCtaTesoreria()
{
	CString strCtaTesoreriaOld = m_strCtaTesoreria;

	GetDlgItem(IDC_EDIT_CTA_TESORERIA)->GetWindowText(m_strCtaTesoreria);

	if (m_strCtaTesoreria == strCtaTesoreriaOld)
		return;

	if (!m_strCtaTesoreria.IsEmpty())
	{
		// Si la cuenta no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCuenta())
		{
			AfxMessageBox(IDC_CUENTA_NO_EXISTS);
			m_strCtaTesoreria = strCtaTesoreriaOld;
			GetDlgItem(IDC_EDIT_CTA_TESORERIA)->SetWindowText(m_strCtaTesoreria);
		}
		else
		{
			if (m_lstCobros.GetItemCount() != 0)
				GetDlgItem(IDOK)->EnableWindow();
		}
	}
	else
	{
		m_strDesCtaTesoreria.Empty();
		GetDlgItem(IDC_EDIT_DESCTATESORERIA)->SetWindowText(m_strDesCtaTesoreria);
	}
}

/******************************************************************************************/
void CDlgIntroCobros::OnBnClickedBtnCtaTesoreria()
{
	INT_PTR status;

	m_dlgBusquedaCuentas.SetTipo(CDialogBusqueda::CUENTAS);
	status = m_dlgBusquedaCuentas.DoModal();
	if (status == IDOK)
	{
		m_strCtaTesoreria = m_dlgBusquedaCuentas.GetCodigo();
		m_strDesCtaTesoreria = m_dlgBusquedaCuentas.GetDescripcion();

		GetDlgItem(IDC_EDIT_CTA_TESORERIA)->SetWindowText(m_strCtaTesoreria);
		GetDlgItem(IDC_EDIT_DESCTATESORERIA)->SetWindowText(m_strDesCtaTesoreria);

		if (m_lstCobros.GetItemCount() != 0)
			GetDlgItem(IDOK)->EnableWindow();
	}
}

/******************************************************************************************/
void CDlgIntroCobros::OnEnKillfocusEditCliente()
{
	CString strClienteOld = m_strCliente;

	GetDlgItem(IDC_EDIT_CLIENTE)->GetWindowText(m_strCliente);

	if (m_strCliente == strClienteOld)
		return;

	if (!m_strCliente.IsEmpty())
	{
		// Si el cliente no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCliente())
		{
			AfxMessageBox(IDC_CLIENTE_NO_EXISTS);
			m_strCliente = strClienteOld;
			GetDlgItem(IDC_EDIT_CLIENTE)->SetWindowText(m_strCliente);
		}
	}
	else
	{
		m_strDesCliente.Empty();
		GetDlgItem(IDC_EDIT_DESCLIENTE)->SetWindowText(m_strDesCliente);
	}
}

/******************************************************************************************/
void CDlgIntroCobros::OnBnClickedBtnCliente()
{
	INT_PTR status;

	m_dlgBusquedaClientes.SetTipo(CDialogBusqueda::CLIENTES);
	status = m_dlgBusquedaClientes.DoModal();
	if (status == IDOK)
	{
		m_strCliente = m_dlgBusquedaClientes.GetCodigo();
		m_strDesCliente = m_dlgBusquedaClientes.GetDescripcion();

		GetDlgItem(IDC_EDIT_CLIENTE)->SetWindowText(m_strCliente);
		GetDlgItem(IDC_EDIT_DESCLIENTE)->SetWindowText(m_strDesCliente);

		GetDlgItem(ID_BUSCAR)->EnableWindow();
	}
}

/******************************************************************************************/
void CDlgIntroCobros::OnEnKillfocusEditFcobro()
{
	CString strOldFCobro = m_strFCobro;

	GetDlgItem(IDC_EDIT_FCOBRO)->GetWindowText(m_strFCobro);

	if (!m_strFCobro.IsEmpty())
	{
		// Si la forma de cobro no existe se deja el anterior y se da un mensaje de error
		if (!BuscaFCobro())
		{
			AfxMessageBox(IDC_FCOBRO_NO_EXISTS);
			m_strFCobro = strOldFCobro;
			GetDlgItem(IDC_EDIT_FCOBRO)->SetWindowText(m_strFCobro);
		}
	}
	else
	{
		m_strDesFCobro.Empty();
		GetDlgItem(IDC_EDIT_DESFCOBRO)->SetWindowText(m_strDesFCobro);
	}
}

/******************************************************************************************/
void CDlgIntroCobros::OnBnClickedBtnFcobro()
{
	INT_PTR status;

	m_dlgBusquedaFCobro.SetTipo(CDialogBusqueda::FPAGCOB);
	status = m_dlgBusquedaFCobro.DoModal();
	if (status == IDOK)
	{
		m_strFCobro = m_dlgBusquedaFCobro.GetCodigo();
		m_strDesFCobro = m_dlgBusquedaFCobro.GetDescripcion();
	}

	GetDlgItem(IDC_EDIT_FCOBRO)->SetWindowText(m_strFCobro);
	GetDlgItem(IDC_EDIT_DESFCOBRO)->SetWindowText(m_strDesFCobro);
}

/******************************************************************************************/
void CDlgIntroCobros::OnBnClickedBuscar()
{
	//CCobros rsCobros(m_db);

	if (m_rsCobros.IsOpen())
		m_rsCobros.Close();

	m_rsCobros.m_strFilter = "CUENTA = '" + m_strCliente + "' AND ESTADO = '" + COBRO_PENDIENTE + "'";
	if (!m_strFCobro.IsEmpty())
		m_rsCobros.m_strFilter += " AND FCOBRO = '" + m_strFCobro + "'";

	if (!m_rsCobros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	m_lstCobros.DeleteAllItems();
	m_dImporte = 0;
	GetDlgItem(IDC_IMPORTE)->SetWindowText("0");

	int iFila = 0;
	CString strImporte;
	while (!m_rsCobros.IsEOF())
	{
		// Se rellena el listCtrl
		m_lstCobros.InsertItem(iFila, _T(""));
		m_lstCobros.SetItemText(iFila, 0, _T(""));
		m_lstCobros.SetItemText(iFila, 1, m_rsCobros.m_NUMEFEC.Trim());
		m_lstCobros.SetItemText(iFila, 2, m_rsCobros.m_FCOBRO.Trim());
		m_lstCobros.SetItemText(iFila, 3, m_rsCobros.m_FECHLIBRA.Format("%d/%m/%Y"));
		strImporte.Format("%g", m_rsCobros.m_EUROS);
		m_lstCobros.SetItemText(iFila, 4, strImporte);

		iFila++;
		m_rsCobros.MoveNext();
	}

	if (iFila != 0 && !m_strCtaTesoreria.IsEmpty())
		GetDlgItem(IDOK)->EnableWindow();
}

/******************************************************************************************/
void CDlgIntroCobros::OnNMClickCobros(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE item = (LPNMITEMACTIVATE) pNMHDR;
	int iFila = item->iItem;
	int iColumna = item->iSubItem;

	// Si es la columna del checkbox miramos si se ha activado o no para actualizar
	// el importe total
	if (iColumna == 0)
	{
		BOOL bActivo = m_lstCobros.GetCheck(iFila);
		if (!bActivo)
			m_dImporte += atof(m_lstCobros.GetItemText(iFila,4));
		else
			m_dImporte -= atof(m_lstCobros.GetItemText(iFila,4));

		CString strImporte;
		strImporte.Format("%g", m_dImporte);
		GetDlgItem(IDC_IMPORTE)->SetWindowText(strImporte);
	}


	*pResult = 0;
}
/******************************************************************************************/
void CDlgIntroCobros::OnBnClickedOk()
{
	HRESULT hErr = S_OK;

	if (m_rsCobros.GetRecordCount() == 0)
		return;

	m_rsCobros.MoveFirst();
	int iFila = 0;
	while (!m_rsCobros.IsEOF() && hErr == S_OK)
	{
		if (m_lstCobros.GetCheck(iFila))
		{
			m_rsCobros.m_BANCO = m_strCtaTesoreria;
			m_rsCobros.m_ESTADO = COBRADO;

			hErr = m_rsCobros.UpdateCobros();
		}

		iFila++;
		m_rsCobros.MoveNext();
	}

	m_rsCobros.Close();
	LimpiaVentana();

	//OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgIntroCobros::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsCobros.m_pDatabase = db;
}

/******************************************************************************************/
BOOL CDlgIntroCobros::BuscaCuenta()
{
	BOOL bExists = FALSE;

	CCuentas rsCuentas(m_db);

	rsCuentas.m_strFilter = "CUENTA LIKE '" + m_strCtaTesoreria + "'";

	if (!rsCuentas.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	if (!rsCuentas.m_CUENTA.IsEmpty())
	{
		m_strDesCtaTesoreria = rsCuentas.m_NOMBRE.Trim();
		GetDlgItem(IDC_EDIT_CTA_TESORERIA)->SetWindowText(m_strCtaTesoreria);
		GetDlgItem(IDC_EDIT_DESCTATESORERIA)->SetWindowText(m_strDesCtaTesoreria);
		bExists = TRUE;
	}

	rsCuentas.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgIntroCobros::BuscaCliente()
{
	BOOL bExists = FALSE;

	CClientes rsClientes(m_db);

	rsClientes.m_strFilter = "CUENTA LIKE '" + m_strCliente + "'";

	if (!rsClientes.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	if (!rsClientes.m_CUENTA.IsEmpty())
	{
		m_strDesCliente = rsClientes.m_NOMBRE.Trim();
		GetDlgItem(IDC_EDIT_CLIENTE)->SetWindowText(m_strCliente);
		GetDlgItem(IDC_EDIT_DESCLIENTE)->SetWindowText(m_strDesCliente);

		GetDlgItem(ID_BUSCAR)->EnableWindow();

		bExists = TRUE;
	}

	rsClientes.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgIntroCobros::BuscaFCobro()
{
	BOOL bExists = FALSE;
	CFPagCob rsFCobro(m_db);

	rsFCobro.m_strFilter = "FCOBRO LIKE '" + m_strFCobro + "'";
	if (!rsFCobro.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la forma de cobro existe se rellena la descripción 
	if (!rsFCobro.m_FCOBRO.IsEmpty())
	{
		m_strDesFCobro = rsFCobro.m_DFCOBRO.Trim();
		bExists = TRUE;
	}

	rsFCobro.Close();

	UpdateData(FALSE);

	return bExists;
}

/******************************************************************************************/
void CDlgIntroCobros::LimpiaVentana()
{
	m_strCtaTesoreria.Empty();
	m_strDesCtaTesoreria.Empty();
	m_strCliente.Empty();
	m_strDesCliente.Empty();
	m_strFCobro.Empty();
	m_strDesFCobro.Empty();

	m_lstCobros.DeleteAllItems();

	GetDlgItem(ID_BUSCAR)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_dImporte = 0;

	UpdateData(FALSE);
}

