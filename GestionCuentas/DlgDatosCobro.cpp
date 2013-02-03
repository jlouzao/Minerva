// DlgDatosCobro.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgDatosCobro.h"
#include ".\dlgdatoscobro.h"


// Cuadro de diálogo de CDlgDatosCobro

IMPLEMENT_DYNAMIC(CDlgDatosCobro, CDialog)
CDlgDatosCobro::CDlgDatosCobro(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDatosCobro::IDD, pParent)
	, m_strDivisa(_T(""))
	, m_strCobro(_T(""))
	, m_strDesDivisa(_T(""))
	, m_strDesCobro(_T(""))
	, m_strVencimientos(_T(""))
	, m_strPrimer(_T(""))
	, m_strDiasEntre(_T(""))
	, m_strPago1(_T(""))
	, m_strPago2(_T(""))
	, m_strPago3(_T(""))
	, m_strIniDia(_T(""))
	, m_strIniMes(_T(""))
	, m_strFinDia(_T(""))
	, m_strFinMes(_T(""))
	, m_strNSeguro(_T(""))
	, m_strSeguro(_T(""))
	, m_strDesSeguro(_T(""))
	, m_strRiesgo(_T(""))
	, m_strRiesgoAct(_T(""))
	, m_strCuenta1(_T(""))
	, m_strCuenta2(_T(""))
	, m_strCuenta3(_T(""))
	, m_strCuenta4(_T(""))
	, m_strEntidad(_T(""))
	, m_strIBAN(_T(""))
{
}

CDlgDatosCobro::~CDlgDatosCobro()
{
}

void CDlgDatosCobro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DIVISA, m_ctrlDivisa);
	DDX_Text(pDX, IDC_DIVISA, m_strDivisa);
	DDV_MaxChars(pDX, m_strDivisa, 3);
	DDX_Control(pDX, IDC_COBRO, m_ctrlCobro);
	DDX_Text(pDX, IDC_COBRO, m_strCobro);
	DDV_MaxChars(pDX, m_strCobro, 1);
	DDX_Text(pDX, IDC_DES_DIVISA, m_strDesDivisa);
	DDX_Text(pDX, IDC_DES_COBRO, m_strDesCobro);
	DDX_Text(pDX, IDC_VENCIMIENTOS, m_strVencimientos);
	DDX_Text(pDX, IDC_PRIMER, m_strPrimer);
	DDX_Text(pDX, IDC_DIASENTRE, m_strDiasEntre);
	DDX_Text(pDX, IDC_PAGO1, m_strPago1);
	DDX_Text(pDX, IDC_PAGO2, m_strPago2);
	DDX_Text(pDX, IDC_PAGO3, m_strPago3);
	DDX_Text(pDX, IDC_INI_DIA, m_strIniDia);
	DDX_Text(pDX, IDC_INI_MES, m_strIniMes);
	DDX_Text(pDX, IDC_FIN_DIA, m_strFinDia);
	DDX_Text(pDX, IDC_FIN_MES, m_strFinMes);
	DDX_Text(pDX, IDC_NSEGURO, m_strNSeguro);
	DDV_MaxChars(pDX, m_strNSeguro, 10);
	DDX_Control(pDX, IDC_SEGURO, m_ctrlSeguro);
	DDX_Text(pDX, IDC_SEGURO, m_strSeguro);
	DDV_MaxChars(pDX, m_strSeguro, 3);
	DDX_Text(pDX, IDC_DES_SEGURO, m_strDesSeguro);
	DDX_Text(pDX, IDC_RIESGO, m_strRiesgo);
	DDX_Text(pDX, IDC_RIESGO_ACT, m_strRiesgoAct);
	DDX_Text(pDX, IDC_CUENTA1, m_strCuenta1);
	DDV_MaxChars(pDX, m_strCuenta1, 4);
	DDX_Text(pDX, IDC_CUENTA2, m_strCuenta2);
	DDV_MaxChars(pDX, m_strCuenta2, 4);
	DDX_Text(pDX, IDC_CUENTA3, m_strCuenta3);
	DDV_MaxChars(pDX, m_strCuenta3, 2);
	DDX_Text(pDX, IDC_CUENTA4, m_strCuenta4);
	DDV_MaxChars(pDX, m_strCuenta4, 10);
	DDX_Text(pDX, IDC_ENTIDAD, m_strEntidad);
	DDV_MaxChars(pDX, m_strEntidad, 35);
	DDX_Text(pDX, IDC_IBAN, m_strIBAN);
	DDV_MaxChars(pDX, m_strIBAN, 24);
	DDX_Control(pDX, IDC_INI_DIA, m_ctrlIniDia);
	DDX_Control(pDX, IDC_INI_MES, m_ctrlIniMes);
	DDX_Control(pDX, IDC_FIN_DIA, m_ctrlFinDia);
	DDX_Control(pDX, IDC_FIN_MES, m_ctrlFinMes);
	DDX_Control(pDX, IDC_RIESGO, m_ctrlRiesgo);
	DDX_Control(pDX, IDC_RIESGO_ACT, m_ctrlRiesgoAct);
}


