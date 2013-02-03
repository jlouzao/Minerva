// DlgDatosFacturacionClientes.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgDatosFacturacionClientes.h"
#include ".\dlgdatosfacturacionclientes.h"

#define SI 0
#define NO 1

// Cuadro de diálogo de CDlgDatosFacturacionClientes

IMPLEMENT_DYNAMIC(CDlgDatosFacturacionClientes, CDialog)
CDlgDatosFacturacionClientes::CDlgDatosFacturacionClientes(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDatosFacturacionClientes::IDD, pParent)
	, m_strComercial1(_T(""))
	, m_strComercial2(_T(""))
	, m_strComercial3(_T(""))
	, m_strPronto(_T(""))
	, m_bFiscal(FALSE)
	//, m_strCuentaComercial(_T(""))
	, m_strCuentaFiscal(_T(""))
	, m_strDesCuentaFiscal(_T(""))
	//, m_strDesCuentaComercial(_T(""))
	, m_strGrupoFacturacion(_T(""))
	, m_strCopias(_T(""))
	, m_strAbonar(_T(""))
	, m_strNombre(_T(""))
	, m_strDireccion(_T(""))
	, m_strSG(_T(""))
	, m_strNumero(_T(""))
	, m_strCP(_T(""))
	, m_strPoblacion(_T(""))
	, m_strProvincia(_T(""))
	, m_strPais(_T(""))
	, m_strDesPais(_T(""))
	, m_strTarifa(_T(""))
	//, m_bComercial(FALSE)
	, m_strPorrete(_T(""))
	, m_bAbonoProx(FALSE)
{
}

CDlgDatosFacturacionClientes::~CDlgDatosFacturacionClientes()
{
}

void CDlgDatosFacturacionClientes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TARIFA, m_comboTarifa);
	DDX_Text(pDX, IDC_COMERCIAL1, m_strComercial1);
	DDX_Text(pDX, IDC_COMERCIAL2, m_strComercial2);
	DDX_Text(pDX, IDC_COMERCIAL3, m_strComercial3);
	DDX_Text(pDX, IDC_PRONTOPAGO, m_strPronto);
	DDX_Radio(pDX, IDC_RFISCAL1, m_bFiscal);
//	DDX_Text(pDX, IDC_CUENTA_COMERCIAL, m_strCuentaComercial);
//	DDV_MaxChars(pDX, m_strCuentaComercial, 9);
	DDX_Text(pDX, IDC_CUENTA_FISCAL, m_strCuentaFiscal);
	DDV_MaxChars(pDX, m_strCuentaFiscal, 9);
	DDX_Text(pDX, IDC_DES_CUENTA_FISCAL, m_strDesCuentaFiscal);
