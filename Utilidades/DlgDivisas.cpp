// DlgDivisas.cpp: archivo de implementación
//
#include "stdafx.h"
#include "DlgDivisas.h"
#include ".\dlgDivisas.h"

#define INICIAL 0
#define BUSCADO 1

// Cuadro de diálogo de CDlgDivisas

IMPLEMENT_DYNAMIC(CDlgDivisas, CDialog)
CDlgDivisas::CDlgDivisas(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDivisas::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strDescripcion(_T(""))
	, m_strCambio(_T(""))
	,bUpdate(FALSE)
	,iEstado(INICIAL)
{
	
}

CDlgDivisas::~CDlgDivisas()
{
}

void CDlgDivisas::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODIGO, m_ctrlCodigo);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
	DDV_MaxChars(pDX, m_strCodigo, 3);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
	DDV_MaxChars(pDX, m_strDescripcion, 20);
	DDX_Text(pDX, IDC_CAMBIO, m_strCambio);
	DDV_MaxChars(pDX, m_strCambio, 13);
}
BEGIN_MESSAGE_MAP(CDlgDivisas, CDialog)
	ON_BN_CLICKED(IDLIMPIAR, OnBnClickedLimpiar)
	ON_EN_KILLFOCUS(IDC_CODIGO, OnEnKillfocusCodigo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
	ON_EN_KILLFOCUS(IDC_CAMBIO, OnEnKillfocusCambio)
END_MESSAGE_MAP()

BOOL CDlgDivisas::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_rsDivisas.m_strSort="DIVISA";
	if (!m_rsDivisas.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	m_dlgBusqueda.SetConexion(m_db);
	if(m_rsDivisas.GetRecordCount()==0)
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
	m_rsDivisas.MoveLast();
	strUltimo=m_rsDivisas.m_DIVISA.TrimRight();
	m_rsDivisas.MoveFirst();
	strPrimero=m_rsDivisas.m_DIVISA.TrimRight();
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
		BuscarDivisas();
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
void CDlgDivisas::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsDivisas.m_pDatabase = m_db;
}
/******************************************************************************************/
void CDlgDivisas::SetDivisas(CString Codigo,CString Descripcion)
{
	m_strCodigo = Codigo;
	m_strDescripcion=Descripcion;
}
/******************************************************************************************/
void CDlgDivisas::SetUpdate(BOOL Update)
{
	bUpdate = Update;
}
/*********************************************************************************/
void CDlgDivisas::OnBnClickedLimpiar()
{
	m_strCodigo.Empty();
	Limpiar();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/*********************************************************************************/
void CDlgDivisas::Limpiar()
{
	m_strDescripcion.Empty();
	m_strCambio.Empty();

	UpdateData(FALSE);
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(FALSE);
	iEstado=INICIAL;
	m_rsDivisas.MoveFirst();
}
/*********************************************************************************/
void CDlgDivisas::OnEnKillfocusCodigo()
{
	if(m_rsDivisas.GetRecordCount()==0)
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}
	CString strCodigoAux=m_strCodigo;
	GetDlgItem(IDC_CODIGO)->GetWindowText(m_strCodigo);
	//si el codigo anterior es igual al nuevo, no hace chequeo//
	if (m_strCodigo==strCodigoAux)
		return;

	if (m_strCodigo.IsEmpty() && iEstado==INICIAL)
		return;
	if (m_strCodigo.IsEmpty() && iEstado==BUSCADO)
	{
		Limpiar();
		return;
	}
	if (BuscarDivisas()==TRUE)//si encuentra el codigo
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
void CDlgDivisas::OnBnClickedOk()
{
	HRESULT Op;
	UpdateData(TRUE);
	if(m_strCodigo.IsEmpty())
	{
		AfxMessageBox(IDS_NO_CODIGO);
		GetDlgItem(IDC_CODIGO)->SetFocus();
		return;
	}
	m_rsDivisas.m_DIVISA=m_strCodigo;
	m_rsDivisas.m_DDIVISA=m_strDescripcion.TrimRight();
	m_rsDivisas.m_CAMBIO=atof(m_strCambio);
	if(bUpdate==TRUE)
	{
		Op=m_rsDivisas.UpdateDivisa();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	else
	{
		Op=m_rsDivisas.Insert();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	m_rsDivisas.Close();
	if (!m_rsDivisas.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return ;
	}
	m_rsDivisas.MoveLast();
	strUltimo=m_rsDivisas.m_DIVISA.TrimRight();
	m_rsDivisas.MoveFirst();
	strPrimero=m_rsDivisas.m_DIVISA.TrimRight();
	OnBnClickedLimpiar();
	m_dlgBusqueda.InicializarListas();
}
/*********************************************************************************/
void CDlgDivisas::OnBnClickedBuscar()
{
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusqueda.SetTipo(CDialogBusqueda::DIVISAS);
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
	BuscarDivisas();	
	RellenaCampos();
	UpdateData(FALSE);
	ChequeaPosicion();
	iEstado=BUSCADO;
}

//****************************************************************************************************
void CDlgDivisas::OnBnClickedIni()//va al inicio de los registros
{
	m_rsDivisas.MoveFirst();
	m_strCodigo=m_rsDivisas.m_DIVISA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsDivisas.m_DDIVISA.TrimRight();//lo guarda en la variable
	RellenaCampos();
	ChequeaPosicion();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/***************************************************************************************************/
void CDlgDivisas::OnBnClickedFin()
{
	m_rsDivisas.MoveLast();
	m_strCodigo=m_rsDivisas.m_DIVISA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsDivisas.m_DDIVISA.TrimRight();//lo guarda en la variable
	RellenaCampos();
	ChequeaPosicion();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//****************************************************************************************************
void CDlgDivisas::OnBnClickedAnt()
{
	m_rsDivisas.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsDivisas.m_DIVISA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsDivisas.m_DDIVISA.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//**************************************************************************************************
void CDlgDivisas::OnBnClickedSig()
{
	if (iEstado == BUSCADO)
		m_rsDivisas.MoveNext();//me muevo al Siguiente
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsDivisas.m_DIVISA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsDivisas.m_DDIVISA.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	//********* COMPRUEBA QUE NO SEA EL ÚLTIMO REGISTRO*********
	ChequeaPosicion();
	iEstado=BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//*****************************************************************************************************************
void CDlgDivisas::ChequeaPosicion()
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
BOOL CDlgDivisas::BuscarDivisas()
{
	CString strAux;
	m_rsDivisas.MoveFirst();
	while (!m_rsDivisas.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsDivisas.m_DIVISA.TrimRight();//elimina el texto vacio por detras
		if (m_strCodigo==strAux)//si encuentra la referencia
		{
			return TRUE;
			break;//sal del bucle;
		}
		m_rsDivisas.MoveNext();
	}
	return FALSE;
}
/*************************************************************************************/
BOOL CDlgDivisas::ChequeaNumeros(CString cadena)
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
void CDlgDivisas::OnEnKillfocusCambio()
{
	CString strAux=m_strCambio;
	GetDlgItem(IDC_CAMBIO)->GetWindowText(m_strCambio);
	if(ChequeaNumeros(m_strCambio)==FALSE)
	{
		m_strCambio=strAux;
		GetDlgItem(IDC_CAMBIO)->SetWindowText(m_strCambio);
		GetDlgItem(IDC_CAMBIO)->SetFocus();
	}
	else
	{
		GetDlgItem(IDC_CAMBIO)->SetWindowText(m_strCambio);
	}
}
/*************************************************************************************/
void CDlgDivisas::RellenaCampos()
{
	m_strCambio.Format("%.2f", m_rsDivisas.m_CAMBIO);
	bUpdate=TRUE;
	m_strDescripcion=m_rsDivisas.m_DDIVISA.TrimRight();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	iEstado=BUSCADO;
	UpdateData(FALSE);
}