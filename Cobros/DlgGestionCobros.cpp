// DlgGestionCobros.cpp: archivo de implementación
/******************************************************************************************/

#include "stdafx.h"
#include "DlgGestionCobros.h"
#include ".\dlggestioncobros.h"
#include "CobrosMngr.h"
#include "DlgDesglose.h"

/******************************************************************************************/
// Cuadro de diálogo de CDlgGestionCobros
/******************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgGestionCobros, CDialog)
CDlgGestionCobros::CDlgGestionCobros(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGestionCobros::IDD, pParent)
	, m_strEstado(_T(""))
	, m_strDesEstado(_T(""))
	, m_strNumFac(_T(""))
	, m_strNumEfec(_T(""))
	, m_strNumEfec2(_T(""))
	, m_strNumEfec3(_T(""))
	, m_strCuenta(_T(""))
	, m_strNombre(_T(""))
	, m_strFCobro(_T(""))
	, m_strDesFCobro(_T(""))
	, m_strImporte(_T(""))
	, m_fechaLibra(0)
	, m_fechaVenci(0)
	, m_fechaRecep()
	, m_strRemesa(_T(""))
	, m_strCtaTesoreria(_T(""))
	, m_strCentro(_T(""))
	, m_strDesCentro(_T(""))
	, m_strObservaciones(_T(""))
{
}

/******************************************************************************************/
CDlgGestionCobros::~CDlgGestionCobros()
{
}

/******************************************************************************************/
void CDlgGestionCobros::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ESTADO, m_strDesEstado);
	DDX_Text(pDX, IDC_EDIT_NUMFAC, m_strNumFac);
	DDV_MaxChars(pDX, m_strNumFac, 10);
	DDX_Text(pDX, IDC_EDIT_NUMEFEC, m_strNumEfec);
	DDX_Text(pDX, IDC_EDIT_NUMEFEC2, m_strNumEfec2);
	DDV_MaxChars(pDX, m_strNumEfec2, 1);
	DDX_Text(pDX, IDC_EDIT_NUMEFEC3, m_strNumEfec3);
	DDV_MaxChars(pDX, m_strNumEfec3, 1);
	DDX_Text(pDX, IDC_EDIT_CUENTA, m_strCuenta);
	DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_EDIT_NOMBRE, m_strNombre);
	DDX_Text(pDX, IDC_EDIT_FCOBRO, m_strFCobro);
	DDV_MaxChars(pDX, m_strFCobro, 1);
	DDX_Text(pDX, IDC_EDIT_DESFCOBRO, m_strDesFCobro);
	DDX_Text(pDX, IDC_IMPORTE, m_strImporte);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_LIBRA, m_fechaLibra);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_VENCI, m_fechaVenci);
	DDX_DateTimeCtrl(pDX, IDC_FECHA_RECEP, m_fechaRecep);
	DDX_Text(pDX, IDC_REMESA, m_strRemesa);
	DDV_MaxChars(pDX, m_strRemesa, 10);
	DDX_Text(pDX, IDC_CTA_TESORERIA, m_strCtaTesoreria);
	DDV_MaxChars(pDX, m_strCtaTesoreria, 9);
	DDX_Text(pDX, IDC_EDIT_CENTRO, m_strCentro);
	DDV_MaxChars(pDX, m_strCentro, 3);
	DDX_Text(pDX, IDC_EDIT_NOMBRECENTRO, m_strDesCentro);
	DDX_Text(pDX, IDC_OBSERVACIONES, m_strObservaciones);
	DDV_MaxChars(pDX, m_strObservaciones, 35);

	DDX_Control(pDX, IDC_EDIT_NUMEFEC2, m_cNumEfec2);
	DDX_Control(pDX, IDC_EDIT_NUMEFEC3, m_cNumEfec3);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgGestionCobros, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_NUMFAC, OnEnKillfocusEditNumfac)
	ON_BN_CLICKED(ID_BUSCAR, OnBnClickedBuscar)
	ON_EN_KILLFOCUS(IDC_EDIT_NUMEFEC3, OnEnKillfocusEditNumefec3)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_BTN_NUMEFEC, OnBnClickedBtnNumefec)
	ON_BN_CLICKED(IDC_BTN_CUENTA, OnBnClickedBtnCuenta)
	ON_BN_CLICKED(IDC_BTN_FCOBRO, OnBnClickedBtnFcobro)
	ON_BN_CLICKED(IDC_BTN_CENTRO, OnBnClickedBtnCentro)
	ON_EN_KILLFOCUS(IDC_EDIT_FCOBRO, OnEnKillfocusEditFcobro)
	ON_EN_KILLFOCUS(IDC_EDIT_CUENTA, OnEnKillfocusEditCuenta)
	ON_EN_KILLFOCUS(IDC_EDIT_CENTRO, OnEnKillfocusEditCentro)
	ON_EN_KILLFOCUS(IDC_EDIT_NUMEFEC2, OnEnKillfocusEditNumefec2)
	ON_EN_KILLFOCUS(IDC_IMPORTE, OnEnKillfocusImporte)
	ON_BN_CLICKED(ID_LIMPIAR, OnBnClickedLimpiar)
	ON_BN_CLICKED(ID_DESGLOSAR, OnBnClickedDesglosar)
