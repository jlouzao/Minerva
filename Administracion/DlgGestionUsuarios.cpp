// DlgGestionUsuarios.cpp: archivo de implementación
//

#include "stdafx.h"
#include "DlgGestionUsuarios.h"
#include ".\dlggestionusuarios.h"
#include "DlgCrearUsuario.h"
#include "DlgCambiarPassw.h"
#include "BD.h"

/*****************************************************************************************/
// Cuadro de diálogo de CDlgGestionUsuarios
/*****************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgGestionUsuarios, CDialog)
CDlgGestionUsuarios::CDlgGestionUsuarios(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGestionUsuarios::IDD, pParent)
{
}

/*****************************************************************************************/
CDlgGestionUsuarios::~CDlgGestionUsuarios()
{
}

/*****************************************************************************************/
void CDlgGestionUsuarios::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USUARIOS, m_lstUsuarios);
}
/*****************************************************************************************/

BEGIN_MESSAGE_MAP(CDlgGestionUsuarios, CDialog)
	ON_BN_CLICKED(ID_AGREGAR, OnBnClickedAgregar)
	ON_BN_CLICKED(ID_ELIMINAR, OnBnClickedEliminar)
	ON_BN_CLICKED(ID_PASSWORD, OnBnClickedPassword)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_LIST_USUARIOS, OnLbnSelchangeListUsuarios)
END_MESSAGE_MAP()

/******************************************************************************************/
BOOL CDlgGestionUsuarios::OnInitDialog()
{
	CDialog::OnInitDialog();

	/* Se carga la lista con los usuarios */
	CargarListaUsuarios();

	/* Se desabilita el botón Eliminar y contraseña hasta que se seleccione un elemento de la lista */
	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
	GetDlgItem(ID_PASSWORD)->EnableWindow(FALSE);

	return TRUE;  // devolver TRUE a menos que se establezca el foco en un control
}

/*****************************************************************************************/
// Controladores de mensajes de CDlgGestionUsuarios
/*****************************************************************************************/

void CDlgGestionUsuarios::OnBnClickedAgregar()
{
	CDlgCrearUsuario dlgCrearUsuario;
	dlgCrearUsuario.SetConexion(m_db);
	dlgCrearUsuario.DoModal();

	/* Se actualiza la lista de usuarios */
	CargarListaUsuarios();

	/* Se desabilita el botón Eliminar y contraseña hasta que se seleccione un elemento de la lista */
	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
	GetDlgItem(ID_PASSWORD)->EnableWindow(FALSE);
}

/*****************************************************************************************/
void CDlgGestionUsuarios::OnBnClickedEliminar()
{
	HRESULT hErr = S_OK;

	/* Se confirma que se quiera eliminar el usuario */
	CString strMsg;
	strMsg.Format(IDS_CONFIRMAR_ELIMINAR, m_strUsuario);

	if ( MessageBox(strMsg,"Minerva",MB_YESNO+ MB_ICONINFORMATION) == IDYES)
	{
		/* Se elimina el usuario en la tabla de Usuario */
		CUsuario rsUsuario(m_db);
		rsUsuario.m_USUARIO = m_strUsuario;
		hErr = rsUsuario.DeleteFromUser();

		if (hErr == S_OK)
			m_lstUsuarios.DeleteString(m_iIndex);

		/* Se desabilita el botón Eliminar y contraseña hasta que se seleccione un elemento de la lista */
		GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
		GetDlgItem(ID_PASSWORD)->EnableWindow(FALSE);
	}
}

/*****************************************************************************************/
void CDlgGestionUsuarios::OnBnClickedPassword()
{
	CDlgCambiarPassw dlgCambiarPassw;
	dlgCambiarPassw.SetConexion(m_db);
	dlgCambiarPassw.SetUsuario(m_strUsuario);
	dlgCambiarPassw.DoModal();

	/* Se Habilita el botón Eliminar y contraseña */
	GetDlgItem(ID_ELIMINAR)->EnableWindow(TRUE);
	GetDlgItem(ID_PASSWORD)->EnableWindow(TRUE);
}

/*****************************************************************************************/
void CDlgGestionUsuarios::OnLbnSelchangeListUsuarios()
{
	/* Obtenemos el perfil que ha sido seleccionado */
	m_iIndex = m_lstUsuarios.GetCurSel();
	m_lstUsuarios.GetText (m_iIndex, m_strUsuario);

	/* Si se ha seleccionado un usuario se habilitan los botones de eliminar y de contaseña */
	GetDlgItem(ID_ELIMINAR)->EnableWindow(TRUE);
	GetDlgItem(ID_PASSWORD)->EnableWindow(TRUE);
}

/*****************************************************************************************/
void CDlgGestionUsuarios::OnBnClickedCancel()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	OnCancel();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgGestionUsuarios::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgGestionUsuarios::CargarListaUsuarios()
{
	CString strUser;
	CUsuario rsUsuario(m_db);

	if (!rsUsuario.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	m_lstUsuarios.ResetContent();

	while (!rsUsuario.IsEOF())
	{	
		strUser = rsUsuario.m_USUARIO;
		strUser = strUser.Trim();
		m_lstUsuarios.AddString(strUser);
		rsUsuario.MoveNext();
	}

	rsUsuario.Close();
}




