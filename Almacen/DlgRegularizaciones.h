#pragma once

#include "resource.h"
#include "atltime.h"
#include "afxcmn.h"
#include "Utilidades.h"
#include "afxwin.h"

// Cuadro de diálogo de CDlgRegularizaciones

class CDlgRegularizaciones : public CDialog
{
	DECLARE_DYNAMIC(CDlgRegularizaciones)

public:
	CDlgRegularizaciones(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgRegularizaciones();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_REGULARIZACIONES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

private:
	CDatabase *m_db;
	CString m_strCodArti;
	CString m_strVariacionOld;
	int m_iNumArti;
	BOOL m_bFocusListCtrl;
	
	CDialogBusqueda m_dlgBusquedaArticulo;
	CDialogBusqueda m_dlgBusquedaAlmacen;
	CDialogBusqueda m_dlgBusquedaDocumento;

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void BuscaArticulo();
	BOOL BuscaAlmacen();
	BOOL BuscaDocumento();
	BOOL CompruebaAlmacen();
	BOOL CompruebaDocumento();
	BOOL CompruebaObservaciones();
	void InsertaRegistroVacio();
	void LimpiaVentana(BOOL bAlmacen);
	void IniDocumento();
	void ActualizaVariacion();

	DECLARE_MESSAGE_MAP()

public:
	CTime m_timeFecha;
	CString m_strCodAlmacen;
	CString m_strDesAlmacen;
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
	afx_msg void OnLvnItemchangedLstarticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);
	CEdit m_ctrlAlmacen;
	CEdit m_ctrlObservaciones;
};
