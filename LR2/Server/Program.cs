internal class Program
{
    private static async Task Main(string[] args)
    {
        // V1
        //ServerV1.Run();

        // V2
        await ServerV2.Run();
    }
} 