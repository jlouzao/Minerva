// DlgPais.cpp: archivo de implementación
//
#include "stdafx.h"
#include "DlgPais.h"
#include ".\dlgpais.h"

#define INICIAL 0
#define BUSCADO 1

// Cuadro de diálogo de CDlgPais

IMPLEMENT_DYNAMIC(CDlgPais, CDialog)
CDlgPais::CDlgPais(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPais::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strDescripcion(_T(""))
	, bUpdate(FALSE)
	, iEstado(INICIAL)
{
}

CDlgPais::~CDlgPais()
{
}

void CDlgPais::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
	DDV_MaxChars(pDX, m_strCodigo, 3);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
	DDV_MaxChars(pDX, m_strDescripcion, 35);
}


BEGIN_MESSAGE_MAP(CDlgPais, CDialog)
	ON_BN_CLICKED(IDLIMPIAR, OnBnClickedLimpiar)
	ON_EN_KILLFOCUS(IDC_CODIGO, OnEnKillfocusCodigo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
END_MESSAGE_MAP()

BOOL CDlgPais::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_rsPais.m_strSort="CPAIS";
	if (!m_rsPais.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	m_dlgBusqueda.SetConexion(m_db);
	if(m_rsPais.GetRecordCount()==0)
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
	VERIFY(m_botonFin.AutoLoad(IDC_FIN, this));
	/********** CARGA LOS DATOS **************/
	m_rsPais.MoveLast();
	strUltimo=m_rsPais.m_CPAIS.TrimRight();
	m_rsPais.MoveFirst();
	strPrimero=m_rsPais.m_CPAIS.TrimRight();
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
		BuscarPais();
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
void CDlgPais::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsPais.m_pDatabase = m_db;
}
/******************************************************************************************/
void CDlgPais::SetPais(CString Codigo,CString Descripcion)
{
	m_strCodigo = Codigo;
	m_strDescripcion=Descripcion;
}
/******************************************************************************************/
void CDlgPais::SetUpdate(BOOL Update)
{
	bUpdate = Update;
}
/*********************************************************************************/
void CDlgPais::OnBnClickedLimpiar()
{
	m_strCodigo.Empty();
	Limpiar();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
void CDlgPais::Limpiar()
{
	m_strDescripcion.Empty();
	UpdateData(FALSE);
	iEstado=INICIAL;
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(FALSE);
	m_rsPais.MoveFirst();
}
/*********************************************************************************/
void CDlgPais::OnEnKillfocusCodigo()
{
	if(m_rsPais.GetRecordCount()==0)
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
	if (BuscarPais()==TRUE)//si encuentra el codigo
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
void CDlgPais::OnBnClickedOk()
{
	HRESULT Op;
	UpdateData(TRUE);//recoge los datos
	if(m_strCodigo.IsEmpty())//si no hay codigo "cruje"
	{
		AfxMessageBox(IDS_NO_CODIGO);
		GetDlgItem(IDC_CODIGO)->SetFocus();
		return;
	}
	/**** Guarda las variables en el objeto CPais *****/
	m_rsPais.m_CPAIS=m_strCodigo;
	m_rsPais.m_DPAIS=m_strDescripcion.TrimRight();
	/*****************************************************/
	if(bUpdate==TRUE)
	{
		Op=m_rsPais.UpdatePais();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	else
	{
		Op=m_rsPais.Insert();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	m_rsPais.Close();
	if (!m_rsPais.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	m_rsPais.MoveLast();
	strUltimo=m_rsPais.m_CPAIS.TrimRight();
	m_rsPais.MoveFirst();
	strPrimero=m_rsPais.m_CPAIS.TrimRight();
	OnBnClickedLimpiar();
	m_dlgBusqueda.InicializarListas();
}
/*********************************************************************************/
void CDlgPais::OnBnClickedBuscar()
{
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusqueda.SetTipo(CDialogBusqueda::PAIS);
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
	BuscarPais();
	ChequeaPosicion();
	iEstado=BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}

//****************************************************************************************************
void CDlgPais::OnBnClickedIni()//va al inicio de los registros
{
	/*GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);//y de siguiente*/
	
	m_rsPais.MoveFirst();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodigo=m_rsPais.m_CPAIS.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsPais.m_DPAIS.TrimRight();//lo guarda en la variable
	ChequeaPosicion();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/***************************************************************************************************/
void CDlgPais::OnBnClickedFin()
{
	/*GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente*/
	
	m_rsPais.MoveLast();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodigo=m_rsPais.m_CPAIS.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsPais.m_DPAIS.TrimRight();//lo guarda en la variable
	ChequeaPosicion();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
		GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//****************************************************************************************************
void CDlgPais::OnBnClickedAnt()
{
	m_rsPais.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsPais.m_CPAIS.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsPais.m_DPAIS.TrimRight();//lo guarda en la variable
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//**************************************************************************************************
void CDlgPais::OnBnClickedSig()
{
	if (iEstado == BUSCADO)
		m_rsPais.MoveNext();//me muevo al Siguiente
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsPais.m_CPAIS.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsPais.m_DPAIS.TrimRight();//lo guarda en la variable
 	UpdateData(FALSE);
	ChequeaPosicion();
	iEstado = BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//*****************************************************************************************************************
void CDlgPais::ChequeaPosicion()
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
BOOL CDlgPais::BuscarPais()
{
	CString strAux;
	m_rsPais.MoveFirst();
	while (!m_rsPais.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsPais.m_CPAIS.TrimRight();//elimina el texto vacio por detras
		if (m_strCodigo==strAux)//si encuentra la referencia
		{
			return TRUE;
			break;//sal del bucle;
		}
		m_rsPais.MoveNext();
	}
	return FALSE;
}
//*****************************************************************************************************************
void CDlgPais::RellenaCampos()
{
	bUpdate=TRUE;
	m_strDescripcion=m_rsPais.m_DPAIS.TrimRight();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	iEstado=BUSCADO;
	UpdateData(FALSE);
}