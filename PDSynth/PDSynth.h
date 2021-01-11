#pragma once

#include "IPlug_include_in_plug_hdr.h"
#include "PDSynth_DSP.h"
#include <map>

const int kNumPresets = 1;

enum ECtrlTags
{
  kCtrlTagMeter = 0
};

using namespace iplug;
using namespace igraphics;
using DSP = PDSynth_DSP;

class PDSynth final : public Plugin
{
public:
  PDSynth(const InstanceInfo& info);

#if IPLUG_EDITOR
  IGraphics* CreateGraphics() override;
  void LayoutUI(IGraphics* pGraphics) override;
#endif

#if IPLUG_DSP
  void ProcessBlock(sample** inputs, sample** outputs, int nFrames) override;
  void ProcessMidiMsg(const IMidiMsg& msg) override;
  void OnReset() override;
  void OnParamChange(int paramIdx) override;
  DSP mDSP;
  int mSessionID = 0;
  IPlugQueue<int> mParamsToUpdate {DSP::numParameters};
  std::vector<DSP::Parameter> mSOULParams;
  std::vector<DSP::MIDIMessage> mIncomingMIDIMessages;
#endif

  int GetIPlugParamIdx(const char* soulParamID) { return mParamMap[soulParamID]; }
  std::map<const char*, int> mParamMap;
};
