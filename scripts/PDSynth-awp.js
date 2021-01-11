/* Declares the PDSynth Audio Worklet Processor */

class PDSynth_AWP extends AudioWorkletGlobalScope.WAMProcessor
{
  constructor(options) {
    options = options || {}
    options.mod = AudioWorkletGlobalScope.WAM.PDSynth;
    super(options);
  }
}

registerProcessor("PDSynth", PDSynth_AWP);
