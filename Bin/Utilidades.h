#pragma once

// CEditReport

class CEditReport : public CEdit
{
	DECLARE_DYNAMIC(CEditReport)

public:
	CEditReport();
	virtual ~CEditReport();

protected:

	//{{AFX_MSG(CReportCtrl)
	afx_msg void OnEnKillfocus();
	afx_msg void OnEnSetfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


///////////////////////////////////////////////////////////////////////////////
// ReportCtrl.h
//
// CReportCtrl, a CListCtrl derived class that is specialized on "Report View"
// style. 
//
// Features:
//
// 1, Item sorting by clicking on column header.
// 2, Sub-item text edit.
// 3, Item repositioning.
// 4, Customizing checkbox styles, including "single" and "disabled".
// 5, Sending a message to parent window when user clicks on a checkbox.
// 6, Convenient item insertion, deletion, moving, and sub-item text changing.
// 7, Sub-item images and color
// 8, And much more... 
//
// This code may be used in compiled form in any way you desire. This file may be
// redistributed unmodified by any means PROVIDING it is not sold for profit without
// the authors written consent, and providing that this notice and the authors name 
// is included. If the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file .
//
// This file is provided "as is" with no expressed or implied warranty.
//
// Written by Bin Liu (abinn32@yahoo.com)
//
// History
//
// Nov. 26, 2003 - Initial release.
// Dec. 03, 2003 - Fixed a bug in "EndEdit" where item text were not preperly committed.
//                 Completed the implementation of the "Sort-Separator" feature.
// Jan. 01, 2004 - Fixed a bug in "SetItemData".
//               - Added message "WM_EDIT_COMMITTED" which is sent to the parent window
//                 when an item text editing is committed.
//               - Fixed a bug in "SetItemText"(double type).
//               - Fixed a bug where item sorting does not work properly when there
//                 are multiple CReportCtrl objects on same window.
//
///////////////////////////////////////////////////////////////////////////////

#include "Utilidades.h"

#ifndef __REPORTCTRL_H__
#define __REPORTCTRL_H__

// Sent to parent window when user clicked on the checkbox of an item:
// wParam: The item index in the list ctrl
// lParam: The mouse event type(WM_LBUTTONDOWN, WM_RBUTTONDOWN, etc) which generated this event. 
// Note: This message is not sent when the checkbox states were altered programmatically
//       by calling "SetItem", it is only sent when the user "physically" clicked the
//       checkbox using mouse or joystick etc.
#define WM_ON_CHKBOX	(WM_APP + 10000)

// Sent to parent window when a column of items were sorted
// wParam: The column index
// lParam: The sort method, either 0(descending) or 1(ascending)
#define WM_ITEM_SORTED	(WM_APP + 10001)

// Sent to parent window when an item text editing was committed
// wParam: The item index
// lParam: The column index
#define WM_EDIT_COMMITTED	(WM_APP + 10002)

// Checkbox styles.
#define RC_CHKBOX_NONE			0 // No checkbox displayed
#define	RC_CHKBOX_NORMAL		1 // Normal, multiple check allowed
#define	RC_CHKBOX_SINGLE		2 // Single check only
#define	RC_CHKBOX_DISABLED		3 // Disabled, cannot be checked/unchecked by user input,
								  // but can be by your code.

// Item state flags for selection, deletion, etc.
// Multiple flags can be combined together using the bit-or operator.
// Note: If RC_ITEM_ALL is set, all other flags are ignored
#define RC_ITEM_NONE		0x0000 // Void, indicates invalid items only
#define	RC_ITEM_ALL			0x0001 // All items regardless of states
#define	RC_ITEM_SELECTED	0x0002 // Selected items
#define	RC_ITEM_UNSELECTED	0x0004 // Unselected items
#define	RC_ITEM_CHECKED		0x0008 // Checked items
#define	RC_ITEM_UNCHECKED	0x0010 // Unchecked items
#define	RC_ITEM_FOCUSED		0x0020 // Focused item
#define	RC_ITEM_UNFOCUSED	0x0040 // Unfocused items

// Item inverting types
#define RC_INVERT_SELECTION	0 // Invert item selection
#define RC_INVERT_CHECKMARK	1 // Invert item check mark

// Removes any custom color from item text and item backgroun
#define COLOR_INVALID	0xffffffff

// -------------------------------------
// -- Definition of LS_item structure --
// -------------------------------------
// This structure allow this derived CListCtrl to store for any items/subitems his own style (bold,color,etc..)
// All styles (item & subitems) for an item are accessible with the helpfull of lParam member.
// But for make the usage transparancy, the "lParam" access method is always available and return the pogrammer value ;o)
// because LS_item structure hold the lParam member before override it, and restore it when needed.
//
/*typedef struct iLS_item
{	LPARAM lParam;											// The user-32 bits data lParam member
    bool   mParam;											// let you know if the original item have a lParam significant member

   	DWORD StyleFlag;										// The style of this item
  	bool in_use;											// true if a font style is in use (except for colors)

	COLORREF txtColor;										// Text color if LIS_TXTCOLOR style 		(default otherwise)
  	COLORREF bgColor;										// BackGround color if LIS_BGCOLOR style	(default otherwise)

	CArray<struct iLS_item *,struct iLS_item *> subitems;   // Allow to have an individual style for subitems  (this array is empty if it's a subitem structure style instance)
	struct iLS_item * row_style;							// Access to the row style (valid only for the ITEM, subitems structure have NULL on this member)
	struct iLS_item * selected_style;						// The selected style for a component

	CFont * cfont;											// The CFont object pointer used for draw this item or subitem
	bool ifont;												// Allow to know if the CFont is a internal or user Cfont object and allow to know if we must memory manage it !
	CFont * merged_font;									// If a combination of differents font is needed (Style from Columns,Line and Item), this is the last CFont object

} LS_item;*/

//////////////////////////////////////////////////////////////////////////
// The CReportCtrl Class Definition
//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) CReportCtrl : public CListCtrl
{
public:		
		
	//////////////////////////////////////////////////////////////////////
	//		Constructor & Destructor
	//////////////////////////////////////////////////////////////////////
	CReportCtrl();
	virtual ~CReportCtrl();

	//////////////////////////////////////////////////////////////////////
	//		Run-time Creation
	//////////////////////////////////////////////////////////////////////
	virtual BOOL Create(CWnd* pParentWnd, UINT nID, LPCRECT lpRect = NULL, DWORD dwStyle = WS_BORDER | WS_TABSTOP);

	///////////////////////////////////////////////////////////////////////
	//		Column Header attributes
	///////////////////////////////////////////////////////////////////////
	
	BOOL SetColumnHeader(const CString& strHeadings); // Set columns and their formats.
	int GetColumnCount() const; // Get the column count.
	BOOL DeleteAllColumns();
	CString GetHeaderText(int nColumn) const;
	BOOL SetHeaderText(int nColumn, LPCTSTR lpText);	
	BOOL HasColumnHeader() const; // FALSE if the list control has LVS_NOCOLUMNHEADER flag
	const CHeaderCtrl* GetHeaderCtrl() const;

	///////////////////////////////////////////////////////////////////////
	//		Images & Color
	///////////////////////////////////////////////////////////////////////
	
	// Column header images
	BOOL SetHeaderImage(int nColumn, int nImageIndex, BOOL bLeftSide = TRUE);
	int GetHeaderImage(int nColumn) const;
	CImageList* SetHeaderImageList(UINT nBitmapID, COLORREF crMask = RGB(255, 0, 255));
	CImageList* SetHeaderImageList(CImageList* pImageList);
	
	// Sub-item images
	BOOL SetItemImage(int nItem, int nSubItem, int nImageIndex);
	int GetItemImage(int nItem, int nSubItem) const;
	CImageList* SetImageList(UINT nBitmapID, COLORREF crMask = RGB(255, 0, 255));
	CImageList* SetImageList(CImageList* pImageList);
	CImageList* GetImageList() const;

	// Sub-item Text & Background Color
	void SetItemTextColor(int nItem = -1, int nSubItem = -1, COLORREF color = COLOR_INVALID, BOOL bRedraw = TRUE);
	COLORREF GetItemTextColor(int nItem, int nSubItem) const;
	void SetItemBkColor(int nItem = -1, int nSubItem = -1, COLORREF color = COLOR_INVALID, BOOL bRedraw = TRUE);
	COLORREF GetItemBkColor(int nItem, int nSubItem) const;

	//////////////////////////////////////////////////////////////////////
	//		Control Styles & Attributes
	//////////////////////////////////////////////////////////////////////
	
	void ResizeToFitParent(); // Resize the list control to occupy parent's client area
	void SetGridLines(BOOL bSet = TRUE); // Show grid lines.
	void SetCheckboxeStyle(int nStyle = RC_CHKBOX_NORMAL); // Set checkbox styles.	
	int GetCheckboxStyle() const;	
	BOOL IsSortable() const; // Is sort allowed?
	BOOL SetSortable(BOOL bSet); // Allow/disallow sorting
	BOOL IsEditable() const; // Is Item text editable?
	void SetEditable(BOOL bSet = TRUE); // Allow item text editting
	
	///////////////////////////////////////////////////////////////////////
	//		Item attributes & operations
	///////////////////////////////////////////////////////////////////////	

	// Item states operation
	int GetFirstItem(DWORD dwStates = RC_ITEM_ALL, int nStartAfter = -1) const;
	int GetLastItem(DWORD dwStates = RC_ITEM_ALL, int nStartBefore = -1) const;
	int GetItemCount(DWORD dwStates = RC_ITEM_ALL) const;	
	DWORD GetItemStates(int nItem) const;
	BOOL ExamItemStates(int nItem, DWORD dwStates) const;
	BOOL SetItemStates(int nItem, DWORD dwNewStates);
	int SetAllItemStates(DWORD dwOldStates, DWORD dwNewStates);
	void InvertItems(int nType); // RC_INVERT_SELECTION or RC_INVERT_CHECKMARK

	// Item Insertion & Deletion	
	int InsertItemEx(int nItem, LPCTSTR lpText, ...); 	
	BOOL DeleteItem(int nItem, BOOL bSelectNextItem = FALSE); // Delete an item.
	int DeleteAllItems(DWORD dwStates = RC_ITEM_ALL); // Delete all qualified items.

	// Item positioning	
	int MoveUp(int nItem, int nCount = 1); // Move an item upwards by "nCount" positions.
	int MoveDown(int nItem, int nCount = 1); // Move an item downwards by "nCount" positions.
	int MoveToTop(int nItem); // Move an item up to the top.
	int MoveToBottom(int nItem); // Move an item down to the bottom.
	int MoveTo(int nItem, int nNewPosition); // Move an item to a particular position 
	BOOL SwapItems(int nItem1, int nItem2);	// Swap two items in the list, including all attributes.

	// Convenient versions of "CListCtrl::SetItemText"	
	BOOL SetItemTextCB(int nItem, int nSubItem, LPCTSTR lpText);
	BOOL SetItemText(int nItem, int nSubItem, INT val);
	BOOL SetItemText(int nItem, int nSubItem, UINT val);
	BOOL SetItemText(int nItem, int nSubItem, LONG val);
	BOOL SetItemText(int nItem, int nSubItem, ULONG val);
	BOOL SetItemText(int nItem, int nSubItem, TCHAR val);
	BOOL SetItemText(int nItem, int nSubItem, DOUBLE val, int nPrecision = -1);
	BOOL SetItemText(int nItem, int nSubItem, const COleDateTime& dateTime, DWORD dwFlags = 0);

	// Sorting	
	BOOL IsSortAscending() const;
	int GetSortedColumn() const;
	void SortItems(int nColumn, BOOL bAscending); // Sort a specified column.
	void SetSortSeparator(LPCTSTR lpSortSeparator = NULL); // Sort-separator, NULL=disabled
	LPCTSTR GetSortSeparator() const;

	// Item text edit	
	BOOL StartEdit(int nItem, int nSubItem); // Display the editbox, previous edit are committed
	BOOL EndEdit(BOOL bCommit = TRUE); // Commit/cancel text edit, hide the editbox
	CEditReport* GetEditControl();	
	/*void SetEditControl(CEdit *pEdit);*/

	///////////////////////////////////////////////////////////////////////
	//		Necessary overloading but Irrelevant to Users
	///////////////////////////////////////////////////////////////////////
	
	int InsertColumn(int nCol, LPCTSTR lpColumnHeading, int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	int InsertColumn(int nCol, const LVCOLUMN* pColumn);
	BOOL DeleteColumn(int nCol);
	BOOL SetCheck(int nItem, BOOL bCheck = TRUE); // overloaded to guard the "single" checkbox style
	BOOL SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem, int nImage, UINT nState, UINT nStateMask, LPARAM lParam);
	BOOL SetItem(const LVITEM* pItem);
	BOOL GetItem(LVITEM* pItem) const;
	DWORD GetItemData(int nItem) const;
	BOOL SetItemData(int nItem, DWORD dwData);
	DWORD SetExtendedStyle(DWORD dwNewStyle);
	BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	BOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
	int InsertItem(UINT nMask, int nItem, LPCTSTR lpItem, UINT nState, UINT nStateMask, int nImage, LPARAM lParam);
	int InsertItem(int nItem, LPCTSTR lpItem, int nImage);
	int InsertItem(const LVITEM* pItem);
	int InsertItem(int nIndex, LPCTSTR lpText);
	BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpText);

