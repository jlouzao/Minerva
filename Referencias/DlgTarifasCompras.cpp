// DlgTarifasCompras.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgTarifasCompras.h"
#include ".\dlgtarifascompras.h"


// Cuadro de diálogo de CDlgTarifasCompras

IMPLEMENT_DYNAMIC(CDlgTarifasCompras, CDialog)
CDlgTarifasCompras::CDlgTarifasCompras(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTarifasCompras::IDD, pParent)
	, m_strDescuento(_T(""))
	, m_strPrecio(_T(""))
{
}

CDlgTarifasCompras::~CDlgTarifasCompras()
{
}

void CDlgTarifasCompras::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DESCUENTO, m_strDescuento);
	DDX_Text(pDX, IDC_PRECIO_COSTE, m_strPrecio);
	DDX_Control(pDX, IDC_PRECIO_COSTE, m_ctrlPrecio);
	DDX_Control(pDX, IDC_DESCUENTO, m_ctrlDescuento);
}


BEGIN_MESSAGE_MAP(CDlgTarifasCompras, CDialog)
	ON_BN_CLICKED(IDC_ACEPTAR, OnBnClickedAceptar)
	ON_BN_CLICKED(IDC_CANCELAR, OnBnClickedCancelar)
	ON_EN_KILLFOCUS(IDC_PRECIO_COSTE, OnEnKillfocusPrecioCoste)
	ON_EN_KILLFOCUS(IDC_DESCUENTO, OnEnKillfocusDescuento)
END_MESSAGE_MAP()

BOOL CDlgTarifasCompras::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (bArtiNuevo==FALSE)
		RellenaCampos();
	UpdateData(FALSE);

	return TRUE;
}
/****************************************************************************/
void CDlgTarifasCompras::setNuevo(BOOL nuevo)
{
	bArtiNuevo=nuevo;
}
/****************************************************************************/
/******************************* FUNCIONES **********************************/
/****************************************************************************/
void CDlgTarifasCompras::SetArticulo(CArticulo *rsArticulo)
{
	m_rsArticulo=rsArticulo;
}
/****************************************************************************/
void CDlgTarifasCompras::SetConexion(CDatabase *db)
{
	m_db=db;
}

void CDlgTarifasCompras::SetReferencia(CString Ref)
{
	m_strCodReferencia=Ref;
}
/****************************************************************************/
void CDlgTarifasCompras::OnBnClickedAceptar()
{
	UpdateData(TRUE);
	m_rsArticulo->m_ETARI2=atof(m_strPrecio);
	m_rsArticulo->m_DTOARCO=atof(m_strDescuento);

	OnOK();
}
/****************************************************************************/
void CDlgTarifasCompras::RellenaCampos()//CString strCodReferencia)
{
	m_strPrecio.Format("%.2f",m_rsArticulo->m_ETARI2);
	m_strDescuento.Format("%.2f",m_rsArticulo->m_DTOARCO);
	UpdateData(FALSE);
}
/****************************************************************************/
void CDlgTarifasCompras::OnBnClickedCancelar()
{
	OnCancel();
}
/****************************************************************************/
void CDlgTarifasCompras::OnEnKillfocusPrecioCoste()
{
	CString strAux=m_strPrecio;
	GetDlgItem(IDC_PRECIO_COSTE)->GetWindowText(m_strPrecio);
	if (strAux==m_strPrecio)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strPrecio)==TRUE)
	{
		GetDlgItem(IDC_PRECIO_COSTE)->SetWindowText(m_strPrecio);
	}
	else
	{
		GetDlgItem(IDC_PRECIO_COSTE)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strPrecio=strAux;
		m_ctrlPrecio.SetFocus();
	}
}
/****************************************************************************/
void CDlgTarifasCompras::OnEnKillfocusDescuento()
{
	CString strAux=m_strDescuento;
	GetDlgItem(IDC_DESCUENTO)->GetWindowText(m_strDescuento);
	if (strAux==m_strDescuento)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strDescuento)==TRUE)
	{
		GetDlgItem(IDC_DESCUENTO)->SetWindowText(m_strDescuento);
	}
	else
	{
		GetDlgItem(IDC_DESCUENTO)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strDescuento=strAux;
		m_ctrlDescuento.SetFocus();
	}
}
/****************************************************************************/
BOOL CDlgTarifasCompras::ChequeaNumeros(CString cadena)
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