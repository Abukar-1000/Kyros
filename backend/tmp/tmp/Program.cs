using System;
using System.IO.Pipes;
using System.Runtime.InteropServices;
using Process.Models;

class Program
{
    static void Main()
    {
        Console.WriteLine("Connecting to C++ Pipe Server...");
        using var pipeClient = new NamedPipeClientStream(".", "ProcessPipe", PipeDirection.InOut);
        pipeClient.Connect();
        Console.WriteLine("Connected!");

        // 1. Calculate the exact expected size of the struct (Should be exactly 260)
        int expectedSize = Marshal.SizeOf<ProcessInfo>();
        byte[] buffer = new byte[expectedSize];

        Console.WriteLine($"Expected struct size: {expectedSize} bytes");

        // 2. Read the binary stream until the buffer is completely filled
        int totalBytesRead = 0;
        while (totalBytesRead < expectedSize)
        {
            int read = pipeClient.Read(buffer, totalBytesRead, expectedSize - totalBytesRead);
            if (read == 0) 
            {
                Console.WriteLine("Pipe disconnected prematurely.");
                return;
            }
            totalBytesRead += read;
            Console.WriteLine($"Total bytes read: {totalBytesRead} of {expectedSize} bytes");
        }

                // 3. Destructure safely using Unmanaged Marshalling (Handles strings correctly)
        IntPtr ptr = Marshal.AllocHGlobal(expectedSize);
        try
        {
            // Copy the 260 bytes from the managed array into unmanaged memory
            Marshal.Copy(buffer, 0, ptr, expectedSize);
            
            // Reconstruct the unmanaged memory layout into your C# struct
            ProcessInfo receivedData = (ProcessInfo)Marshal.PtrToStructure(ptr, typeof(ProcessInfo))!;

            // 4. Output the validated data
            Console.WriteLine("\n--- Data Destructured Successfully ---");
            Console.WriteLine($"Process ID:   {receivedData.ProcessId}");
            Console.WriteLine($"Process Name: {receivedData.ProcessName}");
        }
        finally
        {
            // Always free the allocated unmanaged memory block to prevent memory leaks
            Marshal.FreeHGlobal(ptr);
        }

        // 1. Create your response data object
        ProcessInfo responseData = new ProcessInfo
        {
            ProcessId = 9999,
            ProcessName = "CsharpResponse.exe"
        };

        // 2. Allocate an unmanaged buffer to hold the struct bytes
        int size = Marshal.SizeOf<ProcessInfo>(); // 260 bytes
        byte[] sendBuffer = new byte[size];
        ptr = Marshal.AllocHGlobal(size);

        try
        {
            // Copy the C# struct data into the unmanaged pointer
            Marshal.StructureToPtr(responseData, ptr, false);
            
            // Copy from unmanaged memory into our managed byte array
            Marshal.Copy(ptr, sendBuffer, 0, size);
            
            // 3. Write the 260 bytes directly to the C++ server pipe
            Console.WriteLine("Sending response struct back to C++...");
            pipeClient.Write(sendBuffer, 0, size);
            pipeClient.Flush(); // Ensure the data leaves the C# buffer immediately
            Console.WriteLine("Response sent!");
        }
        finally
        {
            Marshal.FreeHGlobal(ptr);
        }
    }
}
