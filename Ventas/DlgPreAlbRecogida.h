#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "BD.h"
#include "Utilidades.h"
#include "atltime.h"


// Cuadro de diálogo de CDlgPreAlbRecogida

class CDlgPreAlbRecogida : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreAlbRecogida)

public:
	CDlgPreAlbRecogida(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgPreAlbRecogida();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PRE_ALB_RECOGIDA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CPedidos m_rsPedido;
	CAlbaran m_rsAlbaran;
	CArtiVenta m_rsArtiVenta;
	int m_iNumArti;
	int m_iNumArtiPedido;
//	CList <BOOL, BOOL> m_lEnvioSoloLectura;
	CList <double, double> m_lOldRecojo;
	//CStringList m_lTipo;

	CDialogBusqueda m_dlgBusquedaClientes;
	CDialogBusqueda m_dlgBusquedaPedidosCli;
	CDialogBusqueda m_dlgBusquedaArticulos;

	BOOL BuscaCliente();
	BOOL BuscaPedido();
	void BuscaArticulosPedido();
	void BuscaAlbaranes();
	void BuscaDesAlmacen();
	void CambiaCantidadRecogida();

	void InsertaRegistroVacio();
	void BuscaArticulo(CString strCodArti);

	void LimpiaVentana();

	void GuardaAlbaran();
	void RellenaAlbaran();
	void RellenaArtiAlbaran(CArtiAlbaran *rsArtiAlbaran, int iFila);
	void RellenaAlmacen(CAlmacen *rsAlmacen, CInventario *rsInventario, CArtiAlbaran *rsArtiAlbaran, int iFila);
	CString GetTipoMov();


public:
	CString m_strCuenta;
	CString m_strNombre;
	CString m_strPedido;
	CString m_strObservaciones;
	CString m_strAlbaranes;

	//CListCtrl m_lstArticulos;
	CReportCtrl m_lstArticulos;
	afx_msg void OnEnKillfocusEditCuenta();
	afx_msg void OnBnClickedBtnCuenta();
	afx_msg void OnEnKillfocusPedido();
	afx_msg void OnBnClickedBtnPedido();
	//afx_msg void OnNMKillfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);
	afx_msg void OnBnClickedOk();
	CTime m_fechaFinAlq;
	CString m_strAlmacen;
	CString m_strNombreAlmacen;
	afx_msg void OnBnClickedBuscar();
	afx_msg void OnBnClickedEliminar();
	afx_msg void OnNMClickListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
};
