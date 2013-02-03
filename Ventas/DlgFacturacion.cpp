// DlgFacturacion.cpp: archivo de implementación
//
/**************************************************************************************/

#include "stdafx.h"
#include "DlgFacturacion.h"
#include ".\dlgfacturacion.h"
#include "BD.h"
#include "dlgSelecPedidos.h"
#include "Etiquetas.h"

/**************************************************************************************/
// Cuadro de diálogo de CDlgFacturacion
/**************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgFacturacion, CDialog)
CDlgFacturacion::CDlgFacturacion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFacturacion::IDD, pParent)
	, m_strCuenta(_T(""))
	, m_strCuenta2(_T(""))
	, m_strObra(_T(""))
	, m_strObra2(_T(""))
	, m_fecha1(0)
	, m_fecha2(0)
{
}

/**************************************************************************************/
CDlgFacturacion::~CDlgFacturacion()
{
}

/**************************************************************************************/
void CDlgFacturacion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CUENTA, m_strCuenta);
	DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_EDIT_CUENTA2, m_strCuenta2);
	DDV_MaxChars(pDX, m_strCuenta2, 9);
	DDX_Text(pDX, IDC_EDIT_OBRA, m_strObra);
	DDV_MaxChars(pDX, m_strObra, 3);
	DDX_Text(pDX, IDC_EDIT_OBRA2, m_strObra2);
	DDV_MaxChars(pDX, m_strObra2, 3);
	DDX_DateTimeCtrl(pDX, IDC_FECHA1, m_fecha1);
	DDX_DateTimeCtrl(pDX, IDC_FECHA2, m_fecha2);
}

/**************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgFacturacion, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_CUENTA, OnEnKillfocusEditCuenta)
	ON_BN_CLICKED(IDC_BTN_CUENTA, OnBnClickedBtnCuenta)
	ON_EN_KILLFOCUS(IDC_EDIT_CUENTA2, OnEnKillfocusEditCuenta2)
	ON_BN_CLICKED(IDC_BTN_CUENTA2, OnBnClickedBtnCuenta2)
	ON_EN_KILLFOCUS(IDC_EDIT_OBRA, OnEnKillfocusEditObra)
	ON_BN_CLICKED(IDC_BTN_OBRA, OnBnClickedBtnObra)
	ON_EN_KILLFOCUS(IDC_EDIT_OBRA2, OnEnKillfocusEditObra2)
	ON_BN_CLICKED(IDC_BTN_OBRA2, OnBnClickedBtnObra2)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// Controladores de mensajes de CDlgFacturacion
/**************************************************************************************/

/***********************************************************************************************/
BOOL CDlgFacturacion::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Se establece la Base de Datos para los diálogos de búsquedas
	m_dlgBusquedaClientes.SetConexion(m_db);
	m_dlgBusquedaObras.SetConexion(m_db);
	m_dlgBusquedaObras2.SetConexion(m_db);

	/*GetDlgItem(IDC_EDIT_CUENTA2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CUENTA2)->EnableWindow(FALSE);*/
/*	GetDlgItem(IDC_EDIT_OBRA)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBRA)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_OBRA2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBRA2)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA1)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA2)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);*/

	return TRUE;
}

/***********************************************************************************************/
void CDlgFacturacion::OnEnKillfocusEditCuenta()
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
		}
		else
		{
			GetDlgItem(IDC_EDIT_CUENTA)->SetWindowText(m_strCuenta);
			LimpiaObra();
			if (m_strCuenta2.IsEmpty())
			{
				m_strCuenta2 = m_strCuenta;
				GetDlgItem(IDC_EDIT_CUENTA2)->SetWindowText(m_strCuenta2);
			}
		}	
	}
	else
		LimpiaObra();
}

/***********************************************************************************************/
void CDlgFacturacion::OnBnClickedBtnCuenta()
{
	INT_PTR status;

	m_dlgBusquedaClientes.SetTipo(CDialogBusqueda::CLIENTES);
	status = m_dlgBusquedaClientes.DoModal();
	if (status == IDOK)
	{
		m_strCuenta = m_dlgBusquedaClientes.GetCodigo();
		GetDlgItem(IDC_EDIT_CUENTA)->SetWindowText(m_strCuenta);
		LimpiaObra();
		if (m_strCuenta2.IsEmpty())
		{
			m_strCuenta2 = m_strCuenta;
			GetDlgItem(IDC_EDIT_CUENTA2)->SetWindowText(m_strCuenta2);
		}
	}
}

/***********************************************************************************************/
void CDlgFacturacion::OnEnKillfocusEditCuenta2()
{
	CString strCuentaOld2 = m_strCuenta2;

	GetDlgItem(IDC_EDIT_CUENTA2)->GetWindowText(m_strCuenta2);

	if (m_strCuenta2 == strCuentaOld2)
		return;

	if (!m_strCuenta2.IsEmpty())
	{
		// Si el cliente no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCliente())
		{
			AfxMessageBox(IDC_CLIENTE_NO_EXISTS);
			m_strCuenta2 = strCuentaOld2;
			GetDlgItem(IDC_EDIT_CUENTA2)->SetWindowText(m_strCuenta2);
			return;
		}
		else
		{
			GetDlgItem(IDC_EDIT_CUENTA2)->SetWindowText(m_strCuenta2);
			LimpiaObra2();
		}
	}
	else
		LimpiaObra2();
}

