#if IPLUG_EDITOR

#include "IControls.h"
#include "PDSynth.h"

IGraphics* PDSynth::CreateGraphics()
{
  return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
}

void PDSynth::LayoutUI(IGraphics* pGraphics)
{
  const IRECT bounds = pGraphics->GetBounds().GetPadded(-10);
  pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
  pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
  pGraphics->AttachPanelBackground(COLOR_DARK_GRAY);
  pGraphics->AttachControl(new ITextControl(bounds.GetFromTLHC(200, 50), "PDSynth", IText(50)));
  pGraphics->AttachControl(new IVKeyboardControl(bounds.GetFromBottom(100)));
  pGraphics->AttachControl(new IVTabSwitchControl(bounds.GetCentredInside(350,50), GetIPlugParamIdx("Shape")));
}

#endif