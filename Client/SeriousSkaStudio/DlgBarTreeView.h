// DlgBarTreeView.h: interface for the CDlgBarTreeView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGBARTREEVIEW_H__97A19AEB_ACE0_11D5_8AB4_00C0262D9BFE__INCLUDED_)
#define AFX_DLGBARTREEVIEW_H__97A19AEB_ACE0_11D5_8AB4_00C0262D9BFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DlgClient.h"
#include "ModelTreeCtrl.h"
#include "Textbox.h"
#include "SplitterFrame.h"
#include "DlgTemplate.h"
#include "TexView.h"

#define GR_PARENT         0
#define GR_ANIMSET        1
#define GR_COLISION       2
#define GR_LOD            3
#define GR_TEXTURE        4
#define GR_LISTOPTIONS    5
#define GR_SHADERS        6
#define GR_ALLFRAMES_BBOX 7
#define GR_BONE           8
//안태훈 수정 시작	//(Add & Modify SSSE Effect)(0.1)
#define GR_SKATAG         9
//안태훈 수정 끝	//(Add & Modify SSSE Effect)(0.1)
//안태훈 수정 시작	//(Effect Add & Modify for Close Beta)(0.1)
#define GR_ANIMEFFECT     10
//안태훈 수정 끝	//(Effect Add & Modify for Close Beta)(0.1)
#define GR_RIDINGPOSITION	11

class Control
{
public:
	Control()
	{
	}

	FLOAT ct_fLeft; // rect
	FLOAT ct_fRight;
	INDEX ct_iTop;
	INDEX ct_iBottom; 
	INDEX ct_iID; // id of control
	CDialog *ct_pParentDlg; // parent dlg
};

class CDlgBarTreeView : public CDlgTemplate
{
public:
	CDlgBarTreeView();
	virtual ~CDlgBarTreeView();

	BOOL Create( CWnd* pParentWnd, UINT nIDTemplate, UINT nStyle, UINT nID);
	CSize CalcDynamicLayout(int nLength, DWORD nMode);
	CSize CalcLayout(int nLength, DWORD nMode);
	void AddDialogControls(CDialog *pDlg);
	void RemoveDialogControls(CDialog *pDlg);
	void AddControlToArray(CWnd *pChild, CDialog *pDlg);
	void RemoveControlFromArray(CWnd *pChild, CDialog *pDlg);
	void ResizeDlgWithChildren(CDialog *pDlg,CRect rcDlg);
	
	NodeInfo &GetNodeInfo(HTREEITEM hItem);
	NodeInfo &GetSelectedNodeInfo();

	void ShowSurfaceShader(MeshSurface *pmsrf,MeshLOD *pmlod,MeshInstance *pmshi);
	void ChangeShaderOnSelectedSurfaces(CTString fnNewShader);
	void ChangeTextureOnSelectedSurfaces(CTString strControlID,CTString strNewTexID);
	void ChangeTextureCoordsOnSelectedSurfaces(CTString strControlID,INDEX iNewTexCoordsIndex);
	void ChangeColorOnSelectedSurfaces(CTString strControlID,COLOR colNewColor);
	void ChangeFloatOnSelectedSurfaces(CTString strControlID,FLOAT fNewFloat);
	void ChangeFlagOnSelectedSurfaces(CTString strControlID,BOOL bChecked,INDEX iFlagIndex);
	void UpdateSurfaceSubSurfaces(const NodeInfo &niSurface);
	BOOL IsSurfaceSelected(MeshSurface &msrf);

	void ChangeColorOnSelectedModel(COLOR colNewColor);

	void VScrollControls(CDialog *pDlg);
	void UpdateModelInstInfo(CModelInstance *pmi);
	void AddSkeleton(CModelInstance &mi, HTREEITEM hParent);
	void AddMeshInstances(CModelInstance &mi,HTREEITEM hParent);
	void AddSurfaces(CModelInstance &mi,MeshLOD &mlod,HTREEITEM hParent);
	void AddWeightMaps(CModelInstance &mi,MeshLOD &mlod,HTREEITEM hParent);
//안태훈 수정 시작	//(Add & Modify SSSE Effect)(0.1)
	void AddSkaTags(CModelInstance &mi,MeshLOD &mlod,HTREEITEM hParent);
//안태훈 수정 끝	//(Add & Modify SSSE Effect)(0.1)
	void AddMorphMaps(CModelInstance &mi,MeshLOD &mlod,HTREEITEM hParent);
	void AddColisionBoxes(CModelInstance &mi,HTREEITEM hParent);
	void AddAllFramesBBox(CModelInstance &mi,HTREEITEM hParent);
	HTREEITEM AddAnimSet(CModelInstance &mi,HTREEITEM hParent);
	HTREEITEM AddModelInst(CModelInstance &mi, CModelInstance *pmiParent, HTREEITEM hParent);
//안태훈 수정 시작	//(Effect Add & Modify for Close Beta)(0.1)
	void AddAnimEffects(CModelInstance &mi,HTREEITEM hParent);
//안태훈 수정 끝	//(Effect Add & Modify for Close Beta)(0.1)
	void AddRideSetting(CModelInstance &mi,HTREEITEM hParent);

	void ExpandAllModelInstances(HTREEITEM hItem);
	
