// DlgDatosFacturacion.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgDatosFacturacion.h"
#include ".\dlgdatosfacturacion.h"

#define N 0
#define S 1

// Cuadro de diálogo de CDlgDatosFacturacion

IMPLEMENT_DYNAMIC(CDlgDatosFacturacion, CDialog)
CDlgDatosFacturacion::CDlgDatosFacturacion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDatosFacturacion::IDD, pParent)
	, m_strDto1(_T(""))
	, m_strDto2(_T(""))
	, m_strDto3(_T(""))
	, m_strPronto(_T(""))
	, m_strPorcentaje(_T(""))
	, m_strRetencion(_T(""))
	, m_strCompras(_T(""))
	, m_strComDes(_T(""))
	, m_strDesRetencion(_T(""))
	, m_cIrpf(0)
	, m_bIrpf(FALSE)
{
}

CDlgDatosFacturacion::~CDlgDatosFacturacion()
{
}

void CDlgDatosFacturacion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_DES_COM1, m_strDto1);
	DDX_Text(pDX, IDC_DES_COM2, m_strDto2);
	DDX_Text(pDX, IDC_DES_COM3, m_strDto3);
	DDX_Text(pDX, IDC_PRONTO_PAGO, m_strPronto);
	DDX_Text(pDX, IDC_PORCENTAJE, m_strPorcentaje);
	DDX_Text(pDX, IDC_CUENTA, m_strRetencion);
	DDV_MaxChars(pDX, m_strRetencion, 9);
	DDX_Text(pDX, IDC_COMPRAS, m_strCompras);
	DDV_MaxChars(pDX, m_strCompras, 9);
	DDX_Text(pDX, IDC_TEXTOCULTO, m_strComDes);
	DDX_Text(pDX, IDC_TEXTOCULTO2, m_strDesRetencion);
	DDX_Radio(pDX, IDC_IRPF1, m_bIrpf);
	DDX_Radio(pDX, IDC_IRPF1, m_bIrpf);
	
}


BEGIN_MESSAGE_MAP(CDlgDatosFacturacion, CDialog)
	ON_BN_CLICKED(IDC_IRPF1, OnBnClickedIrpf1)
	ON_BN_CLICKED(IDC_IRPF2, OnBnClickedIrpf2)
	ON_BN_CLICKED(IDC_BOTON_RETENCION, OnBnClickedBotonRetencion)
	ON_BN_CLICKED(IDC_BOTON_COMPRA, OnBnClickedBotonCompra)
	ON_EN_KILLFOCUS(IDC_PORCENTAJE, OnEnKillfocusPorcentaje)
	ON_EN_KILLFOCUS(IDC_CUENTA, OnEnKillfocusCuenta)
	ON_EN_KILLFOCUS(IDC_DES_COM1, OnEnKillfocusDesCom1)
	ON_EN_KILLFOCUS(IDC_DES_COM2, OnEnKillfocusDesCom2)
	ON_EN_KILLFOCUS(IDC_DES_COM3, OnEnKillfocusDesCom3)
	ON_EN_KILLFOCUS(IDC_PRONTO_PAGO, OnEnKillfocusProntoPago)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_COMPRAS, OnEnKillfocusCompras)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CDlgDatosFacturacion::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_BOTON_RETENCION)->EnableWindow(FALSE);
	if (m_bUpdate==TRUE)
	{
		/////CARGA/LOS/DATOS////
		m_strDto1.Format("%.2f",m_rsProve->m_DCTO2);
		m_strDto2.Format("%.2f",m_rsProve->m_DCTO3);
		m_strDto3.Format("%.2f",m_rsProve->m_DCTOS);
		m_strPronto.Format("%.2f",m_rsProve->m_PP);
		m_strPorcentaje.Format("%.2f",m_rsProve->m_PORRETE);
		m_strRetencion=m_rsProve->m_CTARETE;
		m_strCompras=m_rsProve->m_CTACOM;
		UpdateData(FALSE);

		m_strDesRetencion=BuscaCuentas(m_strRetencion);
		m_strComDes=BuscaCuentas(m_strCompras);
		
		if (m_rsProve->m_RETENCION=='S')
		{
			m_bIrpf=S;
			Activa();
		}
		if (m_rsProve->m_RETENCION=='N')
		{
			m_bIrpf=N;	
			Desactiva();
		}
		UpdateData(FALSE);
	}
	return FALSE;
}
/****************************************************************************************************/
/***                                        FUNCIONES
/****************************************************************************************************/
void CDlgDatosFacturacion::SetProve(CProve *rsProve )
{
	m_rsProve=rsProve;	
}
/////////////////////////////////////////////////////
void CDlgDatosFacturacion::SetUpdate(BOOL bUpdate)
{
	m_bUpdate = bUpdate;
}
/////////////////////////////////////////////////////
void CDlgDatosFacturacion::SetConexion(CDatabase *db)//realiza la conexion con las tablas
{
	m_db = db;
	m_rsProve->m_pDatabase=m_db;
}
/////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnBnClickedIrpf2()
{
	m_bIrpf=S;
	Activa();
}
/////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnBnClickedIrpf1()
{
	m_bIrpf=N;
	Desactiva();
}
/////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnBnClickedBotonRetencion()
{
	INT_PTR Estado=IDOK;
	m_dlgBusquedaCuentas.SetConexion(m_db);
	m_dlgBusquedaCuentas.SetTipo(CDialogBusqueda::CUENTAS);
	Estado=m_dlgBusquedaCuentas.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strRetencion=m_dlgBusquedaCuentas.GetCodigo();
	GetDlgItem(IDC_CUENTA)->SetWindowText(m_strRetencion);
	m_strDesRetencion=m_dlgBusquedaCuentas.GetDescripcion();
	GetDlgItem(IDC_TEXTOCULTO2)->SetWindowText(m_strDesRetencion);
}

