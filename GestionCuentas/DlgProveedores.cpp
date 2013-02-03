// DlgProveedores.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgProveedores.h"
#include ".\dlgproveedores.h"


#define NACIONAL 0
#define INTRACOMUNITARIO 1
#define TERCEROS 2

#define NO 1
#define SI 0

// Cuadro de diálogo de CDlgProveedores

IMPLEMENT_DYNAMIC(CDlgProveedores, CDialog)
CDlgProveedores::CDlgProveedores(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProveedores::IDD, pParent)
	, m_strCodCuenta(_T(""))
	, m_timeAlta(0)
	, m_strNombre(_T(""))
	, m_strNomFicha(_T(""))
	, m_strDire(_T(""))
	, m_strSg(_T(""))
	, m_strNum(_T(""))
	, m_strCP(_T(""))
	, m_strProvincia(_T(""))
	, m_strPoblacion(_T(""))
	, m_strPais(_T(""))
	, m_strCIF(_T(""))
	, m_strIdentificacion(_T(""))
	, m_strTelf2(_T(""))
	, m_strEmail(_T(""))
	, m_strContacto(_T(""))
	, m_strCargo(_T(""))
	, m_strIdioma(_T(""))
	, m_strObservaciones(_T(""))
	, m_bTipo1(FALSE)
	, m_iTipo2(0)
	, m_timeBaja(0)
	, m_strDesPais(_T(""))
	, m_strDesIdioma(_T(""))
{
}

CDlgProveedores::~CDlgProveedores()
{
	m_bUpdate=FALSE;
}

void CDlgProveedores::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_COD_CUENTA, m_strCodCuenta);
		DDV_MaxChars(pDX, m_strCodCuenta, 9);
	DDX_Text(pDX, IDC_NOM_CUENTA, m_strNombre);
		DDV_MaxChars(pDX, m_strNombre, 50);
	DDX_Text(pDX, IDC_NOMBRE, m_strNomFicha);
		DDV_MaxChars(pDX, m_strNomFicha, 35);
	DDX_Text(pDX, IDC_DIRECCION, m_strDire);
		DDV_MaxChars(pDX, m_strDire, 50);
	DDX_Text(pDX, IDC_SG, m_strSg);
		DDV_MaxChars(pDX, m_strSg, 2);
	DDX_Text(pDX, IDC_NUM, m_strNum);
		DDV_MaxChars(pDX, m_strNum, 3);
	DDX_Text(pDX, IDC_CP, m_strCP);
		DDV_MaxChars(pDX, m_strCP, 5);
	DDX_Text(pDX, IDC_PROVINCIA, m_strProvincia);
		DDV_MaxChars(pDX, m_strProvincia, 15);
	DDX_Text(pDX, IDC_POBLACION, m_strPoblacion);
		DDV_MaxChars(pDX, m_strPoblacion, 25);
	DDX_Text(pDX, IDC_CIF, m_strCIF);
		DDV_MaxChars(pDX, m_strCIF, 15);
	DDX_Text(pDX, IDC_IDENTIFICACION, m_strIdentificacion);
		DDV_MaxChars(pDX, m_strIdentificacion, 14);
	DDX_Text(pDX, IDC_TELEFONO1, m_strTelf1);
		DDV_MaxChars(pDX, m_strTelf1, 15);
	DDX_Text(pDX, IDC_TELEFONO2, m_strTelf2);
		DDV_MaxChars(pDX, m_strTelf2, 15);
	DDX_Text(pDX, IDC_FAX, m_strFax);
		DDV_MaxChars(pDX, m_strFax, 15);
	DDX_Text(pDX, IDC_EMAIL, m_strEmail);
		DDV_MaxChars(pDX, m_strEmail, 50);
	DDX_Text(pDX, IDC_CONTACTO, m_strContacto);
		DDV_MaxChars(pDX, m_strContacto, 35);
	DDX_Text(pDX, IDC_CARGO, m_strCargo);
		DDV_MaxChars(pDX, m_strCargo, 15);
	DDX_Text(pDX, IDC_PLAZO, m_strPlazo);
		DDV_MaxChars(pDX, m_strPlazo, 13);
	DDX_Text(pDX, IDC_OBSERVACIONES, m_strObservaciones);
		DDV_MaxChars(pDX, m_strObservaciones, 50);
	DDX_Radio(pDX, IDC_INVERSION1, m_bTipo1);
	DDX_Radio(pDX, IDC_IVA1, m_iTipo2);
	DDX_DateTimeCtrl(pDX, IDC_FECHBAJA, m_timeBaja);
	DDX_DateTimeCtrl(pDX, IDC_FECHALTA, m_timeAlta);
	DDX_Text(pDX, IDC_DES_PAIS, m_strDesPais);
	DDX_Text(pDX, IDC_DES_IDIOMA, m_strDesIdioma);
	DDX_Text(pDX, IDC_PAIS, m_strPais);
	DDX_Text(pDX, IDC_IDIOMA, m_strIdioma);
}