END_MESSAGE_MAP()

/******************************************************************************************/
// Controladores de mensajes de CDlgGestionCobros
/******************************************************************************************/

/******************************************************************************************/
BOOL CDlgGestionCobros::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_iTipo == NUEVO)
	{
		SetWindowText("Creación de cobro");
		m_cNumEfec2.SetReadOnly();
		m_cNumEfec3.SetReadOnly();
		GetDlgItem(ID_BTN_NUMEFEC)->ShowWindow(SW_HIDE);
		GetDlgItem(ID_DESGLOSAR)->ShowWindow(SW_HIDE);
	}
	else if (m_iTipo == MODIFICACION)
	{
		SetWindowText("Modificación de cobro");
		GetDlgItem(ID_DESGLOSAR)->EnableWindow(FALSE);
	}

	// Se establece la Base de Datos para los diálogos de búsquedas
	m_dlgBusquedaFacturas.SetConexion(m_db);
	m_dlgBusquedaCobros.SetConexion(m_db);
	m_dlgBusquedaClientes.SetConexion(m_db);
	m_dlgBusquedaFCobro.SetConexion(m_db);
	m_dlgBusquedaCentros.SetConexion(m_db);

	GetDlgItem(IDC_EDIT_CUENTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FCOBRO)->EnableWindow(FALSE);
	GetDlgItem(IDC_IMPORTE)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_LIBRA)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_VENCI)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_RECEP)->EnableWindow(FALSE);
	GetDlgItem(IDC_REMESA)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTA_TESORERIA)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CENTRO)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBSERVACIONES)->EnableWindow(FALSE);

	return FALSE;
}

/******************************************************************************************/
void CDlgGestionCobros::OnEnKillfocusEditNumfac()
{
	CString strNumFacOld = m_strNumFac;

	GetDlgItem(IDC_EDIT_NUMFAC)->GetWindowText(m_strNumFac);

	if (m_strNumFac == strNumFacOld)
		return;

	if (!m_strNumFac.IsEmpty())
	{
		// Si la factura no existe salimos, si no se busca el cobro
		if (!BuscaFactura())
		{
			AfxMessageBox(IDC_FACTURA_NO_EXISTS);
			m_strNumFac = strNumFacOld;
			GetDlgItem(IDC_EDIT_NUMFAC)->SetWindowText(m_strNumFac);
		}
		else
		{
			if (m_iTipo == NUEVO)
				BuscaSiguienteCobro();
			else if (m_iTipo == MODIFICACION)
				BuscaCobro();
		}
	}
	else
		LimpiaVentana(TRUE);

}

/******************************************************************************************/
void CDlgGestionCobros::OnBnClickedBuscar()
{
	INT_PTR status;

	CString strNumFacOld = m_strNumFac;

	m_dlgBusquedaFacturas.SetTipo(CDialogBusqueda::FACTURAS);
	status = m_dlgBusquedaFacturas.DoModal();
	if (status == IDOK)
	{
		LimpiaVentana(TRUE);

		m_strNumFac = m_dlgBusquedaFacturas.GetCodigo();

		/* Busca la factura y el cobro la muestra */
		if (!m_strNumFac.IsEmpty())
		{
			if (BuscaFactura())
			{
				if (m_iTipo == NUEVO)
					BuscaSiguienteCobro();
				else if (m_iTipo == MODIFICACION)
				{	
					if (!BuscaCobro())		
						m_strNumFac = strNumFacOld;
				}
			}
		}

		GetDlgItem(IDC_EDIT_NUMFAC)->SetWindowText(m_strNumFac);
	}
}