void CDlgDatosFacturacion::OnBnClickedBotonCompra()
{
	INT_PTR Estado=IDOK;
	m_dlgBusquedaCuentas.SetConexion(m_db);
	m_dlgBusquedaCuentas.SetTipo(CDialogBusqueda::CUENTAS);
	Estado=m_dlgBusquedaCuentas.DoModal();
	if(Estado==IDCANCEL)
	{
		return;
	}
	m_strCompras=m_dlgBusquedaCuentas.GetCodigo();
	m_strComDes=m_dlgBusquedaCuentas.GetDescripcion();
	GetDlgItem(IDC_COMPRAS)->SetWindowText(m_strCompras);
	GetDlgItem(IDC_TEXTOCULTO)->SetWindowText(m_strComDes);
}
/////////////////////////////////////////////////////////////////////////////////
////////
/////////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnEnKillfocusPorcentaje()
{
	CString strAux=m_strPorcentaje;
	GetDlgItem(IDC_PORCENTAJE)->GetWindowText(m_strPorcentaje);
	if (strAux==m_strPorcentaje)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strPorcentaje)==TRUE)
	{
		GetDlgItem(IDC_PORCENTAJE)->SetWindowText(m_strPorcentaje);
	}
	else
	{
		GetDlgItem(IDC_PORCENTAJE)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strPorcentaje=strAux;
		m_ctrlPorcentaje.SetFocus();
	}	
}
/////////////////////////////////////////////////////////////////////////////////
////////
/////////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnEnKillfocusCuenta()
{
	CString strAux;
	GetDlgItem(IDC_CUENTA)->GetWindowText(strAux);
	CCuentas rsCuenta;
	rsCuenta.m_strFilter="CUENTA LIKE '" + strAux + "'";//filtro de busqueda
	if (!rsCuenta.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}
	if (rsCuenta.m_NOMBRE.IsEmpty())
	{
		AfxMessageBox(IDC_CODIGONOVALIDO);
		GetDlgItem(IDC_CUENTA)->SetWindowText(m_strRetencion);
		return; 
	}
	m_strRetencion=strAux;
	GetDlgItem(IDC_CUENTA)->SetWindowText(m_strRetencion);
	m_strDesRetencion=rsCuenta.m_NOMBRE.TrimRight();
	GetDlgItem(IDC_TEXTOCULTO2)->SetWindowText(m_strDesRetencion);
}
/////////////////////////////////////////////////////////////////////////////////
////////
/////////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnEnKillfocusCompras()
{
	CString strAux;
	GetDlgItem(IDC_COMPRAS)->GetWindowText(strAux);
	if (strAux.IsEmpty())
	{
		m_strComDes.Empty();
		GetDlgItem(IDC_TEXTOCULTO)->SetWindowText(m_strComDes);
		return;
	}
	CCuentas rsCuenta;
	rsCuenta.m_strFilter="CUENTA LIKE '" + strAux + "'";//filtro de busqueda
	if (!rsCuenta.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}
	if (rsCuenta.m_NOMBRE.IsEmpty())
	{
		AfxMessageBox(IDC_CODIGONOVALIDO);
		GetDlgItem(IDC_COMPRAS)->SetWindowText(m_strCompras);
		return; 
	}
	m_strCompras=strAux;
	GetDlgItem(IDC_COMPRAS)->SetWindowText(m_strCompras);
	m_strComDes=rsCuenta.m_NOMBRE.TrimRight();
	GetDlgItem(IDC_TEXTOCULTO)->SetWindowText(m_strComDes);
}

