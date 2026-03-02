using System;
using System.Runtime.InteropServices;
using System.Windows.Interop;

namespace editor
{
    public class EngineHost : HwndHost
    {
        [DllImport("Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr InitializeEngineWindow(IntPtr parentHwnd, int width, int height);

        [DllImport("Engine.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RenderFrame();

        protected override HandleRef BuildWindowCore(HandleRef hwndParent)
        {
            IntPtr childHwnd = InitializeEngineWindow(hwndParent.Handle, 800, 600);
            return new HandleRef(this, childHwnd);
        }

        protected override void DestroyWindowCore(HandleRef hwnd)
        {}
    }
}