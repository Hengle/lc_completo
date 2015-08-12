227
%{
#include "StdH.h"
#include "EntitiesMP/GravityMarker.h"
%}

uses "EntitiesMP/Marker";

event EChangeGravity {
  CEntityPointer penNewGravity,
};

class CGravityRouter: CMarker {
name      "Gravity Router";
thumbnail "Thumbnails\\GravityRouter.tbn";
features "IsImportant";

properties:

components:
  1 editor model   MODEL_MARKER     "Data\\Models\\Editor\\GravityRouter.mdl",
  2 editor texture TEXTURE_MARKER   "Data\\Models\\Editor\\GravityRouter.tex"

functions:

  /* Get force type name, return empty string if not used. */
  const CTString &GetForceName(INDEX i)
  {
    return m_strName;
  }
  
  /* Get force in given point. */
  void GetForce(INDEX i, const FLOAT3D &vPoint, 
    CForceStrength &fsGravity, CForceStrength &fsField)
  {
    if( m_penTarget!=NULL && IsOfClass( m_penTarget, &CGravityMarker_DLLClass)) 
    {
      m_penTarget->GetForce(i, vPoint, fsGravity, fsField);
    }
  }
  /* Get entity that controls the force, used for change notification checking. */
  CEntity *GetForceController(INDEX iForce)
  {
    return this;
  }

  /* Handle an event, return false if the event is not handled. */
  BOOL HandleEvent(const CEntityEvent &ee)
  {
    if( ((EChangeGravity &) ee).ee_slEvent==EVENTCODE_EChangeGravity)
    {
      m_penTarget = ((EChangeGravity &) ee).penNewGravity;
      // notify engine that gravity defined by this entity has changed
      NotifyGravityChanged();
      return TRUE;
    }
    return FALSE;
  }

procedures:
  Main()
  {
    InitAsEditorModel();
    SetPhysicsFlags(EPF_MODEL_IMMATERIAL);
    SetCollisionFlags(ECF_IMMATERIAL);

    // set appearance
    SetModel(MODEL_MARKER);
    SetModelMainTexture(TEXTURE_MARKER);

    // set name
    if (m_strName=="Marker") {
      m_strName = "Gravity Router";
    }

    if( m_penTarget!=NULL && !IsOfClass( m_penTarget, &CGravityMarker_DLLClass)) {
      WarningMessage( "Entity '%s' is not of Gravity Marker class!", m_penTarget);
      m_penTarget = NULL;
    }

    return;
  }
};