	POINT m_ptEditting; // Position of the subitem that is currently being edited

	BOOL _IsEditVisible() const;

protected:	
	
	// Helper functions for internal use
	BOOL _IsValidIndex(int nIndex) const;
	BOOL _ItemCheckMonitor(int nIndex, BOOL bBefore, BOOL bAfter, UINT nMsg);
//	BOOL _IsEditVisible() const;
	void _MouseClkMonitor(UINT nMsg, UINT nFlags, CPoint point, BOOL bTriggerEdit);
	static void _StringSplit(const CString &str, CStringArray& arr, TCHAR chDelimitior);
	void _UnsetSortedColumn();
	BOOL _SetItemStatesNoVerify(int nItem, DWORD dwNewStates);
	void _EnsureSingleCheck(int nItem);
	DWORD _GetHeaderTextFormat(int nColumn) const;
	void _UpdateColumn(int nColumn, BOOL bInsert);
	void _AllocItemMemory(int nItem);
	void _FreeItemMemory(int nItem);
	BOOL _PartialSort(int nStart, int nEnd);
	int _FindSeparator(int nStartAfter, int nColumn) const;
	void _QuickSortRecursive(int* pArr, int nLow, int nHigh);
	int _CompareItems(int nItem1, int nItem2);

	// Member data	
	CEditReport* m_pWndEdit; // Edit control, for subitem edit
	LPTSTR m_pszSeparator; // Sort separator
	BOOL m_bAllowEdit; // Is subitem edit allowed?
	int m_nChkStyle; // Checkbox style
	DWORD m_dwPrevEditFmt; // Format of previously edited subitem
	CImageList m_imgList; // Image list for items
	CImageList m_headerImgList; // Image list for the header control
	int m_nSortCol; // The sorted column, -1 if none
	BOOL m_bSortAscending; // Is sort ascending?