BEGIN_MESSAGE_MAP(CDlgDatosCobro, CDialog)
	ON_BN_CLICKED(IDC_BOTON_DIVISA, OnBnClickedBotonDivisa)
	ON_BN_CLICKED(IDC_BOTON_FORMA_COBRO, OnBnClickedBotonFormaCobro)
	ON_BN_CLICKED(IDC_BOTON_SEGUROS, OnBnClickedBotonSeguros)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_DIVISA, OnEnKillfocusDivisa)
	ON_EN_KILLFOCUS(IDC_COBRO, OnEnKillfocusCobro)
	ON_EN_KILLFOCUS(IDC_SEGURO, OnEnKillfocusSeguro)
	ON_EN_KILLFOCUS(IDC_INI_DIA, OnEnKillfocusIniDia)
	ON_EN_KILLFOCUS(IDC_INI_MES, OnEnKillfocusIniMes)
	ON_EN_KILLFOCUS(IDC_FIN_DIA, OnEnKillfocusFinDia)
	ON_EN_KILLFOCUS(IDC_FIN_MES, OnEnKillfocusFinMes)
	ON_EN_KILLFOCUS(IDC_RIESGO, OnEnKillfocusRiesgo)
	ON_EN_KILLFOCUS(IDC_RIESGO_ACT, OnEnKillfocusRiesgoAct)
END_MESSAGE_MAP()

