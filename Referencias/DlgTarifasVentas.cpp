// DlgTarifasVentas.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgTarifasVentas.h"
#include ".\dlgtarifasventas.h"
#include "BD.h"
#include "Utilidades.h"

#define ALQUILER 0
#define VENTAS 1
#define OTROS 2
#define ENTREGA 3
#define RECOGIDA 4

#define MES 0
#define DLABORABLE 1
#define DNATURAL 2

// Cuadro de diálogo de CDlgTarifasVentas

IMPLEMENT_DYNAMIC(CDlgTarifasVentas, CDialog)
CDlgTarifasVentas::CDlgTarifasVentas(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTarifasVentas::IDD, pParent)
	, m_strCodCuenta(_T(""))
	, m_strTarifa1(_T("")), m_strTarifa2(_T("")), m_strTarifa3(_T("")), m_strTarifa4(_T("")), m_strTarifa5(_T(""))
	, m_strTarifa6(_T("")), m_strTarifa7(_T("")), m_strTarifa8(_T("")), m_strTarifa9(_T(""))
	, m_strDescuento1(_T("")), m_strDescuento2(_T("")), m_strDescuento3(_T("")), m_strDescuento4(_T(""))
	, m_strDescuento5(_T("")), m_strDescuento6(_T("")), m_strDescuento7(_T("")), m_strDescuento8(_T(""))
	, m_strDescuento9(_T(""))
	, m_strDesCuenta(_T(""))
	, m_iTipoVenta('S')
	, m_iTipoAlq('M')
	, m_strTarVen(_T(""))
	, bArtiNuevo(FALSE)
{
}

CDlgTarifasVentas::~CDlgTarifasVentas()
{
}

void CDlgTarifasVentas::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CUENTA, m_strCodCuenta);
	DDX_Text(pDX, IDC_TARIFAA, m_strTarifa1);
	DDX_Text(pDX, IDC_TARIFAB, m_strTarifa2);
	DDX_Text(pDX, IDC_TARIFAC, m_strTarifa3);
	DDX_Text(pDX, IDC_TARIFAD, m_strTarifa4);
	DDX_Text(pDX, IDC_TARIFAE, m_strTarifa5);
	DDX_Text(pDX, IDC_TARIFAF, m_strTarifa6);
	DDX_Text(pDX, IDC_TARIFAG, m_strTarifa7);
	DDX_Text(pDX, IDC_TARIFAH, m_strTarifa8);
	DDX_Text(pDX, IDC_TARIFAI, m_strTarifa9);
	DDX_Text(pDX, IDC_DESCUENTOA, m_strDescuento1);
	DDX_Text(pDX, IDC_DESCUENTOB, m_strDescuento2);
	DDX_Text(pDX, IDC_DESCUENTOC, m_strDescuento3);
	DDX_Text(pDX, IDC_DESCUENTOD, m_strDescuento4);
	DDX_Text(pDX, IDC_DESCUENTOE, m_strDescuento5);
	DDX_Text(pDX, IDC_DESCUENTOF, m_strDescuento6);
	DDX_Text(pDX, IDC_DESCUENTOG, m_strDescuento7);
	DDX_Text(pDX, IDC_DESCUENTOH, m_strDescuento8);
	DDX_Text(pDX, IDC_DESCUENTOI, m_strDescuento9);
	DDX_Text(pDX, IDC_EDIT1, m_strDesCuenta);
	DDX_Radio(pDX, IDC_TIPOVENTA1, m_iTipoVenta);
	DDX_Radio(pDX, IDC_ALQUILER1, m_iTipoAlq);
	DDX_Control(pDX, IDC_CUENTA, m_ctrlCuenta);
	DDX_Control(pDX, IDC_TARIFAA, m_ctrlTarifa1);
	DDX_Control(pDX, IDC_TARIFAB, m_ctrlTarifa2);
	DDX_Control(pDX, IDC_TARIFAC, m_ctrlTarifa3);
	DDX_Control(pDX, IDC_TARIFAD, m_ctrlTarifa4);
	DDX_Control(pDX, IDC_TARIFAE, m_ctrlTarifa5);
	DDX_Control(pDX, IDC_TARIFAF, m_ctrlTarifa6);
	DDX_Control(pDX, IDC_TARIFAG, m_ctrlTarifa7);
	DDX_Control(pDX, IDC_TARIFAH, m_ctrlTarifa8);
	DDX_Control(pDX, IDC_TARIFAI, m_ctrlTarifa9);
	DDX_Control(pDX, IDC_DESCUENTOA, m_ctrlDescuento1);
	DDX_Control(pDX, IDC_DESCUENTOB, m_ctrlDescuento2);
	DDX_Control(pDX, IDC_DESCUENTOC, m_ctrlDescuento3);
	DDX_Control(pDX, IDC_DESCUENTOD, m_ctrlDescuento4);
	DDX_Control(pDX, IDC_DESCUENTOE, m_ctrlDescuento5);
	DDX_Control(pDX, IDC_DESCUENTOF, m_ctrlDescuento6);
	DDX_Control(pDX, IDC_DESCUENTOG, m_ctrlDescuento7);
	DDX_Control(pDX, IDC_DESCUENTOH, m_ctrlDescuento8);
	DDX_Control(pDX, IDC_DESCUENTOI, m_ctrlDescuento9);
	DDX_Text(pDX, IDC_TARIFA_VENTA, m_strTarVen);
}