/***********************************************************************************************/
void CDlgFacturacion::OnBnClickedBtnCuenta2()
{
	INT_PTR status;

	m_dlgBusquedaClientes.SetTipo(CDialogBusqueda::CLIENTES);
	status = m_dlgBusquedaClientes.DoModal();
	if (status == IDOK)
	{
		m_strCuenta2 = m_dlgBusquedaClientes.GetCodigo();
		GetDlgItem(IDC_EDIT_CUENTA2)->SetWindowText(m_strCuenta2);

		LimpiaObra2();
	}
}

/***********************************************************************************************/
void CDlgFacturacion::OnEnKillfocusEditObra()
{
	CString strObraOld = m_strObra;

	GetDlgItem(IDC_EDIT_OBRA)->GetWindowText(m_strObra);

	if (m_strObra == strObraOld)
		return;

	if (!m_strObra.IsEmpty())
	{
		// Si la Obra no existe se deja la anterior y se da un mensaje de error
		if (!BuscaObra(m_strCuenta, m_strObra))
		{
			AfxMessageBox(IDC_OBRA_NO_EXISTS);
			m_strObra = strObraOld;
		}

		GetDlgItem(IDC_EDIT_OBRA)->SetWindowText(m_strObra);
		if (m_strObra2.IsEmpty() && m_strCuenta == m_strCuenta2)
		{
			m_strObra2 = m_strObra;
			GetDlgItem(IDC_EDIT_OBRA2)->SetWindowText(m_strObra2);
		}
	}
}

/***********************************************************************************************/
void CDlgFacturacion::OnBnClickedBtnObra()
{
	INT_PTR status;

	m_dlgBusquedaObras.SetTipo(CDialogBusqueda::DIRENV);
	m_dlgBusquedaObras.SetCliente(m_strCuenta);

	status = m_dlgBusquedaObras.DoModal();
	if (status == IDOK)
	{
		m_strObra = m_dlgBusquedaObras.GetCodigo();
		GetDlgItem(IDC_EDIT_OBRA)->SetWindowText(m_strObra);

		if (m_strObra2.IsEmpty() && m_strCuenta == m_strCuenta2)
		{
			m_strObra2 = m_strObra;
			GetDlgItem(IDC_EDIT_OBRA2)->SetWindowText(m_strObra2);
		}
	}
}

/***********************************************************************************************/
void CDlgFacturacion::OnEnKillfocusEditObra2()
{
	CString strCliente;
	CString strObraOld2 = m_strObra2;

	GetDlgItem(IDC_EDIT_OBRA2)->GetWindowText(m_strObra2);

	if (m_strObra2 == strObraOld2)
		return;

	if (!m_strObra2.IsEmpty())
	{
		/*if (m_strCuenta2.IsEmpty())
			strCliente = m_strCuenta;
		else
			strCliente = m_strCuenta2;*/

		// Si la Obra no existe se deja la anterior y se da un mensaje de error
		if (!BuscaObra(m_strCuenta2, m_strObra2))
		{
			AfxMessageBox(IDC_OBRA_NO_EXISTS);
			m_strObra2 = strObraOld2;
			GetDlgItem(IDC_EDIT_OBRA2)->SetWindowText(m_strObra2);
		}
	}
}

/***********************************************************************************************/
void CDlgFacturacion::OnBnClickedBtnObra2()
{
	INT_PTR status;
	CString strCliente;

	m_dlgBusquedaObras2.SetTipo(CDialogBusqueda::DIRENV);

	/*if (m_strCuenta2.IsEmpty())
		strCliente = m_strCuenta;
	else
		strCliente = m_strCuenta2;*/

	m_dlgBusquedaObras2.SetCliente(m_strCuenta2);
	status = m_dlgBusquedaObras2.DoModal();
	if (status == IDOK)
	{
		m_strObra2 = m_dlgBusquedaObras2.GetCodigo();
		GetDlgItem(IDC_EDIT_OBRA2)->SetWindowText(m_strObra2);
	}
}

/******************************************************************************************/
void CDlgFacturacion::OnBnClickedOk()
{
	UpdateData();

	BuscaPedidos();

	CDlgSelecPedidos dlgSelecPedidos;
	dlgSelecPedidos.SetConexion(m_db);
	dlgSelecPedidos.SetPedidos(&m_rsPedidos);
	dlgSelecPedidos.DoModal();

	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgFacturacion::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsPedidos.m_pDatabase = m_db;
}

