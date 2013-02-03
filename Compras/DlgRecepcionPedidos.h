#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "Utilidades.h"
#include "BD.h"
#include "afxwin.h"

// Cuadro de diálogo de CDlgRecepcionPedidos

class CDlgRecepcionPedidos : public CDialog
{
	DECLARE_DYNAMIC(CDlgRecepcionPedidos)

public:
	CDlgRecepcionPedidos(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgRecepcionPedidos();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_RECEPCION_PEDIDOS };

private:
	CDatabase *m_db;
	CCompras m_rsCompras;
	CArtiCompra m_rsArtiCompra;
	//CList <BOOL, BOOL> m_lEnvioSoloLectura;
	BOOL bSoloLectura;
	CList <double, double> m_lOldEnvio;

	CDialogBusqueda m_dlgBusquedaProveedores;
	CDialogBusqueda m_dlgBusquedaPedidos;

	BOOL BuscaCliente();
	BOOL BuscaPedido();
	void BuscaArticulosPedido();
	void BuscaAlbaranes();
	void CambiaCantidadRecibido();

	void GuardaAlbaran();
	void RellenaAlbaran(CAlbCompra *rsAlbaran);
	void RellenaArtiAlbaran(CArtiAlbCompra *rsArtiAlbCompra, int iFila, CString strNAlbCom);
	void RellenaAlmacen(CAlmacen *rsAlmacen, CInventario *rsInventario, int iFila, CString strNAlbCom);
	CString GetTipoMov();

	void LimpiaVentana();

	DECLARE_MESSAGE_MAP()

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

public:
	CString m_strCuenta;
	CString m_strPedido;
	CString m_strObservaciones;
	CString m_strNombre;
	CString m_strAlbaranes;

	CReportCtrl m_lstArticulos;
	afx_msg void OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);

	afx_msg void OnBnClickedBtnCuenta();
	afx_msg void OnBnClickedBtnPedido();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusCuenta();
	afx_msg void OnEnKillfocusPedido();
	afx_msg void OnLvnItemchangedListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
};
