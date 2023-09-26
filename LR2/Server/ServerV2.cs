using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using WebTecLr2_Server;
using static System.Runtime.InteropServices.JavaScript.JSType;

public static class ServerV2
{
    private static Logger logger;
    private static Socket socket;
    private static Thread listenThread;

    public static async Task Run()
    {
        logger = new Logger("server.log");
        IPEndPoint ipPoint = new IPEndPoint(IPAddress.Any, 8888);
        socket = new Socket(
            AddressFamily.InterNetwork,
            SocketType.Stream,
            ProtocolType.Tcp
        );
        socket.Bind(ipPoint);
        socket.Listen();
        logger.Log($"Сервер запущен по адресу {ipPoint}");
        while (true)
        {
            var client = await socket.AcceptAsync();
            var thread = new Thread(() => HandleClientAsync(client));
            thread.Start();
        }

    }

    private static async Task HandleClientAsync(Socket client)
    {
        while (true)
        {
            Thread.Sleep(1000);
            byte[] data = new byte[1024];
            var amount = await client.ReceiveAsync(data);
            if (amount > 0)
            {
                var thread = new Thread(() => HandleRequestAsync(client, data));
                thread.Start();
            } 
            else
            {
                logger.Log($"Соединение закрыто {client.RemoteEndPoint}");
                break;
            }
        }
    }

    private static async Task HandleRequestAsync(Socket client, byte[] data)
    {
        var str = Encoding.ASCII.GetString(data.AsSpan().TrimEnd((byte)0));
        logger.Log($"Получен запрос от клиента {client.RemoteEndPoint}. {str}");
        var response = Encoding.ASCII.GetBytes(str.Reverse().ToArray());
        Thread.Sleep(1500);
        client.Send(response);
        logger.Log($"Обработан запрос от клиента {client.RemoteEndPoint}");
    }

}