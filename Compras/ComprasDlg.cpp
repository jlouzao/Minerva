// ComprasDlg.cpp: archivo de implementación
//

#include "stdafx.h"
#include "ComprasDlg.h"
#include ".\comprasdlg.h"
#include "DlgBuscaCompra.h"


// Cuadro de diálogo de CComprasDlg

IMPLEMENT_DYNAMIC(CComprasDlg, CDialog)
CComprasDlg::CComprasDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComprasDlg::IDD, pParent)
	, m_strProveedor(_T(""))
	, m_strDesProveedor(_T(""))
	, m_strDireccion(_T(""))
	, m_strNumero(_T(""))
	, m_strCP(_T(""))
	, m_strPoblacion(_T(""))
	, m_strTelefono(_T(""))
	, m_strFax(_T(""))
	, m_strAlmacen(_T(""))
	, m_strDesAlmacen(_T(""))
	, m_bTipo(FALSE)
	, m_strCentro(_T(""))
	, m_strDesCentro(_T(""))
	, m_strFPagCob(_T(""))
	, m_strDesFPagCob(_T(""))
	, m_dNPagos(0)
	, m_dPago(0)
	, m_dDiaPago1(0)
	, m_dDiaPago2(0)
	, m_dDiaPago3(0)
	, m_strPP(_T(""))
	, m_dDiasDescuento(0)
	//, m_dDescuento1(0)
	, m_dDescuento2(0)
	, m_dDescuento3(0)
	, m_strObsped(_T(""))
	, m_strReferencia(_T(""))
	, m_dTotalBruto(0)
	, dDtoGeneral(0)
{
	m_timeFech= CTime::GetCurrentTime();
	m_bNuevo = TRUE;
	m_bReadOnly = TRUE;
	m_iNumArti = 0;
	dDtoGeneral = 0;
}

CComprasDlg::~CComprasDlg()
{
}

void CComprasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROVEEDOR, m_strProveedor);
	DDV_MaxChars(pDX, m_strProveedor, 9);
	DDX_Text(pDX, IDC_DES_PROVEEDOR, m_strDesProveedor);
	DDX_Text(pDX, IDC_DIRECCION, m_strDireccion);
	DDX_Text(pDX, IDC_NUMERO, m_strNumero);
	DDX_Text(pDX, IDC_CP, m_strCP);
	DDX_Text(pDX, IDC_POBLACION, m_strPoblacion);
	DDX_Text(pDX, IDC_OBSERVACIONES, m_strObservaciones);
	DDX_Text(pDX, IDC_TELEFONO, m_strTelefono);
	DDV_MaxChars(pDX, m_strTelefono, 15);
	DDX_Text(pDX, IDC_FAX, m_strFax);
	DDV_MaxChars(pDX, m_strFax, 15);
	DDX_Text(pDX, IDC_ALMACEN, m_strAlmacen);
	DDV_MaxChars(pDX, m_strAlmacen, 9);
	DDX_Text(pDX, IDC_DES_ALMACEN, m_strDesAlmacen);
	DDX_Radio(pDX, IDC_RB_NACIONAL, m_bTipo);
	DDX_Text(pDX, IDC_CENTRO, m_strCentro);
	DDV_MaxChars(pDX, m_strCentro, 3);
	DDX_Text(pDX, IDC_DES_CENTRO, m_strDesCentro);
	DDX_Text(pDX, IDC_FPAGCOB, m_strFPagCob);
	DDX_Text(pDX, IDC_DES_FPAGCOB, m_strDesFPagCob);
	DDX_Text(pDX, IDC_N_PAGOS, m_dNPagos);
	DDX_Text(pDX, IDC_PAGO, m_dPago);
	DDX_Text(pDX, IDC_DIA_PAGO1, m_dDiaPago1);
	DDX_Text(pDX, IDC_DIA_PAGO2, m_dDiaPago2);
	DDX_Text(pDX, IDC_DIA_PAGO3, m_dDiaPago3);
	DDX_Text(pDX, IDC_PP, m_strPP);
	DDX_Text(pDX, IDC_DIAS_DESCUENTO, m_dDiasDescuento);
	DDX_Text(pDX, IDC_DESCUENTO1, dDtoGeneral);//m_dDescuento1);
	DDX_Text(pDX, IDC_DESCUENTO2, m_dDescuento2);
	DDX_Text(pDX, IDC_DESCUENTO3, m_dDescuento3);
	DDX_Text(pDX, IDC_OBSPED, m_strObsped);
	DDV_MaxChars(pDX, m_strObsped, 100);
	DDX_Text(pDX, IDC_REFERENCIA, m_strReferencia);
	DDV_MaxChars(pDX, m_strReferencia, 25);
	DDX_DateTimeCtrl(pDX, IDC_FECHA, m_timeFech);
	DDX_Control(pDX, IDC_LIST_ARTICULOS, m_lstArticulos);
	//	DDX_Text(pDX, IDC_EDIT_ESTADO2, m_dTotalBruto);
	DDX_Text(pDX, IDC_TOTALBRUTO, m_strTotalBruto);
	DDX_Control(pDX, IDC_PROVEEDOR, m_ctrlProveedor);
	DDX_Control(pDX, IDC_ALMACEN, m_ctrlAlmacen);
	DDX_Control(pDX, IDC_CENTRO, m_ctrlCentro);
	DDX_Control(pDX, IDC_OBSPED, m_ctrlObsPed);
	DDX_Control(pDX, ID_BUSCAR, m_ctrlBuscar);
	DDX_Control(pDX, IDC_REFERENCIA, m_ctrlReferencia);
	DDX_Control(pDX, IDC_FPAGCOB, m_ctrlFPagCob);
	//	DDX_Text(pDX, IDC_DTOGENERAL, m_strDtoGeneral);
	DDX_Control(pDX, IDC_N_PAGOS, m_ctrlNPagos);
	DDX_Control(pDX, IDC_PAGO, m_ctrlPago);
	DDX_Control(pDX, IDC_DIAS_DESCUENTO, m_ctrlDiasDes);
	DDX_Control(pDX, IDC_DIA_PAGO1, m_ctrlDiaPago1);
	DDX_Control(pDX, IDC_DIA_PAGO3, m_ctrlDiaPago3);
	DDX_Control(pDX, IDC_DIA_PAGO2, m_ctrlDiaPago2);
	DDX_Control(pDX, IDC_DESCUENTO1, m_ctrlDescuento);
	DDX_Control(pDX, IDC_PP, m_ctrlPP);
}


BEGIN_MESSAGE_MAP(CComprasDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CUENTA, OnBnClickedBtnCuenta)
	ON_BN_CLICKED(IDC_BTN_CENTRO, OnBnClickedBtnCentro)
	ON_EN_KILLFOCUS(IDC_PROVEEDOR, OnEnKillfocusProveedor)
	ON_EN_KILLFOCUS(IDC_CENTRO, OnEnKillfocusCentro)
	ON_BN_CLICKED(IDC_BTN_ALMACEN, OnBnClickedBtnAlmacen)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(ID_MODIFICAR, OnBnClickedModificar)
	ON_BN_CLICKED(ID_NUEVO, OnBnClickedNuevo)
	ON_EN_KILLFOCUS(IDC_ALMACEN, OnEnKillfocusAlmacen)
	ON_BN_CLICKED(ID_BUSCAR, OnBnClickedBuscar)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ARTICULOS, OnNMClickListArticulos)
	ON_NOTIFY(NM_SETFOCUS, IDC_LIST_ARTICULOS, OnNMSetfocusListArticulos)
	ON_NOTIFY(NM_SETFOCUS, IDC_FECHA, OnNMSetfocusFecha)
	ON_MESSAGE(WM_KILLFOCUS, OnEnKillfocusEditlabel)
	ON_BN_CLICKED(ID_ELIMINAR, OnBnClickedEliminar)
//	ON_EN_KILLFOCUS(IDC_DTOGENERAL, OnEnKillfocusDtogeneral)
	ON_EN_KILLFOCUS(IDC_DESCUENTO1, OnEnKillfocusDescuento1)
	ON_BN_CLICKED(IDC_BTN_FPAGCOB, OnBnClickedBtnFpagcob)
	ON_EN_KILLFOCUS(IDC_FPAGCOB, OnEnKillfocusFpagcob)
	ON_EN_KILLFOCUS(IDC_PP, OnEnKillfocusPp)
END_MESSAGE_MAP()


// Controladores de mensajes de CComprasDlg
/*******************************************************************************************************/
BOOL CComprasDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_dlgBusquedaProveedor.SetConexion(m_db);
	m_dlgBusquedaCentros.SetConexion(m_db);
	m_dlgBusquedaAlmacen.SetConexion(m_db);
	m_dlgBusquedaArticulos.SetConexion(m_db);
	m_dlgBusquedaFpagcob.SetConexion(m_db);