BEGIN_MESSAGE_MAP(CDlgTarifasVentas, CDialog)
	ON_BN_CLICKED(IDC_TIPOVENTA1, OnBnClickedTipoventa1)
	ON_BN_CLICKED(IDC_TIPOVENTA2, OnBnClickedTipoventa2)
	ON_BN_CLICKED(IDC_TIPOVENTA3, OnBnClickedTipoventa3)
	ON_BN_CLICKED(IDC_TIPOVENTA4, OnBnClickedTipoventa4)
	ON_BN_CLICKED(IDC_TIPOVENTA5, OnBnClickedTipoventa5)
	ON_BN_CLICKED(IDC_ALQUILER1, OnBnClickedAlquiler1)
	ON_BN_CLICKED(IDC_ALQUILER2, OnBnClickedAlquiler2)
	ON_BN_CLICKED(IDC_ALQUILER3, OnBnClickedAlquiler3)
	ON_BN_CLICKED(IDB_CUENTA_ALQUILER, OnBnClickedCuentaAlquiler)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_CUENTA, OnEnKillfocusCuenta)
	ON_EN_KILLFOCUS(IDC_TARIFAA, OnEnKillfocusTarifaa)
	ON_EN_KILLFOCUS(IDC_TARIFAB, OnEnKillfocusTarifab)
	ON_EN_KILLFOCUS(IDC_TARIFAC, OnEnKillfocusTarifac)
	ON_EN_KILLFOCUS(IDC_TARIFAD, OnEnKillfocusTarifad)
	ON_EN_KILLFOCUS(IDC_TARIFAE, OnEnKillfocusTarifae)
	ON_EN_KILLFOCUS(IDC_TARIFAF, OnEnKillfocusTarifaf)
	ON_EN_KILLFOCUS(IDC_TARIFAG, OnEnKillfocusTarifag)
	ON_EN_KILLFOCUS(IDC_TARIFAH, OnEnKillfocusTarifah)
	ON_EN_KILLFOCUS(IDC_TARIFAI, OnEnKillfocusTarifai)
	ON_EN_KILLFOCUS(IDC_DESCUENTOA, OnEnKillfocusDescuentoa)
	ON_EN_KILLFOCUS(IDC_DESCUENTOB, OnEnKillfocusDescuentob)
	ON_EN_KILLFOCUS(IDC_DESCUENTOC, OnEnKillfocusDescuentoc)
	ON_EN_KILLFOCUS(IDC_DESCUENTOD, OnEnKillfocusDescuentod)
	ON_EN_KILLFOCUS(IDC_DESCUENTOE, OnEnKillfocusDescuentoe)
	ON_EN_KILLFOCUS(IDC_DESCUENTOF, OnEnKillfocusDescuentof)
	ON_EN_KILLFOCUS(IDC_DESCUENTOG, OnEnKillfocusDescuentog)
	ON_EN_KILLFOCUS(IDC_DESCUENTOH, OnEnKillfocusDescuentoh)
	ON_EN_KILLFOCUS(IDC_DESCUENTOI, OnEnKillfocusDescuentoi)
	ON_EN_KILLFOCUS(IDC_TARIFA_VENTA, OnEnKillfocusTarifaVenta)