//	DDX_Text(pDX, IDC_DES_CUENTA_COMERCIAL, m_strDesCuentaComercial);
	DDX_Text(pDX, IDC_GRUPO_FACTURACION, m_strGrupoFacturacion);
	DDV_MaxChars(pDX, m_strGrupoFacturacion, 1);
	DDX_Text(pDX, IDC_COPIAS, m_strCopias);
	DDX_Text(pDX, IDC_ABONAR, m_strAbonar);
	DDX_Text(pDX, IDC_NOMBRE, m_strNombre);
	DDV_MaxChars(pDX, m_strNombre, 50);
	DDX_Text(pDX, IDC_DIRECCION, m_strDireccion);
	DDV_MaxChars(pDX, m_strDireccion, 50);
	DDX_Text(pDX, IDC_SG, m_strSG);
	DDV_MaxChars(pDX, m_strSG, 2);
	DDX_Text(pDX, IDC_NUMERO, m_strNumero);
	DDV_MaxChars(pDX, m_strNumero, 5);
	DDX_Text(pDX, IDC_CP, m_strCP);
	DDV_MaxChars(pDX, m_strCP, 5);
	DDX_Text(pDX, IDC_POBLACION, m_strPoblacion);
	DDV_MaxChars(pDX, m_strPoblacion, 25);
	DDX_Text(pDX, IDC_PROVINCIA, m_strProvincia);
	DDV_MaxChars(pDX, m_strProvincia, 15);
	DDX_Text(pDX, IDC_PAIS, m_strPais);
	DDV_MaxChars(pDX, m_strPais, 3);
	DDX_Text(pDX, IDC_DES_PAIS, m_strDesPais);
	DDV_MaxChars(pDX, m_strDesPais, 25);
	DDX_Control(pDX, IDC_CUENTA_FISCAL, m_ctrlCuentaFiscal);
	//DDX_Control(pDX, IDC_CUENTA_COMERCIAL, m_ctrlCuentaComercial);
	DDX_CBString(pDX, IDC_COMBO_TARIFA, m_strTarifa);
	//DDX_Radio(pDX, IDC_RCOMERCIAL1, m_bComercial);
	DDX_Text(pDX, IDC_PORCENTAJE_FISCAL, m_strPorrete);
	DDX_Check(pDX, IDC_PROXIMA_FACTURA, m_bAbonoProx);
	DDX_Control(pDX, IDC_COMERCIAL1, m_ctrlComercial1);
	DDX_Control(pDX, IDC_COMERCIAL2, m_ctrlComercial2);
	DDX_Control(pDX, IDC_COMERCIAL3, m_ctrlComercial3);
	DDX_Control(pDX, IDC_PRONTOPAGO, m_ctrlPronto);
	DDX_Control(pDX, IDC_PORCENTAJE_FISCAL, m_ctrlPorrete);
	DDX_Control(pDX, IDC_COPIAS, m_ctrlCopias);
	DDX_Control(pDX, IDC_ABONAR, m_ctrlAbonar);
	DDX_Control(pDX, IDC_NUMERO, m_ctrlNumero);
	DDX_Control(pDX, IDC_PAIS, m_ctrlPais);
}


BEGIN_MESSAGE_MAP(CDlgDatosFacturacionClientes, CDialog)
	ON_EN_KILLFOCUS(IDC_CUENTA_FISCAL, OnEnKillfocusCuentaFiscal)
//	ON_EN_KILLFOCUS(IDC_CUENTA_COMERCIAL, OnEnKillfocusCuentaComercial)
	ON_EN_KILLFOCUS(IDC_PAIS, OnEnKillfocusPais)
	ON_BN_CLICKED(IDC_PROXIMA_FACTURA, OnBnClickedProximaFactura)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BOTON_FISCAL, OnBnClickedBotonFiscal)
//	ON_BN_CLICKED(IDC_BOTON_COMERCIAL, OnBnClickedBotonComercial)
	ON_BN_CLICKED(IDC_BOTON_PAIS, OnBnClickedBotonPais)
	ON_EN_KILLFOCUS(IDC_COMERCIAL1, OnEnKillfocusComercial1)
	ON_EN_KILLFOCUS(IDC_COMERCIAL2, OnEnKillfocusComercial2)
	ON_EN_KILLFOCUS(IDC_COMERCIAL3, OnEnKillfocusComercial3)
	ON_EN_KILLFOCUS(IDC_PRONTOPAGO, OnEnKillfocusProntopago)
	ON_EN_KILLFOCUS(IDC_PORCENTAJE_FISCAL, OnEnKillfocusPorcentajeFiscal)
	ON_EN_KILLFOCUS(IDC_ABONAR, OnEnKillfocusAbonar)
	ON_BN_CLICKED(IDC_RFISCAL2, OnBnClickedRfiscal2)
	ON_BN_CLICKED(IDC_RFISCAL1, OnBnClickedRfiscal1)
//	ON_BN_CLICKED(IDC_RCOMERCIAL1, OnBnClickedRcomercial1)
//	ON_BN_CLICKED(IDC_RCOMERCIAL2, OnBnClickedRcomercial2)
END_MESSAGE_MAP()

