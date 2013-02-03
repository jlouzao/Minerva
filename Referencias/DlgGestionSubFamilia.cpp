// DlgGestionFamilias.cpp: archivo de implementación
//
#include "stdafx.h"
#include "DlgGestionSubFamilia.h"
#include ".\dlggestionsubfamilia.h"


// Cuadro de diálogo de CDlgGestionFamilias

IMPLEMENT_DYNAMIC(CDlgGestionSubFamilia, CDialog)
CDlgGestionSubFamilia::CDlgGestionSubFamilia(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGestionSubFamilia::IDD, pParent)
	, m_strCodSFamilia(_T(""))
	, m_strDesSFamilia(_T(""))
	, m_strComercial(_T(""))
	, m_strCompra(_T(""))
	, m_strCFamilia(_T(""))
	, m_strDFamilia(_T(""))
{
}

CDlgGestionSubFamilia::~CDlgGestionSubFamilia()
{
	m_rsSubFamilia.Close();
	m_rsFamilia.Close();
}

void CDlgGestionSubFamilia::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SUBFAMILIA, m_strCodSFamilia);
	DDV_MaxChars(pDX, m_strCodSFamilia, 3);
	DDX_Text(pDX, IDC_DSUBFAMILIA, m_strDesSFamilia);
	DDV_MaxChars(pDX, m_strDesSFamilia, 35);
	DDX_Text(pDX, IDC_DESCOMERCIAL, m_strComercial);
	DDX_Text(pDX, IDC_DESCOMPRA, m_strCompra);


	DDX_Text(pDX, IDC_CFAMILIA, m_strCFamilia);
	DDX_Text(pDX, IDC_DFAMILIA, m_strDFamilia);
}


BEGIN_MESSAGE_MAP(CDlgGestionSubFamilia, CDialog)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDC_NUEVO, OnBnClickedNuevo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDB_BUSCAR_SUBFAMILIA, OnBnClickedBuscarSubFamilia)
	ON_EN_KILLFOCUS(IDC_SUBFAMILIA, OnEnKillfocusSFamilia)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_EN_KILLFOCUS(IDC_DESCOMERCIAL, OnEnKillfocusDescomercial)
	ON_EN_KILLFOCUS(IDC_DESCOMPRA, OnEnKillfocusDescompra)
	ON_BN_CLICKED(IDB_BUSCAR_FAMILIA, OnBnClickedBuscarFamilia)
	ON_EN_KILLFOCUS(IDC_CFAMILIA, OnEnKillfocusCfamilia)
END_MESSAGE_MAP()