END_MESSAGE_MAP()

BOOL CDlgTarifasVentas::OnInitDialog()
{
	CDialog::OnInitDialog();
	//m_dlgBusquedaCuentas.SetConexion(m_db);
	
	if (bArtiNuevo==FALSE)
	{
		RellenaCampos();		
	}
	else
	{
		TraAlquiler();
	}

	UpdateData(FALSE);
	return TRUE;
}
void CDlgTarifasVentas::SetNuevo(BOOL nuevo)
{
	bArtiNuevo=nuevo;
}
/*********************************************************************************************/
/***                       OPTIONBUTTON DEL TIPO DE VENTA                                  ***/
/*********************************************************************************************/
void CDlgTarifasVentas::OnBnClickedTipoventa1()
{
	Seleccionar();
	iOpcionVenta=ALQUILER;
}

void CDlgTarifasVentas::OnBnClickedTipoventa2()
{
	Deseleccionar();
	iOpcionVenta=VENTAS;
}

void CDlgTarifasVentas::OnBnClickedTipoventa3()
{
	Deseleccionar();
	iOpcionVenta=OTROS;
}

void CDlgTarifasVentas::OnBnClickedTipoventa4()
{
	Deseleccionar();
	iOpcionVenta=ENTREGA;
}

void CDlgTarifasVentas::OnBnClickedTipoventa5()
{
	Deseleccionar();
	iOpcionVenta=RECOGIDA;
}
void CDlgTarifasVentas::OnBnClickedAlquiler1()
{
	m_iTipoAlq= MES;
}

void CDlgTarifasVentas::OnBnClickedAlquiler2()
{
	m_iTipoAlq=DLABORABLE;
}

void CDlgTarifasVentas::OnBnClickedAlquiler3()
{
	m_iTipoAlq=DNATURAL;
}

void CDlgTarifasVentas::OnBnClickedCuentaAlquiler()
{
	m_dlgBusquedaCuentas.SetConexion(m_db);
	m_dlgBusquedaCuentas.SetTipo(CDialogBusqueda::CUENTAS);
	m_dlgBusquedaCuentas.DoModal();
	m_strCodCuenta=m_dlgBusquedaCuentas.GetCodigo();
	m_strDesCuenta=m_dlgBusquedaCuentas.GetDescripcion();
	GetDlgItem(IDC_CUENTA)->SetWindowText(m_strCodCuenta);
	GetDlgItem(IDC_DES_ALQUILER)->SetWindowText(m_strDesCuenta);
}
/*******************************************************************************************/
void CDlgTarifasVentas::SetArticulo(CArticulo *rsArticulo)
{
	m_rsArticulo=rsArticulo;
}

