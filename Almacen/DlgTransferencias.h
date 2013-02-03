#pragma once

#include "resource.h"
#include "utilidades.h"
#include "afxwin.h"

// Cuadro de diálogo de CDlgTransferencias

class CDlgTransferencias : public CDialog
{
	DECLARE_DYNAMIC(CDlgTransferencias)

public:
	CDlgTransferencias(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgTransferencias();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_TRANFERENCIAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

private:
	CDatabase *m_db;
	CString m_strCodArti;
	CString m_strTransferenciaOld;
	int m_iNumArti;
	BOOL m_bFocusListCtrl;

	CDialogBusqueda m_dlgBusquedaArticulo;
	CDialogBusqueda m_dlgBusquedaAlmacen;
	CDialogBusqueda m_dlgBusquedaDocumento;

	void BuscaArticulo();
	BOOL BuscaAlmacen(BOOL bOrigen);
	BOOL BuscaDocumento();
	BOOL CompruebaAlmacenOrig();
	BOOL CompruebaAlmacenDest();
	BOOL CompruebaDocumento();
	BOOL CompruebaObservaciones();
	void InsertaRegistroVacio();
	void LimpiaVentana(BOOL bAlmacen);
	void IniDocumento();
	void ComprobarTransferencia();

	DECLARE_MESSAGE_MAP()

public:
	CTime m_timeFecha;
	CString m_strCodAlmacenOrig;
	CString m_strDesAlmacenOrig;
	CString m_strCodAlmacenDest;
	CString m_strDesAlmacenDest;
	CString m_strCodDoc;
	CString m_strDesDoc;
	CString m_strObservaciones;
	CReportCtrl m_lstArticulos;
	afx_msg void OnBnClickedBuscar();
	afx_msg void OnNMSetfocusLstarticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEliminar();
	afx_msg void OnNMClickLstarticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnAlmacen();
	afx_msg void OnBnClickedBtnDocumento();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusEditAlmacen();
	afx_msg void OnEnKillfocusEditDocumento();
	afx_msg void OnEnKillfocusEditObservaciones();
	afx_msg void OnLvnInsertitemLstarticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);

	afx_msg void OnBnClickedBtnAlmacen2();
	afx_msg void OnEnKillfocusEditAlmacen2();
	CEdit m_ctrlAlmacenOrig;
	CEdit m_ctrlObservaciones;
};
