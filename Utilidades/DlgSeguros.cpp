// DlgSeguros.cpp: archivo de implementación
//
#include "stdafx.h"
#include "DlgSeguros.h"
#include ".\dlgSeguros.h"

#define INICIAL 0
#define BUSCADO 1

// Cuadro de diálogo de CDlgSeguros

IMPLEMENT_DYNAMIC(CDlgSeguros, CDialog)
CDlgSeguros::CDlgSeguros(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSeguros::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strDescripcion(_T(""))
	, bUpdate(FALSE)
	, iEstado(INICIAL)
{
}

CDlgSeguros::~CDlgSeguros()
{
}

void CDlgSeguros::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODIGO, m_ctrlCodigo);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
	DDV_MaxChars(pDX, m_strCodigo, 3);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
	DDV_MaxChars(pDX, m_strDescripcion, 25);
}


BEGIN_MESSAGE_MAP(CDlgSeguros, CDialog)
	ON_BN_CLICKED(IDLIMPIAR, OnBnClickedLimpiar)
	ON_EN_KILLFOCUS(IDC_CODIGO, OnEnKillfocusCodigo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
END_MESSAGE_MAP()

BOOL CDlgSeguros::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_rsSeguros.m_strSort="SEGURO";
	if (!m_rsSeguros.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	m_dlgBusqueda.SetConexion(m_db);
	if(m_rsSeguros.GetRecordCount()==0)
	{
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
		return FALSE;
	}
	/*********** CARGA LOS BOTONES ***********
	VERIFY(m_botonIni.AutoLoad(IDC_INI, this));
	VERIFY(m_botonSig.AutoLoad(IDC_SIG, this));
	VERIFY(m_botonAnt.AutoLoad(IDC_ANT, this));
	VERIFY(m_botonFin.AutoLoad(IDC_FIN, this));*/
	m_rsSeguros.MoveLast();
	strUltimo=m_rsSeguros.m_SEGURO.TrimRight();
	m_rsSeguros.MoveFirst();
	strPrimero=m_rsSeguros.m_SEGURO.TrimRight();
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
		BuscarSeguros();
		RellenaCampos();
		if (m_strCodigo.IsEmpty())
		{
			GetDlgItem(IDC_INI)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		}
	}
	/*****************************************/
	UpdateData(TRUE);

	GetDlgItem(IDC_CODIGO)->SetFocus();
	return FALSE;
}
/******************************************************************************************/
void CDlgSeguros::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsSeguros.m_pDatabase = m_db;
}
/******************************************************************************************/
void CDlgSeguros::SetSeguros(CString Codigo,CString Descripcion)
{
	m_strCodigo = Codigo;
	m_strDescripcion=Descripcion;
}
/******************************************************************************************/
void CDlgSeguros::SetUpdate(BOOL Update)
{
	bUpdate = Update;
}
/*********************************************************************************/
void CDlgSeguros::OnBnClickedLimpiar()
{
	m_strCodigo.Empty();
	Limpiar();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
void CDlgSeguros::Limpiar()
{
	m_strDescripcion.Empty();
	UpdateData(FALSE);
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(FALSE);
	iEstado=INICIAL;
	bUpdate=FALSE;
	m_rsSeguros.MoveFirst();
}
/*********************************************************************************/
void CDlgSeguros::OnEnKillfocusCodigo()
{
	if (m_rsSeguros.GetRecordCount()==0)
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
	if (m_strCodigo.IsEmpty())
	{
		Limpiar();
		return;
	}
	if (BuscarSeguros()==TRUE)//si encuentra el codigo
	{
		RellenaCampos();
		ChequeaPosicion();//comprueba que no es ni el primero ni el ultimo
	}
	else//sino se encuentra 
	{
		Limpiar();
		bUpdate=FALSE;//se debe insertar en caso de pulsar OK
	}
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
}
/*********************************************************************************/
void CDlgSeguros::OnBnClickedOk()
{
	HRESULT Op;
	UpdateData(TRUE);
	if(m_strCodigo.IsEmpty())
	{
		AfxMessageBox(IDS_NO_CODIGO);
		GetDlgItem(IDC_CODIGO)->SetFocus();
		return;
	}
	m_rsSeguros.m_SEGURO=m_strCodigo;
	m_rsSeguros.m_DSEGURO=m_strDescripcion.TrimRight();
	if(bUpdate==TRUE)
	{
		Op=m_rsSeguros.UpdateSeguro();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	else
	{
		Op=m_rsSeguros.Insert();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	m_rsSeguros.Close();
	if (!m_rsSeguros.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	m_rsSeguros.MoveLast();
	strUltimo=m_rsSeguros.m_SEGURO.TrimRight();
	m_rsSeguros.MoveFirst();
	strPrimero=m_rsSeguros.m_SEGURO.TrimRight();
	OnBnClickedLimpiar();
	m_dlgBusqueda.InicializarListas();
}
/*********************************************************************************/
void CDlgSeguros::OnBnClickedBuscar()
{
	INT_PTR Estado;
	m_dlgBusqueda.SetTipo(CDialogBusqueda::SEGURO);
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
	BuscarSeguros();
	ChequeaPosicion();
	iEstado=BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}

//****************************************************************************************************
void CDlgSeguros::OnBnClickedIni()//va al inicio de los registros
{
	/*GetDlgItem(IDC_INI)->EnableWindow(FALSE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente*/
	
	m_rsSeguros.MoveFirst();
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsSeguros.m_SEGURO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsSeguros.m_DSEGURO.TrimRight();//lo guarda en la variable
	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/***************************************************************************************************/
void CDlgSeguros::OnBnClickedFin()
{
	/*GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente*/
	
	m_rsSeguros.MoveLast();
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsSeguros.m_SEGURO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsSeguros.m_DSEGURO.TrimRight();//lo guarda en la variable
	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//****************************************************************************************************
void CDlgSeguros::OnBnClickedAnt()
{
	m_rsSeguros.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsSeguros.m_SEGURO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsSeguros.m_DSEGURO.TrimRight();//lo guarda en la variable
	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();	
}
//**************************************************************************************************
void CDlgSeguros::OnBnClickedSig()
{
	if (iEstado == BUSCADO)
		m_rsSeguros.MoveNext();//me muevo al Siguiente
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsSeguros.m_SEGURO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsSeguros.m_DSEGURO.TrimRight();//lo guarda en la variable
 	UpdateData(FALSE);
	ChequeaPosicion();
	iEstado = BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//*****************************************************************************************************************
void CDlgSeguros::ChequeaPosicion()
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
BOOL CDlgSeguros::BuscarSeguros()
{
	CString strAux;
	m_rsSeguros.MoveFirst();
	while (!m_rsSeguros.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsSeguros.m_SEGURO.TrimRight();//elimina el texto vacio por detras
		if (m_strCodigo==strAux)//si encuentra la referencia
		{
			return TRUE;
			break;//sal del bucle;
		}
		m_rsSeguros.MoveNext();
	}
	return FALSE;
}
//*****************************************************************************************************************
void CDlgSeguros::RellenaCampos()
{
	bUpdate=TRUE;
	m_strDescripcion=m_rsSeguros.m_DSEGURO.TrimRight();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	iEstado=BUSCADO;
	UpdateData(FALSE);
}
