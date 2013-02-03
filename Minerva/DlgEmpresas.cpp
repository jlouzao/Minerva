// DlgEmpresas.cpp: archivo de implementación
//

#include "stdafx.h"
#include "Minerva.h"
#include "MinervaDlg.h"
#include "DlgEmpresas.h"
#include ".\dlgempresas.h"

// Cuadro de diálogo de CDlgEmpresas

IMPLEMENT_DYNAMIC(CDlgEmpresas, CDialog)

/*************************************************************************/
CDlgEmpresas::CDlgEmpresas(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEmpresas::IDD, pParent)
{
	m_bPrimeraVez = FALSE;
}

/*************************************************************************/
CDlgEmpresas::~CDlgEmpresas()
{
}

/*************************************************************************/
void CDlgEmpresas::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_EMPRESAS, m_lstEmpresas);
}

/*************************************************************************/
BOOL CDlgEmpresas::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_rsEmpresas.m_strSort = "DESCRIPCION";

/////////////////////////////////////////////////////////
//       Busca e introduce todas las empresas          //
/////////////////////////////////////////////////////////

	if (!m_rsEmpresas.Open())
	{
		AfxMessageBox(IDC_ERROR_BD);
		return FALSE;
	}

	while (!m_rsEmpresas.IsEOF())
	{
		m_lstEmpresas.AddString(m_rsEmpresas.m_DESCRIPCION);
		m_rsEmpresas.MoveNext();
	}

	m_rsEmpresas.Close();

	/* Se desabilita el botón Aceptar hasta que se seleccione una Empresa */
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	return TRUE;  // devolver TRUE a menos que se establezca el foco en un control
}

BEGIN_MESSAGE_MAP(CDlgEmpresas, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_LBN_DBLCLK(IDC_LIST_EMPRESAS, OnLbnDblclkListEmpresas)
	ON_LBN_SELCHANGE(IDC_LIST_EMPRESAS, OnLbnSelchangeListEmpresas)
END_MESSAGE_MAP()


// Controladores de mensajes de CDlgEmpresas

/**************************************************************************************/
void CDlgEmpresas::OnLbnSelchangeListEmpresas()
{
	int iIndice = m_lstEmpresas.GetCurSel(); //recoge la selección del objeto ListBox
	m_lstEmpresas.GetText(iIndice, m_strNombreEmpresa);//para saber el nombre de la empresa

	/* Se habilita el botón Aceptar */
	GetDlgItem(IDOK)->EnableWindow(TRUE);

}

/**************************************************************************************/
void CDlgEmpresas::OnLbnDblclkListEmpresas()
{
	OnBnClickedOk();
}

/**************************************************************************************/
void CDlgEmpresas::OnBnClickedOk()
{
	m_rsEmpresas.m_strFilter = "DESCRIPCION LIKE '" + m_strNombreEmpresa + "'";  //filtro para seleccionar
	if (!m_rsEmpresas.Open())//sino se abre correctamente
	{
		AfxMessageBox(IDC_ERROR_BD);//mensaje de error
		return;
	}

	m_strIdEmpresa=m_rsEmpresas.m_ID;//cogemos el registro oportuno
	
	m_rsEmpresas.Close();//cerramos la selección
	OnOK();
}

/**************************************************************************************/
void CDlgEmpresas::OnBnClickedCancel()
{
	/* Si es la primera vez que se va a seleccionar una empresa se da mensaje de error
	   si se intenta cerrar la ventana sin haber seleccionado una */
	if (m_bPrimeraVez)
	{
		CString strMsg;
		strMsg.LoadString(IDS_CERRAR_APP);

		if (MessageBox(strMsg,"Minerva",MB_YESNO+MB_ICONQUESTION)==IDYES)
			OnCancel();
	}
	else
		OnCancel();
}

/**************************************************************************************/
/******  FUNCIONES                                                                    */
/**************************************************************************************/

CString CDlgEmpresas::GetIdEmpresa()
{
	return m_strIdEmpresa;
}

/**************************************************************************************/
CString CDlgEmpresas::GetNombreEmpresa()
{
	return m_strNombreEmpresa;
}

/**************************************************************************************/
void CDlgEmpresas::SetPrimeraVez(BOOL bFlag)
{
	m_bPrimeraVez = bFlag;
}






