using System;
using System.IO.Pipes;
using System.Runtime.InteropServices;
using System.Security.Principal;
using Process.Models;

class Program
{
    static void Main()
    {
        Console.WriteLine("Connecting to C++ Pipe Server...");
        using var pipeClient = new NamedPipeClientStream(
            ".", 
            "ProcessPipe",
            PipeDirection.In
        );

        pipeClient.Connect();
        Console.WriteLine("Connected!");

        List<ProcessInfo> receivedProcesses = new List<ProcessInfo>();
        while (pipeClient.IsConnected)
        {
            //
            ProcessInfo? processInfo = GetObj(pipeClient);
            if (processInfo == null)
            {
                continue;
            }

            Console.WriteLine("--------------------------------------");
            Console.WriteLine($"[Received] Process ID:   {processInfo.Value.ProcessId}");
            Console.WriteLine($"[Received] Process Name: {processInfo.Value.ProcessName}");
            Console.WriteLine($"[Received] Is Running:  {processInfo.Value.IsRunning}");
            receivedProcesses.Add(processInfo.Value);
        }
        Console.WriteLine($"Total processes received: {receivedProcesses.Count}");
    }

    static ProcessInfo? GetObj(NamedPipeClientStream pipeClient)
    {
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
                return null;
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

            return receivedData;
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error during struct reconstruction: {ex.Message}");
            return null;
        }
        finally
        {
            // Always free the allocated unmanaged memory block to prevent memory leaks
            Marshal.FreeHGlobal(ptr);
        }
    }
}
