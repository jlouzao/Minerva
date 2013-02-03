// DlgSelecObra.cpp: archivo de implementación
//
/**************************************************************************************/

#include "stdafx.h"
#include "DlgSelecObra.h"
#include ".\dlgselecobra.h"
#include "BD.h"
#include "GestionDlg.h"
#include "DlgCierreObra.h"
#include "Etiquetas.h"

/**************************************************************************************/
// Cuadro de diálogo de CDlgSelecObra
/**************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgSelecObra, CDialog)
CDlgSelecObra::CDlgSelecObra(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelecObra::IDD, pParent)
	, m_strCuenta(_T(""))
	, m_strNombre(_T(""))
	, m_strObra(_T(""))
	, m_strNomObra(_T(""))
{
}

/**************************************************************************************/
CDlgSelecObra::~CDlgSelecObra()
{
}

/**************************************************************************************/
void CDlgSelecObra::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CUENTA, m_strCuenta);
	DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_EDIT_NOMBRE, m_strNombre);
	DDX_Text(pDX, IDC_EDIT_OBRA, m_strObra);
	DDV_MaxChars(pDX, m_strObra, 3);
	DDX_Text(pDX, IDC_EDIT_NOMBRE_OBRA, m_strNomObra);
}

/**************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgSelecObra, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_CUENTA, OnEnKillfocusEditCuenta)
	ON_BN_CLICKED(IDC_BTN_CUENTA, OnBnClickedBtnCuenta)
	ON_EN_KILLFOCUS(IDC_EDIT_OBRA, OnEnKillfocusEditObra)
	ON_BN_CLICKED(IDC_BTN_OBRA, OnBnClickedBtnObra)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/**************************************************************************************/
// Controladores de mensajes de CDlgSelecObra
/**************************************************************************************/

/***********************************************************************************************/
BOOL CDlgSelecObra::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Según el tipo que sea se pone un título u otro
	CString strTitulo;
	if (m_iTipo == ALTAMOD)
		strTitulo.LoadString(IDC_TITULO_ALTAMOD);
	else if (m_iTipo == CIERRE)
		strTitulo.LoadString(IDC_TITULO_CIERRE);
	if (m_iTipo == CONSULTA)
		strTitulo.LoadString(IDC_TITULO_CONSULTA);

	SetWindowText(strTitulo);

	// Se establece la Base de Datos para los diálogos de búsquedas
	m_dlgBusquedaClientes.SetConexion(m_db);
	m_dlgBusquedaObras.SetConexion(m_db);

	GetDlgItem(IDC_EDIT_OBRA)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBRA)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	return TRUE;
}

/***********************************************************************************************/
void CDlgSelecObra::OnEnKillfocusEditCuenta()
{
	CString strCuentaOld = m_strCuenta;

	GetDlgItem(IDC_EDIT_CUENTA)->GetWindowText(m_strCuenta);

	if (m_strCuenta == strCuentaOld)
		return;

	if (!m_strCuenta.IsEmpty())
	{
		// Si el cliente no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCliente())
		{
			AfxMessageBox(IDC_CLIENTE_NO_EXISTS);
			m_strCuenta = strCuentaOld;
			GetDlgItem(IDC_EDIT_CUENTA)->SetWindowText(m_strCuenta);
			return;
		}
		else
		{
			if (m_iTipo == ALTAMOD)
				GetDlgItem(IDOK)->EnableWindow(TRUE);
		}
	}
	else
		LimpiaVentana();
}

/**************************************************************************************/
void CDlgSelecObra::OnBnClickedBtnCuenta()
{
	INT_PTR status;

	m_dlgBusquedaClientes.SetTipo(CDialogBusqueda::CLIENTES);
	status = m_dlgBusquedaClientes.DoModal();
	if (status == IDOK)
	{
		LimpiaVentana();

		m_strCuenta = m_dlgBusquedaClientes.GetCodigo();
		m_strNombre = m_dlgBusquedaClientes.GetDescripcion();

		GetDlgItem(IDC_EDIT_OBRA)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OBRA)->EnableWindow(TRUE);

		UpdateData(FALSE);

		if (m_iTipo == ALTAMOD)
			GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
}

