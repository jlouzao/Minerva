#pragma once

#include "Resource.h"
#include "afxwin.h"
#include "atltime.h"
#include "BD.h"
#include "utilidades.h"


// Cuadro de diálogo de CDlgCliente

class CDlgCliente : public CDialog
{
	DECLARE_DYNAMIC(CDlgCliente)

public:
	CDlgCliente(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgCliente();

	virtual BOOL OnInitDialog();
	void SetCodigo(CString strAux);//trae el codigo desde donde le llamen
	void SetConexion(CDatabase *db);
	void EsNuevo(BOOL);

	BOOL ChequeaNumeros(CString);

	BOOL EncuentraPais(CString);
	BOOL EncuentraZona(CString);
	BOOL EncuentraIdioma(CString);
	void EncuentraMatricula(CString);
	BOOL EncuentraTransportista(CString);
	BOOL EncuentraCuenta(CString, bool);
// Datos del cuadro de diálogo
	enum { IDD = IDD_CLIENTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:

	CDatabase *m_db;
	CClientes m_rsCliente;

	BOOL m_bUpdate;
	BOOL m_bCreado;

	CDialogBusqueda m_dlgBusquedaDirEnv;
	CDialogBusqueda m_dlgBusquedaPais;
	CDialogBusqueda m_dlgBusquedaIdioma;
	CDialogBusqueda m_dlgBusquedaZona;
	CDialogBusqueda m_dlgBusquedaCuenta;
	CDialogBusqueda m_dlgBusquedaTransportista;

	CString m_strCodigo;
	CString m_strNombreC;
	CString m_strNombre;
	CString m_strCIF;
	CString m_strDireccion;
	CString m_strNumero;
	CString m_strCP;
	CString m_strSG;
	CString m_strPoblacion;
	CString m_strProvincia;
	CString m_strPais;
	CString m_strDesPais;
	CString m_strTelefono;
	CString m_strTelefono2;
	CString m_strFax;
	CString m_strEmail;
	int m_iDetaMayo;
	CString m_strIdentificador;
	int m_iTipo;
	CString m_strContacto;
	CString m_strIdioma;
	CString m_strDesIdioma;
	CString m_strDesZona;
	CString m_strZona;
	CString m_strObservaciones;
	CTime m_CTimeAlta;
	CTime m_CTimeBaja;
	CString m_strRepresentante;
	CString m_strDesRepresentante;
	CString m_strComision1;
	CString m_strSubRepresentante;
	CString m_strDesSubRepresentante;
	CString m_strComision2;
	CString m_strTransportista;
	CString m_strDesTransportista;
	CString m_strTelefonoTrans;
	CString m_strMatricula;
	CString m_strDNI;
	
	afx_msg void OnBnClickedBotonPais();
	afx_msg void OnBnClickedBotonIdioma();
	afx_msg void OnBnClickedBotonZona();
	afx_msg void OnBnClickedBotonRepresentante();
	afx_msg void OnBnClickedBotonSubrepresentante();
	afx_msg void OnBnClickedBotonTransportista();
	afx_msg void OnBnClickedBotonCobro();
	afx_msg void OnBnClickedFacturacion();

	afx_msg void OnEnKillfocusPais();
	afx_msg void OnEnKillfocusIdioma();
	afx_msg void OnEnKillfocusZona();
	afx_msg void OnEnKillfocusRepresentante();
	afx_msg void OnEnKillfocusSubrepresentante();
	afx_msg void OnEnKillfocusTransportista();

	CEdit m_ctrlPais;
	CEdit m_ctrlIdioma;
	CEdit m_ctrlZona;
	CEdit m_ctrlRepresentante;
	CEdit m_ctrlSubRepresentante;
	CEdit m_ctrlTransportista;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusComision1();
	afx_msg void OnEnKillfocusComision2();
	CEdit m_ctrlComision1;
	CEdit m_ctrlComision2;
	afx_msg void OnBnClickedDireccionEnvio();
	afx_msg void OnBnClickedCancel();
};