	//////////////////////////////////////////////////////////////////////
	// Wizard Generated Stuff
	//////////////////////////////////////////////////////////////////////

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Generated message map functions

protected:	

	//{{AFX_MSG(CReportCtrl)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnEnKillfocus( WPARAM wParam, LPARAM lParam );
//	afx_msg LRESULT OnEnSetfocus( WPARAM wParam, LPARAM lParam );
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// End of CReportCtrl Class Definition
//////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __REPORTCTRL_H__
#pragma once
#include "afxcmn.h"

#include "resource.h"

// Cuadro de di�logo de CDialogBusqueda

#ifndef __DIALOGBUSQUEDA_H__
#define __DIALOGBUSQUEDA_H__

#define IDD_DLG_BUSQUEDA                50001

class __declspec(dllexport) CDialogBusqueda : public CDialog
{
	DECLARE_DYNAMIC(CDialogBusqueda)

public:

	enum Types
	{
		ARTICULOS =  1,
		FAMILIAS,
		SUBFAMILIAS,
		CUENTAS,
		ALMACEN,
		PROVEEDORES,
		CLIENTES,
		CONCEPTOS,
		IDIOMA, 
		PAIS,
		DIVISAS,
		FPAGCOB,
		DIRENV,
		ZONA,
		RUTRAN,
		SEGURO,
		CENTROS,
		OFERTAS,
		PEDIDOS,
		ALBARANES,
		PEDIDOSCLI,
		COMPRAS,
		ALBCOMPRA,
		PEDIDOSPROVE,
		FACTURAS,
		ALBARANESPEDIDOCLI,
		COBROS,
		ESTADOS,
	};	

