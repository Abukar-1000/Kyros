using System.Runtime.InteropServices;

public static class BinaryConverter
{
    public static T ByteToStruct<T>(byte[] bytes) where T : struct
    {
        int size = Marshal.SizeOf(typeof(T));
        if (bytes.Length < size)
        {
            throw new ArgumentException("Byte array is too small for this structure.");
        }

        // Allocate unmanaged memory and copy byte array there
        IntPtr ptr = Marshal.AllocHGlobal(size);
        try
        {
            Marshal.Copy(bytes, 0, ptr, size);
            // Marshal the raw unmanaged memory into the C# struct object
            return (T)Marshal.PtrToStructure(ptr, typeof(T))!;
        }
        finally
        {
            // Free the memory to prevent memory leaks
            Marshal.FreeHGlobal(ptr);
        }
    }
}