void CDlgTarifasVentas::SetConexion(CDatabase *db)
{
	m_db=db;
}
/*************************************************************************************/
/***                RELLENA TODOS LOS CAMPOS DEL FORMULARIO                        ***/
/*************************************************************************************/
void CDlgTarifasVentas::RellenaCampos()
{
	//Rellena los campos de tarifa
	m_strTarifa1.Format("%.3f",m_rsArticulo->m_ETARI1);	
	m_strTarifa2.Format("%.3f",m_rsArticulo->m_ETARIB1);
	m_strTarifa3.Format("%.3f",m_rsArticulo->m_ETARIC1);
	m_strTarifa4.Format("%.3f",m_rsArticulo->m_ETARID1);
	m_strTarifa5.Format("%.3f",m_rsArticulo->m_ETARIE1);
	m_strTarifa6.Format("%.3f",m_rsArticulo->m_ETARIF1);
	m_strTarifa7.Format("%.3f",m_rsArticulo->m_ETARIG1);
	m_strTarifa8.Format("%.3f",m_rsArticulo->m_ETARIH1);
	m_strTarifa9.Format("%.3f",m_rsArticulo->m_ETARII1);
	m_strTarVen.Format("%.3f",m_rsArticulo->m_TARVEN);
	//Rellena los campos de descuento
	m_strDescuento1.Format("%.2f",m_rsArticulo->m_DTOTAR1);
	m_strDescuento2.Format("%.2f",m_rsArticulo->m_DTOTARB1);
	m_strDescuento3.Format("%.2f",m_rsArticulo->m_DTOTARC1);
	m_strDescuento4.Format("%.2f",m_rsArticulo->m_DTOTARD1);
	m_strDescuento5.Format("%.2f",m_rsArticulo->m_DTOTARE1);
	m_strDescuento6.Format("%.2f",m_rsArticulo->m_DTOTARF1);
	m_strDescuento7.Format("%.2f",m_rsArticulo->m_DTOTARG1);
	m_strDescuento8.Format("%.2f",m_rsArticulo->m_DTOTARH1);
	m_strDescuento9.Format("%.2f",m_rsArticulo->m_DTOTARI1);
	//Rellena el campo de Cuenta de alquiler
	m_strCodCuenta=m_rsArticulo->m_CTAALQ.TrimRight();
	//Rellena el campo de Descripción
	RellenaDesCuenta();
	TraAlquiler();
}
/*************************************************************************************/
/***            BUSCA LA DESCRIPCIÓN DE LA CUENTA EN LA TABLA "CUENTAS"            ***/
/*************************************************************************************/
BOOL CDlgTarifasVentas::RellenaDesCuenta()
{
	CCuentas rsCuenta(m_db);
	rsCuenta.m_strFilter = "CUENTA LIKE '" + m_strCodCuenta + "'";	//filtro de busqueda
	if (!rsCuenta.Open(CRecordset::dynaset)) //comprueva si se puede abrir la tabla
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	if (!rsCuenta.m_CUENTA.IsEmpty())
	{
		m_strDesCuenta = rsCuenta.m_NOMBRE.TrimRight();
		return TRUE;
	}
	else
	{
		m_strDesCuenta.Empty();
		GetDlgItem(IDC_DES_ALQUILER)->SetWindowText(m_strDesCuenta);
		return FALSE;
	}		
rsCuenta.Close();}
/*************************************************************************************/
/***                PARA ACTIVAR O DESACTIVAR LOS OPTIONBUTTON                     ***/
/*************************************************************************************/
void CDlgTarifasVentas::Seleccionar()
{
	GetDlgItem(IDC_ALQUILER1)->EnableWindow();
	GetDlgItem(IDC_ALQUILER2)->EnableWindow();
	GetDlgItem(IDC_ALQUILER3)->EnableWindow();
	GetDlgItem(IDC_TARIFA_VENTA)->EnableWindow();
}
void CDlgTarifasVentas::Deseleccionar()
{
	GetDlgItem(IDC_ALQUILER1)->EnableWindow(false);
	GetDlgItem(IDC_ALQUILER2)->EnableWindow(false);
	GetDlgItem(IDC_ALQUILER3)->EnableWindow(false);
	GetDlgItem(IDC_TARIFA_VENTA)->EnableWindow(false);
}
/************************************************************************************/
/*** TRANSFORMA LOS DATOS DE LA TABLA EN OPCIONES VALIDAS DEL OPTION OPTIONBUTTON ***/
/************************************************************************************/
void CDlgTarifasVentas::TraAlquiler()
{
	if (m_rsArticulo->m_ALQUILER.Trim().IsEmpty())
	{
		cTipo='S';
		cTipoAlq='M';
	}
	else
	{		
		cTipo = m_rsArticulo->m_ALQUILER.GetAt(0);
		cTipoAlq = m_rsArticulo->m_TIPOALQ.GetAt(0);
	}

	switch (cTipo)
	{
		case 'S':
			m_iTipoVenta=ALQUILER;
			Seleccionar();
			switch (cTipoAlq)
			{
				case 'M':
					m_iTipoAlq=MES;
					break;
				case 'D':
					m_iTipoAlq=DLABORABLE;
					break;
				case 'N':
					m_iTipoAlq=DNATURAL;
					break;
			}
			break;
		case 'V':
			m_iTipoVenta=VENTAS;
			m_iTipoAlq=MES;
			break;
		case 'N':
			m_iTipoVenta=OTROS;
			m_iTipoAlq=MES;
			break;
		case 'E':
			m_iTipoVenta=ENTREGA;
			m_iTipoAlq=MES;
			break;
		case 'R':
			m_iTipoVenta=RECOGIDA;
			m_iTipoAlq=MES;
			break;
	}
}

