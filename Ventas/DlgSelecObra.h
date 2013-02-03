#pragma once

#include "resource.h"
#include "utilidades.h"

// Cuadro de diálogo de CDlgSelecObra

class CDlgSelecObra : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelecObra)

public:
	CDlgSelecObra(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgSelecObra();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetTipo(int iTipo);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_OBRA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	int m_iTipo;

	CDialogBusqueda m_dlgBusquedaClientes;
	CDialogBusqueda m_dlgBusquedaObras;

	BOOL BuscaCliente();
	BOOL BuscaObra();

	void LimpiaVentana();

public:
	CString m_strCuenta;
	CString m_strNombre;
	CString m_strObra;
	CString m_strNomObra;
	afx_msg void OnEnKillfocusEditCuenta();
	afx_msg void OnBnClickedBtnCuenta();
	afx_msg void OnEnKillfocusEditObra();
	afx_msg void OnBnClickedBtnObra();
	afx_msg void OnBnClickedOk();
};
