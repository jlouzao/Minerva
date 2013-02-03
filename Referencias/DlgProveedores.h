#pragma once

#include "resource.h"
#include "afxcmn.h"
#include "BD.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgProveedores

class CDlgProveedores : public CDialog
{
	DECLARE_DYNAMIC(CDlgProveedores)

public:
	CDlgProveedores(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgProveedores();
	virtual BOOL OnInitDialog();

	void SetConexion(CDatabase *db);
	void SetCodArticulo(CString strCodArti);
	void SetDesArticulo(CString strDesArti);
	void SetProveedores(CList <CProveArti, CProveArti&> *pProve);
	void GetProveedores(CList <CProveArti, CProveArti&> *pProve);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PROVEEDORES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

private:

	CDatabase *m_db;
	CString m_strCodArti;
	CString m_strDesArti;
	CReportCtrl m_lstProve;
	int m_iNumProve;	
	CList <CProveArti, CProveArti&> *m_pProve;
	CString m_strOldTarifa;
	CString m_strOldDescuento;

	CDialogBusqueda m_dlgBusquedaProve;

	void InsertaRegistroVacio();
	void BuscaProve(CString strCodProve);
	BOOL EsNum(CString strNumero);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedEliminar();
	afx_msg void OnNMClickListProve(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBuscar();
	afx_msg void OnNMSetfocusListProve(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnNMKillfocusListProve(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);
	afx_msg void OnBnClickedOk();
};
