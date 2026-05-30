using System.Runtime.InteropServices;

namespace Process.Models
{
    [StructLayout(LayoutKind.Sequential, Pack = 4, CharSet = CharSet.Ansi)]
    public struct ProcessInfo
    {
        public uint ProcessId;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string ProcessName;

        public byte IsRunning;
    }
}