#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "Utilidades.h"
#include "BD.h"
#include "afxwin.h"
#include "atltime.h"
// Cuadro de diálogo de CDlgRecepcionFactura

class CDlgRecepcionFactura : public CDialog
{
	DECLARE_DYNAMIC(CDlgRecepcionFactura)

public:
	CDlgRecepcionFactura(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgRecepcionFactura();

		virtual BOOL OnInitDialog();
		void InsertaRegistroVacio();
		void BuscaArticulos();
		BOOL PreTranslateMessage(MSG* pMsg);
		void SetConexion(CDatabase *db);
		BOOL BuscaPedido();
		BOOL BuscaCliente();
		BOOL CompruebaNumero(CString);
		void LimpiaVentana();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_RECEPCION_FACTURA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CDatabase *m_db;
	CReportCtrl m_lstArticulos;
	int m_iNumArti;
	BOOL m_bReadOnly;
	BOOL m_bFocusListCtrl;
	BOOL m_bFecha;
	BOOL m_bTabFecha;
	CString m_strPedido;
	CList <double, double> m_lOldEnvio;
	CCompras m_rsCompras;
	CDialogBusqueda m_dlgBusquedaPedidos;

	afx_msg void OnNMSetfocusRecepcion(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);
	afx_msg void OnBnClickedPedido();
	CString m_strProveedor;
	CString m_strDesProveedor;
	CString m_strFactura;
	CTime m_TimeRecepcion;
	CTime m_TimeFactura;
	CString m_strIVA;
	CString m_strDesGen;
	CString m_strPP;
	CString m_strTotalBruto;
	CString m_strTotalNeto;
	double m_dTotalBruto;
	double m_dTotalNeto;
	afx_msg void OnEnKillfocusIva();
	afx_msg void OnEnKillfocusPedido();
};
