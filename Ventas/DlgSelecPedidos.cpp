// DlgSelecPedidos.cpp: archivo de implementación
//
/**************************************************************************************/

#include "stdafx.h"
#include "DlgSelecPedidos.h"
#include ".\DlgSelecPedidos.h"
#include "Etiquetas.h"
#include "DlgOpcionesFac.h"

/**************************************************************************************/
// Cuadro de diálogo de CDlgSelecPedidos
/**************************************************************************************/
IMPLEMENT_DYNAMIC(CDlgSelecPedidos, CDialog)
CDlgSelecPedidos::CDlgSelecPedidos(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelecPedidos::IDD, pParent)
	, m_bTodos(FALSE)
{
}

/**************************************************************************************/
CDlgSelecPedidos::~CDlgSelecPedidos()
{
}

/**************************************************************************************/
void CDlgSelecPedidos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PEDIDOS, m_lstPedidos);
	DDX_Check(pDX, IDC_CHECK_TODOS, m_bTodos);
}

/**************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgSelecPedidos, CDialog)
	ON_BN_CLICKED(IDC_CHECK_TODOS, OnBnClickedCheckTodos)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// Controladores de mensajes de CDlgSelecPedidos
/**************************************************************************************/

/***********************************************************************************************/
BOOL CDlgSelecPedidos::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lstPedidos.SetExtendedStyle(m_lstPedidos.GetExtendedStyle()|LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES);

	// Se introducen los nombres de las columnas
	m_lstPedidos.InsertColumn(0,"", LVCFMT_LEFT, 22);			
	m_lstPedidos.InsertColumn(1,"Cliente", LVCFMT_LEFT, 230);
	m_lstPedidos.InsertColumn(2,"Obra", LVCFMT_LEFT, 230);
	m_lstPedidos.InsertColumn(3,"Contrato", LVCFMT_LEFT, 80);

	RellenaPedidos();

	return TRUE;
}

/******************************************************************************************/
void CDlgSelecPedidos::OnBnClickedCheckTodos()
{
	if (m_bTodos)
	{
		m_bTodos = FALSE;
		for (int i=0; i<m_lstPedidos.GetItemCount(); i++)
			m_lstPedidos.SetCheck(i, FALSE);
	}
	else
	{
		m_bTodos = TRUE;
		for (int i=0; i<m_lstPedidos.GetItemCount(); i++)
			m_lstPedidos.SetCheck(i, TRUE);
	}
}

/******************************************************************************************/
void CDlgSelecPedidos::OnBnClickedOk()
{
	// Se recuperan los pedidos seleccionados
	PedidosSeleccionados();

	// Se llama al diálogo para las opciones de facturación
	CDlgOpcionesFac dlgOpcionesFac;
	dlgOpcionesFac.SetConexion(m_db);
	dlgOpcionesFac.SetFacturacion(TRUE);
	dlgOpcionesFac.SetPedidos(&m_lPedidos);
	dlgOpcionesFac.DoModal();

	OnOK();
}

/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgSelecPedidos::SetConexion(CDatabase *db)
{
	m_db = db;
//	m_rsPedidos->m_pDatabase = m_db;
}

/******************************************************************************************/
void CDlgSelecPedidos::SetPedidos(CPedidos *rsPedidos)
{
	m_rsPedidos = rsPedidos;
	m_rsPedidos->m_pDatabase = m_db;
}

/******************************************************************************************/
void CDlgSelecPedidos::RellenaPedidos()
{
	CCuentas rsCuentas(m_db);
	CDirEnv rsDirEnv(m_db);
	CString strCodCliente, strCliente, strCodObra, strObra, strOldCodCliente, strOldCodObra;

	int iFila = 0;

	strOldCodCliente.Empty();
	strOldCodObra.Empty();

	while (!m_rsPedidos->IsEOF())
	{
		// Se busca la descripción del cliente si éste ha cambiado desde la vez anterior
		strCodCliente = m_rsPedidos->m_CUENTA.Trim();

		if (strCodCliente != strOldCodCliente)
		{	
			strCliente = strOldCodCliente = strCodCliente;

			rsCuentas.m_CUENTA.Empty();
			rsCuentas.m_strFilter = "CUENTA = '" +  strCliente + "'";
			if (!rsCuentas.Open(CRecordset::dynaset))
			{
				AfxMessageBox(IDC_ERROR_BD);
				return;
			}

			if (!rsCuentas.m_CUENTA.IsEmpty())
				strCliente += " - " + rsCuentas.m_NOMBRE.Trim();

			rsCuentas.Close();

		}

		// Se busca la descripción de la obra si ésta ha cambiado desde la vez anterior
		strCodObra = m_rsPedidos->m_DIRENV.Trim();

		if (strCodObra != strOldCodObra)
		{
			strObra = strOldCodObra = strCodObra;

			// Se busca la descripción del cliente
			rsDirEnv.m_DIRENV.Empty();
			rsDirEnv.m_strFilter = "DIRENV = '" + strObra + "' AND CLIENTE = '" + strCodCliente + "'";
			if (!rsDirEnv.Open(CRecordset::dynaset))
			{
				AfxMessageBox(IDC_ERROR_BD);
				return;
			}

			if (!rsDirEnv.m_DIRENV.IsEmpty())
				strObra += " - " + rsDirEnv.m_NOMDIRENV.Trim();

			rsDirEnv.Close();			
		}

		// Se rellena el listCtrl
		m_lstPedidos.InsertItem(iFila, _T(""));
		m_lstPedidos.SetItemText(iFila, 0, _T(""));
		m_lstPedidos.SetItemText(iFila, 1, strCliente);
		m_lstPedidos.SetItemText(iFila, 2, strObra);
		m_lstPedidos.SetItemText(iFila, 3, m_rsPedidos->m_NUMPEDIDO.Trim());
	
		iFila++;
		m_rsPedidos->MoveNext();
	}
}

/******************************************************************************************/
void CDlgSelecPedidos::PedidosSeleccionados()
{
	for(int i=0; i<m_lstPedidos.GetItemCount(); i++)
	{
		// Si está chequeado nos quedamos con el número de pedido
		if (m_lstPedidos.GetCheck(i))
		{
			m_rsPedidos->MoveFirst();
			m_rsPedidos->Move(i);
			m_lPedidos.AddTail(*m_rsPedidos);
		}
	}

	m_rsPedidos->Close();
}