BEGIN_MESSAGE_MAP(CDlgProveedores, CDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_INVERSION1, OnBnClickedInversion1)
	ON_BN_CLICKED(IDC_INVERSION2, OnBnClickedInversion2)
	ON_BN_CLICKED(IDC_ACEPTAR, OnBnClickedAceptar)
	ON_BN_CLICKED(IDC_IVA1, OnBnClickedIva1)
	ON_BN_CLICKED(IDC_IVA2, OnBnClickedIva2)
	ON_BN_CLICKED(IDC_IVA3, OnBnClickedIva3)
	ON_BN_CLICKED(IDC_BOTON_PAIS, OnBnClickedBotonPais)
	ON_BN_CLICKED(IDC_BOTON_IDIOMA, OnBnClickedBotonIdioma)
	ON_BN_CLICKED(IDC_BOTON_FACTURACION, OnBnClickedBotonFacturacion)
	ON_BN_CLICKED(IDC_BOTON_PAGOS, OnBnClickedBotonPagos)
	ON_EN_KILLFOCUS(IDC_PAIS, OnEnKillfocusPais)
	ON_EN_KILLFOCUS(IDC_IDIOMA, OnEnKillfocusIdioma)
END_MESSAGE_MAP()

BOOL CDlgProveedores::OnInitDialog()
{
	CDialog::OnInitDialog();

	/******* CARGA LAS BUSQUEDAS PARA AHORRAR TIEMPO ********/
	m_dlgBusquedaPais.SetConexion(m_db); 
	m_dlgBusquedaIdioma.SetConexion(m_db);
	/*******************************************************/
	/***********      RELLENA LOS CAMPOS      **************/
	/*******************************************************/
	m_rsProve.m_strFilter="CUENTA LIKE '" + m_strCodCuenta + "'";//filtro de busqueda
	if (!m_rsProve.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (m_bUpdate==FALSE)
	{
		m_timeAlta=CTime::GetCurrentTime();//pone la fecha de hoy
		GetDlgItem(IDC_COD_CUENTA)->SetWindowText(m_strCodCuenta);
		m_strNombre="";
		m_strNomFicha="";
		m_strDire="";
		m_strSg="";
		m_strNum="";
		m_strCP="";
		m_strProvincia="";
		m_strPoblacion="";
		m_strPais="";
		m_strCIF="";
		/////////////////////////////
		m_strIdentificacion="";
		m_strTelf1="";
		m_strTelf2="";
		m_strEmail="";
		m_strContacto="";
		m_strCargo="";
		m_strIdioma="";
		m_strPlazo="0";
		m_strObservaciones="";
		m_timeBaja=NULL;
		m_cTipo=' ';
		UpdateData(FALSE);
		return FALSE;
	}
	m_strNombre=m_rsProve.m_NOMBRE.TrimRight();
	m_strNomFicha=m_rsProve.m_NOMFICHA.TrimRight();
	m_strDire=m_rsProve.m_DIRECCION.TrimRight();
	m_strSg=m_rsProve.m_SG.TrimRight();
	m_strNum=m_rsProve.m_NUMERO.TrimRight();
	m_strCP=m_rsProve.m_CP.TrimRight();
	m_strProvincia=m_rsProve.m_PROVINCIA.TrimRight();
	m_strPoblacion=m_rsProve.m_POBLACION.TrimRight();
	m_strPais=m_rsProve.m_CPAIS.TrimRight();
	m_strCIF=m_rsProve.m_CIF.TrimRight();
	/////////////////////////////
	m_strIdentificacion=m_rsProve.m_IVAIDEN.TrimRight();
	m_strTelf1=m_rsProve.m_TELEFONO.TrimRight();
	m_strTelf2=m_rsProve.m_TEL2.TrimRight();
	m_strFax=m_rsProve.m_FAX.TrimRight();
	m_strEmail=m_rsProve.m_EMAIL.TrimRight();
	m_strContacto=m_rsProve.m_CONTACTO.TrimRight();
	m_strCargo=m_rsProve.m_CARGO.TrimRight();
	m_strIdioma=m_rsProve.m_IDIOMA.TrimRight();
	m_strPlazo.Format("%.0f",m_rsProve.m_PLAZOENT);
	m_strObservaciones=m_rsProve.m_OBSER1.TrimRight();
	if (m_rsProve.m_FECHALTA==NULL)
	{
		m_timeAlta=CTime::GetCurrentTime();
	}
	else
		m_timeAlta=m_rsProve.m_FECHALTA;
	m_timeBaja=m_rsProve.m_FECHBAJA;
	m_cTipo=m_rsProve.m_TIPO.GetAt(0);
	switch (m_cTipo)
	{
		case ' ':
			m_iTipo2=NACIONAL;m_bTipo1=NO;break;
		case 'V':
			m_iTipo2=NACIONAL;m_bTipo1=SI;break;
		case 'J':
			m_iTipo2=INTRACOMUNITARIO;m_bTipo1=NO;break;
		case 'R':
			m_iTipo2=INTRACOMUNITARIO;m_bTipo1=SI;break;
		case 'S':
			m_iTipo2=TERCEROS;m_bTipo1=NO;break;
		case 'T':
			m_iTipo2=TERCEROS;m_bTipo1=SI;break;
		default:
			m_iTipo2=NACIONAL;m_bTipo1=SI;
	}

	EncuentraPais(m_strPais);
	EncuentraIdioma(m_strIdioma);
	UpdateData(FALSE);
	return FALSE;
}
/****************************************************************************************************/
/***                                        FUNCIONES
/****************************************************************************************************/
void CDlgProveedores::SetConexion(CDatabase *db)//realiza la conexion con las tablas
{
	m_db = db;
	m_rsProve.m_pDatabase=m_db;
}
/****************************************************************************************************/
void CDlgProveedores::SetCodigo(CString strAux)
{
	m_strCodCuenta=strAux;
}
/****************************************************************************************************/
void CDlgProveedores::OnBnClickedCancel()
{
	m_rsProve.Close();
	OnCancel();
}
/****************************************************************************************************/
void CDlgProveedores::OnBnClickedInversion1()
{
	m_bTipo1=NO;
	//GetDlgItem(IDC_IVA1)->EnableWindow(TRUE);
}

void CDlgProveedores::OnBnClickedInversion2()
{
	m_bTipo1=SI;
	//GetDlgItem(IDC_IVA1)->EnableWindow(FALSE);
}
/******************************************************************************************************/
void CDlgProveedores::OnBnClickedAceptar()
{
	UpdateData(TRUE);
	if(m_strNombre.IsEmpty())
	{
		AfxMessageBox(IDC_NO_DESCRIPCION);
		GetDlgItem(IDC_NOM_CUENTA)->SetFocus();
		return;
	}
	if (m_bTipo1==NO)
	{
		switch (m_iTipo2)
		{
			case NACIONAL:
				m_cTipo=' ';break;
			case INTRACOMUNITARIO:
				m_cTipo='J';break;
			case TERCEROS:
				m_cTipo='S';break;
			default:
				m_cTipo=' ';
		}
	}
	if (m_bTipo1==SI)
	{
		switch (m_iTipo2)
		{
			case NACIONAL:
				m_cTipo='V';break;
			case INTRACOMUNITARIO:
				m_cTipo='R';break;
			case TERCEROS:
				m_cTipo='T';break;
			default:
				m_cTipo='V';
		}
	}
	m_rsProve.m_TIPO=m_cTipo;
	m_rsProve.m_CUENTA=m_strCodCuenta;
	m_rsProve.m_NOMBRE = m_strNombre;
	m_rsProve.m_NOMFICHA = m_strNomFicha;
	m_rsProve.m_DIRECCION = m_strDire;
	m_rsProve.m_DIRECCION = m_strDire;
	m_rsProve.m_DIRECCION = m_strDire;
	m_rsProve.m_SG = m_strSg;
	m_rsProve.m_NUMERO = m_strNum;
	m_rsProve.m_CP = m_strCP;
	m_rsProve.m_POBLACION = m_strPoblacion;
	m_rsProve.m_PROVINCIA = m_strProvincia;
	m_rsProve.m_CPAIS = m_strPais;
	m_rsProve.m_CIF = m_strCIF;
	m_rsProve.m_TIPO = m_cTipo;
	m_rsProve.m_IVAIDEN = m_strIdentificacion;
	m_rsProve.m_TELEFONO = m_strTelf1;
	m_rsProve.m_TEL2 = m_strTelf2;
	m_rsProve.m_FAX = m_strFax;
	m_rsProve.m_EMAIL = m_strEmail;
	m_rsProve.m_CONTACTO = m_strContacto;
	m_rsProve.m_CARGO = m_strCargo;
	m_rsProve.m_IDIOMA = m_strIdioma;
	m_rsProve.m_PLAZOENT=atof(m_strPlazo);
	m_rsProve.m_OBSER1 = m_strObservaciones;
	m_rsProve.m_FECHALTA = m_datetimeFechaBaja;
	m_rsProve.m_FECHBAJA = m_datetimeFechaAlta;

	if (m_bUpdate==FALSE)//sino existia antes
	{
		if (!m_db->BeginTrans())
	        return;

		HRESULT hErr = S_OK;

		hErr = m_rsProve.Insert();
		if (hErr == S_OK)
		{
			CCuentas rsCuentas(m_db);
			rsCuentas.m_CUENTA=m_strCodCuenta;
			rsCuentas.m_NOMBRE=m_strNombre;
			hErr = rsCuentas.Insert();
		}
		if (hErr == S_OK)
			m_db->CommitTrans();
		else
			m_db->Rollback();
	}
	else
	{
		if (!m_db->BeginTrans())
	        return;
		HRESULT hErr;
		hErr = m_rsProve.UpdateProve();
		if (hErr == S_OK)
		{
			CCuentas rsCuentas(m_db);
			rsCuentas.m_CUENTA=m_strCodCuenta;
			rsCuentas.m_NOMBRE=m_strNombre;
			hErr = rsCuentas.UpdateRegistro();
		}
		if (hErr == S_OK)
			m_db->CommitTrans();
		else
			m_db->Rollback();
	}
	m_rsProve.Close();
	OnCancel();
}
//////////////////////////////////////////////////////////////////////////
void CDlgProveedores::EsNuevo(BOOL bUpdate)
{
	m_bUpdate=bUpdate;
}
//////////////////////////////////////////////////////////////////////////
void CDlgProveedores::OnBnClickedIva1()
{
	m_iTipo2=NACIONAL;
}

void CDlgProveedores::OnBnClickedIva2()
{
	m_iTipo2=INTRACOMUNITARIO;
}

void CDlgProveedores::OnBnClickedIva3()
{
	m_iTipo2=TERCEROS;
}
/////////////////////////////////////////////////////////////////////////////
void CDlgProveedores::OnBnClickedBotonPais()
{
	INT_PTR Estado;
	m_dlgBusquedaPais.SetTipo(CDialogBusqueda::PAIS);
	Estado=m_dlgBusquedaPais.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strPais=m_dlgBusquedaPais.GetCodigo();
	GetDlgItem(IDC_PAIS)->SetWindowText(m_strPais);
	m_strDesPais=m_dlgBusquedaPais.GetDescripcion();
	GetDlgItem(IDC_DES_PAIS)->SetWindowText(m_strDesPais);
}
/////////////////////////////////////////////////////////////////////////////
void CDlgProveedores::OnBnClickedBotonIdioma()
{
	INT_PTR Estado;
	m_dlgBusquedaIdioma.SetTipo(CDialogBusqueda::IDIOMA);
	Estado=m_dlgBusquedaIdioma.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strIdioma=m_dlgBusquedaIdioma.GetCodigo();
	GetDlgItem(IDC_IDIOMA)->SetWindowText(m_strIdioma);
	m_strDesIdioma=m_dlgBusquedaIdioma.GetDescripcion();
	GetDlgItem(IDC_DES_IDIOMA)->SetWindowText(m_strDesIdioma);
}
/////////////////////////////////////////////////////////////////////////////
void CDlgProveedores::OnBnClickedBotonFacturacion()
{
	CDlgDatosFacturacion dlgFacturacion;
	dlgFacturacion.SetUpdate(m_bUpdate);
	dlgFacturacion.SetProve(&m_rsProve);
	dlgFacturacion.SetConexion(m_db);
	dlgFacturacion.DoModal();
}
/////////////////////////////////////////////////////////////////////////////
void CDlgProveedores::OnBnClickedBotonPagos()
{
	CDlgDatosPago dlgPagos;
	//dlgPagos.settSetUpdate(m_bUpdate);
	dlgPagos.SetProve(&m_rsProve);
	dlgPagos.SetConexion(m_db);
	dlgPagos.DoModal();
}
/////////////////////////////////////////////////////////////////////////////
void CDlgProveedores::OnEnKillfocusPais()
{
	CString strAux=m_strPais;
	GetDlgItem(IDC_PAIS)->GetWindowText(m_strPais);
	if (m_strPais.IsEmpty())
	{
		m_strDesPais="";
		GetDlgItem(IDC_DES_PAIS)->SetWindowText(m_strDesPais);
		return;
	}
	if (m_strPais==strAux)
	{return;}
	if (EncuentraPais(m_strPais)==FALSE)
	{
		m_strPais=strAux;
		GetDlgItem(IDC_PAIS)->SetWindowText(m_strPais);
		
	}
	else
	{GetDlgItem(IDC_DES_PAIS)->SetWindowText(m_strDesPais);return;}
	GetDlgItem(IDC_PAIS)->SetFocus();
}
/////////////////////////////////////////////////////////////////////////////
void CDlgProveedores::OnEnKillfocusIdioma()
{
	CString strAux=m_strIdioma;
	GetDlgItem(IDC_IDIOMA)->GetWindowText(m_strIdioma);
	if (m_strIdioma.IsEmpty())
	{
		m_strDesIdioma="";
		GetDlgItem(IDC_DES_IDIOMA)->SetWindowText(m_strDesIdioma);
		return;
	}
	if (m_strIdioma==strAux)
	{return;}
	if (EncuentraIdioma(m_strIdioma)==FALSE)
	{
		m_strIdioma=strAux;
		GetDlgItem(IDC_IDIOMA)->SetWindowText(m_strIdioma);
	}
	else
	{GetDlgItem(IDC_DES_IDIOMA)->SetWindowText(m_strDesIdioma);return;}
	GetDlgItem(IDC_IDIOMA)->SetFocus();
}
/***************************************************************************************************/
BOOL CDlgProveedores::EncuentraPais(CString cadena)
{
	CPais rsPais(m_db);
	rsPais.m_strFilter="CPAIS LIKE '" + cadena + "'";
	if (!rsPais.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	if (rsPais.m_DPAIS.IsEmpty())
	{
		rsPais.Close();
		return FALSE;
	}
	else
	{
		m_strDesPais=rsPais.m_DPAIS.TrimRight();
		rsPais.Close();
		return TRUE;
	}
}
/***************************************************************************************************/
BOOL CDlgProveedores::EncuentraIdioma(CString cadena)
{
	CIdiomas rsIdioma(m_db);
	rsIdioma.m_strFilter="IDIOMA LIKE '" + cadena + "'";
	if (!rsIdioma.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (rsIdioma.m_DIDIOMA.IsEmpty())
	{
		rsIdioma.Close();
		return FALSE;
	}
	else
	{
		m_strDesIdioma=rsIdioma.m_DIDIOMA.TrimRight();
		rsIdioma.Close();
		return TRUE;
	}
}
