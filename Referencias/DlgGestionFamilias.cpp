// DlgGestionFamilias.cpp: archivo de implementación
//
#include "stdafx.h"
#include "DlgGestionFamilias.h"
#include ".\dlggestionfamilias.h"


// Cuadro de diálogo de CDlgGestionFamilias

IMPLEMENT_DYNAMIC(CDlgGestionFamilias, CDialog)
CDlgGestionFamilias::CDlgGestionFamilias(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGestionFamilias::IDD, pParent)
	, m_strCodFamilia(_T(""))
	, m_strDesFamilia(_T(""))
	, m_strComercial(_T(""))
	, m_strCompra(_T(""))
{
	bInicial=TRUE;
	bUpdate=FALSE;
}

CDlgGestionFamilias::~CDlgGestionFamilias()
{
	m_rsFamilia.Close();
}

void CDlgGestionFamilias::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FAMILIA, m_strCodFamilia);
		DDV_MaxChars(pDX, m_strCodFamilia, 3);
	DDX_Text(pDX, IDC_DFAMILIA, m_strDesFamilia);
		DDV_MaxChars(pDX, m_strDesFamilia, 35);
	DDX_Text(pDX, IDC_DESCOMERCIAL, m_strComercial);
	DDX_Text(pDX, IDC_DESCOMPRA, m_strCompra);
}


BEGIN_MESSAGE_MAP(CDlgGestionFamilias, CDialog)
	ON_BN_CLICKED(IDC_INI, OnBnClickedIni)
	ON_BN_CLICKED(IDC_ANT, OnBnClickedAnt)
	ON_BN_CLICKED(IDC_SIG, OnBnClickedSig)
	ON_BN_CLICKED(IDC_FIN, OnBnClickedFin)
	ON_BN_CLICKED(IDC_NUEVO, OnBnClickedNuevo)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDB_BUSCAR_FAMILIA, OnBnClickedBuscarFamilia)
	ON_EN_KILLFOCUS(IDC_FAMILIA, OnEnKillfocusFamilia)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_EN_KILLFOCUS(IDC_DESCOMERCIAL, OnEnKillfocusComercial)
	ON_EN_KILLFOCUS(IDC_DESCOMPRA, OnEnKillfocusDescompra)
END_MESSAGE_MAP()

