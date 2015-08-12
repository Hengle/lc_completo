// DlgCreateVirtualDirectory.cpp : implementation file
//

#include "stdafx.h"
#include "DlgCreateVirtualDirectory.h"

#ifdef _DEBUG
#undef new
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateVirtualDirectory dialog


CDlgCreateVirtualDirectory::CDlgCreateVirtualDirectory(CTString strOldName /*= ""*/,
              CTString strTitle /*="Create virtual directory"*/, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateVirtualDirectory::IDD, pParent)
{
	m_strTitle = strTitle;
  //{{AFX_DATA_INIT(CDlgCreateVirtualDirectory)
	m_strDirectoryName = _T(strOldName);
	//}}AFX_DATA_INIT
}


void CDlgCreateVirtualDirectory::DoDataExchange(CDataExchange* pDX)
{
	INDEX i;
  CDialog::DoDataExchange(pDX);

  // if dialog is recieving data
  if( pDX->m_bSaveAndValidate == FALSE)
  {
  }

	//{{AFX_DATA_MAP(CDlgCreateVirtualDirectory)
	DDX_Control(pDX, IDC_DIRECTORY_ICON_LIST, m_DirectoryIconsList);
	DDX_Text(pDX, IDC_EDIT1, m_strDirectoryName);
	DDV_MaxChars(pDX, m_strDirectoryName, 32);
	//}}AFX_DATA_MAP

  // if dialog gives data
  if( pDX->m_bSaveAndValidate != FALSE)
  {
    m_strCreatedDirName = CTString( m_strDirectoryName);
    m_iSelectedIconType = 0;
    // Now set selected directory icon type
    for( i=0; i<m_DirectoryIconsList.GetItemCount(); i++)
    {
      if( m_DirectoryIconsList.GetItemState( i, LVIS_SELECTED) != 0)
      {
        m_iSelectedIconType = i;
        break;
      }
    }
  }
}


BEGIN_MESSAGE_MAP(CDlgCreateVirtualDirectory, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateVirtualDirectory)
	ON_NOTIFY(NM_DBLCLK, IDC_DIRECTORY_ICON_LIST, OnDblclkDirectoryIconList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateVirtualDirectory message handlers

BOOL CDlgCreateVirtualDirectory::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  SetWindowText( m_strTitle);

  m_IconsImageList.Create( IDB_DIRECTORY_ICONS, 16, 1, CLR_NONE);
  m_DirectoryIconsList.SetImageList( &m_IconsImageList, LVSIL_SMALL);

  for( INDEX i=0; i<NO_OF_ICONS; i++)
  {
    m_DirectoryIconsList.InsertItem( i, "", i);
  }

  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCreateVirtualDirectory::OnDblclkDirectoryIconList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
  if( m_strCreatedDirName != "")
    EndDialog(IDOK);
	*pResult = 0;
}