void CDlgTarifasVentas::OnBnClickedOk()
{
	UpdateData(TRUE);
	m_rsArticulo->m_CTAALQ = m_strCodCuenta.TrimRight();
	m_rsArticulo->m_TARVEN = atof(m_strTarVen);
	m_rsArticulo->m_ETARI1=atof(m_strTarifa1);
	m_rsArticulo->m_ETARIB1=atof(m_strTarifa2);
	m_rsArticulo->m_ETARIC1=atof(m_strTarifa3);
	m_rsArticulo->m_ETARID1=atof(m_strTarifa4);
	m_rsArticulo->m_ETARIE1=atof(m_strTarifa5);
	m_rsArticulo->m_ETARIF1=atof(m_strTarifa6);
	m_rsArticulo->m_ETARIG1=atof(m_strTarifa7);
	m_rsArticulo->m_ETARIH1=atof(m_strTarifa8);
	m_rsArticulo->m_ETARII1=atof(m_strTarifa9);
	m_rsArticulo->m_DTOTAR1=atof(m_strDescuento1);
	m_rsArticulo->m_DTOTARB1=atof(m_strDescuento2);
	m_rsArticulo->m_DTOTARC1=atof(m_strDescuento3);
	m_rsArticulo->m_DTOTARD1=atof(m_strDescuento4);
	m_rsArticulo->m_DTOTARE1=atof(m_strDescuento5);
	m_rsArticulo->m_DTOTARF1=atof(m_strDescuento6);
	m_rsArticulo->m_DTOTARG1=atof(m_strDescuento7);
	m_rsArticulo->m_DTOTARH1=atof(m_strDescuento8);
	m_rsArticulo->m_DTOTARI1=atof(m_strDescuento9);
	m_rsArticulo->m_ALQUILER=NToLVenta();
	OnOK();
}