BOOL CDlgDatosFacturacionClientes::OnInitDialog()
{
	CDialog::OnInitDialog();
	/*******INICIO EL COMBO CON TODOS LOS ELEMENTOS QUE VA A LLEVAR ******/
	m_comboTarifa.AddString("A");m_comboTarifa.AddString("B");m_comboTarifa.AddString("C");
	m_comboTarifa.AddString("D");m_comboTarifa.AddString("E");m_comboTarifa.AddString("F");
	m_comboTarifa.AddString("G");m_comboTarifa.AddString("H");m_comboTarifa.AddString("I");
    /******* CARGA LAS BUSQUEDAS PARA AHORRAR TIEMPO ********/
	m_dlgBusquedaPais.SetConexion(m_db); 
	m_dlgBusquedaCuenta.SetConexion(m_db);
	/********************************************************/
	if (m_bUpdate == TRUE)
	{
		m_strTarifa=m_rsCliente->m_TARIFA.TrimRight();
		m_strComercial1.Format("%.2f",m_rsCliente->m_DCTOS2);
		m_strComercial2.Format("%.2f",m_rsCliente->m_DCTOS3);
		m_strComercial3.Format("%.2f",m_rsCliente->m_DCTOS);
		m_strPronto.Format("%.2f",m_rsCliente->m_PP);
		m_strCuentaFiscal=m_rsCliente->m_CTARETE.TrimRight();
		m_strPorrete.Format("%.3f",m_rsCliente->m_PORRETE);
	//	m_strCuentaComercial=m_rsCliente->m_CTRCTA.TrimRight();
		////////////////////////////////////////////////////
	//	m_strDesCuentaComercial=EncuentraCuenta(m_strCuentaComercial);
		m_strPais=EncuentraPais(m_strPais);
		////////////////////////////////////////////////////
		m_strGrupoFacturacion=m_rsCliente->m_GRUFAC;
		m_strCopias.Format("%.0f",m_rsCliente->m_COPFAC);
		m_strAbonar.Format("%.2f",m_rsCliente->m_AABONAR);
		m_strNombre=m_rsCliente->m_NOMFAC.TrimRight();
		m_strDireccion=m_rsCliente->m_DIREFAC.TrimRight();
		m_strSG=m_rsCliente->m_SGFAC.TrimRight();
		m_strNumero=m_rsCliente->m_NUMEFAC.TrimRight();
		m_strCP=m_rsCliente->m_CPFAC.TrimRight();
		m_strPoblacion=m_rsCliente->m_POBFAC.TrimRight();
		m_strProvincia=m_rsCliente->m_PROVFAC.TrimRight();
		m_strPais=m_rsCliente->m_CPAISFAC.TrimRight();
		m_strDesPais=EncuentraPais(m_strPais);
		////////////////////////////////////////////////////
		if (m_rsCliente->m_RETFISCAL=='S')
		{
			m_bFiscal=SI;
			GetDlgItem(IDC_RFISCAL1)->CheckRadioButton(0,1,0);
			OnBnClickedRfiscal1();
			m_strDesCuentaFiscal=EncuentraCuenta(m_strCuentaFiscal);
			GetDlgItem(IDC_DES_CUENTA_FISCAL)->SetWindowText(m_strDesCuentaFiscal);
		}
		else
		{
			OnBnClickedRfiscal2();
			m_bFiscal=NO;
			GetDlgItem(IDC_RFISCAL1)->CheckRadioButton(0,1,1);
		}
		/*if (m_rsCliente->m_RETCOMER=='S')
		{
			m_bComercial=SI;
			GetDlgItem(IDC_RCOMERCIAL1)->CheckRadioButton(0,1,0);
			OnBnClickedRcomercial1();
			m_strDesCuentaComercial=EncuentraCuenta(m_strCuentaComercial);
			GetDlgItem(IDC_DES_CUENTA_COMERCIAL)->SetWindowText(m_strDesCuentaComercial);
		}
		else
		{
			OnBnClickedRcomercial2();
			m_bComercial=NO;
			GetDlgItem(IDC_RFISCAL1)->CheckRadioButton(0,1,1);
		}*/
		if (m_rsCliente->m_ABOPFAC=='S')
		{
			
			m_bAbonoProx=NO;
		}
		else
		{
			m_bAbonoProx=SI;
		}
		UpdateData(FALSE);
	}
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
/////         realiza la conexion con las tablas
///////////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgDatosFacturacionClientes::SetCliente(CClientes *rsCliente )
{
	m_rsCliente=rsCliente;	
}
/*********************************************************************************************************/
void CDlgDatosFacturacionClientes::SetUpdate(BOOL bUpdate)
{
	m_bUpdate = bUpdate;
}
/*********************************************************************************************************/
void CDlgDatosFacturacionClientes::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsCliente->m_pDatabase=m_db;
}
/*********************************************************************************************************/
/****
/*********************************************************************************************************/
void CDlgDatosFacturacionClientes::OnEnKillfocusCuentaFiscal()
{
	CString strAux=m_strCuentaFiscal;
	CString strDesAux;
	GetDlgItem(IDC_CUENTA_FISCAL)->GetWindowText(m_strCuentaFiscal);
	if (m_strCuentaFiscal.IsEmpty())
	{
		m_strDesCuentaFiscal.Empty();
		GetDlgItem(IDC_DES_CUENTA_FISCAL)->SetWindowText(m_strDesCuentaFiscal);
		return;
	}
	strDesAux=EncuentraCuenta(m_strCuentaFiscal);
	if (strDesAux.IsEmpty())
	{
		m_strCuentaFiscal=strAux;
		GetDlgItem(IDC_CUENTA_FISCAL)->SetWindowText(m_strCuentaFiscal);
		m_ctrlCuentaFiscal.SetFocus();
	}
	else
	{
		m_strDesCuentaFiscal=strDesAux;
		GetDlgItem(IDC_DES_CUENTA_FISCAL)->SetWindowText(m_strDesCuentaFiscal);
	}
}
/*********************************************************************************************************/
/****
/*********************************************************************************************************/
/*void CDlgDatosFacturacionClientes::OnEnKillfocusCuentaComercial()
{
	CString strAux=m_strCuentaComercial;
	CString strDesAux;
	GetDlgItem(IDC_CUENTA_COMERCIAL)->GetWindowText(m_strCuentaComercial);
	if (m_strCuentaComercial.IsEmpty())
	{
		m_strDesCuentaComercial.Empty();
		GetDlgItem(IDC_DES_CUENTA_COMERCIAL)->SetWindowText(m_strDesCuentaComercial);
		return;
	}
	strDesAux=EncuentraCuenta(m_strCuentaComercial);
	if (strDesAux.IsEmpty())
	{
		m_strCuentaComercial=strAux;
		GetDlgItem(IDC_CUENTA_COMERCIAL)->SetWindowText(m_strCuentaComercial);
		m_ctrlCuentaComercial.SetFocus();
	}
	else
	{
		m_strDesCuentaComercial=strDesAux;
		GetDlgItem(IDC_DES_CUENTA_COMERCIAL)->SetWindowText(m_strDesCuentaComercial);
	}
}
/*********************************************************************************************************/
/****
/*********************************************************************************************************/
void CDlgDatosFacturacionClientes::OnEnKillfocusPais()
{
	CString strAux=m_strPais;
	GetDlgItem(IDC_PAIS)->GetWindowText(m_strPais);
	if (m_strPais.IsEmpty())
	{
		m_strDesPais.Empty();
		GetDlgItem(IDC_DES_PAIS)->SetWindowText(m_strDesPais);
		return;
	}
	CString strDesAux=EncuentraPais(m_strPais);
	if (strDesAux.IsEmpty())
	{
		m_strPais=strAux;
		GetDlgItem(IDC_PAIS)->SetWindowText(m_strPais);
		m_ctrlPais.SetFocus();
	}
	else
	{
		m_strDesPais=strDesAux;
		GetDlgItem(IDC_DES_PAIS)->SetWindowText(m_strDesPais);
	}
}
/*********************************************************************************************************/
/****
/*********************************************************************************************************/
void CDlgDatosFacturacionClientes::OnBnClickedProximaFactura()
{
	if(m_bAbonoProx==NO)
	{
		//GetDlgItem(IDC_ABONAR)->EnableWindow(TRUE);
		m_bAbonoProx=SI;
		return;
	}
	if(m_bAbonoProx==SI)
	{
		//GetDlgItem(IDC_ABONAR)->EnableWindow(FALSE);
		m_bAbonoProx=NO;
		return;
	}
}
/*********************************************************************************************************/
/****
/*********************************************************************************************************/
void CDlgDatosFacturacionClientes::OnBnClickedOk()
{
	UpdateData(TRUE);
	m_rsCliente->m_TARIFA=m_strTarifa.TrimRight();
	m_rsCliente->m_DCTOS2=atof(m_strComercial1.TrimRight());
	m_rsCliente->m_DCTOS3=atof(m_strComercial2.TrimRight());
	m_rsCliente->m_DCTOS=atof(m_strComercial3.TrimRight());
	m_rsCliente->m_PP=atof(m_strPronto.TrimRight());
	m_rsCliente->m_PORRETE=atof(m_strPorrete.TrimRight());
	if (m_bFiscal==SI)
	{		m_rsCliente->m_RETFISCAL='S';	}
	else
	{		m_rsCliente->m_RETFISCAL='N';	}
/*	if (m_bComercial==SI)
	{		m_rsCliente->m_RETCOMER='S';	}
	else
	{		m_rsCliente->m_RETCOMER='N';	}*/
	if (m_bAbonoProx==SI)
	{		m_rsCliente->m_ABOPFAC='N';	}
	else
	{		m_rsCliente->m_ABOPFAC='S';		}
//	m_rsCliente->m_CTRCTA=m_strCuentaComercial.TrimRight();
	m_rsCliente->m_CTARETE=m_strCuentaFiscal.TrimRight();
	m_rsCliente->m_GRUFAC=m_strGrupoFacturacion.TrimRight();
	m_rsCliente->m_COPFAC=atof(m_strCopias.TrimRight());
	m_rsCliente->m_AABONAR=atof(m_strAbonar.TrimRight());
	m_rsCliente->m_NOMFAC=m_strNombre.TrimRight();
	m_rsCliente->m_DIREFAC=m_strDireccion.TrimRight();
	m_rsCliente->m_SGFAC=m_strSG.TrimRight();
	m_rsCliente->m_NUMEFAC=m_strNumero.TrimRight();
	m_rsCliente->m_CPFAC=m_strCP.TrimRight();
	m_rsCliente->m_POBFAC=m_strPoblacion.TrimRight();
	m_rsCliente->m_PROVFAC=m_strProvincia.TrimRight();
	m_rsCliente->m_CPAISFAC=m_strPais.TrimRight();
	OnOK();
}
/*********************************************************************************************************/
/****
/*********************************************************************************************************/
void CDlgDatosFacturacionClientes::OnBnClickedBotonFiscal()
{
	INT_PTR Estado;
	m_dlgBusquedaCuenta.SetTipo(CDialogBusqueda::CUENTAS);
	Estado=m_dlgBusquedaCuenta.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strCuentaFiscal=m_dlgBusquedaCuenta.GetCodigo();
	m_strDesCuentaFiscal=m_dlgBusquedaCuenta.GetDescripcion();
	GetDlgItem(IDC_CUENTA_FISCAL)->SetWindowText(m_strCuentaFiscal);
	GetDlgItem(IDC_DES_CUENTA_FISCAL)->SetWindowText(m_strDesCuentaFiscal);

}
/*********************************************************************************************************/
/****
/*********************************************************************************************************/
/*void CDlgDatosFacturacionClientes::OnBnClickedBotonComercial()
{
	INT_PTR Estado;
	m_dlgBusquedaCuenta.SetTipo(CDialogBusqueda::CUENTAS);
	Estado=m_dlgBusquedaCuenta.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strCuentaComercial=m_dlgBusquedaCuenta.GetCodigo();
	m_strDesCuentaComercial=m_dlgBusquedaCuenta.GetDescripcion();
	GetDlgItem(IDC_CUENTA_COMERCIAL)->SetWindowText(m_strCuentaComercial);
	GetDlgItem(IDC_DES_CUENTA_COMERCIAL)->SetWindowText(m_strDesCuentaComercial);
}
/*********************************************************************************************************/
/****
/*********************************************************************************************************/
void CDlgDatosFacturacionClientes::OnBnClickedBotonPais()
{
	INT_PTR Estado;
	m_dlgBusquedaPais.SetTipo(CDialogBusqueda::PAIS);
	Estado=m_dlgBusquedaPais.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strPais=m_dlgBusquedaPais.GetCodigo();
	m_strDesPais=m_dlgBusquedaPais.GetDescripcion();
	GetDlgItem(IDC_PAIS)->SetWindowText(m_strPais);
	GetDlgItem(IDC_DES_PAIS)->SetWindowText(m_strDesPais);
}
/*********************************************************************************************************/
/****
/*********************************************************************************************************/
CString CDlgDatosFacturacionClientes::EncuentraCuenta(CString cadena)
{
	CCuentas rsCuenta(m_db);
	rsCuenta.m_strFilter="CUENTA LIKE '" + cadena + "'";
	if (!rsCuenta.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return NULL;
	}
	if (rsCuenta.m_NOMBRE.IsEmpty())
	{
		rsCuenta.Close();
		return NULL;
	}
	else
	{
		CString strAux=rsCuenta.m_NOMBRE.TrimRight();
		rsCuenta.Close();
		return strAux;
	}
}
/*********************************************************************************************************/
/****
/*********************************************************************************************************/
CString CDlgDatosFacturacionClientes::EncuentraPais(CString cadena)
{
	CPais rsPais(m_db);
	rsPais.m_strFilter="CPAIS LIKE '" + cadena + "'";
	if (!rsPais.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return NULL;
	}
	if (rsPais.m_DPAIS.IsEmpty())
	{
		rsPais.Close();
		return NULL;
	}
	else
	{
		CString strAux=rsPais.m_DPAIS.TrimRight();
		rsPais.Close();
		return strAux;
	}
}
/************************************************************************************************************/
/**		          COMPRUEBA QUE EN LA CADENA NO HAY MAS QUE NUMEROS Y PUNTOS                        
/************************************************************************************************************/
BOOL CDlgDatosFacturacionClientes::ChequeaNumeros(CString cadena)
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
/************************************************************************************************************/
/**		          COMPRUEBA QUE EN LA CADENA NO HAY MAS QUE NUMEROS Y PUNTOS                        
/************************************************************************************************************/
void CDlgDatosFacturacionClientes::OnEnKillfocusComercial1()
{
	CString strAux=m_strComercial1;
	GetDlgItem(IDC_COMERCIAL1)->GetWindowText(m_strComercial1);
	if(m_strComercial1.IsEmpty())
	{return;}
	if(ChequeaNumeros(m_strComercial1)==FALSE)
	{
		m_strComercial1=strAux;
		GetDlgItem(IDC_COMERCIAL1)->SetWindowText(m_strComercial1);
		m_ctrlComercial1.SetFocus();
		return;
	}
}
/************************************************************************************************************/
/**		                                  
/************************************************************************************************************/
void CDlgDatosFacturacionClientes::OnEnKillfocusComercial2()
{
	CString strAux=m_strComercial2;
	GetDlgItem(IDC_COMERCIAL2)->GetWindowText(m_strComercial2);
	if(m_strComercial2.IsEmpty())
	{return;}
	if(ChequeaNumeros(m_strComercial2)==FALSE)
	{
		m_strComercial2=strAux;
		GetDlgItem(IDC_COMERCIAL2)->SetWindowText(m_strComercial2);
		m_ctrlComercial2.SetFocus();
		return;
	}
}
/************************************************************************************************************/
/**		                             
/************************************************************************************************************/
void CDlgDatosFacturacionClientes::OnEnKillfocusComercial3()
{
	CString strAux=m_strComercial3;
	GetDlgItem(IDC_COMERCIAL3)->GetWindowText(m_strComercial3);
	if(m_strComercial3.IsEmpty())
	{return;}
	if(ChequeaNumeros(m_strComercial3)==FALSE)
	{
		m_strComercial3=strAux;
		GetDlgItem(IDC_COMERCIAL3)->SetWindowText(m_strComercial3);
		m_ctrlComercial3.SetFocus();
		return;
		
	}	
}
/************************************************************************************************************/
/**		                                 
/************************************************************************************************************/
void CDlgDatosFacturacionClientes::OnEnKillfocusProntopago()
{
	CString strAux=m_strPronto;
	GetDlgItem(IDC_PRONTOPAGO)->GetWindowText(m_strPronto);
	if(m_strPronto.IsEmpty())
	{return;}
	if(ChequeaNumeros(m_strPronto)==FALSE)
	{
		m_strPronto=strAux;
		GetDlgItem(IDC_PRONTOPAGO)->SetWindowText(m_strPronto);
		m_ctrlPronto.SetFocus();
		return;
	}	
}
/************************************************************************************************************/
/**		                             
/************************************************************************************************************/
void CDlgDatosFacturacionClientes::OnEnKillfocusPorcentajeFiscal()
{
	CString strAux=m_strPorrete;
	GetDlgItem(IDC_PORCENTAJE_FISCAL)->GetWindowText(m_strPorrete);
	if(m_strPorrete.IsEmpty())
	{return;}
	if(ChequeaNumeros(m_strPorrete)==FALSE)
	{
		m_strPorrete=strAux;
		GetDlgItem(IDC_PORCENTAJE_FISCAL)->SetWindowText(m_strPorrete);
		m_ctrlPorrete.SetFocus();
		return;
	}
}
/************************************************************************************************************/
/**		                                  
/************************************************************************************************************/
void CDlgDatosFacturacionClientes::OnEnKillfocusAbonar()
{
	CString strAux=m_strAbonar;
	GetDlgItem(IDC_ABONAR)->GetWindowText(m_strAbonar);
	if(m_strAbonar.IsEmpty())
	{return;}
	if(ChequeaNumeros(m_strAbonar)==FALSE)
	{
		m_strAbonar=strAux;
		GetDlgItem(IDC_ABONAR)->SetWindowText(m_strAbonar);
			m_ctrlAbonar.SetFocus();
		return;
	}
}
/************************************************************************************************************/
/**		                                 
/************************************************************************************************************/