/******************************************************************************************/
void CDlgGestionCobros::OnEnKillfocusEditNumefec2()
{
	CString strOldNumEfec2 = m_strNumEfec2;

	GetDlgItem(IDC_EDIT_NUMEFEC2)->GetWindowText(m_strNumEfec2);
	GetDlgItem(IDC_EDIT_NUMEFEC3)->GetWindowText(m_strNumEfec3);

    if (m_strNumEfec2 == strOldNumEfec2)
		return;

	if (!m_strNumEfec2.IsEmpty() && !m_strNumEfec3.IsEmpty())
	{
		if (!(BuscaCobroEfec()))
		{
			AfxMessageBox(IDC_COBRO_NO_EXISTS);
			LimpiaVentana(FALSE);
		}
	}
}

/******************************************************************************************/
void CDlgGestionCobros::OnEnKillfocusEditNumefec3()
{
	CString strOldNumEfec3 = m_strNumEfec3;

	GetDlgItem(IDC_EDIT_NUMEFEC2)->GetWindowText(m_strNumEfec2);
	GetDlgItem(IDC_EDIT_NUMEFEC3)->GetWindowText(m_strNumEfec3);

    if (m_strNumEfec3 == strOldNumEfec3)
		return;

	if (!m_strNumEfec2.IsEmpty() && !m_strNumEfec3.IsEmpty())
	{
		if (!(BuscaCobroEfec()))
		{
			AfxMessageBox(IDC_COBRO_NO_EXISTS);
			LimpiaVentana(FALSE);
		}
	}
}

/******************************************************************************************/
void CDlgGestionCobros::OnBnClickedBtnNumefec()
{
	INT_PTR status;

	m_dlgBusquedaCobros.SetTipo(CDialogBusqueda::COBROS);
	m_dlgBusquedaCobros.SetFactura(m_strNumFac);
	status = m_dlgBusquedaCobros.DoModal();
	if (status == IDOK)
	{
		LimpiaVentana(FALSE);

		CString strNumEfec = m_dlgBusquedaCobros.GetCodigo();

		if (!strNumEfec.IsEmpty())
		{
			m_strNumEfec = strNumEfec.Left(strNumEfec.Find("/"));
			m_strNumEfec2 = strNumEfec.Mid(strNumEfec.Find("/")+1, 1);
			m_strNumEfec3 = strNumEfec.Right(strNumEfec.GetLength() - strNumEfec.ReverseFind('/') - 1);

			GetDlgItem(IDC_EDIT_NUMEFEC)->SetWindowText(m_strNumEfec);
			GetDlgItem(IDC_EDIT_NUMEFEC2)->SetWindowText(m_strNumEfec2);
			GetDlgItem(IDC_EDIT_NUMEFEC3)->SetWindowText(m_strNumEfec3);

			if (!(BuscaCobroEfec()))
			{
				AfxMessageBox(IDC_COBRO_NO_EXISTS);
				LimpiaVentana(FALSE);
			}
		}
	}
}

/******************************************************************************************/
void CDlgGestionCobros::OnEnKillfocusImporte()
{
	CString strImporteAux;

	GetDlgItem(IDC_IMPORTE)->GetWindowText(strImporteAux);
	if (!CompruebaNumero(strImporteAux))
	{
		AfxMessageBox(IDC_NO_NUMBER);
		GetDlgItem(IDC_IMPORTE)->SetWindowText(m_strImporte);
		GetDlgItem(IDC_IMPORTE)->SetFocus();
	}
	else
		m_strImporte = strImporteAux;

	GetDlgItem(IDC_IMPORTE)->SetWindowText(m_strImporte);
}

/******************************************************************************************/
void CDlgGestionCobros::OnEnKillfocusEditCuenta()
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
	}
	else
	{
		m_strNombre.Empty();
		GetDlgItem(IDC_EDIT_NOMBRE)->SetWindowText(m_strNombre);
	}

}

