#pragma once

#include "resource.h"
#include "BD.h"
#include "Utilidades.h"
#include "afxcmn.h"
#include "atltime.h"

// Cuadro de diálogo de CDlgAPreAlbDespieceRecogida

class CDlgPreAlbDespieceRecogida : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreAlbDespieceRecogida)

public:
	CDlgPreAlbDespieceRecogida(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgPreAlbDespieceRecogida();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PRE_ALB_DESPIECE_RECOGIDA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

private:
	CDatabase *m_db;
	CPedidos m_rsPedido;
	CAlbaran m_rsAlbaran;
	int m_iNumArti;
	CList <int, int> m_lOldRecojo;
	CStringList m_strTipo;
	CStringList m_strTipoAlquiler;
	BOOL m_bFocusListCtrl;
	BOOL m_bObser;
	BOOL m_bTabObser;

	CDialogBusqueda m_dlgBusquedaClientes;
	CDialogBusqueda m_dlgBusquedaPedidosCli;
	CDialogBusqueda m_dlgBusquedaArticulos;
	CDialogBusqueda m_dlgBusquedaAlbaranesPedidoCli;

	BOOL PreTranslateMessage(MSG* pMsg);

	void InsertaRegistroVacio();

	BOOL BuscaCliente();
	BOOL BuscaPedido();
	BOOL BuscaAlbaran();
	void BuscaArticulosAlbaran();
	void BuscaArticulo(CString strCodArti);
	void BuscaDesAlmacen();

	void GuardaAlbaran();
	void RellenaAlbaran();
	void RellenaArtiAlbaran(CArtiAlbaran *rsArtiAlbaran, int iFila);
	void RellenaAlmacen(CAlmacen *rsAlmacen, CInventario *rsInventario, CArtiAlbaran *rsArtiAlbaran, int iFila);
	CString GetTipoMov();

	void LimpiaVentana(BOOL bLimpiaCuenta = TRUE);	
	void CambiaCantidad();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCuenta;
	CString m_strNombre;
	CString m_strPedido;
	//CListCtrl m_lstArticulos;
	CReportCtrl m_lstArticulos;
	CString m_strObservaciones;
	CTime m_timeFechaFin;
	afx_msg void OnEnKillfocusEditCuenta();
	afx_msg void OnBnClickedBtnCuenta();
	afx_msg void OnEnKillfocusPedido();
	afx_msg void OnBnClickedBtnPedido();
	CString m_strAlbaran;
	afx_msg void OnBnClickedBtnAlbaran();
	afx_msg void OnEnKillfocusAlbaran();
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);
	afx_msg void OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBuscar();
	afx_msg void OnBnClickedEliminar();
	afx_msg void OnNMClickListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	CString m_strAlmacen;
	CString m_strNombreAlmacen;
	afx_msg void OnEnSetfocusObserAlbaran();
};
