#pragma once

#include "resource.h"
#include "afxwin.h"
#include "Utilidades.h"
#include "afxcmn.h"

#define GESTCOMPRA        1
#define GESTALBARAN		  2

// Cuadro de diálogo de CDlgBuscaCompra

class CDlgBuscaCompra : public CDialog
{
	DECLARE_DYNAMIC(CDlgBuscaCompra)

public:
	CDlgBuscaCompra(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgBuscaCompra();
	virtual BOOL OnInitDialog();

	void SetConexion(CDatabase *db);
	void SetTipo(int iTipo);
	CString GetNumCompra();
	void BuscaDesCuenta();

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_BUSCACOMPRA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV
	DECLARE_MESSAGE_MAP()

public:
	CString m_strNumCompra;
	CString m_strCuenta;
	//CEdit m_cNumOferta;
	afx_msg void OnEnKillfocusNumCompra();
	afx_msg void OnBnClickedBtnCompra();

private: 
	CDatabase *m_db;
	int m_iTipo;
	CDialogBusqueda m_dlgBusqueda;

	BOOL BuscaNumCompra();
	BOOL BuscaNumAlbCompra();
public:
	afx_msg void OnBnClickedOk();
	CString m_strDesCuenta;
};