BOOL CDlgDatosCobro::OnInitDialog()
{
	CDialog::OnInitDialog();

	/******* CARGA LAS BUSQUEDAS PARA AHORRAR TIEMPO ********/
	m_dlgBusquedaCobro.SetConexion(m_db); 
	m_dlgBusquedaSeguro.SetConexion(m_db);
	m_dlgBusquedaDivisa.SetConexion(m_db);
	/********************************************************/
	if (m_bUpdate == TRUE)
	{
		m_strDivisa=m_rsCliente->m_DIVISA.TrimRight();
		m_strCobro=m_rsCliente->m_FCOBRO;
		m_strVencimientos.Format("%.0f",m_rsCliente->m_NCOBROS);
		m_strPrimer.Format("%.0f",m_rsCliente->m_VTO1);
		m_strDiasEntre.Format("%.0f",m_rsCliente->m_DVTO);
		m_strPago1.Format("%.0f",m_rsCliente->m_DIA1);
		m_strPago2.Format("%.0f",m_rsCliente->m_DIA2);
		m_strPago3.Format("%.0f",m_rsCliente->m_DIA3);
		m_strIniDia.Format("%.0f",m_rsCliente->m_DIVAC);
		m_strIniMes.Format("%.0f",m_rsCliente->m_MIVAC);
		m_strFinDia.Format("%.0f",m_rsCliente->m_DFVAC);
		m_strFinMes.Format("%.0f",m_rsCliente->m_MFVAC);
		m_strNSeguro=m_rsCliente->m_NUMCOMPA;
		m_strSeguro=m_rsCliente->m_SEGURO;
		m_strRiesgo.Format("%.2f",m_rsCliente->m_ERIESCLI);
		m_strRiesgoAct.Format("%.2f",m_rsCliente->m_ERIACCLI);
		m_strCuenta1=m_rsCliente->m_CC1.TrimRight();
		m_strCuenta2=m_rsCliente->m_CC2.TrimRight();
		m_strCuenta3=m_rsCliente->m_DC.TrimRight();
		m_strCuenta4=m_rsCliente->m_CTACORR.TrimRight();
		m_strEntidad=m_rsCliente->m_NOMBCO.TrimRight();
		m_strIBAN=m_rsCliente->m_IBAN.TrimRight();
		//////////////////////////////////////////
		EncuentraSeguro(m_strSeguro);
		EncuentraDivisa(m_strDivisa);
		EncuentraCobro(m_strCobro.Trim());
		//////////////////////////////////////////
		//m_strDesDivisa;
		//m_strDesCobro;
		//m_strDesSeguro

		UpdateData(FALSE);
	}
	return FALSE;
}
/****************************************************************************************************/
/***                                        FUNCIONES
/****************************************************************************************************/
void CDlgDatosCobro::SetCliente(CClientes *rsCliente )
{
	m_rsCliente=rsCliente;	
}
/****************************************************************************************************/
void CDlgDatosCobro::SetUpdate(BOOL bUpdate)
{
	m_bUpdate=bUpdate;	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
/////         realiza la conexion con las tablas
///////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgDatosCobro::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsCliente->m_pDatabase=m_db;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
///			             CREA UN DIALOGO DE BUSQUEDA DE LA TABLA DIVISA
//////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgDatosCobro::OnBnClickedBotonDivisa()
{
	INT_PTR Estado;
	m_dlgBusquedaDivisa.SetTipo(CDialogBusqueda::DIVISAS);
	Estado=m_dlgBusquedaDivisa.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strDivisa=m_dlgBusquedaDivisa.GetCodigo();
	GetDlgItem(IDC_DIVISA)->SetWindowText(m_strDivisa);
	m_strDesDivisa=m_dlgBusquedaDivisa.GetDescripcion();
	GetDlgItem(IDC_DES_DIVISA)->SetWindowText(m_strDesDivisa);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
///			         CREA UN DIALOGO DE BUSQUEDA DE LA TABLA FORMA DE PAGO
//////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgDatosCobro::OnBnClickedBotonFormaCobro()
{
	INT_PTR Estado;
	m_dlgBusquedaCobro.SetTipo(CDialogBusqueda::FPAGCOB);
	Estado=m_dlgBusquedaCobro.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strCobro=m_dlgBusquedaCobro.GetCodigo();
	GetDlgItem(IDC_COBRO)->SetWindowText(m_strCobro);
	m_strDesCobro=m_dlgBusquedaCobro.GetDescripcion();
	GetDlgItem(IDC_DES_COBRO)->SetWindowText(m_strDesCobro);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
///			             CREA UN DIALOGO DE BUSQUEDA DE LA TABLA SEGUROS
//////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgDatosCobro::OnBnClickedBotonSeguros()
{
	INT_PTR Estado;
	m_dlgBusquedaSeguro.SetTipo(CDialogBusqueda::SEGURO);
	Estado=m_dlgBusquedaSeguro.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strSeguro=m_dlgBusquedaSeguro.GetCodigo();
	GetDlgItem(IDC_SEGURO)->SetWindowText(m_strSeguro);
	m_strDesSeguro=m_dlgBusquedaSeguro.GetDescripcion();
	GetDlgItem(IDC_DES_SEGURO)->SetWindowText(m_strDesSeguro);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
///        AL HACER CLICK EN ACEPTAR, GUARDA LOS DATOS EN   m_rsClientes 
//////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgDatosCobro::OnBnClickedOk()
{
	UpdateData(TRUE);
	m_rsCliente->m_DIVISA=m_strDivisa.TrimRight();
	m_rsCliente->m_FCOBRO=m_strCobro.TrimRight();
	m_rsCliente->m_NCOBROS=atof(m_strVencimientos.TrimRight());
	m_rsCliente->m_VTO1=atof(m_strPrimer.TrimRight());
	m_rsCliente->m_DVTO=atof(m_strDiasEntre.TrimRight());
	m_rsCliente->m_DIA1=atof(m_strPago1.TrimRight());
	m_rsCliente->m_DIA2=atof(m_strPago2.TrimRight());
	m_rsCliente->m_DIA3=atof(m_strPago3.TrimRight());
	m_rsCliente->m_DIVAC=atof(m_strIniDia.TrimRight());
	m_rsCliente->m_MIVAC=atof(m_strIniMes.TrimRight());
	m_rsCliente->m_DFVAC=atof(m_strFinDia.TrimRight());
	m_rsCliente->m_MFVAC=atof(m_strFinMes.TrimRight());
	m_rsCliente->m_NUMCOMPA=m_strNSeguro.TrimRight();
	m_rsCliente->m_SEGURO=m_strSeguro.TrimRight();
	m_rsCliente->m_ERIACCLI=atof(m_strRiesgoAct.TrimRight());
	m_rsCliente->m_ERIESCLI=atof(m_strRiesgo.TrimRight());
	m_rsCliente->m_CC1=m_strCuenta1.TrimRight();
	m_rsCliente->m_CC2=m_strCuenta2.TrimRight();
	m_rsCliente->m_DC=m_strCuenta3.TrimRight();
	m_rsCliente->m_CTACORR=m_strCuenta4.TrimRight();
	m_rsCliente->m_NOMBCO=m_strEntidad.TrimRight();
	m_rsCliente->m_IBAN=m_strIBAN.TrimRight();
	OnOK();
}
/////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////
void CDlgDatosCobro::OnEnKillfocusRiesgo()
{
	CString strAux=m_strRiesgo;
	GetDlgItem(IDC_RIESGO)->GetWindowText(m_strRiesgo);
	if(ChequeaNumeros(m_strRiesgo)==FALSE)
	{
		m_strRiesgo=strAux;
		GetDlgItem(IDC_RIESGO)->SetWindowText(m_strRiesgo);
		m_ctrlRiesgo.SetFocus();
	}
}

void CDlgDatosCobro::OnEnKillfocusRiesgoAct()
{
	CString strAux=m_strRiesgoAct;
	GetDlgItem(IDC_RIESGO_ACT)->GetWindowText(m_strRiesgoAct);
	if(ChequeaNumeros(m_strRiesgoAct)==FALSE)
	{
		m_strRiesgoAct=strAux;
		GetDlgItem(IDC_RIESGO_ACT)->SetWindowText(m_strRiesgoAct);
		m_ctrlRiesgoAct.SetFocus();
	}
}

void CDlgDatosCobro::OnEnKillfocusDivisa()
{
	CString strAux=m_strDivisa;
	GetDlgItem(IDC_DIVISA)->GetWindowText(m_strDivisa);
	if (m_strDivisa.IsEmpty())
	{
		m_strDesDivisa="";
		GetDlgItem(IDC_DES_DIVISA)->SetWindowText(m_strDesDivisa);
		return;
	}
	if (m_strDivisa==strAux)
	{return;}
	if (EncuentraDivisa(m_strDivisa)==FALSE)
	{
		m_strDivisa=strAux;
		GetDlgItem(IDC_DIVISA)->SetWindowText(m_strDivisa);
	}
	else
	{GetDlgItem(IDC_DES_DIVISA)->SetWindowText(m_strDesDivisa);return;}
	m_ctrlDivisa.SetFocus();
}
/////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////
void CDlgDatosCobro::OnEnKillfocusCobro()
{
	CString strAux=m_strCobro;
	GetDlgItem(IDC_COBRO)->GetWindowText(m_strCobro);
	if (m_strCobro.IsEmpty())
	{
		m_strDesCobro="";
		GetDlgItem(IDC_DES_COBRO)->SetWindowText(m_strDesCobro);
		return;
	}
	if (m_strCobro==strAux)
	{return;}
	if (EncuentraCobro(m_strCobro)==FALSE)
	{
		m_strCobro=strAux;
		GetDlgItem(IDC_COBRO)->SetWindowText(m_strCobro);
	}
	else
	{GetDlgItem(IDC_DES_COBRO)->SetWindowText(m_strDesCobro);return;}
	m_ctrlCobro.SetFocus();
}
/////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////
void CDlgDatosCobro::OnEnKillfocusSeguro()
{
	CString strAux=m_strSeguro;
	GetDlgItem(IDC_SEGURO)->GetWindowText(m_strSeguro);
	if (m_strSeguro.IsEmpty())
	{
		m_strDesSeguro="";
		GetDlgItem(IDC_DES_SEGURO)->SetWindowText(m_strDesSeguro);
		return;
	}
	if (m_strSeguro==strAux)
	{return;}
	if (EncuentraSeguro(m_strSeguro)==FALSE)
	{
		m_strSeguro=strAux;
		GetDlgItem(IDC_SEGURO)->SetWindowText(m_strSeguro);
	}
	else
	{GetDlgItem(IDC_DES_SEGURO)->SetWindowText(m_strDesSeguro);return;}
	m_ctrlSeguro.SetFocus();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///		          SE BUSCA LA DESCRIPCION DEL CAMPO SEGURO EN LA TABLA CORRESPONDIENTE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CDlgDatosCobro::EncuentraSeguro(CString cadena)
{
	CSeguro rsSeguro(m_db);
	rsSeguro.m_strFilter="SEGURO LIKE '" + cadena + "'";
	if (!rsSeguro.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsSeguro.m_DSEGURO.IsEmpty())
	{
		rsSeguro.Close();
		return FALSE;
	}
	else
	{
		m_strDesSeguro=rsSeguro.m_DSEGURO.TrimRight();
		rsSeguro.Close();
		return TRUE;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///		         SE BUSCA LA DESCRIPCION DEL CAMPO DIVISA EN LA TABLA CORRESPONDIENTE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CDlgDatosCobro::EncuentraDivisa(CString cadena)
{
	CDivisas rsDivisa(m_db);
	rsDivisa.m_strFilter="DIVISA LIKE '" + cadena + "'";
	if (!rsDivisa.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsDivisa.m_DDIVISA.IsEmpty())
	{
		rsDivisa.Close();
		return FALSE;
	}
	else
	{
		m_strDesDivisa=rsDivisa.m_DDIVISA.TrimRight();
		rsDivisa.Close();
		return TRUE;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///		          SE BUSCA LA DESCRIPCION DEL CAMPO FORMA DE COBRO EN LA TABLA CORRESPONDIENTE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CDlgDatosCobro::EncuentraCobro(CString cadena)
{
	if (cadena.IsEmpty())
		return FALSE;
	CFPagCob rsCobro(m_db);
	rsCobro.m_strFilter="FCOBRO LIKE '" + cadena + "'";
	if (!rsCobro.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsCobro.m_DFCOBRO.IsEmpty())
	{
		rsCobro.Close();
		return FALSE;
	}
	else
	{
		m_strDesCobro=rsCobro.m_DFCOBRO.TrimRight();
		rsCobro.Close();
		return TRUE;
	}
}
/************************************************************************************************************/
/**		          COMPRUEBA QUE EL DIA NO ES SUPERIOR A 31 NI INFERIOR A 1                           
/************************************************************************************************************/
void CDlgDatosCobro::OnEnKillfocusIniDia()
{
	CString strAux=m_strIniDia;
	GetDlgItem(IDC_INI_DIA)->GetWindowText(m_strIniDia);
	if(atoi(m_strIniDia)>31||atoi(m_strIniDia)<1)
	{
		m_strIniDia=strAux;
		GetDlgItem(IDC_INI_DIA)->SetWindowText(m_strIniDia);
		AfxMessageBox(IDC_DIA_NOVALIDO);
		m_ctrlIniDia.SetFocus();
	}
}
void CDlgDatosCobro::OnEnKillfocusFinDia()
{
	CString strAux=m_strFinDia;
	GetDlgItem(IDC_FIN_DIA)->GetWindowText(m_strFinDia);
	if(atoi(m_strFinDia)>31||atoi(m_strFinDia)<1)
	{
		m_strFinDia=strAux;
		GetDlgItem(IDC_FIN_DIA)->SetWindowText(m_strFinDia);
		AfxMessageBox(IDC_DIA_NOVALIDO);
		m_ctrlFinDia.SetFocus();
	}
}
/************************************************************************************************************/
/**		          COMPRUEBA QUE EL MES NO ES SUPERIOR A 12 NI INFERIOR A 1                           
/************************************************************************************************************/
void CDlgDatosCobro::OnEnKillfocusIniMes()
{
	CString strAux=m_strIniMes;
	GetDlgItem(IDC_INI_MES)->GetWindowText(m_strIniMes);
	if(atoi(m_strIniMes)>12||atoi(m_strIniMes)<1)
	{
		m_strIniMes=strAux;
		GetDlgItem(IDC_INI_MES)->SetWindowText(m_strIniMes);
		AfxMessageBox(IDC_MES_NOVALIDO);
		m_ctrlIniMes.SetFocus();
	}
}
void CDlgDatosCobro::OnEnKillfocusFinMes()
{
	CString strAux=m_strFinMes;
	GetDlgItem(IDC_FIN_MES)->GetWindowText(m_strFinMes);
	if(atoi(m_strFinMes)>12||atoi(m_strFinMes)<1)
	{
		m_strFinMes=strAux;
		GetDlgItem(IDC_FIN_MES)->SetWindowText(m_strFinMes);
		AfxMessageBox(IDC_MES_NOVALIDO);
		m_ctrlFinMes.SetFocus();
	}
}
/************************************************************************************************************/
/**		          COMPRUEBA QUE EN LA CADENA NO HAY MAS QUE NUMEROS Y PUNTOS                        
/************************************************************************************************************/
BOOL CDlgDatosCobro::ChequeaNumeros(CString cadena)
{
	BOOL bPunto = FALSE;	
	for (int i = 0; i<cadena.GetLength(); i++)
	{
		if ((cadena.GetAt(i) < '0' || cadena.GetAt(i) > '9')) 	
		{				
			if (cadena.GetAt(i)== '.' && bPunto == FALSE)
				bPunto = TRUE;
			else
				return FALSE;
		}
	}
	return TRUE;
}