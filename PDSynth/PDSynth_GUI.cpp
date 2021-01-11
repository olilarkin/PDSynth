#if IPLUG_EDITOR

#include "IControls.h"
#include "PDSynth.h"

IGraphics* PDSynth::CreateGraphics()
{
  return MakeGraphics(*this, PLUG_WIDTH, PLUG_HEIGHT, PLUG_FPS, GetScaleForScreen(PLUG_WIDTH, PLUG_HEIGHT));
}

void PDSynth::LayoutUI(IGraphics* pGraphics)
{
  IRECT bounds = pGraphics->GetBounds().GetPadded(-10);
  pGraphics->AttachCornerResizer(EUIResizerMode::Scale, false);
  pGraphics->LoadFont("Roboto-Regular", ROBOTO_FN);
  
  auto kbArea = bounds.ReduceFromBottom(100);
  auto wheels = kbArea.ReduceFromLeft(100);
  auto panel = bounds.GetPadded(-10.f);
  auto logo = panel.GetGridCell(0, 1, 5);
  auto buttons = panel.GetGridCell(2, 1, 5);
  auto sliders = panel.GetGridCell(4, 1, 5);

  const IVStyle style {
    DEFAULT_SHOW_LABEL,           // show label
    false,           // show value
    {                             // color spec:
      DEFAULT_BGCOLOR,              // Background
      DEFAULT_FGCOLOR,              // Foreground
      DEFAULT_PRCOLOR,              // Pressed
      COLOR_BLACK,                  // Frame
      DEFAULT_HLCOLOR,              // Highlight
      DEFAULT_SHCOLOR,              // Shadow
      IColor::FromHSLA(0.49, 1., 0.5f),                  // Extra 1
      DEFAULT_X2COLOR,              // Extra 2
      DEFAULT_X3COLOR               // Extra 3
    },
    {                             // label text:
      DEFAULT_TEXT_SIZE,            // size
      COLOR_WHITE,         // color
      "Roboto-Regular",             // font
      EAlign::Center,               // horizontal align
      EVAlign::Middle,              // vertical align
      0                             // angle
    },
    {                             // value text:
      DEFAULT_TEXT_SIZE,            // size
      COLOR_BLACK,         // color
      "Roboto-Regular",             // font
      EAlign::Center,               // horizontal align
      EVAlign::Bottom,              // vertical align
      0,                            // angle
      DEFAULT_TEXTENTRY_BGCOLOR,    // text entry BG color
      DEFAULT_TEXTENTRY_FGCOLOR     // text entry text color
    },
    DEFAULT_HIDE_CURSOR,          // hide cursor
    DEFAULT_DRAW_FRAME,           // draw frame
    false,         // draw shadows
    DEFAULT_EMBOSS,               // emboss
    0.1,            // roundness
    DEFAULT_FRAME_THICKNESS,      // frame thickness
    DEFAULT_SHADOW_OFFSET,        // shadow offset
    DEFAULT_WIDGET_FRAC,          // widget fraction
    DEFAULT_WIDGET_ANGLE          // widget angle
  };

  pGraphics->AttachPanelBackground(COLOR_DARK_GRAY);

  pGraphics->AttachControl(new ITextControl(logo.FracRectVertical(0.25, true), "PDSynth", IText(50, COLOR_WHITE)));

  pGraphics->AttachControl(new IVKeyboardControl(kbArea, 36, 72), kCtrlTagKeyboard);
  
//  pGraphics->AttachControl(new ISVGControl(buttons.SubRectVertical(3, 0), pGraphics->LoadSVG(WAVES_FN)));
  pGraphics->AttachControl(new IVTabSwitchControl(buttons.SubRectVertical(3, 0), GetIPlugParamIdx("Shape"), {"0", "1", "2", "3", "4", "5", "6", "7"}, "SHAPE", style));
  pGraphics->AttachControl(new IWheelControl(wheels.FracRectHorizontal(0.5f)));
  pGraphics->AttachControl(new IWheelControl(wheels.FracRectHorizontal(0.5f, true), IMidiMsg::EControlChangeMsg::kModWheel));
  pGraphics->AttachControl(new IVSliderControl(sliders.SubRectHorizontal(4, 0), GetIPlugParamIdx("DCW"), "DCW", style));
  pGraphics->AttachControl(new IVSliderControl(sliders.SubRectHorizontal(4, 1), GetIPlugParamIdx("Volume"), "VOL", style));
  pGraphics->AttachControl(new IVGroupControl(sliders.SubRectHorizontal(4, 3).GetFromRight(10.f), "OUT", 0.f, 0.f));
  pGraphics->AttachControl(new IVLEDMeterControl<>(sliders.SubRectHorizontal(4, 3).GetFromRight(10.f)), kCtrlTagMeter);
  pGraphics->SetQwertyMidiKeyHandlerFunc([pGraphics](const IMidiMsg& msg)
  {
    pGraphics->GetControlWithTag(kCtrlTagKeyboard)->As<IVKeyboardControl>()->SetNoteFromMidi(msg.NoteNumber(), msg.StatusMsg() == IMidiMsg::kNoteOn);
  });
}

#endif