////////////////////SE DA FORMA AL GRID////////////////////
	//Se establece el estilo	
	m_lstArticulos.SetGridLines(TRUE);

	// Añadiendo la lista de imágenes se consigue hacer cada casilla más grande
	CImageList m_ImageList;
	m_ImageList.Create(1, 16, ILC_COLOR,1,1); 
	m_lstArticulos.SetImageList(&m_ImageList); 

	// Se introducen los nombres de las columnas
	m_lstArticulos.InsertColumn(0,"Código", LVCFMT_LEFT, 105);			
	m_lstArticulos.InsertColumn(1,"Descripción", LVCFMT_LEFT, 190);
	m_lstArticulos.InsertColumn(2,"Cantidad", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(3,"Tarifa", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(4,"Dcto", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(5,"IVA", LVCFMT_LEFT, 55);
	m_lstArticulos.InsertColumn(6,"Descripción detallada", LVCFMT_LEFT, 180);
	m_lstArticulos.SetEditable(TRUE); // Allow sub-text edit
	// Se inicializa el primer item todo vacío para permitir escribir en él
	InsertaRegistroVacio();
	// Se inicializa el flag
	m_bFocusListCtrl = FALSE;

	
	// Se deshabilita el botón de Buscar, Eliminar y Aceptar
	GetDlgItem(ID_BUSCAR)->EnableWindow(FALSE);
	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	// Se inicializa la variable con el título y se activan o desactivan los editbox
	// según el tipo
	if (m_iTipo == GESTCOMPRAS)
	{
		m_strTitulo = TITULO_GESTION;
	}
	else if(m_iTipo == GESTALBARAN)
	{
		m_strTitulo = TITULO_ALBARANES;
		GetDlgItem(ID_NUEVO)->EnableWindow(FALSE);
		SoloLectura();
	}

	SetWindowText(m_strTitulo);

	// Se inicializan las variables para controlar acciones
	m_bTabFecha = FALSE;

	UpdateData(FALSE);

	return TRUE;
}
/*******************************************************************************************************/
/********************************* FUNCIONES REFERENTES AL GRID ****************************************/
/*******************************************************************************************************/
void CComprasDlg::InsertaRegistroVacio()
{
	m_lstArticulos.InsertItem(m_iNumArti, _T(""));
	m_lstArticulos.SetItemText(m_iNumArti, 0, "");
	m_lstArticulos.SetItemText(m_iNumArti, 1, "");
	m_lstArticulos.SetItemText(m_iNumArti, 2, "");
	m_lstArticulos.SetItemText(m_iNumArti, 3, "");
	m_lstArticulos.SetItemText(m_iNumArti, 4, "");
	m_lstArticulos.SetItemText(m_iNumArti, 5, "");
	m_lstArticulos.SetItemText(m_iNumArti, 6, "");


	m_lstArticulos.EnsureVisible(m_iNumArti, FALSE);

}
/******************************************************************************************/
BOOL CComprasDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if  (pMsg->wParam == VK_TAB)
		{
			// Si se ha pulsado el tabulador y venimos de la casilla de la fecha,
			//se debe editar la casilla del listCtrl
			if (m_bFecha)
				m_bTabFecha = TRUE;
		}
	}

	return(CDialog::PreTranslateMessage(pMsg));
}
/******************************************************************************************/
void CComprasDlg::OnNMClickListArticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_iTipo == GESTALBARAN)
	{	
		GetDlgItem(IDOK)->SetFocus();
		return;
	}
	// Se deshabilita el botón de Eliminar si hay algún elemento seleccionado para ser editado
	POSITION pos = m_lstArticulos.GetFirstSelectedItemPosition();
	int iIndex = m_lstArticulos.GetNextSelectedItem(pos);            

	if (m_lstArticulos.GetSelectedCount() > 0 && iIndex != m_lstArticulos.GetItemCount()-1)
		GetDlgItem(ID_ELIMINAR)->EnableWindow(TRUE);
	else
		GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);

	*pResult = 0;
}
/******************************************************************************************/
void CComprasDlg::OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_iTipo == GESTALBARAN)
		GetDlgItem(IDOK)->SetFocus();
		return;

	// Se comprueba si se ha seleccionado una Cuenta o un Almacén
	if (!m_bFocusListCtrl)
	{
		m_bFocusListCtrl = TRUE;

		if (m_strProveedor.IsEmpty())
		{
			AfxMessageBox(IDS_NO_PROVEEDOR);
			m_lstArticulos.EndEdit();
			m_bFocusListCtrl = FALSE;
			return;
		}
		if (m_iTipo == ALBARAN)
			return;

		// Si es una compra o un albarán se debe seleccionar un almacén obligatoriamente
		if ((m_iTipo == GESTCOMPRAS) && m_strAlmacen.IsEmpty())
		{
			AfxMessageBox(IDS_NO_ALMACEN);
			m_lstArticulos.EndEdit();
			m_bFocusListCtrl = FALSE;
			return;
		}
	}
	// Si se ha pulsado tabulador y venimos de Atn. al Cliente se activa la primera casilla
	if (((m_iTipo == GESTCOMPRAS && !m_strProveedor.IsEmpty()) || 
		(m_iTipo != GESTCOMPRAS && !m_strProveedor.IsEmpty() && !m_strAlmacen.IsEmpty())) && m_bTabFecha)
	{
		m_lstArticulos.EndEdit();
		m_lstArticulos.StartEdit(m_iNumArti, 0);						
		m_bFecha = FALSE;
		m_bTabFecha = FALSE;
	}

	// Si vamos a la casilla de la descripción pero no hay código se devuelve el foco
	CString strCod = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 0);
	if (m_lstArticulos.m_ptEditting.y != -1 && m_lstArticulos.m_ptEditting.y != 0 && strCod.IsEmpty())
	{
		m_lstArticulos.EndEdit();
		m_lstArticulos.StartEdit(m_iNumArti, 0);			
	}

	// Se asigna el límite de caracteres de la primer casilla, la del código, a 15 y del
	// resto a 100 que son los máximos que puede tener la descripción detallada
	if (m_lstArticulos.m_ptEditting.y == 0)
		m_lstArticulos.GetEditControl()->SetLimitText(15);
	else if (!strCod.IsEmpty())
		m_lstArticulos.GetEditControl()->SetLimitText(255);

	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);

	*pResult = 0;
}
/*******************************************************************************************************/
void CComprasDlg::BuscaArticulosPedido(CString strNumCompras)
{
	CArtiCompra rsArtiCompra(m_db);

	rsArtiCompra.m_strFilter = "NPEDCOM LIKE '" + strNumCompras + "'";
	if (!rsArtiCompra.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	int iIndice = 0;
	m_dTotalBruto = 0;
	while (!rsArtiCompra.IsEOF())
	{
		//Nombre del articulo
		m_lstArticulos.InsertItem(iIndice, _T(""));
		m_lstArticulos.SetItemText(iIndice, 0, rsArtiCompra.m_ARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 0, RGB(183, 183, 183), TRUE);
		//Descripcion del articulo(solo lectura)
		m_lstArticulos.SetItemText(iIndice, 1, rsArtiCompra.m_DESARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 1, RGB(183, 183, 183), TRUE);
		// Se escribe la cantidad
		CString strCantidad;
		strCantidad.Format("%g", rsArtiCompra.m_CANTI);
		m_lstArticulos.SetItemText(iIndice, 2, strCantidad);
		m_lOldCantidad.AddTail((int)rsArtiCompra.m_CANTI);
//		m_lIniCantidad.AddTail((int)rsArtiCompra.m_CANTI);
		// Se escribe la tarifa
		CString strTarifa;
		strTarifa.Format("%g", rsArtiCompra.m_IMPOARTI);
		m_lstArticulos.SetItemText(iIndice, 3, strTarifa);
		m_lOldTarifa.AddTail(rsArtiCompra.m_IMPOARTI);
		//Se escribe el descuento
		CString strDto;
		strDto.Format("%g", rsArtiCompra.m_DTOARTI);
		m_lstArticulos.SetItemText(iIndice, 4, strDto);
		m_lOldDto.AddTail(rsArtiCompra.m_DTOARTI);
		//Se escribe el IVA
		CString strIVA;
		strIVA.Format("%g", rsArtiCompra.m_IVARTI);
		m_lstArticulos.SetItemText(iIndice, 5, strIVA);
		m_lstArticulos.SetItemText(iIndice, 6, rsArtiCompra.m_DESARMEMO.Trim());
		//Se calcula el Valor total
		m_dTotalBruto += rsArtiCompra.m_CANTI * rsArtiCompra.m_IMPOARTI * (1 - (rsArtiCompra.m_DTOARTI / 100)) * (1 - (atof(m_strDtoGeneral)/100)); 

		iIndice ++;
		m_iNumArti++;
		rsArtiCompra.MoveNext();
	}
	rsArtiCompra.Close();

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_TOTALBRUTO)->SetWindowText(m_strTotalBruto);
}
/******************************************************************************************/
void CComprasDlg::OnNMSetfocusFecha(NMHDR *pNMHDR, LRESULT *pResult)
{
	m_bFecha = TRUE;
	*pResult = 0;
}
/******************************************************************************************/
void CComprasDlg::BuscaArticulo(CString strCodArti)
{
	// Se carga el listCtrl con el Código, la Descripción, el Tipo, el Tipo de Alquiler
	//y la tarifa 
	CArticulo rsArticulo(m_db);
	
	// Se comprueba si ese artículo ya está en el CListCtrl. Para ello se busca el
	//elemento, si lo encuentra devuelve el índice de la fila donde lo encontro y si
	//no, devuelve el indice de la última fila o -1 
	LVFINDINFO info;
	int iIndex;
	
	info.flags = LVFI_STRING | LVFI_WRAP;
	info.psz = strCodArti;
	iIndex = m_lstArticulos.FindItem(&info);
	if ( iIndex != m_iNumArti && iIndex != -1)
	{
		m_lstArticulos.SetItemText(m_iNumArti, 0, "");
		AfxMessageBox(IDS_ARTI_YA_EN_LISTA);
		return;
	}

	// Se busca el artículo
	rsArticulo.m_strFilter = "ARTI LIKE '" + strCodArti + "'";
	if (!rsArticulo.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	// Si el articulo no se encuentra salimos reseteando el campo
	if (rsArticulo.m_ARTI.IsEmpty())
	{
		m_lstArticulos.SetItemText(m_iNumArti, 0, "");
		AfxMessageBox(IDS_ARTI_NO_EXISTE);
		return;
	}
	m_lstArticulos.SetItemText(m_iNumArti, 0, rsArticulo.m_ARTI.Trim());
	m_lstArticulos.SetItemBkColor(m_iNumArti, 0, RGB(183, 183, 183), TRUE);
	m_lstArticulos.SetItemText(m_iNumArti, 1, rsArticulo.m_DESARTI.Trim());
	m_lstArticulos.SetItemBkColor(m_iNumArti, 1, RGB(183, 183, 183), TRUE);
	// Se escribe la cantidad
	m_lstArticulos.SetItemText(m_iNumArti, 2, "0");
	m_lOldCantidad.AddTail((int)0);//Para calcular precio total
//	m_lIniCantidad.AddTail((int)0);
	m_lstArticulos.SetItemText(m_iNumArti, 3, rsArticulo.m_ETARI2);
	m_lstArticulos.SetItemText(m_iNumArti, 4, rsArticulo.m_DTOARCO);
	m_lstArticulos.SetItemText(m_iNumArti, 5, rsArticulo.m_IVARTI);
	m_lstArticulos.SetItemText(m_iNumArti, 6, rsArticulo.m_DESARMEMO.Trim());
	//m_lstArticulos.SetItemBkColor(m_iNumArti, 6, RGB(183, 183, 183), TRUE);
	m_lstArticulos.EnsureVisible(m_iNumArti, FALSE);
	// Se añade Tarifa y Dto a la lista de valores iniciales
	m_lOldTarifa.AddTail(rsArticulo.m_ETARI2);
	m_lOldDto.AddTail( rsArticulo.m_DTOARCO);

	/*CString strTarifa, strDto;
	strTarifa.Format("%f", rsArticulo.m_ETARI2);
	strDto.Format("%f", rsArticulo.m_DTOARCO);
	m_lOldTarifa.AddTail(strTarifa);
	m_lOldDto.AddTail(strTarifa);*/

	rsArticulo.Close();

	m_iNumArti++;

	InsertaRegistroVacio();

	// Se deshabilita el botón de Eliminar
	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
	// Se calcula el PRECIO
	double iCantidad = atoi(m_lstArticulos.GetItemText(m_iNumArti, 2));
	double dTarifa = atof(m_lstArticulos.GetItemText(m_iNumArti, 3));
	double dDto = atof(m_lstArticulos.GetItemText(m_iNumArti, 4));

	// Primero se debe restar el precio de la cantidad anterior.
	//double dPrecioAnterior = iOldCantidad * dTarifa * (1 - (dDto / 100));
	//m_dTotalBruto -= dPrecioAnterior;

	// Se calcula el nuevo precio total
	m_dTotalBruto += iCantidad * dTarifa * (1 - (dDto / 100));;

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_TOTALBRUTO)->SetWindowText(m_strTotalBruto);

	//m_lOldCantidad.SetAt(m_lOldCantidad.FindIndex(m_iNumArti), iCantidad);
	/*m_strTotalBruto.Format("%f",m_dTotalBruto);
	GetDlgItem(IDC_TOTALBRUTO)->SetWindowText(m_strTotalBruto);*/
}
/*****************************************************************************************/
LRESULT CComprasDlg::OnEnKillfocusEditlabel(WPARAM, LPARAM lParam)
{
	HRESULT hErr  = 0;

	// Si el foco va a la primera columna y es una fila vacía
	if (m_lstArticulos.m_ptEditting.y == 0 && m_lstArticulos.m_ptEditting.x == m_iNumArti)
	{
		CString strCodArti;

		// Se coge el código del artículo
		int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
		if (len != 0)
		{
			m_lstArticulos.GetEditControl()->GetLine(0, strCodArti.GetBuffer(len), len);
			strCodArti.ReleaseBuffer(len);
			if (!strCodArti.IsEmpty())
				BuscaArticulo(strCodArti);
		}
	}

	// Se obtiene lo que contiene la primera columna
	CString strCod = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 0);

	// En las columnas que deben estar inactivas se pone el textbox a readonly o si el
	// flag de m_bReadOnly está a TRUE
	if ((m_lstArticulos.m_ptEditting.y == 0 && !strCod.IsEmpty()) || m_lstArticulos.m_ptEditting.y == 1)
		//|| m_lstArticulos.m_ptEditting.y == 6)
		m_lstArticulos.GetEditControl()->SetReadOnly(TRUE);
	else if (m_lstArticulos.m_ptEditting.y != -1)
			m_lstArticulos.GetEditControl()->SetReadOnly(FALSE);
	
	
	// Si se cambia la cantidad de artículos se debe recalcular el precio total
	if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y ==2)
		CambiaCantidad();
	
	// Si se cambia la tarifa de un artículo se debe recalcular el precio total
	else if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y == 3)
		CambiaTarifa();

	// Si se cambia el descuento de un artículo se debe recalcular el precio total
	else if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y == 4)
		CambiaDescuento();

	// Se comprueba si el iva es un número
	else if (!strCod.IsEmpty() && m_lstArticulos.m_ptEditting.y == 5)
		CompruebaIva();

	return hErr;
}
/******************************************************************************************/
void CComprasDlg::CambiaCantidad()
{
	// Se comprueba si en la cantidad son todo dígitos
	CString strCantidad /*, strOldCantidad*/;
	int iCantidad, iOldCantidad, iFila;

	iFila = m_lstArticulos.m_ptEditting.x;

	int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
	m_lstArticulos.GetEditControl()->GetLine(0, strCantidad.GetBuffer(len), len);
	strCantidad.ReleaseBuffer(len);

	iOldCantidad = m_lOldCantidad.GetAt(m_lOldCantidad.FindIndex(iFila));

	// Se comprueba si en la cantidad son todo números enteros
	for (int i = 0; i<strCantidad.GetLength(); i++)
	{
		if (strCantidad.GetAt(i) < '0' || strCantidad.GetAt(i) > '9') 
		{
			m_lstArticulos.SetItemText(iFila, 2, iOldCantidad);
			return;
		}
	}

	// Si cantidad no tiene nada se considera 0
	if (strCantidad.IsEmpty())
	{
		iCantidad = 0;
		m_lstArticulos.SetItemText(iFila, 5, iCantidad);
	}
	else
		iCantidad = atoi(strCantidad);

	// Si la cantidad no ha cambiado abandonamos la función
	if (iCantidad == iOldCantidad)
		return;

	//m_lstArticulos.SetItemTextCB(iFila, 5, strCantidad);

	// Se recalcula el PRECIO
	double dTarifa = atof(m_lstArticulos.GetItemText(iFila, 3));
	double dDto = atof(m_lstArticulos.GetItemText(iFila, 4));

	// Primero se debe restar el precio de la cantidad anterior.
	double dPrecioAnterior;
	if (m_strDtoGeneral=="")
	{
		dPrecioAnterior = iOldCantidad * dTarifa * (1 - (dDto / 100));
		m_dTotalBruto -= dPrecioAnterior;
		// Se calcula el nuevo precio total
		m_dTotalBruto += (iCantidad * dTarifa * (1 - (dDto / 100)));
	}
	else
	{
		dPrecioAnterior = iOldCantidad * dTarifa * (1 - (dDto / 100));
		m_dTotalBruto -= dPrecioAnterior;
		m_dTotalBruto += (iCantidad * dTarifa * (1 - (dDto / 100)));
	}
	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_TOTALBRUTO)->SetWindowText(m_strTotalBruto);

	m_lOldCantidad.SetAt(m_lOldCantidad.FindIndex(iFila), iCantidad);

	// Si es un pedido o un albarán, si no hubiera unidades disponibles se da un aviso
