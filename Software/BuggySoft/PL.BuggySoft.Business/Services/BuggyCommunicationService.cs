using System;
using System.Linq;
using PL.BuggySoft.Infrastructure.Models.Messages;
using PL.BuggySoft.Infrastructure.Services;
using PL.Common.Socket;
using PL.Logger;

namespace PL.BuggySoft.Business.Services
{
	/// <summary>Service that takes care of communicating with the buggy.
	/// </summary>
	public class BuggyCommunicationService : IBuggyCommunicationService
	{
		#region Definitions

		private readonly ISender mSender;
		private readonly ILogFile mComLogFile;

		#endregion Definitions

		#region Constructor(s)

		/// <summary>Initializes a new instance of the <see cref="BuggyCommunicationService"/> class.
		/// </summary>
		/// <param name="sender">The sender.</param>
		/// <param name="comLogFile">The COM log file.</param>
		public BuggyCommunicationService(ISender sender, ILogFile comLogFile)
		{
			mSender = sender;
			mSender.OnConnect += SenderOnOnConnect;
			mSender.OnDataReceived += SenderOnOnDataReceived;
			mSender.OnDisconnect += SenderOnOnDisconnect;

			mComLogFile = comLogFile;
		}

		#endregion Constructor(s)

		#region Sender events

		private void SenderOnOnDisconnect(object sender, EventArgs eventArgs)
		{
			mComLogFile?.Info("Connected.");
		}

		private void SenderOnOnConnect(object sender, EventArgs eventArgs)
		{
			mComLogFile?.Info("Disconnected.");
		}

		private void SenderOnOnDataReceived(object sender, SocketDataReceivedEventArgs socketDataReceivedEventArgs)
		{
			// Convert the string containing Hex characters to a byte array.
			var rawMessage = Enumerable.Range(0, socketDataReceivedEventArgs.Data.Length)
				.Where(x => x % 2 == 0)
				.Select(x => Convert.ToByte(socketDataReceivedEventArgs.Data.Substring(x, 2), 16))
				.ToArray();

			var message = BuggyMessageFactory.CreateWrapperForRawMessage(rawMessage);

			if (message != null)
			{
				mComLogFile?.Info($"< {message}");
			}
			else
			{
				mComLogFile?.Error($"Unknown message received: ({socketDataReceivedEventArgs.Data})");
			}
		}

		#endregion Sender events

		#region Public methods

		/// <summary>Start attempting to connect to the Buggy.</summary>
		public void Connect()
		{
			mSender?.Start();
		}

		#endregion Public methods
	}
}