	void ResetControls();

	void SetCustomTabText(char *strText);
	// select dialog to show
	void ShowControlGroup(INDEX iGroup);

	// for reselecting an item after refresh
	BOOL RememberSelectedItem(HTREEITEM hParent,HTREEITEM hSelected);
	// find previously selected item
	BOOL ReselectItem(HTREEITEM hParent);
	// check sec per frame control 
	void CheckSecPerFrameCtrl(BOOL bCheck);

	void SelItemChanged(HTREEITEM hSelected);
	void OnItemClick(HTREEITEM hItem,HTREEITEM hLastSelected);
	void OnItemIconClick(HTREEITEM hItem);
	void TogleSurfaceSelection(HTREEITEM hItem);
	void SelectAllSurfaces(HTREEITEM hItem);
	void DeSelectAllSurfaces(HTREEITEM hParent = NULL);
	void SelectMeshSurface(HTREEITEM hItem);
	void DeselectMeshSurface(HTREEITEM hItem);
	void FillBonesToComboBox(CDlgClient &dlgClient, CSkeleton *pskl,INDEX iSelectedIndex, SINT iComboBoxContorlID);
	void FillParentDropDown(CModelInstance *pmi);

	CModelTreeCtrl  m_TreeCtrl;       // tree view control
	CImageList      m_IconsImageList; // image lis for tree control

	// dialogs
	CDlgClient m_dlgParent;
	CDlgClient m_dlgAnimSet;
	CDlgClient m_dlgColision;
	CDlgClient m_dlgAllFrames;
	CDlgClient m_dlgLod;
	CDlgClient m_dlgBone;
	CDlgClient m_dlgTexture;
	CDlgClient m_dlgListOpt;
	CDlgClient m_dlgShader;
//안태훈 수정 시작	//(Add & Modify SSSE Effect)(0.1)
	CDlgClient m_dlgSkaTag;
//안태훈 수정 끝	//(Add & Modify SSSE Effect)(0.1)
//안태훈 수정 시작	//(Effect Add & Modify for Close Beta)(0.1)
	CDlgClient m_dlgAnimEffect;
//안태훈 수정 끝	//(Effect Add & Modify for Close Beta)(0.1)
	CDlgClient m_dlgRideSet; // Child 모델의 dlgParent 값을 그대로 카피하여 사용.(읽기만 허용)

	CDialog    *pdlgCurrent;

	CTexView   m_tvTexView;

	CStaticStackArray<class Control> dlg_aControls;

	// controls in parent dialog
	CTextBox m_tbOffPosX;
	CTextBox m_tbOffPosY;
	CTextBox m_tbOffPosZ;
	CTextBox m_tbOffRotH;
	CTextBox m_tbOffRotP;
	CTextBox m_tbOffRotB;
	CTextBox m_tbMiName;
	// controls in animset dialog
	CTextBox m_tbTreshold;
	CTextBox m_tbAnimSpeed;
	CTextBox m_tbWalkSpeed;
	CTextBox m_tbWalkLoopSec;
	// controls in colision dialog
	CTextBox m_tbColName;
	CTextBox m_tbColWidth;
	CTextBox m_tbColHeight;
	CTextBox m_tbColLength;
	CTextBox m_tbColPosX;
	CTextBox m_tbColPosY;
	CTextBox m_tbColPosZ;
	// controls in all frames bbox
	CTextBox m_tbAFBBWidth;
	CTextBox m_tbAFBBHeight;
	CTextBox m_tbAFBBLength;
	CTextBox m_tbAFBBPosX;
	CTextBox m_tbAFBBPosY;
	CTextBox m_tbAFBBPosZ;
//안태훈 수정 시작	//(Add & Modify SSSE Effect)(0.1)
	// controls in ska tag
	CTextBox m_tbSTName;
	CTextBox m_tbSTBlendFactor1;
	CTextBox m_tbSTBlendFactor2;
	CTextBox m_tbSTBlendFactor3;
	CTextBox m_tbSTBlendFactor4;
	CTextBox m_tbSTOffsetPosX;
	CTextBox m_tbSTOffsetPosY;
	CTextBox m_tbSTOffsetPosZ;
	CTextBox m_tbSTOffsetRotAxisX;
	CTextBox m_tbSTOffsetRotAxisY;
	CTextBox m_tbSTOffsetRotAxisZ;
	CTextBox m_tbSTOffsetRotAngle;
//안태훈 수정 끝	//(Add & Modify SSSE Effect)(0.1)
//안태훈 수정 시작	//(Effect Add & Modify for Close Beta)(0.1)
	// controls in anim effect
	CTextBox m_tbAEAnimName;
	CTextBox m_tbAEStartTime;
	CTextBox m_tbAEEffectGroupName;
//안태훈 수정 끝	//(Effect Add & Modify for Close Beta)(0.1)

	// controls in lod dialog
	CTextBox m_tbDistance;
	// controls in texture dialog
	CTextBox m_tbTextureName;

//  CSize m_Size;
	// Generated message map functions

protected:
	//{{AFX_MSG(CDlgBarTreeView)
	afx_msg void OnSelchangeModeSelectTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_DLGBARTREEVIEW_H__97A19AEB_ACE0_11D5_8AB4_00C0262D9BFE__INCLUDED_)