/*	if (m_iTipo == PEDIDO || m_iTipo == ALBARAN)
		CompruebaArtiDisponible(m_lstArticulos.GetItemText(iFila, 0), iFila, iCantidad);*/
}
/******************************************************************************************/
void CComprasDlg::CambiaDescuento()
{
	CString strDto;
	double dDto, dOldDto;
	int iFila;

	iFila = m_lstArticulos.m_ptEditting.x;

	int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
	m_lstArticulos.GetEditControl()->GetLine(0, strDto.GetBuffer(len), len);
	strDto.ReleaseBuffer(len);

	dOldDto = m_lOldDto.GetAt(m_lOldDto.FindIndex(iFila));

	// Se comprueba si en el descuento hay sólo números
	if (!CompruebaNumero(strDto))
	{
		m_lstArticulos.SetItemText(iFila, 4, dOldDto);
		return;
	}

	// Si el descuento está vacío se considera 0
	if (strDto.IsEmpty())
	{
		dDto = 0;
		m_lstArticulos.SetItemText(iFila, 4, dDto);
	}
	else
		dDto = atof(strDto);

	// Si el descuento no ha cambiado abandonamos la función
	if (dDto == dOldDto)
		return;

//	m_lstArticulos.SetItemTextCB(iFila, 7, strDto);

	// Se recalcula el PRECIO
	int iCantidad = atoi(m_lstArticulos.GetItemText(iFila, 2));
	double dTarifa = atof(m_lstArticulos.GetItemText(iFila, 3));

	// Primero se debe restar el precio que suponía con la tarifa anterior.
	double dPrecioAnterior;
	if (m_strDtoGeneral=="")
	{
		dPrecioAnterior= iCantidad * dTarifa * (1 - dOldDto / 100);
		m_dTotalBruto -= dPrecioAnterior;
		// Se calcula el nuevo precio total
		m_dTotalBruto += iCantidad * dTarifa * (1 - (dDto / 100));
	}
	else
		{
		dPrecioAnterior= iCantidad * dTarifa * (1 - (dOldDto / 100));
		m_dTotalBruto -= dPrecioAnterior;
		// Se calcula el nuevo precio total
		m_dTotalBruto += iCantidad * dTarifa * (1 - (dDto / 100));
	}
	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_TOTALBRUTO)->SetWindowText(m_strTotalBruto);

	m_lOldDto.SetAt(m_lOldDto.FindIndex(iFila), dDto);
}
/******************************************************************************************/
void CComprasDlg::CambiaTarifa()
{
	CString strTarifa;
	double dTarifa, dOldTarifa;
	int iFila;

	iFila = m_lstArticulos.m_ptEditting.x;

	int len = m_lstArticulos.GetEditControl()->LineLength(m_lstArticulos.GetEditControl()->LineIndex(0));
	m_lstArticulos.GetEditControl()->GetLine(0, strTarifa.GetBuffer(len), len);
	strTarifa.ReleaseBuffer(len);

	dOldTarifa = m_lOldTarifa.GetAt(m_lOldTarifa.FindIndex(iFila));

	// Se comprueba si en la tarifa son sólo números
	if (!CompruebaNumero(strTarifa))
	{
		m_lstArticulos.SetItemText(iFila, 3, dOldTarifa);
		return;
	}
	// Si cantidad no tiene nada se cosidera 0
	if (strTarifa.IsEmpty())
	{
		dTarifa = 0;
		m_lstArticulos.SetItemText(m_lstArticulos.m_ptEditting.x, 3, dTarifa);
	}
	else
		dTarifa = atof(strTarifa);

	// Si la tarifa no ha cambiado abandonamos la función
	if (dTarifa == dOldTarifa)
		return;

//	m_lstArticulos.SetItemTextCB(iFila, 6, strTarifa);

	// Se recalcula el PRECIO
	int iCantidad = atoi(m_lstArticulos.GetItemText(iFila, 2));
	double dDto = atof(m_lstArticulos.GetItemText(iFila, 4));

	// Primero se debe restar el precio que suponía con la tarifa anterior.
	double dPrecioAnterior;
	if(m_strDtoGeneral=="")
	{
		dPrecioAnterior= iCantidad * dOldTarifa * (1 - (dDto / 100));
		m_dTotalBruto -= dPrecioAnterior;
		// Se calcula el nuevo precio total
		m_dTotalBruto += iCantidad * dTarifa * (1 - (dDto / 100));
	}
	else
	{
		dPrecioAnterior= iCantidad * dOldTarifa * (1 - (dDto / 100));
		m_dTotalBruto -= dPrecioAnterior;
		// Se calcula el nuevo precio total
		m_dTotalBruto += iCantidad * dTarifa * (1 - (dDto / 100));
	}
	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_TOTALBRUTO)->SetWindowText(m_strTotalBruto);

	m_lOldTarifa.SetAt(m_lOldTarifa.FindIndex(iFila), dTarifa);
}
/************************************************************************************************************/
void CComprasDlg::CompruebaIva()
{
	// Se comprueba si el IVA son sólo números. Si no se pone el IVA por defecto que es 16
	CString strIVA = m_lstArticulos.GetItemText(m_lstArticulos.m_ptEditting.x, 5);
		if (!CompruebaNumero(strIVA))
	{
		m_lstArticulos.SetItemText(m_lstArticulos.m_ptEditting.x, 5, "16");
		return;
	}
}
/************************************************************************************************************/
BOOL CComprasDlg::CompruebaNumero(CString strNumero)
{
	BOOL bPunto = FALSE; 

	for (int i = 0; i<strNumero.GetLength(); i++)
	{
		if (strNumero.GetAt(i) < '0' || strNumero.GetAt(i) > '9')
		{ 
			if (strNumero.GetAt(i)== '.' && bPunto == FALSE)
				bPunto = TRUE;
			else
				return FALSE;
		}
	}

	return TRUE;
}
/*******************************************************************************************************/
/*****                                        FUNCIONES                                            *****/
/*******************************************************************************************************/
void CComprasDlg::SetConexion(CDatabase *db)
{
	m_db=db;
	m_rsCompras.m_pDatabase = db;
	m_rsAlbaranC.m_pDatabase = db;
}
/*******************************************************************************************************/
void CComprasDlg::SetTipo(int iTipo)
{
	m_iTipo = iTipo;	
}
/*******************************************************************************************************/
void CComprasDlg::OnBnClickedBtnCuenta()
{
	INT_PTR Estado;
	//Llama al dialogo de busqueda
	m_dlgBusquedaProveedor.SetTipo(CDialogBusqueda::PROVEEDORES);
	m_dlgBusquedaProveedor.SetGestionar(FALSE);
	Estado=m_dlgBusquedaProveedor.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	//Y sino se pulsa Cancel
	LimpiaCampos();
	m_strProveedor=m_dlgBusquedaProveedor.GetCodigo();
	GetDlgItem(IDC_PROVEEDOR)->SetWindowText(m_strProveedor);
	BuscaProveedor();
}
/*******************************************************************************************************/
void CComprasDlg::OnEnKillfocusProveedor()
{
	CString strAuxProve = m_strProveedor;

	GetDlgItem(IDC_PROVEEDOR)->GetWindowText(m_strProveedor);

	if (m_strProveedor == strAuxProve)
		return;

	if (!m_strProveedor.IsEmpty())
	{
		// Si el cliente no existe se deja el anterior y se da un mensaje de error
		if (!BuscaProveedor())
		{
			AfxMessageBox(IDS_PROVEEDOR_NO_EXISTE);
			m_strProveedor = strAuxProve;
			GetDlgItem(IDC_PROVEEDOR)->SetWindowText(m_strProveedor);
		}
	}
	else
		LimpiaVentana();//Campos();
}
/*******************************************************************************************************/
void CComprasDlg::SoloLectura()
{
	//Desactivamos casi todo para que no se pueda editar nada(ya sea por ser un albaran o por ser un pedido
	//del que ya hemos realizado un albaran
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->SetWindowText("Buscar");
	GetDlgItem(IDC_BTN_CUENTA)->EnableWindow(FALSE);//y el de cuenta
	m_ctrlNPagos.SetReadOnly(TRUE);
	m_ctrlPago.SetReadOnly(TRUE);
	m_ctrlDiasDes.SetReadOnly(TRUE);
	m_ctrlDiaPago1.SetReadOnly(TRUE);
	m_ctrlDiaPago2.SetReadOnly(TRUE);
	m_ctrlDiaPago3.SetReadOnly(TRUE);
	m_ctrlDescuento.SetReadOnly(TRUE);
	m_ctrlPP.SetReadOnly(TRUE);
	m_ctrlProveedor.SetReadOnly(TRUE);
	m_ctrlAlmacen.SetReadOnly(TRUE);
	GetDlgItem(IDC_BTN_ALMACEN)->EnableWindow(FALSE);
	m_ctrlCentro.SetReadOnly(TRUE);
	GetDlgItem(IDC_BTN_CENTRO)->EnableWindow(FALSE);
	m_ctrlObsPed.SetReadOnly(TRUE);
	m_ctrlReferencia.SetReadOnly(TRUE);
	GetDlgItem(IDC_FECHA)->EnableWindow(FALSE);
	GetDlgItem(ID_BUSCAR)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_ELIMINAR)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_NUEVO)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_MODIFICAR)->ShowWindow(SW_HIDE);
	GetDlgItem(ID_BUSCAR)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_RB_NACIONAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_RB_EXPORTACION)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_FPAGCOB)->EnableWindow(FALSE);
	m_ctrlFPagCob.SetReadOnly(TRUE);
	//m_lstArticulos.s
}
/*******************************************************************************************************/
void CComprasDlg::LimpiaCampos()
{
	m_strProveedor.Empty();
	m_strDesProveedor.Empty();
	m_strDireccion.Empty();
	m_strNumero.Empty();
	m_strCP.Empty();
	m_strPoblacion.Empty();
	m_strObservaciones.Empty();
	m_strTelefono.Empty();
	m_strFax.Empty();

	UpdateData(FALSE);
}
/*******************************************************************************************************/
BOOL CComprasDlg::BuscaProveedor()
{
	BOOL bExists = FALSE;
	CProve rsProve(m_db);

	rsProve.m_strFilter = "CUENTA LIKE '" + m_strProveedor + "'";
	if (!rsProve.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	// Si el cliente existe se rellenan sus campos 
	if (!rsProve.m_CUENTA.IsEmpty())
	{
		m_strDesProveedor=rsProve.m_NOMFICHA.Trim();
		m_strDireccion=rsProve.m_DIRECCION.TrimRight();
		m_strNumero=rsProve.m_NUMERO.TrimRight();
		m_strCP=rsProve.m_CP.TrimRight();
		m_strPoblacion=rsProve.m_POBLACION.TrimRight();
		m_strObservaciones=rsProve.m_OBSER1.TrimRight();
		m_strTelefono=rsProve.m_TELEFONO.TrimRight();
		m_strFax=rsProve.m_FAX.TrimRight();
		m_strFPagCob=rsProve.m_FCOBRO.TrimRight();
		//busca en la tabla FPagCob la descripción//
		CFPagCob rsPago(m_db);
		rsPago.m_strFilter = "FCOBRO LIKE '"+ m_strFPagCob +"'";
		if (!rsPago.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDS_ERROR_BD);
			return FALSE;
		}
		m_strDesFPagCob=rsPago.m_DFCOBRO.Trim();
		rsPago.Close();
		////////////////////////////////////////////
		m_dNPagos=rsProve.m_NCOBROS;
		m_dDiasDescuento=rsProve.m_DVTO;
		//m_dDescuento1=rsProve.m_DCTOS;
		dDtoGeneral= rsProve.m_DCTOS;
		m_dDescuento2=rsProve.m_DCTO2;
		m_dDescuento3=rsProve.m_DCTO3;
		m_dPago=rsProve.m_VTO1;
		m_dDiaPago1=rsProve.m_DIA1;
		m_dDiaPago2=rsProve.m_DIA2;
		m_dDiaPago3=rsProve.m_DIA3;
		m_strPP.Format("%2.f",rsProve.m_PP);
		bExists=TRUE;
		GetDlgItem(IDOK)->EnableWindow(TRUE);

		if (!m_strAlmacen.IsEmpty())
			GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);
	}
	rsProve.Close();

	UpdateData(FALSE);
	return bExists;
}
/*******************************************************************************************************/
void CComprasDlg::OnBnClickedBtnCentro()
{
	INT_PTR status;

	m_dlgBusquedaCentros.SetTipo(CDialogBusqueda::CENTROS);
	status = m_dlgBusquedaCentros.DoModal();
	if (status == IDOK)
	{
		m_strCentro = m_dlgBusquedaCentros.GetCodigo();
		m_strDesCentro = m_dlgBusquedaCentros.GetDescripcion();
	}

	GetDlgItem(IDC_CENTRO)->SetWindowText(m_strCentro);
	GetDlgItem(IDC_DES_CENTRO)->SetWindowText(m_strDesCentro);
}
/*******************************************************************************************************/
void CComprasDlg::OnEnKillfocusCentro()
{
	CString strAuxCentro = m_strCentro;

	GetDlgItem(IDC_CENTRO)->GetWindowText(m_strCentro);

	if (!m_strCentro.IsEmpty())
	{
		// Si el Centro no existe se deja el anterior y se da un mensaje de error
		if (!BuscaCentro())
		{
			AfxMessageBox(IDS_CENTRO_NO_EXISTE);
			m_strCentro = strAuxCentro;
			GetDlgItem(IDC_CENTRO)->SetWindowText(m_strCentro);
		}
	}
	else
	{	//LimpiaCentro();
		m_strCentro.Empty();
		m_strDesCentro.Empty();

		GetDlgItem(IDC_CENTRO)->SetWindowText(m_strCentro);
		GetDlgItem(IDC_DES_CENTRO)->SetWindowText(m_strDesCentro);
	}
}
/*******************************************************************************************************/
BOOL CComprasDlg::BuscaCentro()
{
	BOOL bExists = FALSE;
	CCentros rsCentros(m_db);

	rsCentros.m_strFilter = "CCENTRO LIKE '" + m_strCentro + "'";
	if (!rsCentros.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	// Si el centro existe se rellena la descripción 
	if (!rsCentros.m_CCENTRO.IsEmpty())
	{
		m_strDesCentro = /*m_rsProforma.m_CENTRO.Trim() =*/ rsCentros.m_DCENTRO.Trim();
		bExists = TRUE;
	}

	rsCentros.Close();

	GetDlgItem(IDC_CENTRO)->SetWindowText(m_strCentro);
	GetDlgItem(IDC_DES_CENTRO)->SetWindowText(m_strDesCentro);

	//UpdateData(FALSE);

	return bExists;
}
/*******************************************************************************************************/
void CComprasDlg::OnBnClickedBtnAlmacen()
{
	INT_PTR status;

	m_dlgBusquedaAlmacen.SetTipo(CDialogBusqueda::ALMACEN);
	status = m_dlgBusquedaAlmacen.DoModal();
	if (status == IDOK)
	{
		m_strAlmacen = m_dlgBusquedaAlmacen.GetCodigo().Trim();
		m_strDesAlmacen = m_dlgBusquedaAlmacen.GetDescripcion().Trim();
	}	

	if (!m_strAlmacen.IsEmpty())
	{
		GetDlgItem(IDC_ALMACEN)->SetWindowText(m_strAlmacen);
		GetDlgItem(IDC_DES_ALMACEN)->SetWindowText(m_strDesAlmacen);

		// El botón de buscar se habilita si es un pedido o albarán
		// y también hay proveedor
		if (!m_strProveedor.IsEmpty())
			GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);

		// Si hubiera ya artículos se comprueba si hay disponibilidad de ellos
		//CompruebaDisponibilidadArticulos();
		// Si no hay disponibilidad de algún artículo, se advierte
		//if (!m_lArtiNoDisponible.IsEmpty())
		//	MuestraAviso();
	}

}
/*******************************************************************************************************/
void CComprasDlg::OnEnKillfocusAlmacen()
{
	CString strAuxAlmacen = m_strAlmacen;

	GetDlgItem(IDC_ALMACEN)->GetWindowText(m_strAlmacen);

	if (!m_strAlmacen.IsEmpty())
	{
		// Si el Almacen no existe se deja el anterior y se da un mensaje de error
		if (!BuscaAlmacen())
		{
			//AfxMessageBox(IDS_ALMACEN_NO_EXISTE);
			m_strAlmacen = strAuxAlmacen;
			GetDlgItem(IDC_ALMACEN)->SetWindowText(m_strAlmacen);
		}
	}
	else
	{	//LimpiaAlmacen();
		m_strAlmacen.Empty();
		m_strDesAlmacen.Empty();

		GetDlgItem(IDC_ALMACEN)->SetWindowText(m_strAlmacen);
		GetDlgItem(IDC_DES_ALMACEN)->SetWindowText(m_strDesAlmacen);
	}
}
/*******************************************************************************************************/
BOOL CComprasDlg::BuscaAlmacen()
{
	BOOL bExists = FALSE;
	CCuentas rsAlmacen(m_db);

	rsAlmacen.m_strFilter = "CUENTA LIKE '" + m_strAlmacen + "'";
	if (!rsAlmacen.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	// Si el centro existe se rellena la descripción 
	if (!rsAlmacen.m_CUENTA.IsEmpty())
	{
		m_strDesAlmacen =  rsAlmacen.m_NOMBRE.Trim();
		bExists = TRUE;

		if (!m_strProveedor.IsEmpty())
			GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);
	}

	rsAlmacen.Close();

	GetDlgItem(IDC_ALMACEN)->SetWindowText(m_strAlmacen);
	GetDlgItem(IDC_DES_ALMACEN)->SetWindowText(m_strDesAlmacen);

	//UpdateData(FALSE);

	return bExists;
}
/*******************************************************************************************************/
void CComprasDlg::OnBnClickedOk()
{
	if (m_iTipo == GESTCOMPRAS)
	{
        // Si alguna casilla del CListCtrl se ha quedado editable se quita
		if (m_lstArticulos.m_ptEditting.x != -1)
			m_lstArticulos.EndEdit(); 
		
		UpdateData();
		GuardaCompra();
	}
	if (m_iTipo == GESTALBARAN)
	{
		Buscar();
	}
}
/*******************************************************************************************************/
void CComprasDlg::GuardaCompra()
{
	HRESULT hErr = S_OK;

	CConta rsConta(m_db);
	CArtiCompra rsArtiCompra(m_db);
	CStringList lAlbaranes;
	CString strNextNumCompra;

	bAlbaranesBorrados = FALSE;//sirve para poner el cartel de los albaranes borrados
	RellenaCompra();// Se rellenan los campos del pedido con lo que contienen los editbox
	// Se crea la transaccion de la compra y luego se insertan cada uno de los artículos que lo componen
	if (!m_db->BeginTrans())
		return;
	// Si es un nuevo registro se inserta, si ya existe se actualiza y se eliminan todos
	// los artículos que pudiera tener y se insertan los que tiene actualmente
	if (m_bNuevo)
	{
		// Se coge el siguiente número de pedido
		hErr = rsConta.GetNextNumPedidoCompra(strNextNumCompra);
		if (hErr == S_OK)
		{
			m_rsCompras.m_NPEDCOM = strNextNumCompra.Trim();
			hErr = m_rsCompras.Insert();
		}
	}
	else
	{	
		if (BuscaAlbaranes(&lAlbaranes))//si hay albaranes para este pedido se eliminan
		{
			hErr = EliminaAlbaranes(&lAlbaranes, m_rsAlbaranC.m_ALMACEN);
			bAlbaranesBorrados = TRUE;
		}
		if (hErr == S_OK)//si se eliminan bien los albaranes
		{
			//tanto si tenia albaranes hechos como si no, se actualiza el pedido y se borran los articulos que
			//pudiese tener
			hErr = m_rsCompras.UpdateCompra();
			if (hErr == S_OK)
			{
				rsArtiCompra.m_NPEDCOM = m_rsCompras.m_NPEDCOM.Trim();
				hErr = rsArtiCompra.DeleteArtiCompra();
			}
		}
	}
	//Se insertan los articulos para este pedido
	if (hErr == S_OK)
	{	
		for (int i=0; i< m_lstArticulos.GetItemCount()-1 && hErr == S_OK;i++)
		{
			rsArtiCompra.m_NPEDCOM = m_rsCompras.m_NPEDCOM.Trim();
			rsArtiCompra.m_ARTI = m_lstArticulos.GetItemText(i, 0);
			rsArtiCompra.m_DESARTI = m_lstArticulos.GetItemText(i, 1);
			rsArtiCompra.m_CANTI = atof(m_lstArticulos.GetItemText(i, 2));
			rsArtiCompra.m_IMPOARTI = atof(m_lstArticulos.GetItemText(i, 3));
			rsArtiCompra.m_DTOARTI = atof(m_lstArticulos.GetItemText(i, 4));
			rsArtiCompra.m_IVARTI = atof(m_lstArticulos.GetItemText(i, 5));
			rsArtiCompra.m_DESARMEMO = m_lstArticulos.GetItemText(i, 6);
			rsArtiCompra.m_RECIBIDOS = 0;

			hErr = rsArtiCompra.Insert();
		}
	}
	//Si todo ha ido bien
	if (hErr == S_OK)
	{
		m_db->CommitTrans();
		CString strMsg, strAlbaranes;
		if (m_bNuevo)
		{
			strMsg.Format(IDS_PEDIDO, m_rsCompras.m_NPEDCOM);
			AfxMessageBox(strMsg,MB_ICONINFORMATION);
		}
		else if(bAlbaranesBorrados == TRUE)
			{
				for (int i=0; i<lAlbaranes.GetCount(); i++)
					strAlbaranes += " " + lAlbaranes.GetAt(lAlbaranes.FindIndex(i)).Trim() + ",";
				strAlbaranes = strAlbaranes.Left(strAlbaranes.GetLength()-1); // Se le quita la última coma
				strMsg.Format(IDS_MODIFICACION_PEDIDO, m_rsCompras.m_NPEDCOM, strAlbaranes);
				AfxMessageBox(strMsg);
			}
			else//No se han borrado albaranes
			{
				CString strMsg;
				strMsg.Format(IDS_PEDIDOMODIFICADO, m_rsCompras.m_NPEDCOM.Trim()); 
				AfxMessageBox(strMsg, MB_ICONINFORMATION);
			}
	}
	else
		m_db->Rollback();

	LimpiaVentana();

	UpdateData(TRUE);

	rsConta.Close();
	rsArtiCompra.Close();
}
/************************************************************************************************************/
BOOL CComprasDlg::BuscaAlbaranes(CStringList *lAlbaranes)
{
	BOOL bExists = FALSE;

	CAlbCompra rsAlbaran(m_db);

	rsAlbaran.m_strFilter = "NPEDCOM LIKE '" + m_rsCompras.m_NPEDCOM + "'";
	if (!rsAlbaran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}

	while (!rsAlbaran.IsEOF())
	{
		lAlbaranes->AddTail(rsAlbaran.m_NALBCOM);
		rsAlbaran.MoveNext();
	}

	// Si al menos hay 1 albaran para el pedido de compra se indica con el flag
	if (lAlbaranes->GetCount() >= 1)
		bExists = TRUE;

	return bExists;
}

