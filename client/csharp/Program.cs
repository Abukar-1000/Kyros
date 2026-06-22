using System.Runtime.InteropServices;
using System.IO.Pipes;
using System;

[StructLayout(LayoutKind.Sequential, Pack = 1)]
public unsafe struct KillFrame
{
    public ushort id;
    public int processId;
    public fixed byte processName[256]; 
}

class Program
{
    static unsafe void Main()
    {
        string pipeName = "GatewayPipe";

        // Connect as an Outward stream matching your C++ duplex layout setup
        using var pipeClient = new NamedPipeClientStream(".", pipeName, PipeDirection.InOut);
        
        Console.WriteLine("Connecting to pipe...");
        try
        {
            pipeClient.Connect(5000);
        }
        catch (TimeoutException)
        {
            Console.WriteLine("Connection timed out.");
            return;
        }

        using var writer = new PipeWriter(pipeClient);

        var data = new KillFrame();
        data.id = 42;
        data.processId = 12345;

        string name = "Discord";
        int bytesToWrite = Math.Min(name.Length, 255);
        
        System.Text.Encoding.ASCII.GetBytes(
            name.AsSpan(0, bytesToWrite), 
            new Span<byte>(data.processName, 256)
        );

        bool result = writer.SendStruct(data);
        Console.WriteLine($"Send result: {result}");
    }
}