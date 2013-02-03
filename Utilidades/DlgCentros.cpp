// DlgCentros.cpp: archivo de implementación
//
#include "stdafx.h"
#include "DlgCentros.h"
#include ".\dlgCentros.h"

#define INICIAL 0
#define BUSCADO 1

// Cuadro de diálogo de CDlgCentros

IMPLEMENT_DYNAMIC(CDlgCentros, CDialog)
CDlgCentros::CDlgCentros(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCentros::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strDescripcion(_T(""))
	, bUpdate(FALSE)
	, iEstado(INICIAL)
{
}

CDlgCentros::~CDlgCentros()
{
}

void CDlgCentros::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODIGO, m_ctrlCodigo);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
	DDV_MaxChars(pDX, m_strCodigo, 3);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
	DDV_MaxChars(pDX, m_strDescripcion, 25);
}


BEGIN_MESSAGE_MAP(CDlgCentros, CDialog)
	ON_BN_CLICKED(IDLIMPIAR, OnBnClickedLimpiar)
	ON_EN_KILLFOCUS(IDC_CODIGO, OnEnKillfocusCodigo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
END_MESSAGE_MAP()

BOOL CDlgCentros::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_rsCentros.m_strSort="CCENTRO";
	if (!m_rsCentros.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	m_dlgBusqueda.SetConexion(m_db);
	if(m_rsCentros.GetRecordCount()==0)
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
	m_rsCentros.MoveLast();
	strUltimo=m_rsCentros.m_CCENTRO.TrimRight();
	m_rsCentros.MoveFirst();
	strPrimero=m_rsCentros.m_CCENTRO.TrimRight();
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
		BuscarCentros();
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
void CDlgCentros::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsCentros.m_pDatabase = m_db;
}
/******************************************************************************************/
void CDlgCentros::SetCentros(CString Codigo,CString Descripcion)
{
	m_strCodigo = Codigo;
	m_strDescripcion=Descripcion;
}
/******************************************************************************************/
void CDlgCentros::SetUpdate(BOOL Update)
{
	bUpdate = Update;
}
/*********************************************************************************/
void CDlgCentros::OnBnClickedLimpiar()
{
	m_strCodigo.Empty();
	Limpiar();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/*********************************************************************************/
void CDlgCentros::Limpiar()
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
	m_rsCentros.MoveFirst();
}
/*********************************************************************************/
void CDlgCentros::OnEnKillfocusCodigo()
{
	if (m_rsCentros.GetRecordCount()==0)
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
	if (BuscarCentros()==TRUE)//si encuentra el codigo
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
void CDlgCentros::OnBnClickedOk()
{
	
	HRESULT Op;
	UpdateData(TRUE);//recoge los datos
	if(m_strCodigo.IsEmpty())//si no hay codigo "cruje"
	{
		AfxMessageBox(IDS_NO_CODIGO);
		GetDlgItem(IDC_CODIGO)->SetFocus();
		return;
	}
	/**** Guarda las variables en el objeto CCentro *****/
	m_rsCentros.m_CCENTRO=m_strCodigo;
	m_rsCentros.m_DCENTRO=m_strDescripcion.TrimRight();
	/*****************************************************/
	if(bUpdate==TRUE)
	{
		Op=m_rsCentros.UpdateCentros();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	else
	{
		Op=m_rsCentros.Insert();
		//si se logra insertar
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	m_rsCentros.Close();//cierra y vuelve a abrir m_rsCentros
	if (!m_rsCentros.Open(CRecordset::dynaset))//para añadir el nuevo registro
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	m_rsCentros.MoveLast();
	strUltimo=m_rsCentros.m_CCENTRO.TrimRight();
	m_rsCentros.MoveFirst();
	strPrimero=m_rsCentros.m_CCENTRO.TrimRight();
	OnBnClickedLimpiar();
	m_dlgBusqueda.InicializarListas();
}
/*********************************************************************************/
void CDlgCentros::OnBnClickedBuscar()
{
	INT_PTR Estado;
	m_dlgBusqueda.SetTipo(CDialogBusqueda::CENTROS);
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
	ChequeaPosicion();
	BuscarCentros();
	iEstado=BUSCADO;
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_CODIGO)->SetFocus();
}

//****************************************************************************************************
void CDlgCentros::OnBnClickedIni()//va al inicio de los registros
{
	/*GetDlgItem(IDC_INI)->EnableWindow(FALSE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente*/
	
	m_rsCentros.MoveFirst();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodigo=m_rsCentros.m_CCENTRO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsCentros.m_DCENTRO.TrimRight();//lo guarda en la variable
	ChequeaPosicion();
	UpdateData(FALSE);
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/***************************************************************************************************/
void CDlgCentros::OnBnClickedFin()
{
	/*GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente*/
	
	m_rsCentros.MoveLast();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodigo=m_rsCentros.m_CCENTRO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsCentros.m_DCENTRO.TrimRight();//lo guarda en la variable
	ChequeaPosicion();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//****************************************************************************************************
void CDlgCentros::OnBnClickedAnt()
{
	m_rsCentros.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsCentros.m_CCENTRO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsCentros.m_DCENTRO.TrimRight();//lo guarda en la variable
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();	
}
//**************************************************************************************************
void CDlgCentros::OnBnClickedSig()
{
	if (iEstado == BUSCADO)
		m_rsCentros.MoveNext();//me muevo al Siguiente
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsCentros.m_CCENTRO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsCentros.m_DCENTRO.TrimRight();//lo guarda en la variable
	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
	iEstado=BUSCADO;

}
//*****************************************************************************************************************
void CDlgCentros::ChequeaPosicion()
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
BOOL CDlgCentros::BuscarCentros()
{
	CString strAux;
	m_rsCentros.MoveFirst();
	while (!m_rsCentros.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsCentros.m_CCENTRO.TrimRight();//elimina el texto vacio por detras
		if (m_strCodigo==strAux)//si encuentra la referencia
		{
			return TRUE;
			break;//sal del bucle;
		}
		m_rsCentros.MoveNext();
	}
	return FALSE;
}
//*****************************************************************************************************************
void CDlgCentros::RellenaCampos()
{
	m_strDescripcion=m_rsCentros.m_DCENTRO.TrimRight();
	bUpdate=TRUE;
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	iEstado=BUSCADO;
	UpdateData(FALSE);
}