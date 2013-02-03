// DlgRuTrans.cpp: archivo de implementación
//
#include "stdafx.h"
#include "DlgRutran.h"
#include ".\dlgRutran.h"

#define INICIAL 0
#define BUSCADO 1

// Cuadro de diálogo de CDlgRutran

IMPLEMENT_DYNAMIC(CDlgRutran, CDialog)
CDlgRutran::CDlgRutran(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRutran::IDD, pParent)
	, m_strCodigo(_T(""))
	, m_strDescripcion(_T(""))
	, m_strModelo(_T(""))
	, m_strMatricula(_T(""))
	, m_strTara(_T(""))
	, m_strTaraMax(_T(""))
	, bUpdate(FALSE)
	, iEstado(INICIAL)
{
}

CDlgRutran::~CDlgRutran()
{
}

void CDlgRutran::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODIGO, m_ctrlCodigo);
	DDX_Text(pDX, IDC_CODIGO, m_strCodigo);
	DDV_MaxChars(pDX, m_strCodigo, 3);
	DDX_Text(pDX, IDC_DESCRIPCION, m_strDescripcion);
	DDV_MaxChars(pDX, m_strDescripcion, 35);
	DDX_Text(pDX, IDC_MODELO, m_strModelo);
	DDV_MaxChars(pDX, m_strModelo, 35);
	DDX_Text(pDX, IDC_MATRICULA, m_strMatricula);
	DDV_MaxChars(pDX, m_strMatricula, 15);
	DDX_Text(pDX, IDC_TARA, m_strTara);
	DDV_MaxChars(pDX, m_strTara, 9);
	DDX_Text(pDX, IDC_TARA_MAX, m_strTaraMax);
	DDV_MaxChars(pDX, m_strTaraMax, 9);
}


BEGIN_MESSAGE_MAP(CDlgRutran, CDialog)
	ON_BN_CLICKED(IDLIMPIAR, OnBnClickedLimpiar)
	ON_EN_KILLFOCUS(IDC_CODIGO, OnEnKillfocusCodigo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDBUSCAR, OnBnClickedBuscar)
	ON_EN_KILLFOCUS(IDC_TARA, OnEnKillfocusTara)
	ON_EN_KILLFOCUS(IDC_TARA_MAX, OnEnKillfocusTaraMax)
END_MESSAGE_MAP()