/******************************************************************************************/
void CDlgGestionCobros::OnBnClickedBtnCuenta()
{
	INT_PTR status;

	m_dlgBusquedaClientes.SetTipo(CDialogBusqueda::CLIENTES);
	status = m_dlgBusquedaClientes.DoModal();
	if (status == IDOK)
	{
		m_strCuenta = m_dlgBusquedaClientes.GetCodigo();

		/* Busca el artículo y lo escribe en el listCtrl */
		if (!m_strCuenta.IsEmpty())
			BuscaCliente();
	}
}

/******************************************************************************************/
void CDlgGestionCobros::OnEnKillfocusEditFcobro()
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
void CDlgGestionCobros::OnBnClickedBtnFcobro()
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
void CDlgGestionCobros::OnEnKillfocusEditCentro()
{
	CString strCentroOld = m_strCentro;

	GetDlgItem(IDC_EDIT_CENTRO)->GetWindowText(m_strCentro);

	if (!m_strCentro.IsEmpty())
	{
		// Si el Centro no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCentro())
		{
			AfxMessageBox(IDC_CENTRO_NO_EXISTS);
			m_strCentro = strCentroOld;
			GetDlgItem(IDC_EDIT_CENTRO)->SetWindowText(m_strCentro);
		}
	}
	else
	{
		m_strDesCentro.Empty();
		GetDlgItem(IDC_EDIT_NOMBRECENTRO)->SetWindowText(m_strDesCentro);
	}
}

/******************************************************************************************/
void CDlgGestionCobros::OnBnClickedBtnCentro()
{
	INT_PTR status;

	m_dlgBusquedaCentros.SetTipo(CDialogBusqueda::CENTROS);
	status = m_dlgBusquedaCentros.DoModal();
	if (status == IDOK)
	{
		m_strCentro = m_dlgBusquedaCentros.GetCodigo();
		m_strDesCentro = m_dlgBusquedaCentros.GetDescripcion();
	}

	GetDlgItem(IDC_EDIT_CENTRO)->SetWindowText(m_strCentro);
	GetDlgItem(IDC_EDIT_NOMBRECENTRO)->SetWindowText(m_strDesCentro);
}

/******************************************************************************************/
void CDlgGestionCobros::OnBnClickedOk()
{	
	HRESULT hErr = S_OK;

	UpdateData();

	RellenaCobro();

	if (m_iTipo == NUEVO)
		hErr = m_rsCobros.Insert();
	else if (m_iTipo == MODIFICACION)
		hErr = m_rsCobros.UpdateCobros();

	LimpiaVentana(TRUE);
	//OnOK();
}

/******************************************************************************************/
void CDlgGestionCobros::OnBnClickedLimpiar()
{
	LimpiaVentana(TRUE);
}

/******************************************************************************************/
void CDlgGestionCobros::OnBnClickedDesglosar()
{
	CDlgDesglose dlgDesglose;
	dlgDesglose.SetConexion(m_db);
	dlgDesglose.SetCobroPadre(&m_rsCobros);
	dlgDesglose.DoModal();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgGestionCobros::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsFactura.m_pDatabase = db;
	m_rsCobros.m_pDatabase = db;
}

/******************************************************************************************/
void CDlgGestionCobros::SetTipo(int iTipo)
{
	m_iTipo = iTipo;
}

