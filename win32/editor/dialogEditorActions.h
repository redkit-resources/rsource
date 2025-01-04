#pragma once

enum
{
	wxID_STORYSCENEEDITOR_ADDSECTION = 7500,
	wxID_STORYSCENEEDITOR_DELETESECTION,

	wxID_STORYSCENEEDITOR_ADDLINE,
	wxID_STORYSCENEEDITOR_INSERTLINE,
	wxID_STORYSCENEEDITOR_DELETELINE,
	wxID_STORYSCENEEDITOR_COPYLINE,
	wxID_STORYSCENEEDITOR_CUTLINE,
	wxID_STORYSCENEEDITOR_PASTELINE,

	wxID_STORYSCENEEDITOR_ADDEVENT,
	wxID_STORYSCENEEDITOR_FINDEVENT,
	wxID_STORYSCENEEDITOR_EDITEVENT,
	wxID_STORYSCENEEDITOR_DELETEEVENT,

	wxID_STORYSCENEEDITOR_ADDLINECOMMENT,
	wxID_STORYSCENEEDITOR_EDITLINECOMMENT,

	wxID_STORYSCENEEDITOR_ADDCHOICE,
	wxID_STORYSCENEEDITOR_DELETECHOICELINE,
	wxID_STORYSCENEEDITOR_ADDCHOICELINE,
	wxID_STORYSCENEEDITOR_INSERTCHOICELINE,
	wxID_STORYSCENEEDITOR_MOVECHOICELINEUP,
	wxID_STORYSCENEEDITOR_MOVECHOICELINEDOWN,

	wxID_STORYSCENEEDITOR_ADDCOMMENT,
	wxID_STORYSCENEEDITOR_INSERTCOMMENT,

	wxID_STORYSCENEEDITOR_ADDQUESTCHOICE,

	wxID_STORYSCENEEDITOR_ADDSCRIPTLINE,
	wxID_STORYSCENEEDITOR_INSERTSCRIPTLINE,

	wxID_STORYSCENEEDITOR_CYCLEELEMENTTYPE,
	wxID_STORYSCENEEDITOR_CHANGETOSCENELINE,
	wxID_STORYSCENEEDITOR_CHANGETOCOMMENT,
	wxID_STORYSCENEEDITOR_CHANGETOSCRIPTLINE,
	wxID_STORYSCENEEDITOR_CHANGETOCHOICE,
	wxID_STORYSCENEEDITOR_CHANGETOQUESTCHOICELINE,

	wxID_STORYSCENEEDITOR_CHECKCONSISTENCY,
	wxID_STORYSCENEEDITOR_PASTEHERE,

	wxID_STORYSCENEEDITOR_CUTELEMENTS,
	wxID_STORYSCENEEDITOR_COPYELEMENTS,
	wxID_STORYSCENEEDITOR_PASTEELEMENTS,
	wxID_STORYSCENEEDITOR_CUTSECTIONS,
	wxID_STORYSCENEEDITOR_COPYSECTIONS,
	wxID_STORYSCENEEDITOR_PASTESECTIONS,

	wxID_STORYSCENEEDITOR_SHIFTSECTIONDOWN,
	wxID_STORYSCENEEDITOR_SHIFTSECTIONUP,

	wxID_STORYSCENEEDITOR_REFRESHDIALOG,

	wxID_STORYSCENEEDITOR_LARGERFONT,
	wxID_STORYSCENEEDITOR_SMALLERFONT,
	
	wxID_STORYSCENEEDITOR_OPENCUTSCENEPREVIEW,

	wxID_STORYSCENEEDITOR_MAKE_COPY_UNIQUE,

	wxID_STORYSCENEEDITOR_REC_VOICE_FOR_LINE,

	wxID_STORYSCENEEDITOR_CAMERA_PREVIEW,
	wxID_STORYSCENEEDITOR_CAMERA_FREE,
	wxID_STORYSCENEEDITOR_CAMERA_EDIT,
	wxID_STORYSCENEEDITOR_NEW_KEYFRAME,
	wxID_STORYSCENEEDITOR_PLAY_TOGGLE,
	wxID_STORYSCENEEDITOR_PLAY_FROM_START,
	wxID_STORYSCENEEDITOR_CUT_CLIP,
	wxID_STORYSCENEEDITOR_SET_CLIPPING_FRONT,
	wxID_STORYSCENEEDITOR_SET_CLIPPING_END,
	wxID_STORYSCENEEDITOR_ALIGN_EVENTS_LEFT,
	wxID_STORYSCENEEDITOR_ALIGN_EVENTS_RIGHT,
	wxID_STORYSCENEEDITOR_ALIGN_EVENTS_TO_CAMERA,

	wxID_STORYSCENEEDITOR_VERIFYSCENE,
	wxID_STORYSCENEEDITOR_VERIFYSECTION,
	wxID_STORYSCENEEDITOR_CREATEDIALOGSET_NEW,
	wxID_STORYSCENEEDITOR_CREATEDIALOGSET_FROMFILE,
	wxID_STORYSCENEEDITOR_CREATEDIALOGSET_FROMPREVSECTION,
	wxID_STORYSCENEEDITOR_CREATEDIALOGSET_FROMSELSECTION,	
	wxID_STORYSCENEEDITOR_CLONESECTION,

	wxID_STORYSCENEEDITOR_RECORD,

	wxID_LIGHT_PRESET_LOAD_FIRST,
	wxID_LIGHT_PRESET_LOAD_LAST = wxID_LIGHT_PRESET_LOAD_FIRST + 10,

	wxID_STORYSCENEEDITOR_CHANGEDIALOGSET = 7600,
	wxID_STORYSCENEEDITOR_CHANGEDIALOGSET_LIMIT = 7699,

	wxID_STORYSCENEEDITOR_ADDSCENEBLOCK = 7700,
	wxID_STORYSCENEEDITOR_ADDSCENETEMPLATE = 7800,
	// leave some space, use 7900 for next item
	wxID_STORYSCENEEDITOR_TOGGLEDOF = 7900,
};