	CDialogBusqueda(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~CDialogBusqueda();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetTipo(int iTipo);
	void SetGestionar(BOOL bGestionar);
	CString GetCodigo();
	CString GetDescripcion();
	void InicializarListas();
	void SetCliente(CString);
	void SetPedido(CString strPedido);
	void SetCodFamilia(CString CodFam);
	void SetFactura(CString strFactura);

	void ReCargaLista();
// Datos del cuadro de di�logo
	enum { IDD = IDD_DLG_BUSQUEDA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstBusqueda;
	
private:
	CDatabase *m_db;
	CStringList m_lstBusquedaPorCod;
	CStringList m_lstBusquedaPorDes;
	CString m_strCodigo;
	CString m_strDescripcion;
	BOOL m_bCodigo;
	int m_iTipo;
	BOOL m_bGestionar;

	CString strCodFamilia;
	CString m_strCliente;
	CString m_strDesCliente;
	CString m_strPedido;
	CString m_strFactura;

	CString strCodigo;

	void CrearListaCodigo();
	void CrearListaDescripcion();

	void CreaListaCodsArticulos();
	void CreaListaDesArticulos();

	void CrearListaCodsFamilias();
	void CrearListaDesFamilias();

	void CrearListaCodsSubFamilias();
	void CrearListaDesSubFamilias();

	void CrearListaCodsCuentas();
	void CrearListaDesCuentas();

	void CrearListaCodsAlmacen();
	void CrearListaDesAlmacen();

	void CrearListaCodsProveedores();
	void CrearListaDesProveedores();

	void CrearListaCodsClientes();
	void CrearListaDesClientes();

	void CrearListaCodsConceptos();
	void CrearListaDesConceptos();

	void CrearListaCodsIdioma();
	void CrearListaDesIdioma();

	void CrearListaCodsPais();
	void CrearListaDesPais();

	void CrearListaCodsDivisas();
	void CrearListaDesDivisas();

	void CrearListaCodsFPagCob();
	void CrearListaDesFPagCob();

	void CrearListaCodsDirEnv();
	void CrearListaDesDirEnv();

	void CrearListaCodsZona();
	void CrearListaDesZona();

	void CrearListaCodsRuTran();
	void CrearListaDesRuTran();

	void CrearListaCodsSeguro();
	void CrearListaDesSeguro();

	void CrearListaCodsCentros();
	void CrearListaDesCentros();

	void CrearListaCodsOfertas();
	void CrearListaDesOfertas();

	void CrearListaCodsPedidos();
	void CrearListaDesPedidos();

	void CrearListaCodsAlbaranes();
	void CrearListaDesAlbaranes();

	void CrearListaCodsPedidosCli();
	void CrearListaDesPedidosCli();

	void CrearListaCodsCompras();
	void CrearListaDesCompras();

	void CrearListaCodsAlbCompra();
	void CrearListaDesAlbCompra();

	void CrearListaCodsPedidosProve();
	void CrearListaDesPedidosProve();

	void CrearListaCodsFacturas();
	void CrearListaDesFacturas();

	void CrearListaCodsAlbaranesPedidoCli();
	void CrearListaDesAlbaranesPedidoCli();

	void CrearListaCodsCobros();
	void CrearListaDesCobros();

	void CrearListaCodsEstados();
	void CrearListaDesEstados();

	void NuevaDirEnv();	void ModificarDirEnv();
	void NuevaIdioma(); void ModificarIdioma();
	void NuevaPais(); void ModificarPais();
	void NuevaFPagCob(); void ModificarFPagCob();
	void NuevaSeguro(); void ModificarSeguro();
	void NuevaCentros(); void ModificarCentros();
	void NuevaConcepto(); void ModificarConcepto();
	void NuevaZona(); void ModificarZona();
	void NuevaRuTran(); void ModificarRuTran();
	void NuevaDivisa(); void ModificarDivisa();

public:
	afx_msg void OnNMDblclkListBusqueda(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnColumnclickListBusqueda(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedAgregar();
	afx_msg void OnBnClickedModificar();
};

#endif // __DIALOGBUSQUEDA_H__
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
	CDlgInformes(CWnd* pParent = NULL);   // Constructor est�ndar
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

// Datos del cuadro de di�logo
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
// ESTADOS

#define COBRO_PENDIENTE     "0"
#define PENDIENTE_REMESAR   "1"
#define SELEC_REMESAR       "2"
#define DESCONTADO          "3"
#define GASTOS_CONT         "4"
#define IMPAGADO            "5"
#define COBRADO             "6"

#define TXT_COBRO_PENDIENTE     "Pendiente"
#define TXT_PENDIENTE_REMESAR   "Pendiente de remesar"
#define TXT_SELEC_REMESAR       "Seleccionado para remesar"
#define TXT_DESCONTADO          "Descontado"
#define TXT_GASTOS_CONT         "Gastos contabilizados"
#define TXT_IMPAGADO            "Impagado"
#define TXT_COBRADO             "Cobrado"

const int iNumEstados = 7;
const CString lstEstados[iNumEstados] = {COBRO_PENDIENTE, PENDIENTE_REMESAR, SELEC_REMESAR, DESCONTADO, GASTOS_CONT, IMPAGADO, COBRADO};
const CString lstDesEstados[iNumEstados] = {TXT_COBRO_PENDIENTE, TXT_PENDIENTE_REMESAR, TXT_SELEC_REMESAR, TXT_DESCONTADO, TXT_GASTOS_CONT, TXT_IMPAGADO, TXT_COBRADO};
