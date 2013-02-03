// DlgZonas.cpp: archivo de implementación
//
#include "stdafx.h"
#include "DlgZona.h"
#include ".\dlgZona.h"


// Cuadro de diálogo de CDlgZona

IMPLEMENT_DYNAMIC(CDlgZona, CDialog)
CDlgZona::CDlgZona(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgZona::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strDescripcion(_T(""))
	, m_strCuenta(_T(""))
	, bUpdate(FALSE)
	, m_strDesCuenta(_T(""))
{
}

CDlgZona::~CDlgZona()
{
	m_rsZona.Close();
}

void CDlgZona::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODIGO, m_ctrlCodigo);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
	DDV_MaxChars(pDX, m_strCodigo, 3);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
	DDV_MaxChars(pDX, m_strDescripcion, 35);
	DDX_Text(pDX, IDC_CUENTA, m_strCuenta);
	DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_DESCUENTA, m_strDesCuenta);
}


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
	//ON_BN_CLICKED(IDBUSCACUENTA, OnBnClickedBuscacuenta)
	ON_BN_CLICKED(IDBUSCACUENTA, OnBnClickedBuscacuenta)
END_MESSAGE_MAP()

BOOL CDlgZona::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_dlgBusqueda.SetConexion(m_db);
	

	if (!m_rsZona.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	/*********** CARGA LOS BOTONES ***********
	VERIFY(m_botonIni.AutoLoad(IDC_INI, this));
	VERIFY(m_botonSig.AutoLoad(IDC_SIG, this));
	VERIFY(m_botonAnt.AutoLoad(IDC_ANT, this));
	VERIFY(m_botonFin.AutoLoad(IDC_FIN, this));*/
	m_rsZona.MoveLast();
	strUltimo=m_rsZona.m_ZONA.TrimRight();
	m_rsZona.MoveFirst();
	strPrimero=m_rsZona.m_ZONA.TrimRight();
	ChequeaPosicion();
    if(!bUpdate)//si es agregar, solo pon los botones de navegación
	{
		bInicial=TRUE;
		GetDlgItem(IDC_CODIGO)->SetWindowText(m_strCodigo);
		GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	}
	else//es modificación, enseña datos al inicio
	{
		if (m_strCodigo.IsEmpty())
		{
			GetDlgItem(IDC_INI)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		}
		else
			RellenaCampos();
	}
	/*****************************************/
	UpdateData(TRUE);

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
	m_strDescripcion.Empty();
	m_strCuenta.Empty();
	
	UpdateData(FALSE);
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	m_rsZona.MoveFirst();
}
/*********************************************************************************/
void CDlgZona::OnEnKillfocusCodigo()
{
	CString strCodigoAux=m_strCodigo;
	GetDlgItem(IDC_CODIGO)->GetWindowText(m_strCodigo);
	/*si el codigo anterior es igual al nuevo, no hace chequeo//
	if (m_strCodigo==strCodigoAux)
		return;
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
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
		GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
		bUpdate=FALSE;//se debe insertar en caso de pulsar OK
	}
	UpdateData(FALSE);
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
	}
	OnBnClickedLimpiar();
	m_dlgBusqueda.InicializarListas();
}
/*********************************************************************************/
void CDlgZona::OnBnClickedBuscar()
{
	INT_PTR Estado;
	m_dlgBusqueda.SetTipo(CDialogBusqueda::ZONA);
	m_dlgBusqueda.SetGestionar(FALSE);
	Estado=m_dlgBusqueda.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}

	m_strCodigo=m_dlgBusqueda.GetCodigo();
	GetDlgItem(IDC_CODIGO)->SetWindowText(m_strCodigo);
	m_strDescripcion=m_dlgBusqueda.GetDescripcion();
	GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);
	BuscarZonas();
	RellenaCampos();
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}

/****************************************************************************************************/
void CDlgZona::OnBnClickedIni()//va al inicio de los registros
{
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente
	
	if (!bUpdate)	
		bUpdate=TRUE;
	m_rsZona.MoveFirst();
	m_strCodigo=m_rsZona.m_ZONA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsZona.m_DZONA.TrimRight();//lo guarda en la variable
	RellenaCampos();
	UpdateData(FALSE);//actualiza la variable
}
/***************************************************************************************************/
void CDlgZona::OnBnClickedFin()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente
	
	if (!bUpdate)	
		bUpdate=TRUE;
	m_rsZona.MoveLast();
	m_strCodigo=m_rsZona.m_ZONA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsZona.m_DZONA.TrimRight();//lo guarda en la variable
	RellenaCampos();
	UpdateData(FALSE);//actualiza la variable
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
}
//**************************************************************************************************
void CDlgZona::OnBnClickedSig()
{
	if (m_strCodigo.IsEmpty() && bInicial)//si está vacio y es el vacio inicial
	{
		OnBnClickedIni();
		bInicial=FALSE;
		return;
	}
	if (!m_strCodigo.IsEmpty() && !bUpdate)//sino está vacio y es nuevo
	{
		OnBnClickedIni();
		return;
	}
	if (!bUpdate)	
		bUpdate=TRUE;
	m_rsZona.MoveNext();
	m_strCodigo=m_rsZona.m_ZONA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsZona.m_DZONA.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	//********* COMPRUEBA QUE NO SEA EL ÚLTIMO REGISTRO*********
	ChequeaPosicion();
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
			bUpdate=TRUE;
			m_strDescripcion=m_rsZona.m_DZONA.TrimRight();
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
	m_strCuenta=m_rsZona.m_CUENTA.TrimRight();
	GetDlgItem(IDC_CUENTA)->SetWindowText(m_strCuenta);
}
/*************************************************************************************
BOOL CDlgZona::ChequeaNumeros(CString cadena)
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
/*	if (BuscaCuenta(m_strCuenta,0)==TRUE)	//si encuentra el registro
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
*/
}
/*************************************************************************************
void CDlgZona::OnBnClickedBuscacuenta()
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
*/
void CDlgZona::OnBnClickedBuscacuenta()
{
	CDialogBusqueda m_dlgBusquedaCuenta;
	//INT_PTR Estado;
	m_dlgBusquedaCuenta.SetConexion(m_db);
	m_dlgBusquedaCuenta.SetTipo(CDialogBusqueda::CUENTAS);
	m_dlgBusquedaCuenta.SetGestionar(FALSE);
}