/************************************************************************************************************/
HRESULT CComprasDlg::EliminaAlbaranes(CStringList *lNumAlbaran, CString strAlmacen)
{
	HRESULT hErr = S_OK;
	CInventario rsInventario(m_db);
	CArtiAlbCompra rsArtiAlbCompra(m_db);
	CArtiCompra rsArtiCompra(m_db);
	CAlmacen rsAlmacen(m_db);

	for (int iIndex=0; iIndex<lNumAlbaran->GetCount() && hErr == S_OK; iIndex++)
	{
		m_rsAlbaranC.m_NALBCOM = lNumAlbaran->GetAt(lNumAlbaran->FindIndex(iIndex));
		m_rsAlbaranC.m_NALBCOM = m_rsAlbaranC.m_NALBCOM.Trim();

		// Se elimina el albarán de la tabla
		hErr = m_rsAlbaranC.DeleteAlbCompra();

		// Se actualiza el inventario, devolviendo las unidades que se habían cogido de cada
		// articulo.
		rsArtiAlbCompra.m_strFilter = "NALBCOM = '" + m_rsAlbaranC.m_NALBCOM + "'";
		if (!rsArtiAlbCompra.Open(CRecordset::dynaset))
			hErr = -1;

		if (hErr == S_OK)
		{
			for (int i=0; i<rsArtiAlbCompra.GetRecordCount() && hErr == S_OK; i++)
			{
				rsInventario.m_strFilter = "ARTI = '" + rsArtiAlbCompra.m_ARTI.Trim()
					+ "' AND ALMACEN = '" + m_strAlmacen + "'";
					if (!rsInventario.Open(CRecordset::dynaset))
						hErr = -1;
					
					if (hErr == S_OK)
					{		
						if (!rsInventario.m_ARTI.IsEmpty())
						{
							rsInventario.m_UNIDISPONIBLE -= (int)rsArtiAlbCompra.m_CANTI;
							hErr = rsInventario.UpdateUniDisponible();

							if (hErr == S_OK)
							{
								rsInventario.m_UNITOTAL -= (int)rsArtiAlbCompra.m_CANTI;
								hErr = rsInventario.UpdateUniTotal();
							}
						}
					}
					rsInventario.Close();
					// Se inicializan a 0 los enviados del Fpedido
					rsArtiCompra.m_NPEDCOM = m_rsCompras.m_NPEDCOM;
					rsArtiCompra.m_ARTI = rsArtiAlbCompra.m_ARTI.Trim();
					rsArtiCompra.m_RECIBIDOS = 0;
					hErr = rsArtiCompra.UpdateRecibidos();

					rsArtiAlbCompra.MoveNext();
			}

			rsArtiAlbCompra.Close();
		}

		// Se eliminan los artículos del albarán
		if (hErr == S_OK)
		{
			rsArtiAlbCompra.m_NALBCOM = m_rsAlbaranC.m_NALBCOM;
			hErr = rsArtiAlbCompra.DeleteArtiAlbCompra();
		}

		// Se eliminan los movimientos de albarán del albarán
		if (hErr == S_OK)
		{
			rsAlmacen.m_NDOC =  atof(m_rsAlbaranC.m_NALBCOM);
			hErr = rsAlmacen.DeleteMovientosAlbaran();
		}
	/*if (hErr == S_OK)
		m_db->CommitTrans();
	else
		m_db->Rollback();*/
	}
	return hErr;

}
/*******************************************************************************************************/
void CComprasDlg::RellenaAlbaran()
{
	m_rsAlbaranC.m_strFilter="NALBCOM LIKE '" + m_strPedido + "'";
	if (!m_rsAlbaranC.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return ;
	}
	if (m_rsAlbaranC.m_EXPORTA == "S")
		m_bTipo = 0;
	else if (m_rsAlbaranC.m_EXPORTA == "N")
		m_bTipo = 1;

	m_strProveedor=m_rsAlbaranC.m_CUENTA.Trim();
	m_strFPagCob = m_rsAlbaranC.m_FCOBRO.Trim();
	m_strAlmacen = m_rsAlbaranC.m_ALMACEN.Trim();
	m_dNPagos = m_rsAlbaranC.m_NCOBROS;
	m_dPago = m_rsAlbaranC.m_VTO1;
	m_dDiasDescuento = m_rsAlbaranC.m_DVTO;
	m_dDiaPago1 = m_rsAlbaranC.m_DIA1;
	m_dDiaPago2 = m_rsAlbaranC.m_DIA2;
	m_dDiaPago3 = m_rsAlbaranC.m_DIA3;
	/*m_dDescuento1*/m_strDtoGeneral.Format("%2.f",m_rsAlbaranC.m_DCTOS);
	m_dDescuento2 = m_rsAlbaranC.m_DCTO2;
	m_dDescuento3 = m_rsAlbaranC.m_DCTO3;
	m_strPP.Format("%2.f",m_rsAlbaranC.m_PP);
	m_timeFech = m_rsAlbaranC.m_FECHALB;
	m_strCentro = m_rsAlbaranC.m_CENTRO.Trim();
	m_strReferencia = m_rsAlbaranC.m_SREF .Trim();
	m_strObsped = m_rsAlbaranC.m_OBSALB.Trim();
	m_rsAlbaranC.Close();
	CFPagCob rsPago(m_db);
	rsPago.m_strFilter = "FCOBRO LIKE '"+ m_strFPagCob +"'";
	if (!rsPago.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	m_strDesFPagCob=rsPago.m_DFCOBRO.Trim();
	rsPago.Close();
	UpdateData(FALSE);
}
/*******************************************************************************************************/
void CComprasDlg::RellenaCompra()
{
	UpdateData(TRUE);

	if (m_iTipo == 0)
		m_rsCompras.m_EXPORTA = "N";
	else if (m_iTipo == 1)
		m_rsCompras.m_EXPORTA = "S";

	m_rsCompras.m_CUENTA = m_strProveedor.Trim();
	m_rsCompras.m_FCOBRO = m_strFPagCob.Trim();
	m_rsCompras.m_NCOBROS = m_dNPagos;
	m_rsCompras.m_VTO1 = m_dPago;
	m_rsCompras.m_DVTO = m_dDiasDescuento;
	m_rsCompras.m_DIA1 = m_dDiaPago1;
	m_rsCompras.m_DIA2 = m_dDiaPago2;
	m_rsCompras.m_DIA3 = m_dDiaPago3;
	m_rsCompras.m_DCTOS = atof(m_strDtoGeneral);// m_dDescuento1;
	m_rsCompras.m_DCTO2 = m_dDescuento2;
	m_rsCompras.m_DCTO3 = m_dDescuento3;
	m_rsCompras.m_PP = atof(m_strPP);
	m_rsCompras.m_FECHPED = m_timeFech;
	m_rsCompras.m_CENTRO = m_strCentro.Trim();
	m_rsCompras.m_SREF = m_strReferencia.Trim();
	m_rsCompras.m_OBSPED = m_strObsped.Trim();
	m_rsCompras.m_ALMACEN = m_strAlmacen;
	//m_rsCompras.m_DCTOGEN = dDtoGeneral;
}
/******************************************************************************************/
void CComprasDlg::LimpiaVentana()
{
	m_bNuevo = TRUE;
	// Si estaba a Read Only se vuelven a inicializar el flag
	if (m_bReadOnly)
	{
		m_bReadOnly = FALSE;
		// Si alguna casilla del CListCtrl se ha quedado editable se quita
		if (m_lstArticulos.m_ptEditting.x != -1)
			m_lstArticulos.EndEdit();
	}
	m_strProveedor.Empty();
	m_strDesProveedor.Empty();
	m_strDireccion.Empty();
	m_strNumero.Empty();
	m_strCP.Empty();
	m_strPoblacion.Empty();
	m_strObservaciones.Empty();
	m_strTelefono.Empty();
	m_strFax.Empty();
	m_strAlmacen.Empty();
	m_strDesAlmacen.Empty();
	m_strCentro.Empty();
	m_strDesCentro.Empty();
	m_bTipo='S';
	m_strFPagCob.Empty();
	m_strDesFPagCob.Empty();
	m_dNPagos=NULL;
	m_dPago=NULL;
	m_dDiaPago1=NULL;
	m_dDiaPago2=NULL;
	m_dDiaPago3=NULL;
	m_strPP.Empty();
	m_dDiasDescuento=NULL;
	//m_dDescuento1=NULL;
	m_strDtoGeneral.Empty();
	m_dDescuento2=NULL;
	m_dDescuento3=NULL;
	m_strObsped.Empty();
	m_strReferencia.Empty();
	m_timeFech= CTime::GetCurrentTime();
	dDtoGeneral = 0;
	m_strDtoGeneral.Empty();

	m_lstArticulos.DeleteAllItems();
//	m_lIniCantidad.RemoveAll();
	m_lArtiEliminados.RemoveAll();
	m_lOldCantidad.RemoveAll();
	m_lOldTarifa.RemoveAll();
	m_lOldDto.RemoveAll();

	InsertaRegistroVacio();
	m_iNumArti = 0;
	m_dTotalBruto=0;
	m_strTotalBruto.Format("%.2f",m_dTotalBruto);
	
	SetWindowText(m_strTitulo);
	
	UpdateData(FALSE);

	GetDlgItem(ID_BUSCAR)->EnableWindow(FALSE);
	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);

	GetDlgItem(IDOK)->EnableWindow(FALSE);
}
/******************************************************************************************/
void CComprasDlg::OnBnClickedModificar()
{
	Buscar();
}
/******************************************************************************************/
void CComprasDlg::Buscar()
{
	INT_PTR status;

	CDlgBuscaCompra dlgBuscaCompra;
	dlgBuscaCompra.SetConexion(m_db);
	dlgBuscaCompra.SetTipo(m_iTipo);
	status = dlgBuscaCompra.DoModal();
	if (status == IDOK)
	{
		LimpiaVentana();
		m_strPedido = dlgBuscaCompra.GetNumCompra();

		if (m_iTipo == GESTCOMPRAS)
		{
			if (BuscaCompra(m_strPedido))
			{
				m_rsCompras.m_NPEDCOM=m_strPedido;
				m_bNuevo = FALSE;
				// Se indica en el título de la ventana el número de oferta		
				SetWindowText(m_strTitulo + "  -  " + "Número de Pedido: " + m_strPedido);
				//m_bReadOnly = FALSE;	
				if (m_strAlmacen && m_strCentro)
					GetDlgItem(ID_BUSCAR)->EnableWindow(TRUE);
			}
		}
		else if (m_iTipo == GESTALBARAN)
		{//El albaran siempre existirá
			SetWindowText(m_strTitulo + "  -  " + "Número de Albarán: " + m_strPedido);
			RellenaAlbaran();
			BuscaDatosPersonales(m_strProveedor);
			BuscaCentro();
			BuscaAlmacen();
			BuscarArtiAlb();
			UpdateData(FALSE);
		}

	}
	m_bNuevo = FALSE;
}
/******************************************************************************************/
void CComprasDlg::OnBnClickedNuevo()
{
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CUENTA)->EnableWindow(TRUE);//y el de cuenta
	GetDlgItem(IDC_PROVEEDOR)->EnableWindow(TRUE);//y su edit box
	GetDlgItem(IDC_ALMACEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_ALMACEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_CENTRO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CENTRO)->EnableWindow(TRUE);
	GetDlgItem(IDC_OBSPED)->EnableWindow(TRUE);
	GetDlgItem(IDC_REFERENCIA)->EnableWindow(TRUE);
	GetDlgItem(IDC_FECHA)->EnableWindow(TRUE);
	GetDlgItem(IDC_LIST_ARTICULOS)->EnableWindow(TRUE);
	LimpiaVentana();
}
/******************************************************************************************/
BOOL CComprasDlg::BuscaCompra(CString strCodCompra)
{
	BOOL bExists = FALSE;
	CCompras rsCompra(m_db);

	rsCompra.m_strFilter = "NPEDCOM LIKE '" + strCodCompra + "'";
	if (!rsCompra.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	// Si el cliente existe se rellenan sus campos 
	if (!rsCompra.m_CUENTA.IsEmpty())
	{
		m_strProveedor=rsCompra.m_CUENTA.Trim();
		BuscaDatosPersonales(m_strProveedor);//Busca los datos personales del proveedor//
		m_strFPagCob=rsCompra.m_FCOBRO.TrimRight();
		//BUSCA EN LA TABLA fpagcob LA DESCRIPCION//
		CFPagCob rsPago(m_db);
		rsPago.m_strFilter = "FCOBRO LIKE '"+ m_strFPagCob +"'";
		if (!rsPago.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDS_ERROR_BD);
			return FALSE;
		}
		m_strDesFPagCob=rsPago.m_DFCOBRO.Trim();
		rsPago.Close();
		////////////////////////////////////////////
		m_timeFech=rsCompra.m_FECHPED;
		m_dNPagos=rsCompra.m_NCOBROS;
		m_dDiasDescuento=rsCompra.m_DVTO;
		/*m_dDescuento1*/m_strDtoGeneral.Format("%2.f",rsCompra.m_DCTOS);
		m_dDescuento2=rsCompra.m_DCTO2;
		m_dDescuento3=rsCompra.m_DCTO3;
		m_dPago=rsCompra.m_VTO1;
		m_dDiaPago1=rsCompra.m_DIA1;
		m_dDiaPago2=rsCompra.m_DIA2;
		m_dDiaPago3=rsCompra.m_DIA3;
		m_strPP.Format("%2.f",rsCompra.m_PP);
		m_strCentro=rsCompra.m_CENTRO.Trim();
		BuscaCentro();
		m_strAlmacen=rsCompra.m_ALMACEN.Trim();
		BuscaAlmacen();
		m_strObsped=rsCompra.m_OBSPED.Trim();
		m_strReferencia=rsCompra.m_SREF.Trim();
		if (m_rsCompras.m_EXPORTA == "S")
			m_bTipo = 1;
		else //if (m_rsCompras.m_EXPORTA = "N")
			m_bTipo = 0;

		bExists=TRUE;
		GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
	rsCompra.Close();
	BuscaArticulosPedido(strCodCompra);

	UpdateData(FALSE);
	return bExists;
}
/************************************************************************************************/
void CComprasDlg::BuscaDatosPersonales(CString strProveedor)
{
	CProve rsProve(m_db);

	rsProve.m_strFilter = "CUENTA LIKE '" + strProveedor + "'";
	if (!rsProve.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}
	// Si el cliente existe se rellenan sus campos 
	if (!rsProve.m_CUENTA.IsEmpty())
	{
		m_strDesProveedor=rsProve.m_NOMFICHA.Trim();
		m_strDireccion=rsProve.m_DIRECCION.TrimRight();
		m_strNumero=rsProve.m_NUMERO.TrimRight();
		m_strCP=rsProve.m_CP.TrimRight();
		m_strPoblacion=rsProve.m_POBLACION.TrimRight();
		m_strObservaciones=rsProve.m_OBSER1.TrimRight();
		m_strTelefono=rsProve.m_TELEFONO.TrimRight();
		m_strFax=rsProve.m_FAX.TrimRight();
	}
	rsProve.Close();
	UpdateData(FALSE);
}
/******************************************************************************************/
void CComprasDlg::OnBnClickedEmitir()
{
	if (m_iTipo==GESTCOMPRAS)
	//si estamos en compras, el check actua como emision de pedidos
		if (!m_bEmitir1)
			m_bEmitir1=TRUE;
		else
			m_bEmitir1=FALSE;
	else
	//si no, el check actua como recibir albarán
		if (!m_bEmitir2)
			m_bEmitir2=TRUE;
		else
			m_bEmitir2=FALSE;

}
/******************************************************************************************/
void CComprasDlg::OnBnClickedRecibir()
{
	if (m_iTipo==GESTCOMPRAS)
	//si estamos en compras, el check actua como emision de pedidos
		if (!m_bEmitir2)
			m_bEmitir2=TRUE;
		else
			m_bEmitir2=FALSE;
	else
	//si no, el check actua como recibir albarán
		if (!m_bEmitir3)
			m_bEmitir3=TRUE;
		else
			m_bEmitir3=FALSE;
}
/******************************************************************************************/
void CComprasDlg::OnBnClickedConformar()
{
	if (!m_bEmitir3)
		m_bEmitir3=TRUE;
	else
		m_bEmitir3=FALSE;
}
/******************************************************************************************/
void CComprasDlg::OnBnClickedBuscar()
{
INT_PTR status;

	if (m_strProveedor.IsEmpty())
	{
		AfxMessageBox(IDS_NO_PROVEEDOR);
		return;
	}

	if (m_iTipo != GESTCOMPRAS && m_strAlmacen.IsEmpty())
	{
		AfxMessageBox(IDS_NO_ALMACEN);
		return;
	}

	m_dlgBusquedaArticulos.SetTipo(CDialogBusqueda::ARTICULOS);

	//TRY
	//{
		status = m_dlgBusquedaArticulos.DoModal();
	//}
	/*CATCH (CDBException, exp)
	{
		CString strError;
		exp->GetErrorMessage(strError.GetBuffer(60), 15);
		strError.ReleaseBuffer(60);
	}
	END_CATCH*/

	if (status == IDOK)
	{
		CString strCodArti = m_dlgBusquedaArticulos.GetCodigo();

		/* Busca la obra y se escribe en el listCtrl */
		if (!strCodArti.IsEmpty())
			BuscaArticulo(strCodArti);
	}
}
/**************************************************************************************/
void CComprasDlg::OnBnClickedEliminar()
{
	int iIndex;

	// Se busca el indice de la fila a eliminar
	POSITION pos = m_lstArticulos.GetFirstSelectedItemPosition();
	iIndex = m_lstArticulos.GetNextSelectedItem(pos);            
	////////////////////////////////////////////////////////////////////////////////
	// Se resta el PRECIO del total
	int iCantidad = atoi(m_lstArticulos.GetItemText(iIndex, 2));
	double dTarifa = atof(m_lstArticulos.GetItemText(iIndex, 3));
	double dDto = atof(m_lstArticulos.GetItemText(iIndex, 4));

	// Primero se debe restar el precio que suponía con la tarifa anterior.
	double dPrecioAnterior = iCantidad * dTarifa * (1 - (dDto / 100)) * (1 - (atof(m_strDtoGeneral)/100));
	m_dTotalBruto -= dPrecioAnterior;

	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_TOTALBRUTO)->SetWindowText(m_strTotalBruto);
	// Se elimina el artículo
	m_lstArticulos.DeleteItem(iIndex);
	
	// Se elimina de las listas de cantidades antiguas
	m_lOldCantidad.RemoveAt(m_lOldCantidad.FindIndex(iIndex));
	m_lOldTarifa.RemoveAt(m_lOldTarifa.FindIndex(iIndex));
	m_lOldDto.RemoveAt(m_lOldDto.FindIndex(iIndex));

	m_iNumArti--;

	GetDlgItem(ID_ELIMINAR)->EnableWindow(FALSE);
}
/**********************************************************************************************/
void CComprasDlg::BuscarArtiAlb()
{
	CArtiAlbCompra m_rsArtiAlbCompra(m_db);

	m_rsArtiAlbCompra.m_strFilter = "NALBCOM LIKE '" + m_strPedido + "'";
	if (!m_rsArtiAlbCompra.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return;
	}

	m_lstArticulos.DeleteAllItems();
//	m_lEnvioSoloLectura.RemoveAll();

	// Si el pedido tiene artículos se rellena el listCtrl
	int iIndice = 0;
	m_rsArtiAlbCompra.MoveFirst();
	while (!m_rsArtiAlbCompra.IsEOF())
	{
		//Código del Articulo
		m_lstArticulos.InsertItem(iIndice, _T(""));
		m_lstArticulos.SetItemText(iIndice, 0, m_rsArtiAlbCompra.m_ARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 0, RGB(183, 183, 183), TRUE);
		//Descripción del Articulo
		m_lstArticulos.SetItemText(iIndice, 1, m_rsArtiAlbCompra.m_DESARTI.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 1, RGB(183, 183, 183), TRUE);
		//Cantidad que se trajo en el albaran actual
		CString strPedidos;
		strPedidos.Format("%g", m_rsArtiAlbCompra.m_CANTI);
		m_lstArticulos.SetItemText(iIndice, 2, strPedidos);
		m_lstArticulos.SetItemBkColor(iIndice, 2, RGB(183, 183, 183), TRUE);
		//Importe del Articulo
		CString strImporte;
		strImporte.Format("%g", m_rsArtiAlbCompra.m_IMPOARTI);
		m_lstArticulos.SetItemText(iIndice, 3, strImporte);
		m_lstArticulos.SetItemBkColor(iIndice, 3, RGB(183, 183, 183), TRUE);
		//Descuento del Articulo
		CString strDescuento;
		strDescuento.Format("%g", m_rsArtiAlbCompra.m_DTOARTI);
		m_lstArticulos.SetItemText(iIndice, 4, strDescuento);
		m_lstArticulos.SetItemBkColor(iIndice, 4, RGB(183, 183, 183), TRUE);
		//IVA del Articulo
		CString strIVA;
		strIVA.Format("%g", m_rsArtiAlbCompra.m_IVARTI);
		m_lstArticulos.SetItemText(iIndice, 5, strIVA);
		m_lstArticulos.SetItemBkColor(iIndice, 5, RGB(183, 183, 183), TRUE);
		//Descripción detallada del Articulo
		m_lstArticulos.SetItemText(iIndice, 6, m_rsArtiAlbCompra.m_DESARMEMO.Trim());
		m_lstArticulos.SetItemBkColor(iIndice, 6, RGB(183, 183, 183), TRUE);
		//////////////////
		m_dTotalBruto += m_rsArtiAlbCompra.m_CANTI * m_rsArtiAlbCompra.m_IMPOARTI * (1 - (m_rsArtiAlbCompra.m_DTOARTI / 100)) * (1 - (atof(m_strDtoGeneral)/100));

		iIndice ++;
		m_rsArtiAlbCompra.MoveNext();
	}

	m_rsArtiAlbCompra.Close();
	m_strTotalBruto.Empty();
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_TOTALBRUTO)->SetWindowText(m_strTotalBruto);
	UpdateData(TRUE);
}
/*********************************************************************************************/
void CComprasDlg::OnEnKillfocusDescuento1()
{
//	double dBaseImponible;
	CString Aux;
	Aux=m_strDtoGeneral;
	GetDlgItem(IDC_DESCUENTO1/*DTOGENERAL*/)->GetWindowText(m_strDtoGeneral);
	if(!CompruebaNumero(m_strDtoGeneral))
	{
		m_strDtoGeneral=Aux;
		GetDlgItem(IDC_DESCUENTO1)->SetWindowText(m_strDtoGeneral);
		GetDlgItem(IDC_DESCUENTO1)->SetFocus();
		return;
	}
	GetDlgItem(IDC_DESCUENTO1)->SetWindowText(m_strDtoGeneral);
	/*CString strDtoOld;
	if (m_strDtoGeneral!="")
		strDtoOld=m_strDtoGeneral;
	else
		strDtoOld="0";
	

	dBaseImponible = m_dTotalBruto / (1-(atof(strDtoOld)/100));//se obtiene el valor burto sin el descuento anterior
	m_dTotalBruto=dBaseImponible * (1 - (atof(m_strDtoGeneral)/100));//se calcula el nuevo valor bruto
	m_strTotalBruto.Format("%.2f", m_dTotalBruto);
	GetDlgItem(IDC_TOTALBRUTO)->SetWindowText(m_strTotalBruto);*/
}
/*********************************************************************************************/
void CComprasDlg::OnEnKillfocusPp()
{
	CString Aux;
	Aux=m_strPP;
	GetDlgItem(IDC_PP)->GetWindowText(m_strPP);
	if(!CompruebaNumero(m_strPP))
	{
		m_strPP=Aux;
		GetDlgItem(IDC_PP)->SetWindowText(m_strPP);
		GetDlgItem(IDC_PP)->SetFocus();
		return;
	}
}
/*********************************************************************************************/
void CComprasDlg::OnBnClickedBtnFpagcob()
{
	INT_PTR Estado;
	m_dlgBusquedaFpagcob.SetTipo(CDialogBusqueda::FPAGCOB);
	Estado=m_dlgBusquedaFpagcob.DoModal();
	if (Estado==IDCANCEL)
	{
		return;
	}
	m_strFPagCob=m_dlgBusquedaFpagcob.GetCodigo();
	GetDlgItem(IDC_FPAGCOB)->SetWindowText(m_strFPagCob);
	m_strDesFPagCob=m_dlgBusquedaFpagcob.GetDescripcion();
	GetDlgItem(IDC_DES_FPAGCOB)->SetWindowText(m_strDesFPagCob);
}
/*********************************************************************************************/
void CComprasDlg::OnEnKillfocusFpagcob()
{
	CString strAux=m_strFPagCob;
	GetDlgItem(IDC_FPAGCOB)->GetWindowText(m_strFPagCob);
	if (m_strFPagCob.IsEmpty())
	{
		m_strDesFPagCob="";
		GetDlgItem(IDC_DES_FPAGCOB)->SetWindowText(m_strDesFPagCob);
		return;
	}
	if (m_strFPagCob==strAux)
	{return;}
	if (BuscaCobro(m_strFPagCob)==FALSE)
	{
		m_strFPagCob=strAux;
		GetDlgItem(IDC_FPAGCOB)->SetWindowText(m_strFPagCob);
	}
	else
	{GetDlgItem(IDC_DES_FPAGCOB)->SetWindowText(m_strDesFPagCob);return;}
}
/*********************************************************************************************/
BOOL CComprasDlg::BuscaCobro(CString cadena)
{
	if (cadena.IsEmpty())
		return FALSE;
	CFPagCob rsCobro(m_db);
	rsCobro.m_strFilter="FCOBRO LIKE '" + cadena + "'";
	if (!rsCobro.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDS_ERROR_BD);
		return FALSE;
	}
	if (rsCobro.m_DFCOBRO.IsEmpty())
	{
		rsCobro.Close();
		return FALSE;
	}
	else
	{
		m_strDesFPagCob=rsCobro.m_DFCOBRO.TrimRight();
		rsCobro.Close();
		return TRUE;
	}
}