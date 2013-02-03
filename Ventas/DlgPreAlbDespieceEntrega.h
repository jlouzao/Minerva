#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "ReportCtrlEx.h"
#include "BD.h"
#include "atltime.h"

// Cuadro de diálogo de CDlgPreAlbDespieceEntrega

class CDlgPreAlbDespieceEntrega : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreAlbDespieceEntrega)

public:
	CDlgPreAlbDespieceEntrega(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgPreAlbDespieceEntrega();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PRE_ALB_DESPIECE_ENTREGA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CPedidos m_rsPedido;
	CAlbaran m_rsAlbaran;
	int m_iNumArti;
	CList <int, int> m_lOldCantidad;
	CStringList m_strTipo;
	CStringList m_strTipoAlquiler;
	BOOL m_bFocusListCtrl;
	BOOL m_bObser;
	BOOL m_bTabObser;

	CDialogBusqueda m_dlgBusquedaClientes;
	CDialogBusqueda m_dlgBusquedaPedidosCli;
	CDialogBusqueda m_dlgBusquedaArticulos;

	BOOL PreTranslateMessage(MSG* pMsg);

	void InsertaRegistroVacio();

	BOOL BuscaCliente();
	BOOL BuscaPedido();
	void BuscaArticulo(CString strCodArti);
	void BuscaDesAlmacen();

	void GuardaAlbaran();
	void RellenaAlbaran();
	void RellenaArtiAlbaran(CArtiAlbaran *rsArtiAlbaran, int iFila);
	void RellenaAlmacen(CAlmacen *rsAlmacen, CInventario *rsInventario, CArtiAlbaran *rsArtiAlbaran, int iFila);
	CString GetTipoMov();

	void LimpiaVentana();	
	void CambiaCantidad();

public:
	CReportCtrlEx m_lstArticulos;
	CString m_strCuenta;
	CString m_strNombre;
	CString m_strPedido;
	double m_dTotalPeso;
	CTime m_timeFechaIni;
	CString m_strObservaciones;
	afx_msg void OnEnKillfocusEditCuenta();
	afx_msg void OnBnClickedBtnCuenta();
	afx_msg void OnEnKillfocusPedido();
	afx_msg void OnBnClickedBtnPedido();
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);
	afx_msg void OnBnClickedBuscar();
	afx_msg void OnBnClickedEliminar();
	afx_msg void OnNMClickListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_strTotalPeso;
	afx_msg void OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	CString m_strAlmacen;
	CString m_strNombreAlmacen;
	afx_msg void OnEnSetfocusObserAlbaran();
};