void CDlgDatosFacturacionClientes::OnBnClickedRfiscal2()
{
	GetDlgItem(IDC_PORCENTAJE_FISCAL)->SetWindowText("");
	GetDlgItem(IDC_PORCENTAJE_FISCAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_CUENTA_FISCAL)->SetWindowText("");
	GetDlgItem(IDC_CUENTA_FISCAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_DES_CUENTA_FISCAL)->SetWindowText("");
	GetDlgItem(IDC_BOTON_FISCAL)->EnableWindow(FALSE);
}

void CDlgDatosFacturacionClientes::OnBnClickedRfiscal1()
{
	GetDlgItem(IDC_PORCENTAJE_FISCAL)->SetWindowText(m_strPorrete);
	GetDlgItem(IDC_PORCENTAJE_FISCAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_CUENTA_FISCAL)->SetWindowText(m_strCuentaFiscal);
	GetDlgItem(IDC_CUENTA_FISCAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_DES_CUENTA_FISCAL)->SetWindowText(m_strDesCuentaFiscal);
	GetDlgItem(IDC_BOTON_FISCAL)->EnableWindow(TRUE);
}

/*void CDlgDatosFacturacionClientes::OnBnClickedRcomercial1()
{
	GetDlgItem(IDC_CUENTA_COMERCIAL)->SetWindowText(m_strCuentaComercial);
	GetDlgItem(IDC_CUENTA_COMERCIAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BOTON_COMERCIAL)->EnableWindow(TRUE);
}

void CDlgDatosFacturacionClientes::OnBnClickedRcomercial2()
{
	GetDlgItem(IDC_CUENTA_COMERCIAL)->SetWindowText("");
	GetDlgItem(IDC_CUENTA_COMERCIAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BOTON_COMERCIAL)->EnableWindow(FALSE);
}*/
