using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using WebTecLr2_Server;

class ServerV1
{
    public static void Run()
    {
        var logger = new Logger("server.log");

        IPEndPoint ipPoint = new IPEndPoint(IPAddress.Any, 8888);
        using Socket socket = new Socket(
            AddressFamily.InterNetwork,
            SocketType.Stream,
            ProtocolType.Tcp
        );
        socket.Bind(ipPoint);
        socket.Listen();
        logger.Log($"Сервер запущен по адресу {ipPoint}");

        while (true)
        {
            logger.Log("Ожидание подключения");
            using Socket client = socket.Accept();
            logger.Log($"Подключён клиент: {client.RemoteEndPoint}");

            while (true)
            {
                Thread.Sleep(1000);
                byte[] b = new byte[1024];
                var amount = client.Receive(b);
                if (amount > 0)
                {
                    var str = Encoding.ASCII.GetString(b.AsSpan().TrimEnd((byte)0));
                    logger.Log($"Получен запрос от клиента {client.RemoteEndPoint}. {str}");
                    var response = Encoding.ASCII.GetBytes(str.Reverse().ToArray());
                    Thread.Sleep(1500);
                    client.Send(response);
                    logger.Log($"Обработан запрос от клиента {client.RemoteEndPoint}");
                } else
                {
                    logger.Log($"Соединение закрыто {client.RemoteEndPoint}");
                    break;
                }
            }
        }
    }
}
