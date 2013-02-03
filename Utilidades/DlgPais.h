#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgPais : public CDialog
{
	DECLARE_DYNAMIC(CDlgPais)

public:
	CDlgPais(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgPais();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetPais(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarPais();
	void Limpiar();
	void ChequeaPosicion();
	void RellenaCampos();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PAIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCodigo;
	CString m_strDescripcion;

	CString strPrimero;
	CString strUltimo;

	int iEstado;
	BOOL bUpdate;

	CPais m_rsPais;
	CDialogBusqueda m_dlgBusqueda;
	CDatabase* m_db;

	/************ Botones de navegación ********
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	/*******************************************/
	
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedBuscar();
};
