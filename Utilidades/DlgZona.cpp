// DlgZona.cpp: archivo de implementación
#include "Utilidades.h"
#include "stdafx.h"
#include "DlgZona.h"
#include ".\dlgZona.h"

#define INICIAL 0
#define BUSCADO 1

// Cuadro de diálogo de CDlgZona

IMPLEMENT_DYNAMIC(CDlgZona, CDialog)
CDlgZona::CDlgZona(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZona::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strDescripcion(_T(""))
	, m_strCuenta(_T(""))
	, m_strDesCuenta(_T(""))
	, bUpdate(FALSE)
	, iEstado(INICIAL)
{
}
/****************************************************************************/
CDlgZona::~CDlgZona()
{
	m_rsZona.Close();
}
/****************************************************************************/
void CDlgZona::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
		DDV_MaxChars(pDX, m_strCodigo, 3);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
		DDV_MaxChars(pDX, m_strDescripcion, 35);
	DDX_Text(pDX, IDC_CUENTA, m_strCuenta);
		DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_DESCUENTA, m_strDesCuenta);
}
/****************************************************************************/
BEGIN_MESSAGE_MAP(CDlgZona, CDialog)
	ON_BN_CLICKED(IDLIMPIAR, OnBnClickedLimpiar)
	ON_EN_KILLFOCUS(IDC_CODIGO, OnEnKillfocusCodigo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
	ON_EN_KILLFOCUS(IDC_CUENTA, OnEnKillfocusCuenta)
	ON_BN_CLICKED(IDBUSCARCUENTA, OnBnClickedBuscarcuenta)
END_MESSAGE_MAP()
/****************************************************************************/
BOOL CDlgZona::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_rsZona.m_strSort="ZONA";
	m_dlgBusquedaZona.SetConexion(m_db);
	m_dlgBusquedaCuenta.SetConexion(m_db);
	if (!m_rsZona.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	if (m_rsZona.GetRecordCount()==0)
	{
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
		return FALSE;
	}
	m_rsZona.MoveLast();
	strUltimo=m_rsZona.m_ZONA.TrimRight();
	m_rsZona.MoveFirst();
	strPrimero=m_rsZona.m_ZONA.TrimRight();
    if(!bUpdate)//si es agregar, solo pon los botones de navegación
	{
		GetDlgItem(IDC_CODIGO)->SetWindowText(m_strCodigo);
		GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);
	}
	else//es modificación, enseña datos al inicio
	{
		BuscarZonas();
		if (!m_strCodigo.IsEmpty())
			RellenaCampos();
	}
	UpdateData(TRUE);
	if (!m_strCodigo.IsEmpty())
		ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
	return FALSE;
}
/******************************************************************************************/
void CDlgZona::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsZona.m_pDatabase = m_db;
}
/******************************************************************************************/
void CDlgZona::SetZona(CString Codigo,CString Descripcion)
{
	m_strCodigo = Codigo;
	m_strDescripcion=Descripcion;
}
/******************************************************************************************/
void CDlgZona::SetUpdate(BOOL Update)
{
	bUpdate = Update;
}
/*********************************************************************************/
void CDlgZona::OnBnClickedLimpiar()
{
	m_strCodigo.Empty();
	Limpiar();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/*********************************************************************************/
void CDlgZona::Limpiar()
{
	m_strDescripcion.Empty();
	m_strCuenta.Empty();
	m_strDesCuenta.Empty();
	
	UpdateData(FALSE);
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(FALSE);
	m_rsZona.MoveFirst();
	iEstado=INICIAL;
}
/*********************************************************************************/
void CDlgZona::OnEnKillfocusCodigo()
{
	if (m_rsZona.GetRecordCount()==0)
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}
	CString strCodigoAux=m_strCodigo;
	GetDlgItem(IDC_CODIGO)->GetWindowText(m_strCodigo);
	//si el codigo anterior es igual al nuevo, no hace chequeo//
	if (m_strCodigo==strCodigoAux)
		return;
	if (m_strCodigo.IsEmpty())
	{
		Limpiar();
		return;
	}
	///////////////////////////////////////////////////////////*/
	if (BuscarZonas()==TRUE)//si encuentra el codigo
	{
		GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);//pintala
		ChequeaPosicion();//comprueba que no es ni el primero ni el ultimo
		RellenaCampos();
		bUpdate=TRUE;//si se debe actualizar en caso de pulsar OK
	}
	else//sino se encuentra 
	{
		m_strDescripcion.Empty();//vacia la variable
		m_strCuenta.Empty();
		m_strDesCuenta.Empty();
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
		GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
		bUpdate=FALSE;//se debe insertar en caso de pulsar OK
	}
	UpdateData(FALSE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
}
/*********************************************************************************/
void CDlgZona::OnBnClickedOk()
{
	HRESULT Op;
	UpdateData(TRUE);
	if(m_strCodigo.IsEmpty())
	{
		AfxMessageBox(IDS_NO_CODIGO);
		GetDlgItem(IDC_CODIGO)->SetFocus();
		return;
	}
	m_rsZona.m_ZONA=m_strCodigo;
	m_rsZona.m_DZONA=m_strDescripcion.TrimRight();
	m_rsZona.m_CUENTA=m_strCuenta.TrimRight();
	if(bUpdate==TRUE)
	{
		Op=m_rsZona.UpdateZona();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	else
	{
		Op=m_rsZona.Insert();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	m_rsZona.Close();
	if (!m_rsZona.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	m_rsZona.MoveLast();
	strUltimo=m_rsZona.m_ZONA.TrimRight();
	m_rsZona.MoveFirst();
	strPrimero=m_rsZona.m_ZONA.TrimRight();
	m_dlgBusquedaZona.InicializarListas();
	OnBnClickedLimpiar();
}
/*********************************************************************************/
void CDlgZona::OnBnClickedBuscar()
{
	INT_PTR Estado;
	m_dlgBusquedaZona.SetTipo(CDialogBusqueda::ZONA);
	m_dlgBusquedaZona.SetGestionar(FALSE);
	Estado=m_dlgBusquedaZona.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}

	m_strCodigo=m_dlgBusquedaZona.GetCodigo();
	GetDlgItem(IDC_CODIGO)->SetWindowText(m_strCodigo);
	m_strDescripcion=m_dlgBusquedaZona.GetDescripcion();
	GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);
	BuscarZonas();
	RellenaCampos();
	ChequeaPosicion();
	iEstado=BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}

/****************************************************************************************************/
void CDlgZona::OnBnClickedIni()//va al inicio de los registros
{
	/*etDlgItem(IDC_INI)->EnableWindow(FALSE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente*/
	
	if (!bUpdate)	
		bUpdate=TRUE;
	m_rsZona.MoveFirst();
	m_strCodigo=m_rsZona.m_ZONA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsZona.m_DZONA.TrimRight();//lo guarda en la variable
	ChequeaPosicion();
	RellenaCampos();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/***************************************************************************************************/
void CDlgZona::OnBnClickedFin()
{
	/*GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente*/
	
	if (!bUpdate)	
		bUpdate=TRUE;
	m_rsZona.MoveLast();
	m_strCodigo=m_rsZona.m_ZONA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsZona.m_DZONA.TrimRight();//lo guarda en la variable
	RellenaCampos();
	ChequeaPosicion();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//****************************************************************************************************
void CDlgZona::OnBnClickedAnt()
{
	m_rsZona.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsZona.m_ZONA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsZona.m_DZONA.TrimRight();//lo guarda en la variable
	RellenaCampos();
	UpdateData(FALSE);
	//********* COMPRUEBA QUE NO SEA EL ÚLTIMO REGISTRO*********
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//**************************************************************************************************
void CDlgZona::OnBnClickedSig()
{
	if (iEstado == BUSCADO)
		m_rsZona.MoveNext();
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsZona.m_ZONA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsZona.m_DZONA.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	//********* COMPRUEBA QUE NO SEA EL ÚLTIMO REGISTRO*********
	ChequeaPosicion();
	iEstado=BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//*****************************************************************************************************************
void CDlgZona::ChequeaPosicion()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	if (m_strCodigo==strPrimero)
	{
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	}
	if (m_strCodigo==strUltimo)
	{
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
}
//*****************************************************************************************************************
BOOL CDlgZona::BuscarZonas()
{
	CString strAux;
	m_rsZona.MoveFirst();
	while (!m_rsZona.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsZona.m_ZONA.TrimRight();//elimina el texto vacio por detras
		if (m_strCodigo==strAux)//si encuentra la referencia
		{
			return TRUE;
			break;//sal del bucle;
		}
		m_rsZona.MoveNext();
	}
	return FALSE;
}
//*****************************************************************************************************************
void CDlgZona::RellenaCampos()
{
	bUpdate=TRUE;
	m_strDescripcion=m_rsZona.m_DZONA.TrimRight();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	iEstado=BUSCADO;
	m_strCuenta=m_rsZona.m_CUENTA.TrimRight();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_CUENTA)->SetWindowText(m_strCuenta);
	BuscarCuenta();
	UpdateData(FALSE);
}
/*************************************************************************************/
void CDlgZona::OnEnKillfocusCuenta()
{
	CString strCuentasAux=m_strCuenta;//para luego poder retornar sino existe el registro
	GetDlgItem(IDC_CUENTA)->GetWindowText(m_strCuenta);
	if(m_strCuenta==strCuentasAux)//si es el mismo que tenia, no hagas nada
		return;
	if(m_strCuenta.IsEmpty())	//sino está vacio 
	{
		m_strDesCuenta="";
		GetDlgItem(IDC_DESCUENTA)->SetWindowText(m_strDesCuenta);
		return;
	}
	if (BuscarCuenta()==TRUE)	//si encuentra el registro
	{
		GetDlgItem(IDC_DESCUENTA)->SetWindowText(m_strDesCuenta);
	}
	else//sino lo encuentra pone el registro anterior
	{
		m_strCuenta=strCuentasAux;
		GetDlgItem(IDC_CUENTA)->SetWindowText(m_strCuenta);
		//AfxMessageBox(IDC_CUENTA_NO_VALIDA);
		//m_ctrlCompras.SetFocus();
	}
}
/*************************************************************************************/
void CDlgZona::OnBnClickedBuscarcuenta()
{
	INT_PTR Estado;
	m_dlgBusquedaCuenta.SetTipo(CDialogBusqueda::CUENTAS);
	m_dlgBusquedaCuenta.SetGestionar(FALSE);
	Estado=m_dlgBusquedaCuenta.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strCuenta=m_dlgBusquedaCuenta.GetCodigo();
	GetDlgItem(IDC_CUENTA)->SetWindowText(m_strCuenta);
	m_strDesCuenta=m_dlgBusquedaCuenta.GetDescripcion();
	GetDlgItem(IDC_DESCUENTA)->SetWindowText(m_strDesCuenta);
}
/*************************************************************************************/
BOOL CDlgZona::BuscarCuenta()
{
	CString strAux;
	CCuentas rsCuenta(m_db);
	rsCuenta.m_strFilter="CUENTA LIKE '" + m_strCuenta + "' ";
	if (!rsCuenta.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	if (rsCuenta.m_CUENTA.IsEmpty())	
	{	
		m_strDesCuenta.Empty();
		return FALSE;
	}
	else
	{
		m_strDesCuenta=rsCuenta.m_NOMBRE;
		return TRUE;
	}
}