/******************************************************************************************/
BOOL CDlgFacturacion::BuscaCliente()
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
		bExists = TRUE;

	rsClientes.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgFacturacion::BuscaObra(CString strCliente, CString strObra)
{
	BOOL bExists = FALSE;
	CDirEnv rsDirEnv(m_db);

	rsDirEnv.m_strFilter = "CLIENTE LIKE '" + strCliente + "' AND DIRENV = '" + strObra + "'";
	if (!rsDirEnv.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la obra existe se rellenan sus campos 
	if (!rsDirEnv.m_CLIENTE.IsEmpty())
		bExists = TRUE;

	rsDirEnv.Close();

	return bExists;
}

/******************************************************************************************/
/*void CDlgFacturacion::LimpiaVentana(BOOL bLimpiaCuenta)
{
	if (bLimpiaCuenta)
		m_strCuenta.Empty();

	m_strCuenta2.Empty();
	m_strObra.Empty();
	m_strObra2.Empty();
	m_fecha1 = NULL;
	m_fecha2 = NULL;

	UpdateData(FALSE);

	m_dlgBusquedaObras.InicializarListas();
	m_dlgBusquedaObras2.InicializarListas();

	/*GetDlgItem(IDC_EDIT_CUENTA2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CUENTA2)->EnableWindow(FALSE);*/
/*	GetDlgItem(IDC_EDIT_OBRA)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBRA)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_OBRA2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_OBRA2)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA1)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA2)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}*/

/******************************************************************************************/
void CDlgFacturacion::LimpiaObra()
{
	m_strObra.Empty();
	GetDlgItem(IDC_EDIT_OBRA)->SetWindowText(m_strObra);
	m_dlgBusquedaObras.InicializarListas();
}

/******************************************************************************************/
void CDlgFacturacion::LimpiaObra2()
{
	m_strObra2.Empty();
	GetDlgItem(IDC_EDIT_OBRA2)->SetWindowText(m_strObra2);
	m_dlgBusquedaObras2.InicializarListas();
}

/******************************************************************************************/
void CDlgFacturacion::BuscaPedidos()
{
	CString strFilter;

	if (!m_strCuenta.IsEmpty() || !m_strCuenta2.IsEmpty())
	{
		if (m_strCuenta.IsEmpty())
			m_strCuenta = " ";  // Se asigna un ascii inferior a cualquier número de cuenta

		if (m_strCuenta2.IsEmpty())
			m_strCuenta2 = "º";  // Se asigna un ascii mayor a cualquier número de cuenta

		strFilter = "CUENTA >= '" + m_strCuenta + "' AND CUENTA <= '" + m_strCuenta2 + "'";
	}

	if (!m_strObra.IsEmpty() || !m_strObra2.IsEmpty())
	{
		if (!strFilter.IsEmpty())
			strFilter += " AND ";

		if (m_strObra.IsEmpty())
			m_strObra = " ";  // Se asigna un ascii inferior a cualquier número de cuenta

		if (m_strObra2.IsEmpty())
			m_strObra2 = "º";  // Se asigna un ascii mayor a cualquier número de cuenta

		if (m_strCuenta == m_strCuenta2)
			strFilter += "DIRENV >= '" + m_strObra + "' AND DIRENV <= '" + m_strObra2 + "'";
		else
		{
			// Se vuelve a hacer por si no había entrado en CUENTA
			if (m_strCuenta.IsEmpty())
				m_strCuenta = " ";  // Se asigna un ascii inferior a cualquier número de cuenta

			if (m_strCuenta2.IsEmpty())
				m_strCuenta2 = "º";  // Se asigna un ascii mayor a cualquier número de cuenta

			strFilter += "((CUENTA = '" + m_strCuenta + "' AND DIRENV >= '" + m_strObra + "')";				
			strFilter += " OR (CUENTA = '" + m_strCuenta2 + "' AND DIRENV <= '" + m_strObra2 + "')";
			strFilter += " OR (CUENTA > '" + m_strCuenta + "' AND CUENTA < '" + m_strCuenta2 + "'))";
		}
	}

	if (m_fecha1 != NULL || m_fecha2 != NULL)
	{
		if (m_fecha1 == NULL)
		{
			CTime fechaAux(1980, 1, 1, 0, 0, 0);
			m_fecha1 = fechaAux; // Se asigna una fecha menor que cualquier otra
		}

		if (m_fecha2 == NULL)
		{
			CTime fechaAux(2100, 1, 1, 0, 0, 0);
			m_fecha2 = fechaAux; // Se asigna una fecha mayor que cualquier otra
		}

		CString strFecha1, strFecha2;
		strFecha1 = m_fecha1.Format("%d/%m/%Y");
		strFecha2 = m_fecha2.Format("%d/%m/%Y");

		if (!strFilter.IsEmpty())
			strFilter += " AND ";

		strFilter += "FECHPED >= '" + strFecha1 + "' AND FECHPED <= '" + strFecha2 + "'";
	}

	if (!strFilter.IsEmpty())
		strFilter += " AND ";

	m_rsPedidos.m_strFilter = strFilter + "ESTADO <> '" + FACTURADO + "'"; // Estado diferente a facturado
	m_rsPedidos.m_strSort = "CUENTA, DIRENV, NUMPEDIDO";

	if (!m_rsPedidos.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}
}