/******************************************************************************************/
BOOL CDlgGestionCobros::BuscaFactura()
{
	BOOL bExists = FALSE;
	//CFacturas rsFactura(m_db);

	m_rsFactura.m_strFilter = "NUMFAC LIKE '" + m_strNumFac + "'";
	if (!m_rsFactura.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la factura existe se rellenan sus campos 
	if (!m_rsFactura.m_NUMFAC.IsEmpty())
		bExists = TRUE;

	m_rsFactura.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgGestionCobros::BuscaCobro()
{
	BOOL bExists = FALSE;

	LimpiaVentana(FALSE);

	m_rsCobros.m_strFilter = "NUMFAC LIKE '" + m_strNumFac + "'";
	if (!m_rsCobros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si la factura existe se rellenan sus campos 
 	if (m_rsCobros.m_NUMFAC.IsEmpty())
	{
		AfxMessageBox(IDC_COBRO_NO_EXISTS);
		bExists = FALSE;
	}
	else
	{
		m_strNumEfec = m_rsCobros.m_NUMFAC.Trim();
		bExists = TRUE;
	}

	m_rsCobros.Close();

	GetDlgItem(IDC_EDIT_NUMEFEC)->SetWindowText(m_strNumEfec);

	return bExists;
}

/******************************************************************************************/
BOOL CDlgGestionCobros::BuscaCobroEfec()
{
	BOOL bExists = FALSE;

	GetDlgItem(IDC_EDIT_NUMEFEC2)->GetWindowText(m_strNumEfec2);
	GetDlgItem(IDC_EDIT_NUMEFEC3)->GetWindowText(m_strNumEfec3);

	m_rsCobros.m_NUMEFEC.Empty();

	CString strNumEfec = m_strNumEfec + "/" + m_strNumEfec2 + "/" + m_strNumEfec3;

	m_rsCobros.m_strFilter = "NUMEFEC LIKE '" + strNumEfec + "'";
	if (!m_rsCobros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}	

	if (!m_rsCobros.m_NUMEFEC.IsEmpty())
	{
		//m_strNumEfec2 = strNumEfec.Mid(strNumEfec.Find("/")+1, 1);
		//m_strNumEfec3 = strNumEfec.Right(strNumEfec.GetLength() - strNumEfec.ReverseFind('/') - 1);

		m_strEstado = m_rsCobros.m_ESTADO.Trim();
		BuscaDesEstado();
		m_strCuenta = m_rsCobros.m_CUENTA.Trim();
		BuscaCliente();

		m_strFCobro = m_rsCobros.m_FCOBRO.Trim();
		BuscaFCobro();

		m_strImporte.Format("%g", m_rsCobros.m_EUROS);
		m_fechaLibra = m_rsCobros.m_FECHLIBRA;
		m_fechaVenci = m_rsCobros.m_FECHA;
		m_fechaRecep = m_rsCobros.m_FRECEP;
		m_strRemesa = m_rsCobros.m_NREMESA.Trim();
		m_strCtaTesoreria = m_rsCobros.m_BANCO.Trim();

		m_strCentro = m_rsCobros.m_CENTRO.Trim();
		BuscaCentro();
		m_strObservaciones = m_rsCobros.m_OBSCOBRO.Trim();

		GetDlgItem(IDC_EDIT_CUENTA)->EnableWindow();
		GetDlgItem(IDC_EDIT_FCOBRO)->EnableWindow();
		GetDlgItem(IDC_IMPORTE)->EnableWindow();
		GetDlgItem(IDC_FECHA_LIBRA)->EnableWindow();
		GetDlgItem(IDC_FECHA_VENCI)->EnableWindow();
		GetDlgItem(IDC_FECHA_RECEP)->EnableWindow();
		GetDlgItem(IDC_REMESA)->EnableWindow();
		GetDlgItem(IDC_CTA_TESORERIA)->EnableWindow();
		GetDlgItem(IDC_EDIT_CENTRO)->EnableWindow();
		GetDlgItem(IDC_OBSERVACIONES)->EnableWindow();

		GetDlgItem(ID_DESGLOSAR)->EnableWindow();

		bExists = TRUE;
	}

	m_rsCobros.Close();

	UpdateData(FALSE);

	return bExists;
}

/******************************************************************************************/
void CDlgGestionCobros::BuscaSiguienteCobro()
{
	m_rsCobros.m_NUMFAC.Empty();

	m_rsCobros.m_strFilter = "NUMFAC LIKE '" + m_strNumFac + "'";
	m_rsCobros.m_strSort = "NUMEFEC";
	if (!m_rsCobros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	m_strNumEfec = m_strNumFac.Trim();
	m_strNumEfec3 = "1";

	// Si no hay ningún cobro para esa factura, será el primero
	if (m_rsCobros.m_NUMFAC.IsEmpty())
	{
		m_strNumEfec2 = "1";		
	}
	else
	{
		// Me voy al último elemento y creo el nuevo número efectivo
		m_rsCobros.MoveLast();

		CString strNumEfec = m_rsCobros.m_NUMEFEC.Trim();
		CString strNumEfec2 = strNumEfec.Mid(strNumEfec.Find("/")+1, 1);
		m_strNumEfec2.Format("%d", atoi(strNumEfec2) + 1);
		
	}

	m_rsCobros.Close();

	/*GetDlgItem(IDC_EDIT_NUMEFEC)->SetWindowText(m_strNumEfec);
	GetDlgItem(IDC_EDIT_NUMEFEC2)->SetWindowText(m_strNumEfec2);
	GetDlgItem(IDC_EDIT_NUMEFEC3)->SetWindowText(m_strNumEfec3);*/

	m_rsCobros.m_NUMFAC = m_strNumFac.Trim();
	m_rsCobros.m_NUMEFEC = m_strNumEfec.Trim() + "/" + m_strNumEfec2.Trim() + "/" + m_strNumEfec3.Trim();
	m_rsCobros.m_ESTADO = COBRO_PENDIENTE;

	GetDlgItem(IDC_EDIT_CUENTA)->EnableWindow();
	GetDlgItem(IDC_EDIT_FCOBRO)->EnableWindow();
	GetDlgItem(IDC_IMPORTE)->EnableWindow();
	GetDlgItem(IDC_FECHA_LIBRA)->EnableWindow();
	GetDlgItem(IDC_FECHA_VENCI)->EnableWindow();
	GetDlgItem(IDC_FECHA_RECEP)->EnableWindow();
	GetDlgItem(IDC_REMESA)->EnableWindow();
	GetDlgItem(IDC_CTA_TESORERIA)->EnableWindow();
	GetDlgItem(IDC_EDIT_CENTRO)->EnableWindow();
	GetDlgItem(IDC_OBSERVACIONES)->EnableWindow();

	m_strDesEstado = TXT_COBRO_PENDIENTE;
	//GetDlgItem(IDC_ESTADO)->SetWindowText(m_strDesEstado);

	m_fechaLibra = m_rsFactura.m_FECHFAC;
	//GetDlgItem(IDC_FECHA_LIBRA)->SetWindowText(m_fechaLibra.Format("%d/%m/%Y"));

	UpdateData(FALSE);
}

/******************************************************************************************/
void CDlgGestionCobros::LimpiaVentana(BOOL bNumFac)
{
	if (bNumFac)
	{
		m_strNumFac.Empty();
		m_strNumEfec.Empty();
	}

	m_strEstado.Empty();
	m_strDesEstado.Empty();
	m_strNumEfec2.Empty();
	m_strNumEfec3.Empty();
	m_strCuenta.Empty();
	m_strNombre.Empty();
	m_strFCobro.Empty();
	m_strDesFCobro.Empty();
	m_strImporte.Empty();
	m_fechaLibra = NULL;
	m_fechaVenci = NULL;
	m_fechaRecep = NULL;
	m_strRemesa.Empty();
	m_strCtaTesoreria.Empty();
	m_strCentro.Empty();
	m_strDesCentro.Empty();
	m_strObservaciones.Empty();

	m_rsCobros.m_NUMEFEC.Empty();;
	m_rsCobros.m_FCOBRO.Empty();
	m_rsCobros.m_NUMFAC.Empty();
	m_rsCobros.m_CUENTA.Empty();
	m_rsCobros.m_NREMESA.Empty();
	m_rsCobros.m_ESTADO.Empty();
	m_rsCobros.m_BANCO.Empty();
	m_rsCobros.m_FECHLIBRA = NULL;
	m_rsCobros.m_FECHA = NULL;
	m_rsCobros.m_FRECEP = NULL;
	m_rsCobros.m_CENTRO.Empty();;
	m_rsCobros.m_OBSCOBRO.Empty();;
	m_rsCobros.m_EUROS = 0.0;

	GetDlgItem(IDC_EDIT_CUENTA)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FCOBRO)->EnableWindow(FALSE);
	GetDlgItem(IDC_IMPORTE)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_LIBRA)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_VENCI)->EnableWindow(FALSE);
	GetDlgItem(IDC_FECHA_RECEP)->EnableWindow(FALSE);
	GetDlgItem(IDC_REMESA)->EnableWindow(FALSE);
	GetDlgItem(IDC_CTA_TESORERIA)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CENTRO)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBSERVACIONES)->EnableWindow(FALSE);

	m_dlgBusquedaCobros.InicializarListas();

	if (m_iTipo == MODIFICACION)
		GetDlgItem(ID_DESGLOSAR)->EnableWindow(FALSE);

	UpdateData(FALSE);
}

