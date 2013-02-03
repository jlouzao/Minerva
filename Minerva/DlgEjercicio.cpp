// DlgEjercicio.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Minerva.h"
#include "DlgEjercicio.h"
#include "DlgEmpresas.h"
#include ".\dlgejercicio.h"
#include "BD.h"

// Cuadro de diálogo de CDlgEjercicio

IMPLEMENT_DYNAMIC(CDlgEjercicio, CDialog)

/**************************************************************************************/
CDlgEjercicio::CDlgEjercicio(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEjercicio::IDD, pParent)
{
	m_bPrimeraVez = FALSE;
}

/**************************************************************************************/
CDlgEjercicio::~CDlgEjercicio()
{
}

/**************************************************************************************/
void CDlgEjercicio::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EJERCICIOS_LISTA, m_lstEjercicios);
}

/**************************************************************************************/
BOOL CDlgEjercicio::OnInitDialog()
{
	CDialog::OnInitDialog();

	CEjercicios rsEjercicio;

	rsEjercicio.m_strFilter = "IDEMPR LIKE '" + m_strIdEmpresa + "'";
	if (!rsEjercicio.Open())//sino se abre correctamente
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	while (!rsEjercicio.IsEOF())
	{
		m_lstEjercicios.AddString(rsEjercicio.m_DESCRIPCION);
		rsEjercicio.MoveNext();
	}
	rsEjercicio.Close();

	/* Se desabilita el botón Aceptar hasta que se seleccione un Ejercicio, si los hay */
	if (m_lstEjercicios.GetCount() > 0)
		GetDlgItem(IDOK)->EnableWindow(FALSE);

	return TRUE;  // devolver TRUE a menos que se establezca el foco en un control
}

/**************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgEjercicio, CDialog)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_LBN_DBLCLK(IDC_EJERCICIOS_LISTA, OnLbnDblclkEjerciciosLista)
	ON_LBN_SELCHANGE(IDC_EJERCICIOS_LISTA, OnLbnSelchangeEjerciciosLista)
END_MESSAGE_MAP()


// Controladores de mensajes de CDlgEjercicio

/**************************************************************************************/
void CDlgEjercicio::OnLbnSelchangeEjerciciosLista()
{
	int iIndice = m_lstEjercicios.GetCurSel(); //recoge la selección del objeto ListBox
	m_lstEjercicios.GetText(iIndice, m_strEjercicio);//para saber el nombre de la empresa

	/* Se habilita el botón Aceptar */
	GetDlgItem(IDOK)->EnableWindow(TRUE);
}


/**************************************************************************************/
void CDlgEjercicio::OnLbnDblclkEjerciciosLista()
{
	OnBnClickedOk();
}

/**************************************************************************************/
void CDlgEjercicio::OnBnClickedOk()
{
	OnOK();
}

/**************************************************************************************/
void CDlgEjercicio::OnBnClickedCancel()
{
	/* Si es la primera vez que se va a seleccionar un ejercicio se da mensaje de error
	   si se intenta cerrar la ventana sin haber seleccionado una */
	if (m_bPrimeraVez)
	{
		CString strMsg;
		strMsg.LoadString(IDS_CERRAR_APP);

		if (MessageBox(strMsg,"Minerva",MB_YESNO+MB_ICONQUESTION)==IDYES)//Mensaje de dialogo
			OnCancel();
	}
	else
		OnCancel();
}

/**************************************************************************************/
/*                     FUNCIONES                                                      */
/**************************************************************************************/
void CDlgEjercicio::SetEmpresa(CString strIdEmpresa)
{
	m_strIdEmpresa = strIdEmpresa;
}

void CDlgEjercicio::SetPrimeraVez(BOOL bFlag)
{
	m_bPrimeraVez = bFlag;
}

