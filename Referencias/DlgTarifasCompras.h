#pragma once

#include "Resource.h"
#include "afxwin.h"
#include "BD.h"

// Cuadro de diálogo de CDlgTarifasCompras

class CDlgTarifasCompras : public CDialog
{
	DECLARE_DYNAMIC(CDlgTarifasCompras)

public:
	CDlgTarifasCompras(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgTarifasCompras();
	virtual BOOL OnInitDialog();

	void SetArticulo(CArticulo *articulo);
	void SetConexion(CDatabase *basedatos);
	void SetReferencia(CString);
	void RellenaCampos();//CString CodReferencia); //rellena los campos con los datos
	void setNuevo(BOOL);
	BOOL ChequeaNumeros(CString);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_TARIFAS_COMPRAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private:
	CArticulo *m_rsArticulo;
	CDatabase *m_db;

public:
	CString m_strDescuento;
	CString m_strPrecio;
	CString m_strCodReferencia;
	BOOL bArtiNuevo;
	afx_msg void OnBnClickedAceptar();
	afx_msg void OnBnClickedCancelar();
	afx_msg void OnEnKillfocusPrecioCoste();
	afx_msg void OnEnKillfocusDescuento();

	CEdit m_ctrlPrecio;
	CEdit m_ctrlDescuento;
};