/******************************************************************************************/
BOOL CDlgGestionCobros::BuscaCliente()
{
	BOOL bExists = FALSE;

	CClientes rsClientes(m_db);

	rsClientes.m_strFilter = "CUENTA LIKE '" + m_strCuenta + "'";

	if (!rsClientes.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	if (!rsClientes.m_CUENTA.IsEmpty())
	{
		m_strNombre = rsClientes.m_NOMBRE.Trim();
		GetDlgItem(IDC_EDIT_CUENTA)->SetWindowText(m_strCuenta);
		GetDlgItem(IDC_EDIT_NOMBRE)->SetWindowText(m_strNombre);
		bExists = TRUE;
	}

	rsClientes.Close();

	return bExists;
}

/******************************************************************************************/
BOOL CDlgGestionCobros::BuscaFCobro()
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
BOOL CDlgGestionCobros::BuscaCentro()
{
	BOOL bExists = FALSE;
	CCentros rsCentros(m_db);

	rsCentros.m_strFilter = "CCENTRO LIKE '" + m_strCentro + "'";
	if (!rsCentros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	// Si el centro existe se rellena la descripción 
	if (!rsCentros.m_CCENTRO.IsEmpty())
	{
		m_strDesCentro = /*m_rsProforma.m_CENTRO.Trim() =*/ rsCentros.m_DCENTRO.Trim();
		bExists = TRUE;
	}

	rsCentros.Close();

	GetDlgItem(IDC_EDIT_CENTRO)->SetWindowText(m_strCentro);
	GetDlgItem(IDC_EDIT_NOMBRECENTRO)->SetWindowText(m_strDesCentro);

	return bExists;
}

/******************************************************************************************/
void CDlgGestionCobros::BuscaDesEstado()
{
	CHAR cEstado = m_strEstado.GetAt(0);

	switch (cEstado)
	{
		case '0': m_strDesEstado = TXT_COBRO_PENDIENTE;
				  break;
		case '1': m_strDesEstado = TXT_PENDIENTE_REMESAR;
				  break;
		case '2': m_strDesEstado = TXT_SELEC_REMESAR;
				  break;
		case '3': m_strDesEstado = TXT_DESCONTADO;
				  break;
		case '4': m_strDesEstado = TXT_GASTOS_CONT;
				  break;
		case '5': m_strDesEstado = TXT_IMPAGADO;
				  break;
		case '6': m_strDesEstado = TXT_COBRADO;
				  break;
	}
}

/******************************************************************************************/
void CDlgGestionCobros::RellenaCobro()
{
	if (m_iTipo == NUEVO)
		m_rsCobros.m_ESTADO = COBRO_PENDIENTE;

	m_rsCobros.m_NUMFAC = m_strNumFac;
	m_rsCobros.m_NUMEFEC = m_strNumEfec + "/" + m_strNumEfec2 + "/" + m_strNumEfec3;
	m_rsCobros.m_CUENTA = m_strCuenta;
	m_rsCobros.m_FCOBRO = m_strFCobro;
	m_rsCobros.m_EUROS = atof(m_strImporte);
	m_rsCobros.m_FECHLIBRA = m_fechaLibra;
	m_rsCobros.m_FECHA = m_fechaVenci;
	m_rsCobros.m_FRECEP = m_fechaRecep;
	m_rsCobros.m_NREMESA = m_strRemesa;
	m_rsCobros.m_CENTRO = m_strCentro;
	m_rsCobros.m_BANCO = m_strCtaTesoreria;
	m_rsCobros.m_OBSCOBRO = m_strObservaciones;
}

/************************************************************************************************************/
/** Comprueba que en la cadena no hay mas que números y como mucho un punto                                **/    
/************************************************************************************************************/
BOOL CDlgGestionCobros::CompruebaNumero(CString strNumero)
{
	BOOL bPunto = FALSE; 

	for (int i = 0; i<strNumero.GetLength(); i++)
	{
		if (strNumero.GetAt(i) < '0' || strNumero.GetAt(i) > '9')
		{ 
			if (strNumero.GetAt(i)== '.' && bPunto == FALSE)
				bPunto = TRUE;
			else
				return FALSE;
		}
	}

	return TRUE;
}