char CDlgTarifasVentas::NToLVenta()
{
	switch (m_iTipoVenta)
	{
		case 0:
			//ALQUILER
			m_rsArticulo->m_TIPOALQ=NToLAlquiler();
			return 'S';
			break;
		case 1:
			//VENTAS
			return 'V';
			break;
		case 2:
			//OTROS
			return 'N';
			break;
		case 3:
			//ENTREGA
			return 'E';
			break;
		case 4:
			//RECOGIDA
			return 'R';
			break;
		default:
			return 'S';
	}
}
char CDlgTarifasVentas::NToLAlquiler()
{
	switch (m_iTipoAlq)
	{
		case 0:
			//ALQUILER
			return 'M';
			break;
		case 1:
			//VENTAS
			return 'D';
			break;
		case 2:
			//OTROS
			return 'N';
			break;
		default:
			return 'M';
	}
}
void CDlgTarifasVentas::OnEnKillfocusCuenta()
{
	CString Aux, Aux2;
	Aux=m_strCodCuenta;
	Aux2=m_strDesCuenta;

	GetDlgItem(IDC_CUENTA)->GetWindowText(m_strCodCuenta);
	if(m_strCodCuenta.IsEmpty())	//sino está vacio el campo de código
	{
		m_strDesCuenta = "";
		GetDlgItem(IDC_DES_ALQUILER)->SetWindowText(m_strDesCuenta);
	}
	else
	{
		if(!RellenaDesCuenta())
		{
			m_strCodCuenta=Aux;
			m_strDesCuenta=Aux2;
		}
	}
	UpdateData(FALSE);
}
/***************************************************************************/
BOOL CDlgTarifasVentas::ChequeaNumeros(CString cadena)
{
	BOOL bPunto = FALSE;	
	for (int i = 0; i<cadena.GetLength(); i++)
	{
		if ((cadena.GetAt(i) < '0' || cadena.GetAt(i) > '9') && (cadena.GetAt(i) != '-' || (cadena.GetAt(i) == '-' && i != 0))) 
		//&& (cadena.GetAt(i) != '.' || cadena.GetAt(i) == '.' && bPunto == FALSE))	
		{				
			if (cadena.GetAt(i)== '.' && bPunto == FALSE)
				bPunto = TRUE;
			else
				return FALSE;
		}
	}
	return TRUE;
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusTarifaa()
{
	CString strAux=m_strTarifa1;
	GetDlgItem(IDC_TARIFAA)->GetWindowText(m_strTarifa1);
	if (strAux==m_strTarifa1)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strTarifa1)==TRUE)
	{
		GetDlgItem(IDC_TARIFAA)->SetWindowText(m_strTarifa1);
	}
	else
	{
		GetDlgItem(IDC_TARIFAA)->SetWindowText(strAux);
		m_strTarifa1=strAux;
		m_ctrlTarifa1.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusTarifab()
{
	CString strAux=m_strTarifa2;
	GetDlgItem(IDC_TARIFAB)->GetWindowText(m_strTarifa2);
	if (strAux==m_strTarifa2)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strTarifa2)==TRUE)
	{
		GetDlgItem(IDC_TARIFAB)->SetWindowText(m_strTarifa2);
	}
	else
	{
		GetDlgItem(IDC_TARIFAB)->SetWindowText(strAux);
		m_strTarifa2=strAux;
		m_ctrlTarifa2.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusTarifac()
{
	CString strAux=m_strTarifa3;
	GetDlgItem(IDC_TARIFAC)->GetWindowText(m_strTarifa3);
	if (strAux==m_strTarifa3)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strTarifa3)==TRUE)
	{
		GetDlgItem(IDC_TARIFAC)->SetWindowText(m_strTarifa3);
	}
	else
	{
		GetDlgItem(IDC_TARIFAC)->SetWindowText(strAux);
		m_strTarifa3=strAux;
		m_ctrlTarifa3.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusTarifad()
{
	CString strAux=m_strTarifa4;
	GetDlgItem(IDC_TARIFAD)->GetWindowText(m_strTarifa4);
	if (strAux==m_strTarifa4)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strTarifa4)==TRUE)
	{
		GetDlgItem(IDC_TARIFAD)->SetWindowText(m_strTarifa4);
	}
	else
	{
		GetDlgItem(IDC_TARIFAD)->SetWindowText(strAux);
		m_strTarifa4=strAux;
		m_ctrlTarifa4.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusTarifae()
{
	CString strAux=m_strTarifa5;
	GetDlgItem(IDC_TARIFAE)->GetWindowText(m_strTarifa5);
	if (strAux==m_strTarifa5)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strTarifa5)==TRUE)
	{
		GetDlgItem(IDC_TARIFAE)->SetWindowText(m_strTarifa5);
	}
	else
	{
		GetDlgItem(IDC_TARIFAE)->SetWindowText(strAux);
		m_strTarifa5=strAux;
		m_ctrlTarifa5.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusTarifaf()
{
	CString strAux=m_strTarifa6;
	GetDlgItem(IDC_TARIFAF)->GetWindowText(m_strTarifa6);
	if (strAux==m_strTarifa6)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strTarifa6)==TRUE)
	{
		GetDlgItem(IDC_TARIFAF)->SetWindowText(m_strTarifa6);
	}
	else
	{
		GetDlgItem(IDC_TARIFAF)->SetWindowText(strAux);
		m_strTarifa6=strAux;
		m_ctrlTarifa6.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusTarifag()
{
	CString strAux=m_strTarifa7;
	GetDlgItem(IDC_TARIFAG)->GetWindowText(m_strTarifa7);
	if (strAux==m_strTarifa7)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strTarifa7)==TRUE)
	{
		GetDlgItem(IDC_TARIFAG)->SetWindowText(m_strTarifa7);
	}
	else
	{
		GetDlgItem(IDC_TARIFAG)->SetWindowText(strAux);
		m_strTarifa7=strAux;
		m_ctrlTarifa7.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusTarifah()
{
	CString strAux=m_strTarifa8;
	GetDlgItem(IDC_TARIFAH)->GetWindowText(m_strTarifa8);
	if (strAux==m_strTarifa8)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strTarifa8)==TRUE)
	{
		GetDlgItem(IDC_TARIFAH)->SetWindowText(m_strTarifa8);		
	}
	else
	{
		GetDlgItem(IDC_TARIFAH)->SetWindowText(strAux);
		m_strTarifa8=strAux;
		m_ctrlTarifa8.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusTarifai()
{
	CString strAux=m_strTarifa9;
	GetDlgItem(IDC_TARIFAI)->GetWindowText(m_strTarifa9);
	if (strAux==m_strTarifa9)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strTarifa9)==TRUE)
	{
		GetDlgItem(IDC_TARIFAI)->SetWindowText(m_strTarifa9);		
	}
	else
	{
		GetDlgItem(IDC_TARIFAI)->SetWindowText(strAux);
		m_strTarifa9=strAux;
		m_ctrlTarifa9.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusDescuentoa()
{
	CString strAux=m_strDescuento1;
	GetDlgItem(IDC_DESCUENTOA)->GetWindowText(m_strDescuento1);
	if (strAux==m_strDescuento1)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDescuento1)==TRUE)
	{
		GetDlgItem(IDC_DESCUENTOA)->SetWindowText(m_strDescuento1);
	}
	else
	{
		GetDlgItem(IDC_DESCUENTOA)->SetWindowText(strAux);
		m_strDescuento1=strAux;
		m_ctrlDescuento1.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusDescuentob()
{
	CString strAux=m_strDescuento2;
	GetDlgItem(IDC_DESCUENTOB)->GetWindowText(m_strDescuento2);
	if (strAux==m_strDescuento2)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDescuento2)==TRUE)
	{
		GetDlgItem(IDC_DESCUENTOB)->SetWindowText(m_strDescuento2);
	}
	else
	{
		
		GetDlgItem(IDC_DESCUENTOB)->SetWindowText(strAux);
		m_strDescuento2=strAux;
		m_ctrlDescuento2.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusDescuentoc()
{
	CString strAux=m_strDescuento3;
	GetDlgItem(IDC_DESCUENTOC)->GetWindowText(m_strDescuento3);
	if (strAux==m_strDescuento3)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDescuento3)==TRUE)
	{
		GetDlgItem(IDC_DESCUENTOC)->SetWindowText(m_strDescuento3);
	}
	else
	{
		GetDlgItem(IDC_DESCUENTOC)->SetWindowText(strAux);
		m_strDescuento3=strAux;
		m_ctrlDescuento3.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusDescuentod()
{
	CString strAux=m_strDescuento4;
	GetDlgItem(IDC_DESCUENTOD)->GetWindowText(m_strDescuento4);
	if (strAux==m_strDescuento4)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDescuento4)==TRUE)
	{
		GetDlgItem(IDC_DESCUENTOD)->SetWindowText(m_strDescuento4);
	}
	else
	{
		GetDlgItem(IDC_DESCUENTOD)->SetWindowText(strAux);
		m_strDescuento4=strAux;
		m_ctrlDescuento4.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusDescuentoe()
{
	CString strAux=m_strDescuento5;
	GetDlgItem(IDC_DESCUENTOE)->GetWindowText(m_strDescuento5);
	if (strAux==m_strDescuento5)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDescuento5)==TRUE)
	{
		GetDlgItem(IDC_DESCUENTOE)->SetWindowText(m_strDescuento5);
	}
	else
	{
		GetDlgItem(IDC_DESCUENTOE)->SetWindowText(strAux);
		m_strDescuento5=strAux;
		m_ctrlDescuento5.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusDescuentof()
{
	CString strAux=m_strDescuento6;
	GetDlgItem(IDC_DESCUENTOF)->GetWindowText(m_strDescuento6);
	if (strAux==m_strDescuento6)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDescuento6)==TRUE)
	{
		GetDlgItem(IDC_DESCUENTOF)->SetWindowText(m_strDescuento6);
	}
	else
	{
		GetDlgItem(IDC_DESCUENTOF)->SetWindowText(strAux);
		m_strDescuento6=strAux;
		m_ctrlDescuento6.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusDescuentog()
{
	CString strAux=m_strDescuento7;
	GetDlgItem(IDC_DESCUENTOG)->GetWindowText(m_strDescuento7);
	if (strAux==m_strDescuento7)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDescuento7)==TRUE)
	{
		GetDlgItem(IDC_DESCUENTOG)->SetWindowText(m_strDescuento7);
	}
	else
	{
		GetDlgItem(IDC_DESCUENTOG)->SetWindowText(strAux);
		m_strDescuento7=strAux;
		m_ctrlDescuento7.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusDescuentoh()
{
	CString strAux=m_strDescuento8;
	GetDlgItem(IDC_DESCUENTOH)->GetWindowText(m_strDescuento8);
	if (strAux==m_strDescuento8)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDescuento8)==TRUE)
	{
		GetDlgItem(IDC_DESCUENTOH)->SetWindowText(m_strDescuento8);
	}
	else
	{
		GetDlgItem(IDC_DESCUENTOH)->SetWindowText(strAux);
		m_strDescuento8=strAux;
		m_ctrlDescuento8.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasVentas::OnEnKillfocusDescuentoi()
{
	CString strAux=m_strDescuento9;
	GetDlgItem(IDC_DESCUENTOI)->GetWindowText(m_strDescuento9);
	if (strAux==m_strDescuento9)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDescuento9)==TRUE)
	{
		GetDlgItem(IDC_DESCUENTOI)->SetWindowText(m_strDescuento9);
	}
	else
	{
		GetDlgItem(IDC_DESCUENTOI)->SetWindowText(strAux);
		m_strDescuento9=strAux;
		m_ctrlDescuento9.SetFocus();
	}
}

void CDlgTarifasVentas::OnEnKillfocusTarifaVenta()
{
	CString strAux=m_strTarVen;
	GetDlgItem(IDC_TARIFA_VENTA)->GetWindowText(m_strTarVen);
	if (strAux==m_strTarVen)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strTarVen)==TRUE)
	{
		GetDlgItem(IDC_TARIFA_VENTA)->SetWindowText(m_strTarVen);
	}
	else
	{
		GetDlgItem(IDC_TARIFA_VENTA)->SetWindowText(strAux);
		m_strTarVen=strAux;
		GetDlgItem(IDC_TARIFA_VENTA)->SetFocus();
	}
}
