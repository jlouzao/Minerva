#pragma once
#include "afxwin.h"

#if !defined __INFORMES_H__
#define __INFORMES_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define IDD_DLG_INFORMES                50319

#define PATH	"Informes\\"

///Los tipos de reportes//////////
#define OFERTA  1
#define PEDIDO  2
#define ALBARAN 3
#define FACTURA 4
#define FACTURA_ORIGEN 5
#define COBRO  6
///Tipo de salida/////////////////
#define PANTALLA 0
#define IMPRESORA 1
//////////////////////////////////
#define FAC1 "Factura 1"
#define FACORIG1 "Factura origen 1"
#define OFE1 "Oferta 1"
#define PED1 "Pedido Simple"
#define PED2 "Pedido Valorado"
#define ALB1 "Albaran 1"
#define COBROS1 "Por Cliente"
//#define ALB1 "Albaran de Entrega"
//#define ALB2 "Albaran de Recogida"
//////////////////////////////////
#define FACRTP1 "Factura-"
#define FACORIGRTP1 "Factura-Origen-"
#define OFERTP1 "Oferta-"
#define PEDRTP1 "Pedido-Simple-"
#define PEDRTP2 "Pedido-Valorado-"
#define ALBRTP1 "Albaran-"
#define COBROSRTP1 "Cobros-Cliente-"
//#define ALBRTP1 "Albaran-Entrega-"
//#define ALBRTP2 "Albaran-Recogida-"
//////////////////////////////////
#include "resource.h"
//////////////////////////////////
struct DatosInforme
{
	CString strTexto;
	CString strRPT;
};
//////////////////////////////////
class  __declspec(dllexport) CDlgInformes : public CDialog
{
	DECLARE_DYNAMIC(CDlgInformes)

public:
	CDlgInformes(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgInformes();
	virtual BOOL OnInitDialog();
	void SetDatos(CDatabase *db, int iTipo);
	void SetFormula(CString strElemento1, CString strElemento2, CTime fecha1 = NULL, CTime fecha2 = NULL, CString strCuenta1 = "",
     CString strCuenta2 = "", CString strCentro1 = "", CString strCentro2 = "", CString strEstado1 = "", 
	 CString strEstado2 = "");

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedTipo1();//pulsado la opcion pantalla
	afx_msg void OnBnClickedTipo2();//pulsado la opcion impresora
	//afx_msg void OnSetFocus(CWnd* pOldWnd);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_INFORMES };
private:
	void CrearListaFactura();
	void CrearListaFacturaOrigen();
	void CrearListaPedido();
	void CrearListaAlbaran();
	void CrearListaOferta();
	void CrearListaCobros();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV
	
	DECLARE_MESSAGE_MAP()

public:
	int iSalida;//para saber por donde debo sacar el reporte(pantalla,archivo o impresora)
	int m_iTipo;//Tipo de informe que queremos
	CString m_strFormula;
	
	CDatabase *m_db;//el puntero a la base de datos
	CList  <DatosInforme, DatosInforme&> m_lInformes;//Lista para guardar los nombres de los RPT
	CListBox m_listReportes;
};
#endif //__INFORMES_H__
