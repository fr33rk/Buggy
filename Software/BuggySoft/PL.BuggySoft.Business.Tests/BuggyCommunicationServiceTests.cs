using NSubstitute;
using NUnit.Framework;
using NUnit.Framework.Internal;
using PL.BuggySoft.Business.Services;
using PL.BuggySoft.Infrastructure.Models.Messages;
using PL.Common.Socket;
using PL.Logger;

namespace PL.BuggySoft.Business.Tests
{
	[TestFixture]
	public class BuggyCommunicationServiceTests
	{
		public class TestableBuggyCommunicationService : BuggyCommunicationService
		{
			private ISender mClient;

			public TestableBuggyCommunicationService(ISender stubClient, ILogFile logFile)
				: base(logFile)
			{
				mClient = stubClient;
			}


			protected override ISender CreateSender(string ip, int port)
			{
				return mClient;				
			}
		}

		[Test]
		public void ComService_MessageReceived_WritteInLog()
		{
			// Arrange
			var stubClient = Substitute.For<ISender>();
			var mockLogFile = Substitute.For<ILogFile>();
			var unitUnderTest = new TestableBuggyCommunicationService(stubClient, mockLogFile);
			var expectedMessage = new VersionMessageWrapper(new byte[]
				{0x06, 0x00, 0x15, 0x07, 0x01, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
			var expectedLogLine = $"< {expectedMessage}";

			unitUnderTest.Connect("127.0.0.1", 6000);

			// Act
			stubClient.OnDataReceived += Raise.EventWith(new object(),
				new SocketDataReceivedEventArgs("060015070102030000000000000000"));

			// Assert.
			mockLogFile.Received(1).Info(expectedLogLine);
		}
	}
}