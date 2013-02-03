// DlgIdiomas.cpp: archivo de implementación
//
#include "stdafx.h"
#include "DlgIdiomas.h"
#include ".\dlgidiomas.h"

#define INICIAL 0
#define BUSCADO 1

// Cuadro de diálogo de CDlgIdiomas

IMPLEMENT_DYNAMIC(CDlgIdiomas, CDialog)
CDlgIdiomas::CDlgIdiomas(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIdiomas::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strDescripcion(_T(""))
	, bUpdate(FALSE)
	, iEstado(INICIAL)
{
}

CDlgIdiomas::~CDlgIdiomas()
{
	m_rsIdioma.Close();
}

void CDlgIdiomas::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
	DDV_MaxChars(pDX, m_strCodigo, 3);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
	DDV_MaxChars(pDX, m_strDescripcion, 35);
}


BEGIN_MESSAGE_MAP(CDlgIdiomas, CDialog)
	ON_BN_CLICKED(IDLIMPIAR, OnBnClickedLimpiar)
	ON_EN_KILLFOCUS(IDC_CODIGO, OnEnKillfocusCodigo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
END_MESSAGE_MAP()

BOOL CDlgIdiomas::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_rsIdioma.m_strSort="IDIOMA";
	if (!m_rsIdioma.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	m_dlgBusqueda.SetConexion(m_db);
	if (m_rsIdioma.GetRecordCount()==0)
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
	m_rsIdioma.MoveLast();
	strUltimo=m_rsIdioma.m_IDIOMA.TrimRight();
	m_rsIdioma.MoveFirst();
	strPrimero=m_rsIdioma.m_IDIOMA.TrimRight();
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
		BuscarIdioma();
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
void CDlgIdiomas::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsIdioma.m_pDatabase = m_db;
}
/******************************************************************************************/
void CDlgIdiomas::SetIdioma(CString Codigo,CString Descripcion)
{
	m_strCodigo = Codigo;
	m_strDescripcion=Descripcion;
}
/******************************************************************************************/
void CDlgIdiomas::SetUpdate(BOOL Update)
{
	bUpdate = Update;
}
/*********************************************************************************/
void CDlgIdiomas::OnBnClickedLimpiar()
{
	m_strCodigo.Empty();
	Limpiar();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/*********************************************************************************/
void CDlgIdiomas::Limpiar()
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
	m_rsIdioma.MoveFirst();
}
/*********************************************************************************/
void CDlgIdiomas::OnEnKillfocusCodigo()
{
	if (m_rsIdioma.GetRecordCount()==0)
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}
	CString strCodigoAux=m_strCodigo;
	GetDlgItem(IDC_CODIGO)->GetWindowText(m_strCodigo);
	if (m_strCodigo.IsEmpty())
	{
		Limpiar();
		return;
	}
	if (m_strCodigo==strCodigoAux)
		return;

	if (m_strCodigo.IsEmpty() && iEstado==INICIAL)
		return;
	if (m_strCodigo.IsEmpty() && iEstado==BUSCADO)
	{
		Limpiar();
		return;
	}
	if (BuscarIdioma()==TRUE)//si encuentra el codigo
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
void CDlgIdiomas::OnBnClickedOk()
{
	HRESULT Op;
	UpdateData(TRUE);//recoge los datos
	if(m_strCodigo.IsEmpty())//si no hay codigo "cruje"
	{
		AfxMessageBox(IDS_NO_CODIGO);
		GetDlgItem(IDC_CODIGO)->SetFocus();
		return;
	}
	/**** Guarda las variables en el objeto CIdiomas *****/
	m_rsIdioma.m_IDIOMA=m_strCodigo;
	m_rsIdioma.m_DIDIOMA=m_strDescripcion.TrimRight();
	/*****************************************************/
	if(bUpdate==TRUE)
	{
		Op=m_rsIdioma.UpdateIdioma();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	else
	{
		Op=m_rsIdioma.Insert();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	//Cierra y abre el objeto m_rsIdioma para tener el objeto recien insertado 
	m_rsIdioma.Close();
	if (!m_rsIdioma.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	m_rsIdioma.MoveLast();
	strUltimo=m_rsIdioma.m_IDIOMA.TrimRight();
	m_rsIdioma.MoveFirst();
	strPrimero=m_rsIdioma.m_IDIOMA.TrimRight();
	OnBnClickedLimpiar();//limpia los campos y coloca los botones en posicion estandar
	m_dlgBusqueda.InicializarListas();
}
/*********************************************************************************/
void CDlgIdiomas::OnBnClickedBuscar()
{
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusqueda.SetTipo(CDialogBusqueda::IDIOMA);
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
	BuscarIdioma();//si coges el resultado del dialogo, no hace falta saber si existe
	ChequeaPosicion();
	iEstado=BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}

//****************************************************************************************************
void CDlgIdiomas::OnBnClickedIni()//va al inicio de los registros
{
	/*GetDlgItem(IDC_INI)->EnableWindow(FALSE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente*/
	
	m_rsIdioma.MoveFirst();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodigo=m_rsIdioma.m_IDIOMA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsIdioma.m_DIDIOMA.TrimRight();//lo guarda en la variable
	ChequeaPosicion();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/***************************************************************************************************/
void CDlgIdiomas::OnBnClickedFin()
{
	/*GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente*/
	
	m_rsIdioma.MoveLast();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodigo=m_rsIdioma.m_IDIOMA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsIdioma.m_DIDIOMA.TrimRight();//lo guarda en la variable
	ChequeaPosicion();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//****************************************************************************************************
void CDlgIdiomas::OnBnClickedAnt()
{
	m_rsIdioma.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsIdioma.m_IDIOMA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsIdioma.m_DIDIOMA.TrimRight();//lo guarda en la variable
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//**************************************************************************************************
void CDlgIdiomas::OnBnClickedSig()
{
	if (iEstado == BUSCADO)
		m_rsIdioma.MoveNext();//me muevo al Siguiente
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsIdioma.m_IDIOMA.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsIdioma.m_DIDIOMA.TrimRight();//lo guarda en la variable
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
	iEstado = BUSCADO;
}
//*****************************************************************************************************************
void CDlgIdiomas::ChequeaPosicion()
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
BOOL CDlgIdiomas::BuscarIdioma()
{
	CString strAux;
	m_rsIdioma.MoveFirst();
	while (!m_rsIdioma.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsIdioma.m_IDIOMA.TrimRight();//elimina el texto vacio por detras
		if (m_strCodigo==strAux)//si encuentra la referencia
		{
			bUpdate=TRUE;
			m_strDescripcion=m_rsIdioma.m_DIDIOMA.TrimRight();
			GetDlgItem(IDOK)->EnableWindow(TRUE);
			GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
			iEstado=BUSCADO;
			return TRUE;
			break;//sal del bucle;
		}
		m_rsIdioma.MoveNext();
	}
	return FALSE;
}
//*****************************************************************************************************************
void CDlgIdiomas::RellenaCampos()
{
	bUpdate=TRUE;
	m_strDescripcion=m_rsIdioma.m_DIDIOMA.TrimRight();
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	iEstado=BUSCADO;
	UpdateData(FALSE);
}