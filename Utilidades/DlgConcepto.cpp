// DlgConceptos.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgConcepto.h"
#include ".\dlgConcepto.h"

#define INICIAL 0
#define BUSCADO 1

// Cuadro de diálogo de CDlgConcepto

IMPLEMENT_DYNAMIC(CDlgConcepto, CDialog)
CDlgConcepto::CDlgConcepto(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConcepto::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strDescripcion(_T(""))
//	, m_strCuenta(_T(""))
//	, m_strEjercicio(_T(""))
	, bUpdate(FALSE)
	, iEstado(INICIAL)
{
}

CDlgConcepto::~CDlgConcepto()
{
}

void CDlgConcepto::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODIGO, m_ctrlCodigo);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
	DDV_MaxChars(pDX, m_strCodigo, 3);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
	DDV_MaxChars(pDX, m_strDescripcion, 25);
/*	DDX_Text(pDX, IDC_CONTA, m_strCuenta);
	DDV_MaxChars(pDX, m_strCuenta, 9);
	DDX_Text(pDX, IDC_EJERCICIO, m_strEjercicio);
	DDV_MaxChars(pDX, m_strEjercicio, 4);*/
}
BEGIN_MESSAGE_MAP(CDlgConcepto, CDialog)
	ON_BN_CLICKED(IDLIMPIAR, OnBnClickedLimpiar)
	ON_EN_KILLFOCUS(IDC_CODIGO, OnEnKillfocusCodigo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
	//ON_EN_KILLFOCUS(IDC_CUENTA, OnEnKillfocusCuenta)
	//ON_EN_KILLFOCUS(IDC_EJERCICIO, OnEnKillfocusEjercicio)
END_MESSAGE_MAP()

BOOL CDlgConcepto::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_rsConcepto.m_strSort="CONCEPTO";
	if (!m_rsConcepto.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	m_dlgBusqueda.SetConexion(m_db);
	if(m_rsConcepto.GetRecordCount()==0)
	{
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
		return FALSE;
	}
	/*********** CARGA LOS BOTONES **************
	VERIFY(m_botonIni.AutoLoad(IDC_INI, this));
	VERIFY(m_botonSig.AutoLoad(IDC_SIG, this));
	VERIFY(m_botonAnt.AutoLoad(IDC_ANT, this));
	VERIFY(m_botonFin.AutoLoad(IDC_FIN, this));*/
	m_rsConcepto.MoveLast();
	strUltimo=m_rsConcepto.m_CONCEPTO.TrimRight();
	m_rsConcepto.MoveFirst();
	strPrimero=m_rsConcepto.m_CONCEPTO.TrimRight();
	ChequeaPosicion();
	if(!bUpdate)//si es agregar, solo pon los botones de navegación
	{
		GetDlgItem(IDC_CODIGO)->SetWindowText(m_strCodigo);
		GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	}
	else//es modificación, enseña datos al inicio
	{
		BuscarConceptos();
		if (m_strCodigo.IsEmpty())
		{
			GetDlgItem(IDC_INI)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		}
		RellenaCampos();
	}
	/*****************************************/
	UpdateData(TRUE);

	GetDlgItem(IDC_CODIGO)->SetFocus();
	return FALSE;
}
/******************************************************************************************/
void CDlgConcepto::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsConcepto.m_pDatabase = db;
}
/******************************************************************************************/
void CDlgConcepto::SetConcepto(CString Codigo,CString Descripcion)
{
	m_strCodigo = Codigo;
	m_strDescripcion=Descripcion;
}
/******************************************************************************************/
void CDlgConcepto::SetUpdate(BOOL Update)
{
	bUpdate = Update;
}
/*********************************************************************************/
void CDlgConcepto::OnBnClickedLimpiar()
{
	m_strCodigo.Empty();
	Limpiar();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/*********************************************************************************/
void CDlgConcepto::Limpiar()
{
	m_strDescripcion.Empty();
//	m_strCuenta.Empty();
//	m_strEjercicio.Empty();
	UpdateData(FALSE);
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(FALSE);
	m_rsConcepto.MoveFirst();
	iEstado=INICIAL;
}
/*********************************************************************************/
void CDlgConcepto::OnEnKillfocusCodigo()
{
	if (m_rsConcepto.GetRecordCount()==0)
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}

	CString strCodigoAux=m_strCodigo;
	GetDlgItem(IDC_CODIGO)->GetWindowText(m_strCodigo);

	if (m_strCodigo==strCodigoAux)
		return;

	if (m_strCodigo.IsEmpty() && iEstado==INICIAL)
		return;
	if (m_strCodigo.IsEmpty() && iEstado==BUSCADO)
	{
		Limpiar();
		return;
	}
	///////////////////////////////////////////////////////////*/
	if (BuscarConceptos()==TRUE)//si encuentra el codigo
	{
		RellenaCampos();
		ChequeaPosicion();//comprueba que no es ni el primero ni el ultimo
	}
	else//sino se encuentra 
	{
		Limpiar();
		bUpdate=FALSE;//se debe insertar en caso de pulsar OK
	}
	UpdateData(FALSE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
}
/*********************************************************************************/
void CDlgConcepto::OnBnClickedOk()
{
	HRESULT Op;
	UpdateData(TRUE);
	if(m_strCodigo.IsEmpty())
	{
		AfxMessageBox(IDS_NO_CODIGO);
		GetDlgItem(IDC_CODIGO)->SetFocus();
		return;
	}
	m_rsConcepto.m_CONCEPTO = m_strCodigo;
	m_rsConcepto.m_DCONCEPTO = m_strDescripcion.TrimRight();
//	m_rsConcepto.m_CONTA = atof(m_strCuenta.TrimRight());
//	m_rsConcepto.m_EJERCICIO = m_strEjercicio.TrimRight();
	if(bUpdate==TRUE)
	{
		Op=m_rsConcepto.UpdateConcepto();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	else
	{
		Op=m_rsConcepto.Insert();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	m_rsConcepto.Close();
	if (!m_rsConcepto.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	m_rsConcepto.MoveLast();
	strUltimo=m_rsConcepto.m_CONCEPTO.TrimRight();
	m_rsConcepto.MoveFirst();
	strPrimero=m_rsConcepto.m_CONCEPTO.TrimRight();
	OnBnClickedLimpiar();
	m_dlgBusqueda.InicializarListas();
}
/*********************************************************************************/
void CDlgConcepto::OnBnClickedBuscar()
{
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusqueda.SetTipo(CDialogBusqueda::CONCEPTOS);
	m_dlgBusqueda.SetGestionar(FALSE);
	Estado=m_dlgBusqueda.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	//Y sino se pulsa Cancel
	m_strCodigo=m_dlgBusqueda.GetCodigo();
	m_strDescripcion=m_dlgBusqueda.GetDescripcion();
	GetDlgItem(IDC_CODIGO)->SetWindowText(m_strCodigo);
	GetDlgItem(IDC_DESCRIPCION)->SetWindowText(m_strDescripcion);
	BuscarConceptos();	
	RellenaCampos();
	UpdateData(FALSE);
	ChequeaPosicion();
	iEstado=BUSCADO;
}

//****************************************************************************************************
void CDlgConcepto::OnBnClickedIni()//va al inicio de los registros
{
	m_rsConcepto.MoveFirst();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodigo=m_rsConcepto.m_CONCEPTO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsConcepto.m_DCONCEPTO.TrimRight();//lo guarda en la variable
	RellenaCampos();
	ChequeaPosicion();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/***************************************************************************************************/
void CDlgConcepto::OnBnClickedFin()
{
	m_rsConcepto.MoveLast();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodigo=m_rsConcepto.m_CONCEPTO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsConcepto.m_DCONCEPTO.TrimRight();//lo guarda en la variable
	RellenaCampos();
	ChequeaPosicion();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//****************************************************************************************************
void CDlgConcepto::OnBnClickedAnt()
{
	m_rsConcepto.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsConcepto.m_CONCEPTO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsConcepto.m_DCONCEPTO.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//**************************************************************************************************
void CDlgConcepto::OnBnClickedSig()
{
	if (iEstado == BUSCADO)
		m_rsConcepto.MoveNext();//me muevo al Siguiente
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsConcepto.m_CONCEPTO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsConcepto.m_DCONCEPTO.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
	iEstado=BUSCADO;
}
//*****************************************************************************************************************
void CDlgConcepto::ChequeaPosicion()
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
BOOL CDlgConcepto::BuscarConceptos()
{
	CString strAux;
	m_rsConcepto.MoveFirst();
	while (!m_rsConcepto.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsConcepto.m_CONCEPTO.TrimRight();//elimina el texto vacio por detras
		if (m_strCodigo==strAux)//si encuentra la referencia
		{
			return TRUE;
			break;//sal del bucle;
		}
		m_rsConcepto.MoveNext();
	}
	return FALSE;
}
//*****************************************************************************************************************
void CDlgConcepto::RellenaCampos()
{
//	m_strCuenta.Format("%.2f", m_rsConcepto.m_CONTA);
//	m_strEjercicio=m_rsConcepto.m_EJERCICIO.TrimRight();
	bUpdate=TRUE;
	m_strDescripcion=m_rsConcepto.m_DCONCEPTO.TrimRight();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	iEstado=BUSCADO;
	UpdateData(FALSE);
}
/*************************************************************************************/
BOOL CDlgConcepto::ChequeaNumeros(CString cadena)
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
/*void CDlgConcepto::OnEnKillfocusCuenta()
{
	CString strAux=m_strCuenta;
	GetDlgItem(IDC_CUENTA)->GetWindowText(m_strCuenta);
	if(ChequeaNumeros(m_strCuenta)==FALSE)
	{
		m_strCuenta=strAux;
		GetDlgItem(IDC_CUENTA)->SetWindowText(m_strCuenta);
		GetDlgItem(IDC_CUENTA)->SetFocus();
	}
	else
	{
		GetDlgItem(IDC_CUENTA)->SetWindowText(m_strCuenta);
	}
}*/
/*************************************************************************************/
//void CDlgConcepto::OnEnKillfocusEjercicio()
//{
	/*CString strAux=m_strEjercicio;
	GetDlgItem(IDC_EJERCICIO)->GetWindowText(m_strEjercicio);
	if(ChequeaNumeros(m_strEjercicio)==FALSE)
	{
		m_strEjercicio=strAux;
		GetDlgItem(IDC_EJERCICIO)->SetWindowText(m_strEjercicio);
		GetDlgItem(IDC_EJERCICIO)->SetFocus();
	}
	else
	{
		GetDlgItem(IDC_EJERCICIO)->SetWindowText(m_strEjercicio);
	}*/
//}
