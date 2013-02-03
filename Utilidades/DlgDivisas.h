#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgIdiomas

class __declspec(dllexport) CDlgDivisas : public CDialog
{
	DECLARE_DYNAMIC(CDlgDivisas)

public:
	CDlgDivisas(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDivisas();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetDivisas(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarDivisas();
	BOOL ChequeaNumeros(CString);
	void ChequeaPosicion();
	void Limpiar();
	void RellenaCampos();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_DIVISAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_ctrlCodigo;
	CString m_strCodigo;
	CString m_strDescripcion;

	CString strPrimero;
	CString strUltimo;

	int iEstado;
	BOOL bUpdate;

	CDivisas m_rsDivisas;
	CDialogBusqueda m_dlgBusqueda;
	CDatabase* m_db;

	/************ Botones de navegación ********/
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedBuscar();
	CString m_strCambio;
	afx_msg void OnEnKillfocusCambio();
};