/////////////////////////////////////////////////////////////////////////////////
////////
/////////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnEnKillfocusDesCom1()
{
	CString strAux=m_strDto1;
	GetDlgItem(IDC_DES_COM1)->GetWindowText(m_strDto1);
	if (strAux==m_strDto1)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDto1)==TRUE)
	{
		GetDlgItem(IDC_DES_COM1)->SetWindowText(m_strDto1);
	}
	else
	{
		GetDlgItem(IDC_DES_COM1)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strDto1=strAux;
		m_ctrlDto1.SetFocus();
	}
}
/////////////////////////////////////////////////////////////////////////////////
////////
/////////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnEnKillfocusDesCom2()
{
	CString strAux=m_strDto2;
	GetDlgItem(IDC_DES_COM2)->GetWindowText(m_strDto2);
	if (strAux==m_strDto2)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDto2)==TRUE)
	{
		GetDlgItem(IDC_DES_COM2)->SetWindowText(m_strDto2);
	}
	else
	{
		GetDlgItem(IDC_DES_COM2)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strDto2=strAux;
		m_ctrlDto2.SetFocus();
	}
}
/////////////////////////////////////////////////////////////////////////////////
////////
/////////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnEnKillfocusDesCom3()
{
	CString strAux=m_strDto3;
	GetDlgItem(IDC_DES_COM3)->GetWindowText(m_strDto3);
	if (strAux==m_strDto3)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDto3)==TRUE)
	{
		GetDlgItem(IDC_DES_COM3)->SetWindowText(m_strDto3);
	}
	else
	{
		GetDlgItem(IDC_DES_COM3)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strDto3=strAux;
		m_ctrlDto3.SetFocus();
	}
}
///////////////////////////////////////////////////////////////////////////////
//////
///////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnEnKillfocusProntoPago()
{
	CString strAux=m_strPronto;
	GetDlgItem(IDC_PRONTO_PAGO)->GetWindowText(m_strPronto);
	if (strAux==m_strPronto)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strPronto)==TRUE)
	{
		GetDlgItem(IDC_PRONTO_PAGO)->SetWindowText(m_strPronto);
	}
	else
	{
		GetDlgItem(IDC_PRONTO_PAGO)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strPronto=strAux;
		m_ctrlPronto.SetFocus();
	}
}
///////////////////////////////////////////////////////////////////////////////
//////
///////////////////////////////////////////////////////////////////////////////
BOOL CDlgDatosFacturacion::ChequeaNumeros(CString cadena)
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
///////////////////////////////////////////////////////////////////////////////
//////
///////////////////////////////////////////////////////////////////////////////
CString CDlgDatosFacturacion::BuscaCuentas(CString cadena)
{
	CCuentas rsCuenta;
	CString Aux;
	rsCuenta.m_strFilter="CUENTA LIKE '" + cadena + "'";//filtro de busqueda
	if (!rsCuenta.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}
	return rsCuenta.m_NOMBRE.TrimRight();;
}
///////////////////////////////////////////////////////////////////////////////
//////
///////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::Activa()
{
	GetDlgItem(IDC_PORCENTAJE)->SetWindowText(m_strPorcentaje);
	GetDlgItem(IDC_CUENTA)->SetWindowText(m_strRetencion);
	GetDlgItem(IDC_TEXTOCULTO2)->SetWindowText(m_strDesRetencion);
	GetDlgItem(IDC_BOTON_RETENCION)->EnableWindow(TRUE);
	GetDlgItem(IDC_PORCENTAJE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CUENTA)->EnableWindow(TRUE);
}
///////////////////////////////////////////////////////////////////////////////
//////
///////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::Desactiva()
{
	GetDlgItem(IDC_PORCENTAJE)->SetWindowText("");
	GetDlgItem(IDC_CUENTA)->SetWindowText("");
	GetDlgItem(IDC_TEXTOCULTO2)->SetWindowText("");
	////////////////////////////////////////////
	GetDlgItem(IDC_BOTON_RETENCION)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORCENTAJE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CUENTA)->EnableWindow(FALSE);
}
///////////////////////////////////////////////////////////////////////////////
//////
///////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnBnClickedOk()
{
	UpdateData(TRUE);
	m_rsProve->m_DCTO2=atof(m_strDto1);
	m_rsProve->m_DCTO3=atof(m_strDto2);
	m_rsProve->m_DCTOS=atof(m_strDto3);
	m_rsProve->m_PP=atof(m_strPronto);
	m_rsProve->m_PORRETE=atof(m_strPorcentaje);
	m_rsProve->m_CTARETE=m_strRetencion;
	m_rsProve->m_CTACOM=m_strCompras;
	if (m_bIrpf==S)
		m_rsProve->m_RETENCION='S';
	if (m_bIrpf==N)
		m_rsProve->m_RETENCION='N';
	OnOK();
}
////////////////////////////////////////////////////////////////////////////////
///////
///////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacion::OnBnClickedCancel()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	OnCancel();
}
