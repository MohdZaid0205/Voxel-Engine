using System;
using System.Runtime.InteropServices;
using System.Windows.Interop;

namespace editor
{
    class EngineEvents
    {
        [DllImport("Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void onEditorButtonClicked(int id);
    }
    
}