BOOL CDlgRutran::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_rsRuTran.m_strSort="CRUTRAN";
	if (!m_rsRuTran.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	m_dlgBusqueda.SetConexion(m_db);
	if(m_rsRuTran.GetRecordCount()==0)
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
	m_rsRuTran.MoveLast();
	strUltimo=m_rsRuTran.m_CRUTRAN.TrimRight();
	m_rsRuTran.MoveFirst();
	strPrimero=m_rsRuTran.m_CRUTRAN.TrimRight();
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
		BuscarRuTrans();
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
void CDlgRutran::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsRuTran.m_pDatabase = m_db;
}
/******************************************************************************************/
void CDlgRutran::SetRuTran(CString Codigo,CString Descripcion)
{
	m_strCodigo = Codigo;
	m_strDescripcion=Descripcion;
}
/******************************************************************************************/
void CDlgRutran::SetUpdate(BOOL Update)
{
	bUpdate = Update;
}
/*********************************************************************************/
void CDlgRutran::OnBnClickedLimpiar()
{
	m_strCodigo.Empty();
	Limpiar();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
void CDlgRutran::Limpiar()
{
	m_strDescripcion.Empty();
	m_strModelo.Empty();
	m_strMatricula.Empty();
	m_strTara.Empty();
	m_strTaraMax.Empty();
	UpdateData(FALSE);
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(FALSE);
	iEstado=INICIAL;
	m_rsRuTran.MoveFirst();
}
/*********************************************************************************/
void CDlgRutran::OnEnKillfocusCodigo()
{
	if (m_rsRuTran.GetRecordCount()==0)
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
	if (BuscarRuTrans()==TRUE)//si encuentra el codigo
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
	UpdateData(FALSE);
}
/*********************************************************************************/
void CDlgRutran::OnBnClickedOk()
{
	HRESULT Op;
	UpdateData(TRUE);
	if(m_strCodigo.IsEmpty())
	{
		AfxMessageBox(IDS_NO_CODIGO);
		GetDlgItem(IDC_CODIGO)->SetFocus();
		return;
	}
	m_rsRuTran.m_CRUTRAN=m_strCodigo;
	m_rsRuTran.m_DRUTRAN=m_strDescripcion.TrimRight();
	m_rsRuTran.m_MATRICULA=m_strMatricula.TrimRight();
	m_rsRuTran.m_MODELO=m_strModelo.TrimRight();
	m_rsRuTran.m_TARA=atof(m_strTara);
	m_rsRuTran.m_PESOMAXIMO=atof(m_strTaraMax);
	if(bUpdate==TRUE)
	{
		Op=m_rsRuTran.UpdateRutran();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	else
	{
		Op=m_rsRuTran.Insert();
		if(!Op==S_OK)
		{
			AfxMessageBox(IDS_ERROR_BD);
		}
	}
	m_rsRuTran.Close();
	if (!m_rsRuTran.Open(CRecordset::dynaset))//comprueba si se puede abrir la tabla
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	m_rsRuTran.MoveFirst();
	strPrimero=m_rsRuTran.m_CRUTRAN.TrimRight();
	m_rsRuTran.MoveLast();
	strUltimo=m_rsRuTran.m_CRUTRAN.TrimRight();
	OnBnClickedLimpiar();
	m_dlgBusqueda.InicializarListas();

}
/*********************************************************************************/
void CDlgRutran::OnBnClickedBuscar()
{
	INT_PTR Estado;
	m_dlgBusqueda.SetTipo(CDialogBusqueda::RUTRAN);
	m_dlgBusqueda.SetGestionar(FALSE);
	Estado=m_dlgBusqueda.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	OnBnClickedLimpiar();
	m_strCodigo=m_dlgBusqueda.GetCodigo();
	m_strDescripcion=m_dlgBusqueda.GetDescripcion();
	BuscarRuTrans();
	RellenaCampos();
	UpdateData(False);
	ChequeaPosicion();
	iEstado=BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}

//****************************************************************************************************
void CDlgRutran::OnBnClickedIni()//va al inicio de los registros
{
	/*GetDlgItem(IDC_INI)->EnableWindow(FALSE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente*/
	
	m_rsRuTran.MoveFirst();
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsRuTran.m_CRUTRAN.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsRuTran.m_DRUTRAN.TrimRight();//lo guarda en la variable
	RellenaCampos();
	UpdateData(FALSE);//actualiza la variable
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
/***************************************************************************************************/
void CDlgRutran::OnBnClickedFin()
{
	/*GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente*/
	
	m_rsRuTran.MoveLast();
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsRuTran.m_CRUTRAN.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsRuTran.m_DRUTRAN.TrimRight();//lo guarda en la variable
	RellenaCampos();
	UpdateData(FALSE);//actualiza la variable
	ChequeaPosicion();
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//****************************************************************************************************
void CDlgRutran::OnBnClickedAnt()
{
	m_rsRuTran.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsRuTran.m_CRUTRAN.TrimRight();//lo guarda en la variable
	m_strDescripcion=m_rsRuTran.m_DRUTRAN.TrimRight();//lo guarda en la variable
	RellenaCampos();
	UpdateData(FALSE);
	//********* COMPRUEBA QUE NO SEA EL ÚLTIMO REGISTRO*********
	ChequeaPosicion();
}
//**************************************************************************************************
void CDlgRutran::OnBnClickedSig()
{
	if (iEstado == BUSCADO)
		m_rsRuTran.MoveNext();//me muevo al Siguiente
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodigo=m_rsRuTran.m_CRUTRAN.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	ChequeaPosicion();
	iEstado=BUSCADO;
	GetDlgItem(IDC_CODIGO)->SetFocus();
}
//*****************************************************************************************************************
void CDlgRutran::ChequeaPosicion()
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
BOOL CDlgRutran::BuscarRuTrans()
{
	CString strAux;
	m_rsRuTran.MoveFirst();
	while (!m_rsRuTran.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsRuTran.m_CRUTRAN.TrimRight();//elimina el texto vacio por detras
		if (m_strCodigo==strAux)//si encuentra la referencia
		{
			return TRUE;
			break;//sal del bucle;
		}
		m_rsRuTran.MoveNext();
	}
	return FALSE;
}
//*****************************************************************************************************************
void CDlgRutran::RellenaCampos()
{
	bUpdate=TRUE;
	m_strDescripcion=m_rsRuTran.m_DRUTRAN.TrimRight();
	iEstado=BUSCADO;
	m_strMatricula=m_rsRuTran.m_MATRICULA.TrimRight();
	m_strModelo=m_rsRuTran.m_MODELO.TrimRight();
	m_strTara.Format("%.2f", m_rsRuTran.m_TARA);
	m_strTaraMax.Format("%.2f", m_rsRuTran.m_PESOMAXIMO);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDLIMPIAR)->EnableWindow(TRUE);
	UpdateData(FALSE);
}
/*************************************************************************************/
BOOL CDlgRutran::ChequeaNumeros(CString cadena)
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
void CDlgRutran::OnEnKillfocusTara()
{
	CString strAux=m_strTara;
	GetDlgItem(IDC_TARA)->GetWindowText(m_strTara);
	if(ChequeaNumeros(m_strTara)==FALSE)
	{
		m_strTara=strAux;
		GetDlgItem(IDC_TARA)->SetWindowText(m_strTara);
		GetDlgItem(IDC_TARA)->SetFocus();
	}
	else
	{
		GetDlgItem(IDC_TARA)->SetWindowText(m_strTara);
	}
}
/*************************************************************************************/
void CDlgRutran::OnEnKillfocusTaraMax()
{
	CString strAux=m_strTaraMax;
	GetDlgItem(IDC_TARA_MAX)->GetWindowText(m_strTaraMax);
	if(ChequeaNumeros(m_strTaraMax)==FALSE)
	{
		m_strTaraMax=strAux;
		GetDlgItem(IDC_TARA_MAX)->SetWindowText(m_strTaraMax);
		GetDlgItem(IDC_TARA_MAX)->SetFocus();
	}
	else
	{
		GetDlgItem(IDC_TARA_MAX)->SetWindowText(m_strTaraMax);
	}
}
/*************************************************************************************/