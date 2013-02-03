// DlgCierreObra.cpp: archivo de implementación
//
/******************************************************************************************/

#include "stdafx.h"
#include "Ventas.h"
#include "DlgCierreObra.h"
#include "BD.h"


/******************************************************************************************/
// Cuadro de diálogo de CDlgCierreObra
/******************************************************************************************/

IMPLEMENT_DYNAMIC(CDlgCierreObra, CDialog)
CDlgCierreObra::CDlgCierreObra(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCierreObra::IDD, pParent)
{
	m_bConsulta = FALSE;
}

/******************************************************************************************/
CDlgCierreObra::~CDlgCierreObra()
{
}

/******************************************************************************************/
void CDlgCierreObra::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ARTICULOS, m_lstArticulos);
}

/******************************************************************************************/
BEGIN_MESSAGE_MAP(CDlgCierreObra, CDialog)
END_MESSAGE_MAP()


// Controladores de mensajes de CDlgCierreObra
/******************************************************************************************/

/***********************************************************************************************/
BOOL CDlgCierreObra::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Añadiendo la lista de imágenes se consigue hacer cada casilla más grande
	CImageList m_ImageList;
	m_ImageList.Create(1, 16, ILC_COLOR,1,1); 
	//m_lstArticulos.SetImageList(&m_ImageList, LVSIL_NORMAL); 
	m_lstArticulos.SetImageList(&m_ImageList); 

	//m_lstArticulos.SetExtendedStyle(m_lstArticulos.GetExtendedStyle()|LVS_EX_GRIDLINES);
	m_lstArticulos.SetGridLines();

	// Se introducen los nombres de las columnas
	m_lstArticulos.InsertColumn(0,"Nº Pedido", LVCFMT_LEFT, 70);			
	m_lstArticulos.InsertColumn(1,"Artículo", LVCFMT_LEFT, 70);
	m_lstArticulos.InsertColumn(2,"Descripción", LVCFMT_LEFT, 170);
	m_lstArticulos.InsertColumn(3,"Pedido", LVCFMT_LEFT, 70);
	m_lstArticulos.InsertColumn(4,"Enviado", LVCFMT_LEFT, 70);
	m_lstArticulos.InsertColumn(5,"Recogido", LVCFMT_LEFT, 70);
	m_lstArticulos.InsertColumn(6,"Situación", LVCFMT_LEFT, 70);

	// Se muestra el cierre de obra
	CierreObra();

	return TRUE;
}



/******************************************************************************************/
/** FUNCIONES                                                                             */
/******************************************************************************************/
void CDlgCierreObra::SetConexion(CDatabase *db)
{
	m_db = db;
}

/******************************************************************************************/
void CDlgCierreObra::SetConsulta(BOOL bConsulta)
{
	m_bConsulta = bConsulta;
}

/******************************************************************************************/
void CDlgCierreObra::SetDatos(CString strCliente, CString strObra)
{
	m_strCliente = strCliente;
	m_strObra = strObra;
}

/******************************************************************************************/
void CDlgCierreObra::CierreObra()
{
	CPedidos rsPedidos(m_db);
	CArtiVenta rsArtiVenta(m_db);
	CDirEnv rsDirEnv(m_db);
	BOOL bHayArticulo = FALSE;
	
	// Se buscan todos los pedidos de esa obra y ese cliente
	rsPedidos.m_strFilter = "CUENTA = '" + m_strCliente + "' AND DIRENV = '" + m_strObra + "'";
	if (!rsPedidos.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return;
	}

	int iFila = -1;
	while (!rsPedidos.IsEOF())
	{
		// Si estamos cerrando obra (no consultando) y está marcado como revisado
		// no se hace nada
		if (m_bConsulta || !rsPedidos.m_REVISADO)
		{
			rsPedidos.m_NUMPEDIDO = rsPedidos.m_NUMPEDIDO.Trim();

			bHayArticulo = FALSE;
			iFila++;
			m_lstArticulos.InsertItem(iFila, _T(""));
			m_lstArticulos.SetItemText(iFila, 0, rsPedidos.m_NUMPEDIDO);
			m_lstArticulos.SetItemBkColor(iFila, 0, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iFila, 1, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iFila, 2, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iFila, 3, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iFila, 4, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iFila, 5, RGB(183, 183, 183), TRUE);
			m_lstArticulos.SetItemBkColor(iFila, 6, RGB(183, 183, 183), TRUE);

			rsArtiVenta.m_strFilter = "NUMPEDIDO = '" + rsPedidos.m_NUMPEDIDO.Trim() + "'";
			if (!rsArtiVenta.Open(CRecordset::dynaset))
			{
				AfxMessageBox(IDC_ERROR_BD);
				return;
			}
			while (!rsArtiVenta.IsEOF())
			{
				// Si es un alquiler y los enviados son distintos a los recogidos es que se ha producido alguna
				// anomalía
				if (rsArtiVenta.m_ALQUILER == "S" && rsArtiVenta.m_ENVIADOS != rsArtiVenta.m_RECOGIDOS)
				{
					bHayArticulo = TRUE;
					iFila++;
					m_lstArticulos.InsertItem(iFila, _T(""));
					m_lstArticulos.SetItemText(iFila, 1, rsArtiVenta.m_ARTI.Trim());
					m_lstArticulos.SetItemText(iFila, 2, rsArtiVenta.m_DESARTI.Trim());
					CString strPedidos;
					strPedidos.Format("%g", rsArtiVenta.m_CANTI);
					m_lstArticulos.SetItemText(iFila, 3, strPedidos);
					CString strEnviados;
					strEnviados.Format("%g", rsArtiVenta.m_ENVIADOS);
					m_lstArticulos.SetItemText(iFila, 4, strEnviados);
					CString strRecogidos;
					strRecogidos.Format("%g", rsArtiVenta.m_RECOGIDOS);
					m_lstArticulos.SetItemText(iFila, 5, strRecogidos);
					CString strDiferencia;
					strDiferencia.Format("%g", rsArtiVenta.m_RECOGIDOS - rsArtiVenta.m_ENVIADOS);
					if (rsArtiVenta.m_RECOGIDOS - rsArtiVenta.m_ENVIADOS > 0)
						strDiferencia = "+" + strDiferencia;
					m_lstArticulos.SetItemText(iFila, 6, strDiferencia);
				}

				rsArtiVenta.MoveNext();
			}

			rsArtiVenta.Close();

			// Si no hay artículo se indica que todo ha ido correctamente
			if (!bHayArticulo)
			{
				iFila++;
				m_lstArticulos.InsertItem(iFila, _T(""));
				m_lstArticulos.SetItemText(iFila, 1, "--");
				m_lstArticulos.SetItemText(iFila, 2, "--");
				m_lstArticulos.SetItemText(iFila, 3, "--");
				m_lstArticulos.SetItemText(iFila, 4, "--");
				m_lstArticulos.SetItemText(iFila, 5, "--");
				m_lstArticulos.SetItemText(iFila, 6, "Correcto");
			}

			// Si no es consulta se marca el pedido como revisado
			if (!m_bConsulta)
				HRESULT hErr = rsPedidos.MarcaRevisado();
		}

		rsPedidos.MoveNext();
	}

	rsPedidos.Close();

	// Se pone el campo de Obra cerrada a 'S'
	//rsDirEnv.m_DIRENV = m_strObra;
	//rsDirEnv.m_OBRACERRA = 'S';
	//HRESULT hErr = rsDirEnv.UpdateCierreObra();
}