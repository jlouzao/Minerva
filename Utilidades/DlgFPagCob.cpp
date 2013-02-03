// DlgFPagCob.cpp: archivo de implementación
//
#include "stdafx.h"
#include "DlgFPagCob.h"
#include ".\dlgFPagCob.h"

#define INICIAL 0
#define BUSCADO 1

// Cuadro de diálogo de CDlgFPagCob

IMPLEMENT_DYNAMIC(CDlgFPagCob, CDialog)
CDlgFPagCob::CDlgFPagCob(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFPagCob::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strDescripcion(_T(""))
	, bUpdate(FALSE)
	, iEstado(INICIAL)
{
}

CDlgFPagCob::~CDlgFPagCob()
{
}

void CDlgFPagCob::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODIGO, m_ctrlCodigo);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
	DDV_MaxChars(pDX, m_strCodigo, 1);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
	DDV_MaxChars(pDX, m_strDescripcion, 15);
}


BEGIN_MESSAGE_MAP(CDlgFPagCob, CDialog)
	ON_BN_CLICKED(IDLIMPIAR, OnBnClickedLimpiar)
	ON_EN_KILLFOCUS(IDC_CODIGO, OnEnKillfocusCodigo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
END_MESSAGE_MAP()

BOOL CDlgFPagCob::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_rsFPagCob.m_strSort="FCOBRO";
	if (!m_rsFPagCob.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	m_dlgBusqueda.SetConexion(m_db);
	if(m_rsFPagCob.GetRecordCount()==0)
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
	/*****************************************/
	m_rsFPagCob.MoveLast();
	strUltimo=m_rsFPagCob.m_FCOBRO.TrimRight();
	m_rsFPagCob.MoveFirst();
	strPrimero=m_rsFPagCob.m_FCOBRO.TrimRight();
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
		BuscarFPagCob();
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
void CDlgFPagCob::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsFPagCob.m_pDatabase = m_db;
}
/******************************************************************************************/
void CDlgFPagCob::SetFPagCob(CString Codigo,CString Descripcion)
{
	m_strCodigo = Codigo;
	m_strDescripcion=Descripcion;
}
/******************************************************************************************/
void CDlgFPagCob::SetUpdate(BOOL Update)
{
	bUpdate = Update;
}
/*********************************************************************************/
void CDlgFPagCob::OnBnClickedLimpiar()
{
	m_strCodigo.Empty();
	Limpiar();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/*********************************************************************************/
void CDlgFPagCob::Limpiar()
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
	m_rsFPagCob.MoveFirst();
}
/*********************************************************************************/
void CDlgFPagCob::OnEnKillfocusCodigo()
{
	if(m_rsFPagCob.GetRecordCount()==0)
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}
	CString strCodigoAux=m_strCodigo;
	GetDlgItem(IDC_CODIGO)->GetWindowText(m_strCodigo);
	/*si el codigo anterior es igual al nuevo, no hace chequeo*/
	if (m_strCodigo==strCodigoAux)
		return;

	if (m_strCodigo.IsEmpty() && iEstado==INICIAL)
		return;
	if (m_strCodigo.IsEmpty() && iEstado==BUSCADO)
	{
		Limpiar();
		return;
	}
	if (BuscarFPagCob()==TRUE)//si encuentra el codigo
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
void CDlgFPagCob::OnBnClickedOk()
{
	HRESULT Op;
	UpdateData(TRUE);
	if(m_strCodigo.IsEmpty())
	{
		AfxMessageBox(IDS_NO_CODIGO);
		GetDlgItem(IDC_CODIGO)->SetFocus();
		return;
	}
	m_rsFPagCob.m_FCOBRO=m_strCodigo;
	m_rsFPagCob.m_DFCOBRO=m_strDescripcion.TrimRight();
	if(bUpdate==TRUE)
	{
		Op=m_rsFPagCob.UpdateFPagCob();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	else
	{
		Op=m_rsFPagCob.Insert();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	m_rsFPagCob.Close();
	if (!m_rsFPagCob.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	m_rsFPagCob.MoveLast();
	strUltimo=m_rsFPagCob.m_FCOBRO.TrimRight();
	m_rsFPagCob.MoveFirst();
	strPrimero=m_rsFPagCob.m_FCOBRO.TrimRight();
	OnBnClickedLimpiar();
	m_dlgBusqueda.InicializarListas();
}
/*********************************************************************************/
void CDlgFPagCob::OnBnClickedBuscar()
{
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusqueda.SetTipo(CDialogBusqueda::FPAGCOB);
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
	BuscarFPagCob();
	ChequeaPosicion();
	iEstado=BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//****************************************************************************************************
void CDlgFPagCob::OnBnClickedIni()//va al inicio de los registros
{
	/*GetDlgItem(IDC_INI)->EnableWindow(FALSE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente*/
	
	m_rsFPagCob.MoveFirst();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodigo=m_rsFPagCob.m_FCOBRO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsFPagCob.m_DFCOBRO.TrimRight();//lo guarda en la variable
	ChequeaPosicion();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/***************************************************************************************************/
void CDlgFPagCob::OnBnClickedFin()
{
	/*GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente*/
	
	m_rsFPagCob.MoveLast();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodigo=m_rsFPagCob.m_FCOBRO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsFPagCob.m_DFCOBRO.TrimRight();//lo guarda en la variable
	ChequeaPosicion();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//****************************************************************************************************
void CDlgFPagCob::OnBnClickedAnt()
{
	m_rsFPagCob.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsFPagCob.m_FCOBRO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsFPagCob.m_DFCOBRO.TrimRight();//lo guarda en la variable
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();

}
//**************************************************************************************************
void CDlgFPagCob::OnBnClickedSig()
{
	if (iEstado == BUSCADO)
		m_rsFPagCob.MoveNext();//me muevo al Siguiente
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsFPagCob.m_FCOBRO.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsFPagCob.m_DFCOBRO.TrimRight();//lo guarda en la variable
 	UpdateData(FALSE);
	ChequeaPosicion();
	iEstado = BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//*****************************************************************************************************************
void CDlgFPagCob::ChequeaPosicion()
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
BOOL CDlgFPagCob::BuscarFPagCob()
{
	CString strAux;
	m_rsFPagCob.MoveFirst();
	while (!m_rsFPagCob.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsFPagCob.m_FCOBRO.TrimRight();//elimina el texto vacio por detras
		if (m_strCodigo==strAux)//si encuentra la referencia
		{
			return TRUE;
			break;//sal del bucle;
		}
		m_rsFPagCob.MoveNext();
	}
	bUpdate=FALSE;
	return FALSE;
}
//*****************************************************************************************************************
void CDlgFPagCob::RellenaCampos()
{
	bUpdate=TRUE;
	m_strDescripcion=m_rsFPagCob.m_DFCOBRO.TrimRight();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	iEstado=BUSCADO;
	UpdateData(FALSE);
}