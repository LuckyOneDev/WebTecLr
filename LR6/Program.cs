// See https://aka.ms/new-console-template for more information
using MailKit.Net.Pop3;
using MailKit.Net.Smtp;
using MimeKit;

// Пункт 1
const string email = "mokshinin@mail.ru";
const string pass = "pf4yRJZFvxd8yKCQQd8x";

using (var smtpClient = new SmtpClient())
{
    smtpClient.Connect("smtp.mail.ru", 465, true);
    smtpClient.Authenticate(email, pass);

    var mailMessage = new MimeMessage();
    mailMessage.From.Add(new MailboxAddress(email, email));
    mailMessage.Sender = new MailboxAddress(email, email);

    mailMessage.To.Add(new MailboxAddress(email, email));
    mailMessage.Subject = "Лабораторная работа 6. Почтовый сервер";
    var body = new BodyBuilder();
    body.HtmlBody = "Прислал Мокшин Иван Николаевич М3О-409Б-20 на <br> Альтернативный ящик Мокшин Иван Николаевич М3О-409Б-20 <br> Время: " + DateTime.Now;
    mailMessage.Body = body.ToMessageBody();
    smtpClient.Send(mailMessage);
    Console.WriteLine("Письмо отправлено");
}

Thread.Sleep(1000);

// Пункт 2  
using (var client = new Pop3Client())
{
    client.Connect("pop.mail.ru", 995, true);
    client.Authenticate(email, pass);

    Console.WriteLine("Количество сообщений: " + client.Count);
    for (int i = client.Count - 1; i > client.Count - 6; i--)
    {
        var message = client.GetMessage(i);
        Console.WriteLine("Тема сообщения: {0}", message.Subject);
    }

    for (int i = client.Count - 1; i > 0 ; i--)
    {
        var message = client.GetMessage(client.Count - 1);
        if (message.From.First().Name == email)
        {
            Console.WriteLine("Сообщение от одногруппника:");
            Console.WriteLine(message.TextBody);
            return;
        }
    }
}