/**************************************************************************************/
void CDlgSelecObra::OnEnKillfocusEditObra()
{
	if (m_strCuenta.IsEmpty())
	{
		AfxMessageBox(IDC_NO_CLIENTE);
		m_strObra.Empty();
		GetDlgItem(IDC_EDIT_OBRA)->SetWindowText(m_strObra);
		return;
	}

	CString strObraOld = m_strObra;

	GetDlgItem(IDC_EDIT_OBRA)->GetWindowText(m_strObra);

	if (m_strObra == strObraOld)
		return;

	if (!m_strObra.IsEmpty())
	{
		// Si la Obra no existe se deja la anterior y se da un mensaje de error
		if (!BuscaObra())
		{
			AfxMessageBox(IDC_OBRA_NO_EXISTS);
			m_strObra = strObraOld;
			GetDlgItem(IDC_EDIT_OBRA)->SetWindowText(m_strObra);
		}
		else
			GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
	else
	{
		m_strNomObra.Empty();
		GetDlgItem(IDC_EDIT_NOMBRE_OBRA)->SetWindowText(m_strNomObra);
	}
}

/**************************************************************************************/
void CDlgSelecObra::OnBnClickedBtnObra()
{
	INT_PTR status;

	if (m_strCuenta.IsEmpty())
	{
		AfxMessageBox(IDC_NO_CLIENTE);
		return;
	}
	m_dlgBusquedaObras.SetTipo(CDialogBusqueda::DIRENV);
	m_dlgBusquedaObras.SetGestionar(FALSE);
	m_dlgBusquedaObras.SetCliente(m_strCuenta);
	status = m_dlgBusquedaObras.DoModal();
	if (status == IDOK)
	{
		m_strObra = m_dlgBusquedaObras.GetCodigo();
		m_strNomObra = m_dlgBusquedaObras.GetDescripcion();
		UpdateData(FALSE);

		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
}

/******************************************************************************************/
void CDlgSelecObra::OnBnClickedOk()
{
	if (m_iTipo == ALTAMOD)
	{
		CDlgDireccionEnvio dlgDireccionEnvio;
		dlgDireccionEnvio.SetConexion(m_db);
		dlgDireccionEnvio.SetCliente(m_strCuenta, m_strNombre);
		if (!m_strObra.IsEmpty())
			dlgDireccionEnvio.SetObra(m_strObra);
		dlgDireccionEnvio.DoModal();
	}
	else
	{
		CDlgCierreObra dlgCierreObra;
		dlgCierreObra.SetConexion(m_db);

		if (m_iTipo == CIERRE)
		{
			CString strMsg;
			strMsg.LoadString(IDS_CERRAR_OBRA);
			if (MessageBox(strMsg, "Minerva", MB_YESNO + MB_ICONQUESTION) != IDYES)
				return;

			dlgCierreObra.SetConsulta(FALSE);
		}
		else if (m_iTipo == CONSULTA)
			dlgCierreObra.SetConsulta(TRUE);

		dlgCierreObra.SetDatos(m_strCuenta, m_strObra);
		dlgCierreObra.DoModal();
	}

	LimpiaVentana();
	//OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgSelecObra::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgSelecObra::SetTipo(int iTipo)
{
	m_iTipo = iTipo;
}

/******************************************************************************************/
void CDlgSelecObra::LimpiaVentana()
{
	m_strCuenta.Empty();
	m_strNombre.Empty();
	m_strObra.Empty();
	m_strNomObra.Empty();

	UpdateData(FALSE);

	m_dlgBusquedaObras.InicializarListas();

	GetDlgItem(IDC_EDIT_OBRA)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBRA)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

/******************************************************************************************/
BOOL CDlgSelecObra::BuscaCliente()
{
	BOOL bExists = FALSE;
	CClientes rsClientes(m_db);

	rsClientes.m_strFilter = "CUENTA LIKE '" + m_strCuenta + "'";
	if (!rsClientes.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el cliente existe se rellenan sus campos 
	if (!rsClientes.m_CUENTA.IsEmpty())
	{
		LimpiaVentana();

		m_strCuenta = rsClientes.m_CUENTA.Trim();
		m_strNombre = rsClientes.m_NOMBRE.Trim();

		GetDlgItem(IDC_EDIT_OBRA)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OBRA)->EnableWindow(TRUE);

		bExists = TRUE;

	}

	rsClientes.Close();

	UpdateData(FALSE);

	return bExists;
}

/******************************************************************************************/
BOOL CDlgSelecObra::BuscaObra()
{
	BOOL bExists = FALSE;
	CDirEnv rsDirEnv(m_db);

	rsDirEnv.m_strFilter = "CLIENTE LIKE '" + m_strCuenta + "' AND DIRENV = '" + m_strObra + "'";
	if (!rsDirEnv.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la obra existe se rellenan sus campos 
	if (!rsDirEnv.m_CLIENTE.IsEmpty())
	{
		m_strNomObra = rsDirEnv.m_NOMDIRENV.Trim();
		GetDlgItem(IDC_EDIT_NOMBRE_OBRA)->SetWindowText(m_strNomObra);
		bExists = TRUE;
	}

	rsDirEnv.Close();

	return bExists;
}