BOOL CDlgGestionFamilias::OnInitDialog()
{
	CDialog::OnInitDialog();
	/******************* CARGA LOS BOTONES ******************
	VERIFY(m_botonIni.AutoLoad(IDC_INI, this));
	VERIFY(m_botonSig.AutoLoad(IDC_SIG, this));
	VERIFY(m_botonAnt.AutoLoad(IDC_ANT, this));
	VERIFY(m_botonFin.AutoLoad(IDC_FIN, this));
	/******* CARGA LAS BUSQUEDAS PARA AHORRAR TIEMPO ********/
	m_dlgBusquedaFamilia.SetConexion(m_db); 
	/******* CARGA LOS REGISTROS DE LA TABLA FAMILIA ********/
	m_rsFamilia.m_strSort="CFAMILIA";
	if (!m_rsFamilia.Open(CRecordset::dynaset))//,NULL, CRecordset::useBookmarks )) 
	{
		AfxMessageBox(IDC_ERROR_BD);
		m_rsFamilia.Close();
		return false;
	}
	/**************** DESHABILITA LOS BOTONES ***************/
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	if (m_rsFamilia.GetRecordCount()==0 || m_rsFamilia.GetRecordCount()==-1)
	{
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		return FALSE;
	}
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	/********* GUARDA EL PRIMER CÓDIGO Y EL ÚLTIMO **********/
	m_rsFamilia.MoveLast();
	strUltimo=m_rsFamilia.m_CFAMILIA.TrimRight();
	m_rsFamilia.MoveFirst();
	strPrimero=m_rsFamilia.m_CFAMILIA.TrimRight();
	

	GetDlgItem(IDC_FAMILIA)->SetFocus();
	return FALSE;  // Devuelve TRUE a menos que establezca el foco en un control
}
//**************************************************************************************************************
//************                              FUNCIONES                                               ************
//**************************************************************************************************************
void CDlgGestionFamilias::SetConexion(CDatabase *db)//realiza la conexion con las tablas
{
	m_db = db;
	m_rsFamilia.m_pDatabase = m_db;
}
/**************************************************************************************************************/
void CDlgGestionFamilias::OnEnKillfocusFamilia()
{
	CString strAux=m_strCodFamilia;
	GetDlgItem(IDC_FAMILIA)->GetWindowText(m_strCodFamilia);
	if (m_strCodFamilia.IsEmpty())
	{
		return;
	}
	if (m_rsFamilia.GetRecordCount()==0)
		return;
	if (BuscaRegistro()==FALSE)//no se encuentra el registro
	{	
		m_strDesFamilia.Empty();//vacia la variable
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
BOOL CDlgGestionFamilias::BuscaRegistro()
{
	CString strAux;
	m_rsFamilia.MoveFirst();
	while (!m_rsFamilia.IsEOF())//Viaja por toda la tabla buscando el registro
	{
		strAux=m_rsFamilia.m_CFAMILIA.TrimRight();//elimina el texto vacio por detras
		if (m_strCodFamilia==strAux)//si encuentra la referencia
		{
			bUpdate=TRUE;
			RellenaCampos();
			//m_strDescripcion=m_rsFamilia.m_DFAMILIA.TrimRight();
			return TRUE;
			break;//sal del bucle;
		}
		m_rsFamilia.MoveNext();
	}
	return FALSE;
}
/**************************************************************************************************************/
void CDlgGestionFamilias::LimpiarCampos()
{
	m_strDesFamilia="";
	m_strComercial="";
	m_strCompra="";
}
/**************************************************************************************************************/
void CDlgGestionFamilias::RellenaCampos()
{
	m_strDesFamilia=m_rsFamilia.m_DFAMILIA.TrimRight();
	m_strComercial.Format("%.2f",m_rsFamilia.m_DTOVFAM);
	m_strCompra.Format("%.2f",m_rsFamilia.m_DTOCFAM);
}

//**************************************************************************************************************
//************                   FUNCIONES  DE LOS BOTONES                                          ************
//**************************************************************************************************************
void CDlgGestionFamilias::OnBnClickedIni()
{
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//y de siguiente
	
	m_rsFamilia.MoveFirst();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodFamilia=m_rsFamilia.m_CFAMILIA.TrimRight();//lo guarda en la variable
	RellenaCampos();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_FAMILIA)->SetFocus();
}
/**************************************************************************************************************/
void CDlgGestionFamilias::OnBnClickedAnt()
{
	m_rsFamilia.MovePrev();//muevete al Anterior
	if (!bUpdate)	
		bUpdate=TRUE;
	m_strCodFamilia=m_rsFamilia.m_CFAMILIA.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_FAMILIA)->SetFocus();
}
/**************************************************************************************************************/
void CDlgGestionFamilias::OnBnClickedSig()
{
	if (m_strCodFamilia.IsEmpty() && bInicial)//si está vacio y es el vacio inicial
	{
		OnBnClickedIni();
		bInicial=FALSE;
		return;
	}
	if (!m_strCodFamilia.IsEmpty() && !bUpdate)//sino está vacio y es nuevo
	{
		OnBnClickedIni();
		return;
	}
	m_rsFamilia.MoveNext();//me muevo al Siguiente
	m_strCodFamilia=m_rsFamilia.m_CFAMILIA.TrimRight();//lo guarda en la variable
	RellenaCampos();
 	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_FAMILIA)->SetFocus();
}
/**************************************************************************************************************/
void CDlgGestionFamilias::OnBnClickedFin()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);//habilito el boton de inicio
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);//y anterior
	GetDlgItem(IDC_FIN)->EnableWindow(FALSE);//deshabilito el boton de final
	GetDlgItem(IDC_SIG)->EnableWindow(FALSE);//y de siguiente
	
	m_rsFamilia.MoveLast();
	if (!bUpdate)
		bUpdate=TRUE;
	m_strCodFamilia=m_rsFamilia.m_CFAMILIA.TrimRight();//lo guarda en la variable
	RellenaCampos();
	UpdateData(FALSE);//actualiza la variable
	GetDlgItem(IDC_FAMILIA)->SetFocus();
}
///////////////////////////////////////////
void CDlgGestionFamilias::OnBnClickedNuevo()
{
	m_strCodFamilia="";
	LimpiarCampos();
	UpdateData(FALSE);
	m_rsFamilia.MoveFirst();
	bInicial=TRUE;
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	bUpdate=FALSE;
}
///////////////////////////////////////////
void CDlgGestionFamilias::OnBnClickedCancel()
{
	OnCancel();
}
//////////////////////////////////////////
void CDlgGestionFamilias::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (m_strCodFamilia.IsEmpty())//si no hay nada escrito
	{
		AfxMessageBox(IDC_CODIGO_NO_VACIO);
	}
    m_rsFamilia.m_CFAMILIA=m_strCodFamilia.TrimRight();
	m_rsFamilia.m_DFAMILIA=m_strDesFamilia.TrimRight();
	m_rsFamilia.m_DTOCFAM=atof(m_strCompra);
	m_rsFamilia.m_DTOVFAM=atof(m_strComercial);
	/************************************/
	GetDlgItem(IDC_INI)->EnableWindow(FALSE);//deshabilito los botones
	GetDlgItem(IDC_ANT)->EnableWindow(FALSE);//ya sea una nueva entrada
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);//o una modificación
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	if(bUpdate==TRUE)//el registro se debe actualizar
	{
		HRESULT RError = m_rsFamilia.UpdateRegistro();
		m_strCodFamilia="";
		LimpiarCampos();
		GetDlgItem(IDC_FAMILIA)->SetFocus();
		UpdateData(FALSE);
	}
	else//el registro se debe insertar
	{
		HRESULT RError = m_rsFamilia.Insert();
		m_strCodFamilia="";
		LimpiarCampos();
		GetDlgItem(IDC_FAMILIA)->SetFocus();
		UpdateData(FALSE);
		if (RError!=S_OK)
		{
			AfxMessageBox("IDC_INSERTAR_BD");
			return;
		}
		m_rsFamilia.Close();//Cierra y abre de nuevo la tabla para cargar el nuevo registro
		m_rsFamilia.m_strSort="CFAMILIA";
		if (!m_rsFamilia.Open(CRecordset::dynaset))//,NULL, CRecordset::useBookmarks )) 
		{
			AfxMessageBox(IDC_ERROR_BD);
			m_rsFamilia.Close();
			return;
		}
		m_rsFamilia.MoveLast();
		strUltimo=m_rsFamilia.m_CFAMILIA.TrimRight();
		m_rsFamilia.MoveFirst();
		strPrimero=m_rsFamilia.m_CFAMILIA.TrimRight();
	}
	OnBnClickedNuevo();
	m_dlgBusquedaFamilia.InicializarListas();
	bInicial=TRUE;
	GetDlgItem(IDC_FAMILIA)->SetFocus();
}
//////////////////////////////////////////
void CDlgGestionFamilias::OnBnClickedBuscarFamilia()
{
	INT_PTR Estado;
	m_dlgBusquedaFamilia.SetTipo(CDialogBusqueda::FAMILIAS);
	Estado=m_dlgBusquedaFamilia.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strCodFamilia=m_dlgBusquedaFamilia.GetCodigo();
	BuscaRegistro();
	RellenaCampos();
	UpdateData(FALSE);
	ChequeaPosicion();
	GetDlgItem(IDC_FAMILIA)->SetFocus();
}
//////////////////////////////////////////////////////////////////////////////////////
void CDlgGestionFamilias::ChequeaPosicion()
{
	GetDlgItem(IDC_INI)->EnableWindow(TRUE);
	GetDlgItem(IDC_ANT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SIG)->EnableWindow(TRUE);
	GetDlgItem(IDC_FIN)->EnableWindow(TRUE);
	if (m_strCodFamilia==strPrimero)
	{
		GetDlgItem(IDC_INI)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANT)->EnableWindow(FALSE);
	}
	if (m_strCodFamilia==strUltimo)
	{
		GetDlgItem(IDC_FIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_SIG)->EnableWindow(FALSE);
	}
}
////////////////////////////////////////////////////////////////////////////////////////
BOOL CDlgGestionFamilias::ChequeaNumeros(CString cadena)
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
////////////////////////////////////////////////////////////////////////////////////////////////
void CDlgGestionFamilias::OnEnKillfocusComercial()
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
////////////////////////////////////////////////////////////////////////////////////////
void CDlgGestionFamilias::OnEnKillfocusDescompra()
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
////////////////////////////////////////////////////////////////////////////////////////
BOOL CDlgGestionFamilias::PreTranslateMessage(MSG* pMsg) 
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