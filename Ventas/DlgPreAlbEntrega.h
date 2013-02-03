#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "Utilidades.h"
#include "BD.h"
#include "afxwin.h"
#include "atltime.h"


// Cuadro de diálogo de CDlgPreAlbEntrega

class CDlgPreAlbEntrega : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreAlbEntrega)

public:
	CDlgPreAlbEntrega(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgPreAlbEntrega();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PRE_ALB_ENTREGA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

private:
	CDatabase *m_db;
	CPedidos m_rsPedido;
	CAlbaran m_rsAlbaran;
	CArtiVenta m_rsArtiVenta;
	CList <BOOL, BOOL> m_lEnvioSoloLectura;
	CList <double, double> m_lOldEnvio;
	CStringList m_lTipo;

	CDialogBusqueda m_dlgBusquedaClientes;
	CDialogBusqueda m_dlgBusquedaPedidosCli;

	BOOL BuscaCliente();
	BOOL BuscaPedido();
	void BuscaArticulosPedido();
	void BuscaAlbaranes();
	void BuscaDesAlmacen();
	void CambiaCantidadEnvio();

	void GuardaAlbaran();
	void RellenaAlbaran();
	void RellenaArtiAlbaran(CArtiAlbaran *rsArtiAlbaran, int iFila);
	void RellenaAlmacen(CAlmacen *rsAlmacen, CInventario *rsInventario, CArtiAlbaran *rsArtiAlbaran, int iFila);
	CString GetTipoMov();

	void LimpiaVentana();

	DECLARE_MESSAGE_MAP()
public:
	//CListCtrl m_lstArticulos;
	CReportCtrl m_lstArticulos;
	CString m_strCuenta;
	CString m_strNombre;
	afx_msg void OnEnKillfocusEditCuenta();
	afx_msg void OnBnClickedBtnCuenta();
	afx_msg void OnEnKillfocusNumpedido();
	afx_msg void OnBnClickedBtnPedido();
	CString m_strPedido;
	//CString m_strTotalPeso;
	afx_msg void OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);
	double m_dTotalPeso;
	afx_msg void OnBnClickedOk();
	CString m_strAlbaranes;
	CTime m_timeFechaIni;
	CString m_strObservaciones;
	CString m_strAlmacen;
	CString m_strNombreAlmacen;
};