BOOL CDlgGestionSubFamilia::OnInitDialog()
{
	CDialog::OnInitDialog();

	/******************* CARGA LOS BOTONES ******************
	VERIFY(m_botonIni.AutoLoad(IDC_INI, this));
	VERIFY(m_botonSig.AutoLoad(IDC_SIG, this));
	VERIFY(m_botonAnt.AutoLoad(IDC_ANT, this));
	VERIFY(m_botonFin.AutoLoad(IDC_FIN, this));
	/******* CARGA LAS BUSQUEDAS PARA AHORRAR TIEMPO ********/
	m_dlgBusquedaSubFamilia.SetConexion(m_db); 
	m_dlgBusquedaFamilia.SetConexion(m_db); 
	/******* CARGA LOS REGISTROS DE LA TABLA FAMILIA ********/
	m_rsFamilia.m_strSort="CFAMILIA";
	if (!m_rsFamilia.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		m_rsFamilia.Close();
		return false;
	}
	if (m_rsFamilia.GetRecordCount()==0)
	{
		AfxMessageBox(IDC_NO_FAMILIA);
		OnCancel();
	}
	/////////////////////////////////////////
	m_rsSubFamilia.m_strSort="CSUBFAM";
	if (!m_rsSubFamilia.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		m_rsSubFamilia.Close();
		return false;
	}
/**************** DESHABILITA LOS BOTONES ***************/
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	/*if (m_rsSubFamilia.GetRecordCount()==0 || m_rsSubFamilia.GetRecordCount()==-1)
	{
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		return FALSE;
	}*/
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
	/********* GUARDA EL PRIMER CÓDIGO Y EL ÚLTIMO **********/
	m_rsSubFamilia.MoveLast();
	strUltimo=m_rsSubFamilia.m_CSUBFAM.TrimRight();
	m_rsSubFamilia.MoveFirst();
	strPrimero=m_rsSubFamilia.m_CSUBFAM.TrimRight();
	UpdateData(FALSE);

	GetDlgItem(IDC_SUBFAMILIA)->SetFocus();
	return FALSE;  // Devuelve TRUE a menos que establezca el foco en un control
}
//**************************************************************************************************************
//************                              FUNCIONES                                               ************
//**************************************************************************************************************
void CDlgGestionSubFamilia::SetConexion(CDatabase *db)//realiza la conexion con las tablas
{
	m_db = db;
	m_rsSubFamilia.m_pDatabase = m_db;
	m_rsFamilia.m_pDatabase = m_db;
}
/**************************************************************************************************************/
void CDlgGestionSubFamilia::OnEnKillfocusSFamilia()
{
	if (m_rsSubFamilia.GetRecordCount()==0)
		return;
	CString strAux=m_strCodSFamilia;
	GetDlgItem(IDC_SUBFAMILIA)->GetWindowText(m_strCodSFamilia);
	if (m_strCodSFamilia.IsEmpty())
	{
		return;
	}
	if (BuscaRegistro()==FALSE)//no se encuentra el registro
	{	
		m_strDesSFamilia.Empty();//vacia la variable
		m_strComercial.Empty();
		m_strCompra.Empty();
		UpdateData(FALSE);
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
		GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
		bUpdate=FALSE;//se debe insertar en caso de pulsar OK
	}
	else
	{
		RellenaCampos();
		ChequeaPosicion();//comprueba que no es ni el primero ni el ultimo
		bUpdate=TRUE;//si se debe actualizar en caso de pulsar OK
		UpdateData(FALSE);
	}
}
/**************************************************************************************************************/
BOOL CDlgGestionSubFamilia::BuscaRegistro()
{
	CString strAux;
	GetDlgItem(IDC_CFAMILIA)->GetWindowText(m_strCFamilia);
	m_rsSubFamilia.MoveFirst();
	while (!m_rsSubFamilia.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsSubFamilia.m_CSUBFAM.TrimRight();//elimina el texto vacio por detras
		if (m_strCodSFamilia==strAux && m_strCFamilia==m_rsSubFamilia.m_CFAMILIA)//si encuentra la subfamilia y pertenece a la familia
		{
			bUpdate=TRUE;
			RellenaCampos();
			//m_strDescripcion=m_rsFamilia.m_DFAMILIA.TrimRight();
			return TRUE;
			break;//sal del bucle;
		}
		m_rsSubFamilia.MoveNext();
	}
	return FALSE;
}
/**************************************************************************************************************/
void CDlgGestionSubFamilia::LimpiarCampos()
{
	m_strDesSFamilia.Empty();
	m_strComercial.Empty();
	m_strCompra.Empty();
}
/**************************************************************************************************************/
void CDlgGestionSubFamilia::RellenaCampos()
{
	m_strDesSFamilia=m_rsSubFamilia.m_DSUBFAM.TrimRight();
	GetDlgItem(IDC_SUBFAMILIA)->SetWindowText(m_strCodSFamilia);
	GetDlgItem(IDC_DSUBFAMILIA)->SetWindowText(m_strDesSFamilia);
//	m_strComercial.Format("%.2f",m_rsSubFamilia.m_DTOVSFAM);
//	m_strCompra.Format("%.2f",m_rsSubFamilia.m_DTOCSFAM);
}
//**************************************************************************************************************
//************                   FUNCIONES  DE LOS BOTONES                                          ************
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnBnClickedIni()
{
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente
	
	m_rsSubFamilia.MoveFirst();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodSFamilia=m_rsSubFamilia.m_CSUBFAM.TrimRight();//lo guarda en la variable
	RellenaCampos();
	ChequeaPosicion();
	//UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_SUBFAMILIA)->SetFocus();
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnBnClickedAnt()
{
	m_rsSubFamilia.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodSFamilia=m_rsSubFamilia.m_CSUBFAM.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_SUBFAMILIA)->SetFocus();
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnBnClickedSig()
{
	if (m_strCodSFamilia.IsEmpty() && bInicial)//si está vacio y es el vacio inicial
	{
		OnBnClickedIni();
		bInicial=FALSE;
		return;
	}
	if (!m_strCodSFamilia.IsEmpty() && !bUpdate)//sino está vacio y es nuevo
	{
		OnBnClickedIni();
		return;
	}
	m_rsSubFamilia.MoveNext();//me muevo al Siguiente
	m_strCodSFamilia=m_rsSubFamilia.m_CSUBFAM.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_SUBFAMILIA)->SetFocus();
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnBnClickedFin()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente
	
	m_rsSubFamilia.MoveLast();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodSFamilia=m_rsSubFamilia.m_CSUBFAM.TrimRight();//lo guarda en la variable
	RellenaCampos();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_SUBFAMILIA)->SetFocus();
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnBnClickedNuevo()
{
	if (m_rsSubFamilia.GetRecordCount()==0)
	{
		return;
	}
	m_strCodSFamilia="";
	LimpiarCampos();
	m_rsSubFamilia.MoveFirst();
	bInicial=TRUE;
	UpdateData(FALSE);
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	bUpdate=FALSE;
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnBnClickedCancel()
{
	OnCancel();
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (m_strCodSFamilia.IsEmpty())//si no hay nada escrito
	{
		AfxMessageBox(IDC_CODIGO_NO_VACIO);
	}
	m_rsSubFamilia.m_CSUBFAM=m_strCodSFamilia.Trim();
	m_rsSubFamilia.m_DSUBFAM=m_strDesSFamilia.Trim();
	m_rsSubFamilia.m_DTOCSFAM=atof(m_strCompra);
	m_rsSubFamilia.m_DTOVSFAM=atof(m_strComercial);
	m_rsSubFamilia.m_CFAMILIA=m_strCFamilia.Trim();
	/************************************/
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);//deshabilito los botones
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//ya sea una nueva entrada
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//o una modificación
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	if(bUpdate==TRUE)//el registro se debe actualizar
	{
		HRESULT RError = m_rsSubFamilia.UpdateRegistro();
		m_strCodSFamilia.Empty();
		LimpiarCampos();
		GetDlgItem(IDC_SUBFAMILIA)->SetFocus();
		UpdateData(FALSE);
		if (RError!=S_OK)
		{
			AfxMessageBox("IDC_INSERTAR_BD");
			return;
		}
	}
	else//el registro se debe insertar
	{
		HRESULT RError = m_rsSubFamilia.Insert();
		m_strCodSFamilia.Empty();
		LimpiarCampos();
		GetDlgItem(IDC_SUBFAMILIA)->SetFocus();
		UpdateData(FALSE);
		if (RError!=S_OK)
		{
			AfxMessageBox("IDC_INSERTAR_BD");
			return;
		}
		m_rsSubFamilia.Close();//Cierra y abre de nuevo la tabla para cargar el nuevo registro
		m_rsSubFamilia.m_strSort="CSUBFAM";
		if (!m_rsSubFamilia.Open(CRecordset::dynaset))//,NULL, CRecordset::useBookmarks )) 
		{
			AfxMessageBox(IDC_ERROR_BD);
			m_rsSubFamilia.Close();
			return;
		}
		m_rsSubFamilia.MoveLast();
		strUltimo=m_rsSubFamilia.m_CSUBFAM.TrimRight();
		m_rsSubFamilia.MoveFirst();
		strPrimero=m_rsSubFamilia.m_CSUBFAM.TrimRight();
	}
	ChequeaPosicion();
	OnBnClickedNuevo();
	m_dlgBusquedaSubFamilia.InicializarListas();
	bInicial=TRUE;
	GetDlgItem(IDC_SUBFAMILIA)->SetFocus();
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnBnClickedBuscarSubFamilia()
{
	INT_PTR Estado;
	m_dlgBusquedaSubFamilia.SetTipo(CDialogBusqueda::SUBFAMILIAS);
	GetDlgItem(IDC_CFAMILIA)->GetWindowText(m_strCFamilia);
	m_dlgBusquedaSubFamilia.SetCodFamilia(m_strCFamilia);
	m_dlgBusquedaSubFamilia.InicializarListas();
	Estado=m_dlgBusquedaSubFamilia.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strCodSFamilia=m_dlgBusquedaSubFamilia.GetCodigo();
	BuscaRegistro();
	RellenaCampos();
	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_SUBFAMILIA)->SetFocus();
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::ChequeaPosicion()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	if (m_strCodSFamilia==strPrimero)
	{
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	}
	if (m_strCodSFamilia==strUltimo)
	{
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
	}
}
//**************************************************************************************************************
BOOL CDlgGestionSubFamilia::ChequeaNumeros(CString cadena)
{
	BOOL bPunto = FALSE;	
	for (int i = 0; i<cadena.GetLength(); i++)
	{
		if ((cadena.GetAt(i) < '0' || cadena.GetAt(i) > '9') && (cadena.GetAt(i) != '-' || (cadena.GetAt(i) == '-' && i != 0))) 
		//&& (cadena.GetAt(i) != '.' || cadena.GetAt(i) == '.' && bPunto == FALSE))	
		{				
			if (cadena.GetAt(i)== '.' && bPunto == FALSE)
				bPunto = TRUE;
			else
				return FALSE;
		}
	}
	return TRUE;
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnEnKillfocusDescomercial()
{
	CString strAux=m_strComercial;
	GetDlgItem(IDC_DESCOMERCIAL)->GetWindowText(m_strComercial);
	if (strAux==m_strComercial)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strComercial)==TRUE)
	{
		GetDlgItem(IDC_DESCOMERCIAL)->SetWindowText(m_strComercial);
	}
	else
	{
		GetDlgItem(IDC_DESCOMERCIAL)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strComercial=strAux;
		GetDlgItem(IDC_DESCOMERCIAL)->SetFocus();
	}
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnEnKillfocusDescompra()
{
	CString strAux=m_strCompra;
	GetDlgItem(IDC_DESCOMPRA)->GetWindowText(m_strCompra);
	if (strAux==m_strCompra)
	{
		return;//Si el anterior y el que recoges ahora son iguales,se sale 
	}
	if (ChequeaNumeros(m_strCompra)==TRUE)
	{
		GetDlgItem(IDC_DESCOMPRA)->SetWindowText(m_strCompra);
	}
	else
	{
		GetDlgItem(IDC_DESCOMPRA)->SetWindowText(strAux);
		AfxMessageBox(IDC_NUMERO_NOVALIDO);
		m_strCompra=strAux;
		GetDlgItem(IDC_DESCOMPRA)->SetFocus();
	}
}
//**************************************************************************************************************
BOOL CDlgGestionSubFamilia::PreTranslateMessage(MSG* pMsg) 
{
     if (pMsg->message == WM_KEYDOWN)
      {
           switch (pMsg->wParam)
           {
                   case VK_RETURN:
					   pMsg->message=VK_TAB;
                    default:
                                break;    
            }
       }
 
     return CDialog::PreTranslateMessage(pMsg);
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnBnClickedBuscarFamilia()
{
	INT_PTR Estado;
	m_dlgBusquedaFamilia.SetTipo(CDialogBusqueda::FAMILIAS);
	Estado=m_dlgBusquedaFamilia.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strCFamilia=m_dlgBusquedaFamilia.GetCodigo();
	m_strDFamilia=m_dlgBusquedaFamilia.GetDescripcion();
	NuevaFamilia();
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::OnEnKillfocusCfamilia()
{
	CString strAux2;
	CString strAux;
	strAux=m_strCFamilia;
	
	GetDlgItem(IDC_CFAMILIA)->GetWindowText(m_strCFamilia);
	if (m_strCFamilia.IsEmpty() || m_strCFamilia == strAux)
	{
		return;
	}	
	m_rsFamilia.MoveFirst();
	while (!m_rsFamilia.IsEOF())
	{
		strAux2=m_rsFamilia.m_CFAMILIA.TrimRight();
		if (m_strCFamilia==strAux2)
		{
			m_strDFamilia=m_rsFamilia.m_DFAMILIA.TrimRight();
			NuevaFamilia();
			return;
		}
		m_rsFamilia.MoveNext();
	}
	m_strCFamilia=strAux;
	GetDlgItem(IDC_CFAMILIA)->SetWindowText(m_strCFamilia);
}
//**************************************************************************************************************
void CDlgGestionSubFamilia::NuevaFamilia()
{
	m_strCodSFamilia="";
	m_strDesSFamilia="";
	//////////////////////PARA LA NAVEGACIÓN/////////////////////////////////////////////
	m_rsSubFamilia.Close();
	m_rsSubFamilia.m_strSort="CSUBFAM";
	m_rsSubFamilia.m_strFilter="CFAMILIA LIKE '" + m_strCFamilia + "'";
	if (!m_rsSubFamilia.Open(CRecordset::dynaset))//,NULL, CRecordset::useBookmarks )) 
	{
		AfxMessageBox(IDC_ERROR_BD);
		m_rsSubFamilia.Close();
		return;
	}
	/////////////////////PARA EL BOTON DE LISTA//////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
	GetDlgItem(IDB_BUSCAR_SUBFAMILIA)->EnableWindow(TRUE);
	GetDlgItem(IDC_DSUBFAMILIA)->EnableWindow(TRUE);
	GetDlgItem(IDC_SUBFAMILIA)->EnableWindow(TRUE);
	GetDlgItem(IDC_SUBFAMILIA)->SetFocus();
	//////////////////////////////////////////
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	//////////////////////////////////////////
	bInicial=TRUE;
	//////////////////////////////////////////
	UpdateData(FALSE);
	//////////////////////////////////////////
	if (m_rsSubFamilia.GetRecordCount()==0)
	{
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		return;
	}
	m_rsSubFamilia.MoveLast();
	strUltimo=m_rsSubFamilia.m_CSUBFAM.TrimRight();
	m_rsSubFamilia.MoveFirst();
	strPrimero=m_rsSubFamilia.m_CSUBFAM.TrimRight();
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
}
